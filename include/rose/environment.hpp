#ifndef __ROSE_ENVIRONMENT_HPP__
#define __ROSE_ENVIRONMENT_HPP__

#include "rose/gc/handle.hpp"
#include "rose/value.hpp"

#include <boost/shared_ptr.hpp>

#include <map>

namespace rose {

class environment;

typedef boost::shared_ptr<environment> environment_ptr;

class environment :
    public std::map<ast_variable, gc::handle<value> >
{
    friend std::ostream& operator<<(std::ostream&, environment const&);

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

    void define(ast_variable const& var, gc::handle<value> val) {
        const_iterator it = find(var);
        if (end() != it) {
            throw std::runtime_error("definition duplicated");
        }

        (*this)[var] = val;
    }

    void assign(ast_variable const& var, gc::handle<value> val) {
        iterator it = find(var);
        if (end() == it) {
            throw std::runtime_error("undefined variable");
        }

        it->second = val;
    }

    gc::handle<value> lookup(ast_variable const& var) const {
        const_iterator it = find(var);
        if (end() != it) {
            return it->second;
        }

        return !!parent_ ?  parent_->lookup(var) : gc::handle<value>();
    }

private:
    environment_ptr parent_;

};  //  class environment

}   //  namespace rose

#endif  //  __ROSE_ENVIRONMENT_HPP__
