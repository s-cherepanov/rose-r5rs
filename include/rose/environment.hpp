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

class environment {
public:
    typedef
        std::map<ast_variable, gc::handle<value> >
        variable_map;

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
        variable_map::const_iterator it = variables_.find(var);
        if (variables_.end() != it) {
            throw std::runtime_error("definition duplicated");
        }

        variables_[var] = val;
    }

    void assign(ast_variable const& var, gc::handle<value> val) {
        variable_map::iterator it = variables_.find(var);
        if (variables_.end() == it) {
            throw std::runtime_error("undefined variable");
        }

        it->second = val;
    }

    gc::handle<value> lookup(ast_variable const& var) const {
        variable_map::const_iterator it = variables_.find(var);
        if (variables_.end() != it) {
            return it->second;
        }

        return !!parent_ ?
            parent_->lookup(var) : gc::handle<value>();
    }

private:
    environment_ptr parent_;
    variable_map variables_;

};  //  class environment

}   //  namespace rose

#endif  //  __ROSE_ENVIRONMENT_HPP__
