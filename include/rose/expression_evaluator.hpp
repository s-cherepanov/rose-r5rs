#ifndef __ROSE_EVAL_EXPRESSION_EVALUATOR_HPP__
#define __ROSE_EVAL_EXPRESSION_EVALUATOR_HPP__

#include "rose/ast.hpp"
#include "rose/environment.hpp"
#include "rose/evaluator.hpp"
#include "rose/gc/handle.hpp"
#include "rose/value.hpp"

#include <boost/variant.hpp>

namespace rose {

template<>
gc::handle<value> eval<ast_expression>(
        ast_expression const& ast, environment_ptr env);

struct expression_evaluator : evaluator_base {
    expression_evaluator(environment_ptr env);

    template<typename Ast>
    result_type operator()(Ast const& ast) const {
        return make_value(ast);
    }

    result_type operator()(ast_variable const& ast) const;

    result_type operator()(ast_quotation const& ast) const;

    result_type operator()(ast_lambda_expression const& ast) const;

    result_type operator()(ast_procedure_call const& ast) const;

    result_type operator()(ast_conditional const& ast) const;

    result_type operator()(ast_assignment const& ast) const;

private:
    bool is_true(value const& val) const;

};  //  struct expression_evaluator

}   //  namespace rose

#endif  //  __ROSE_EVAL_EXPRESSION_EVALUATOR_HPP__
