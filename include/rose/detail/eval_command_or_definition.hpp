#ifndef __ROSE_EVAL_COMMAND_OR_DEFINITION_EVALUATOR_HPP__
#define __ROSE_EVAL_COMMAND_OR_DEFINITION_EVALUATOR_HPP__

#include "rose/ast.hpp"
#include "rose/environment.hpp"
#include "rose/eval.hpp"
#include "rose/gc/handle.hpp"
#include "rose/value.hpp"

#include <boost/variant.hpp>

namespace rose {

template<>
struct eval_visitor<ast_command_or_definition> : eval_base {
    eval_visitor(environment_ptr env) :
        eval_base(env)
    {}

    template<typename Ast>
    result_type operator()(Ast const& ast) const {
        return eval(ast, env);
    }

};  //  struct command_or_definition_evaluator

}   //  namespace rose

#endif  //  __ROSE_EVAL_COMMAND_OR_DEFINITION_EVALUATOR_HPP__
