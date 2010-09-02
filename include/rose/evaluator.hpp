#ifndef __ROSE_EVAL_EVALUATOR_HPP__
#define __ROSE_EVAL_EVALUATOR_HPP__

#include "rose/ast.hpp"
#include "rose/environment.hpp"
#include "rose/gc/handle.hpp"
#include "rose/value.hpp"

#include <boost/variant.hpp>

namespace rose {

template<typename Ast>
gc::handle<value> eval(Ast const& ast, environment_ptr env);

template<>
gc::handle<value> eval<ast_program>(
        ast_program const& ast, environment_ptr env);

struct evaluator_base :
    boost::static_visitor<gc::handle<value> >
{
    environment_ptr env;

    evaluator_base(environment_ptr env) :
        env(env)
    {}

};  //  struct evaluator_base

}   //  namespace rose

#endif  //  __ROSE_EVAL_EVALUATOR_HPP__
