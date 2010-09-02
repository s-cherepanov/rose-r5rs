#ifndef __ROSE_EVAL_HPP__
#define __ROSE_EVAL_HPP__

#include "rose/ast.hpp"
#include "rose/environment.hpp"
#include "rose/gc/handle.hpp"
#include "rose/value.hpp"

#include <boost/variant.hpp>

namespace rose {

struct eval_base : boost::static_visitor<gc::handle<value> > {
    environment_ptr env;

    eval_base(environment_ptr env) :
        env(env)
    {}

};  //  struct eval_base 

template<typename Ast>
struct eval_visitor;

template<typename Ast>
gc::handle<value> eval(Ast const& ast, environment_ptr env) {
    return boost::apply_visitor(eval_visitor<Ast>(env), ast);
}

template<>
gc::handle<value> eval(ast_program const& ast, environment_ptr env);

template<>
gc::handle<value> eval(ast_definition const& ast, environment_ptr env);

}   //  namespace rose

#endif  //  __ROSE_EVAL_HPP__
