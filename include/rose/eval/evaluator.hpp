#ifndef __ROSE_EVAL_EVALUATOR_HPP__
#define __ROSE_EVAL_EVALUATOR_HPP__

#include "rose/ast/program.hpp"
#include "rose/environment.hpp"
#include "rose/gc/handle.hpp"
#include "rose/value.hpp"

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
        ast_expression const& ast,
        environment_ptr env);

template<>
gc::handle<value> eval<ast_command_or_definition>(
        ast_command_or_definition const& ast,
        environment_ptr env);

struct evaluator_base :
    boost::static_visitor<gc::handle<value> >
{
    environment_ptr env;

    evaluator_base(environment_ptr env) :
        env(env)
    {}

};  //  struct evaluator_base

struct expression_evaluator : evaluator_base {
    expression_evaluator(environment_ptr env) :
        evaluator_base(env)
    {}

    gc::handle<value> operator()(int ast) const {
        return gc::handle<value>(new gc::object<value>(value(ast)));
    }

    gc::handle<value> operator()(bool ast) const {
        return gc::handle<value>(new gc::object<value>(value(ast)));
    }

    gc::handle<value> operator()(char ast) const {
        return gc::handle<value>(new gc::object<value>(value(ast)));
    }

    gc::handle<value> operator()(ast_string const& ast) const {
        return gc::handle<value>(new gc::object<value>(value(ast)));
    }

    gc::handle<value> operator()(ast_variable const& ast) const {
        gc::handle<value> val = env->lookup(ast);
        if (!val) {
            throw std::runtime_error("undefined variable");
        }

        return val;
    }

    gc::handle<value> operator()(ast_conditional const& ast) const {
        gc::handle<value> test = eval(ast.test, env);

        if (is_true(*test)) {
            return eval(ast.consequent, env);
        }

        if (!!ast.alternate) {
            return eval(*ast.alternate, env);
        }

        return nil();
    }

    gc::handle<value> operator()(ast_assignment const& ast) const {
        env->assign(ast.variable, eval(ast.expression, env));
        return nil();
    }

    bool is_true(value const& val) const {
        bool const* ptr = boost::get<bool>(&val);
        return !ptr || (*ptr == true);
    }

    template<typename Expression>
    gc::handle<value> operator()(Expression ast) const {
        return nil();
    }

};  //  struct expression_evaluator

template<>
gc::handle<value> eval<ast_expression>(
        ast_expression const& ast,
        environment_ptr env)
{
    return boost::apply_visitor(expression_evaluator(env), ast);
}

struct command_or_definition_evaluator : evaluator_base {
    command_or_definition_evaluator(environment_ptr env) :
        evaluator_base(env)
    {}

    gc::handle<value> operator()(ast_definition const& ast) const {
        env->define(ast.variable, eval(ast.expression, env));
        return nil();
    }

    gc::handle<value> operator()(ast_expression const& ast) const {
        return eval(ast, env);
    }

};  //  struct command_or_definition_evaluator

template<>
gc::handle<value> eval<ast_command_or_definition>(
        ast_command_or_definition const& ast,
        environment_ptr env)
{
    return boost::apply_visitor(command_or_definition_evaluator(env), ast);
}

}   //  namespace rose

#endif  //  __ROSE_EVAL_EVALUATOR_HPP__
