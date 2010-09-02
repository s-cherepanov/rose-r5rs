#include "rose/command_or_definition_evaluator.hpp"

namespace rose {

template<>
gc::handle<value> eval<ast_definition>(
        ast_definition const& ast, environment_ptr env)
{
    env->define(ast.variable, eval(ast.expression, env));
    return nil();
}

template<>
gc::handle<value> eval<ast_command_or_definition>(
        ast_command_or_definition const& ast, environment_ptr env)
{
    return boost::apply_visitor(command_or_definition_evaluator(env), ast);
}

}   //  namespace rose
