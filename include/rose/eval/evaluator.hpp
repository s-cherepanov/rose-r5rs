#ifndef __ROSE_EVAL_EVALUATOR_HPP__
#define __ROSE_EVAL_EVALUATOR_HPP__

#include "rose/ast/program.hpp"
#include "rose/environment.hpp"
#include "rose/gc/handle.hpp"
#include "rose/value.hpp"

#include <boost/bind.hpp>
#include <boost/variant.hpp>

namespace rose {

inline gc::handle<value> nil() {
    static gc::handle<value> n;
    return n;
}

template<typename Ast>
gc::handle<value> eval(Ast const& ast, environment_ptr env);

template<>
gc::handle<value> eval<ast_expression>(
        ast_expression const& ast, environment_ptr env);

template<>
gc::handle<value> eval<ast_command_or_definition>(
        ast_command_or_definition const& ast, environment_ptr env);

template<>
gc::handle<value> eval<ast_datum>(
        ast_datum const& ast, environment_ptr env);

struct evaluator_base :
    boost::static_visitor<gc::handle<value> >
{
    typedef gc::handle<value> result_type;

    environment_ptr env;

    evaluator_base(environment_ptr env) :
        env(env)
    {}

};  //  struct evaluator_base

struct datum_evaluator : evaluator_base {
    datum_evaluator(environment_ptr env) :
        evaluator_base(env)
    {}

    result_type operator()(ast_list const& ast) const {
        return nil();
    }

    result_type operator()(ast_vector const& ast) const {
        using namespace boost;

        vector result;
        std::transform(
                ast.begin(),
                ast.end(),
                std::back_inserter(result),
                bind(&eval<ast_datum>, _1, env));

        return result_type(new gc::object<value>(vector(result)));
    }

    template<typename Ast>
    result_type operator()(Ast const& ast) const {
        return result_type(new gc::object<value>(value(ast)));
    }

};  //  struct datum_evaluator

template<>
gc::handle<value> eval<ast_datum>(
        ast_datum const& ast, environment_ptr env)
{
    return boost::apply_visitor(datum_evaluator(env), ast);
}

struct expression_evaluator : evaluator_base {
    expression_evaluator(environment_ptr env) :
        evaluator_base(env)
    {}

    template<typename Ast>
    result_type operator()(Ast const& ast) const {
        return result_type(new gc::object<value>(value(ast)));
    }

    result_type operator()(ast_variable const& ast) const {
        result_type val = env->lookup(ast);
        if (!val) {
            throw std::runtime_error("undefined variable");
        }

        return val;
    }

    result_type operator()(ast_quotation const& ast) const {
        return eval(ast.quoted, env);
    }

    result_type operator()(ast_lambda_expression const& ast) const {
        return nil();
    }

    result_type operator()(ast_procedure_call const& ast) const {
        return nil();
    }

    result_type operator()(ast_conditional const& ast) const {
        result_type test = eval(ast.test, env);

        if (is_true(*test)) {
            return eval(ast.consequent, env);
        }

        if (!!ast.alternate) {
            return eval(*ast.alternate, env);
        }

        return nil();
    }

    result_type operator()(ast_assignment const& ast) const {
        env->assign(ast.variable, eval(ast.expression, env));
        return nil();
    }

    bool is_true(value const& val) const {
        bool const* ptr = boost::get<bool>(&val);
        return !ptr || (*ptr == true);
    }

};  //  struct expression_evaluator

template<>
gc::handle<value> eval<ast_expression>(
        ast_expression const& ast, environment_ptr env)
{
    return boost::apply_visitor(expression_evaluator(env), ast);
}

struct command_or_definition_evaluator : evaluator_base {
    command_or_definition_evaluator(environment_ptr env) :
        evaluator_base(env)
    {}

    result_type operator()(ast_definition const& ast) const {
        env->define(ast.variable, eval(ast.expression, env));
        return nil();
    }

    result_type operator()(ast_expression const& ast) const {
        return eval(ast, env);
    }

};  //  struct command_or_definition_evaluator

template<>
gc::handle<value> eval<ast_command_or_definition>(
        ast_command_or_definition const& ast, environment_ptr env)
{
    return boost::apply_visitor(command_or_definition_evaluator(env), ast);
}

}   //  namespace rose

#endif  //  __ROSE_EVAL_EVALUATOR_HPP__
