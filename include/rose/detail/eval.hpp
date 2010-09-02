#ifndef __ROSE_DETAIL_EVAL_HPP__
#define __ROSE_DETAIL_EVAL_HPP__

#include "rose/ast.hpp"
#include "rose/gc/handle.hpp"
#include "rose/value.hpp"

#include <boost/shared_ptr.hpp>
#include <boost/variant.hpp>

namespace rose {

class environment;
typedef boost::shared_ptr<environment> environment_ptr;

namespace detail {

struct eval_base : boost::static_visitor<gc::handle<value> > {
    environment_ptr env;

    eval_base(environment_ptr env) :
        env(env)
    {}

};  //  struct eval_base 

template<typename Ast>
struct eval_visitor;

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

template<>
struct eval_visitor<ast_expression> : eval_base {
    eval_visitor(environment_ptr env);

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

};  //  struct eval_visitor<ast_expression>

template<>
struct eval_visitor<ast_datum> : eval_base {
    eval_visitor(environment_ptr env);

    result_type operator()(ast_list const& ast) const;

    result_type operator()(ast_vector const& ast) const;

    template<typename Ast>
    result_type operator()(Ast const& ast) const {
        return make_value(ast);
    }

};  //  struct eval_visitor<ast_datum>

template<typename Ast>
gc::handle<value> eval(Ast const& ast, environment_ptr env) {
    return boost::apply_visitor(eval_visitor<Ast>(env), ast);
}

template<>
gc::handle<value> eval(ast_program const& ast, environment_ptr env);

template<>
gc::handle<value> eval(ast_definition const& ast, environment_ptr env);

}   //  namespace detail
}   //  namespace rose

#endif  //  __ROSE_DETAIL_EVAL_HPP__
