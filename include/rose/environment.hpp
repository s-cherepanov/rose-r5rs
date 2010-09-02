#ifndef __ROSE_ENVIRONMENT_HPP__
#define __ROSE_ENVIRONMENT_HPP__

#include "rose/gc/handle.hpp"
#include "rose/value.hpp"

#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>

#include <map>

namespace rose {

class environment;

typedef boost::shared_ptr<environment> environment_ptr;

class environment :
    public std::map<ast_variable, gc::handle<value> >
{
    friend std::ostream& operator<<(std::ostream&, environment const&);

private:
    typedef
        std::map<ast_variable, gc::handle<value> >
        base_type;

public:
    environment(environment_ptr parent = environment_ptr()) :
        parent_(parent)
    {}

    environment_ptr parent() const {
        return parent_;
    }

    void parent(environment_ptr parent) {
        parent_ = parent;
    }

    template<typename ValueType>
    void define(ast_variable const& var, ValueType const& val) {
        const_iterator it = find(var);
        if (end() != it) {
            throw std::runtime_error("definition duplicated");
        }

        (*this)[var] = val;
    }

    template<typename ValueType>
    void define(std::string const& var, ValueType const& val) {
        define(ast_variable(var), make_value(val));
    }

    void assign(ast_variable const& var, gc::handle<value> val) {
        iterator it = find(var);
        if (end() == it) {
            throw std::runtime_error("undefined variable");
        }

        it->second = val;
    }

    template<typename ValueType>
    void assign(std::string const& var, ValueType const& val) {
        assign(ast_variable(var), make_value(val));
    }

    gc::handle<value> lookup(ast_variable const& var) const {
        const_iterator it = find(var);
        if (end() != it) {
            return it->second;
        }

        return !!parent() ? parent()->lookup(var) : none();
    }

    gc::handle<value> lookup(std::string const& var) const {
        return lookup(ast_variable(var));
    }

private:
    environment_ptr parent_;

};  //  class environment

inline std::ostream& operator<<(std::ostream& out, environment const& env) {
    if (env.empty()) {
        return out << "()";
    }

    out << '(';

    environment::const_iterator it = env.begin();
    out << boost::format("(%1% %2%)") % it->first % it->second;

    while (env.end() != ++it) {
        out << boost::format(" (%1% %2%)") % it->first % it->second;
    }

    return out << ')';
}

}   //  namespace rose

#endif  //  __ROSE_ENVIRONMENT_HPP__
