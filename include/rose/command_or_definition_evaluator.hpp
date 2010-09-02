#ifndef __ROSE_EVAL_COMMAND_OR_DEFINITION_EVALUATOR_HPP__
#define __ROSE_EVAL_COMMAND_OR_DEFINITION_EVALUATOR_HPP__

#include "rose/ast.hpp"
#include "rose/environment.hpp"
#include "rose/evaluator.hpp"
#include "rose/gc/handle.hpp"
#include "rose/value.hpp"

#include <boost/variant.hpp>

namespace rose {

template<>
gc::handle<value> eval<ast_definition>(
        ast_definition const& ast, environment_ptr env);

template<>
gc::handle<value> eval<ast_expression>(
        ast_expression const& ast, environment_ptr env);

template<>
gc::handle<value> eval<ast_command_or_definition>(
        ast_command_or_definition const& ast, environment_ptr env);

struct command_or_definition_evaluator : evaluator_base {
    command_or_definition_evaluator(environment_ptr env) :
        evaluator_base(env)
    {}

    template<typename AstType>
    result_type operator()(AstType const& ast) const {
        return eval(ast, env);
    }

};  //  struct command_or_definition_evaluator

}   //  namespace rose

#endif  //  __ROSE_EVAL_COMMAND_OR_DEFINITION_EVALUATOR_HPP__
