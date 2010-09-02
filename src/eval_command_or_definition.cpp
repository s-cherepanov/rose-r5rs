#include "rose/detail/eval_command_or_definition.hpp"

namespace rose {

template<>
gc::handle<value> eval(ast_definition const& ast, environment_ptr env) {
    env->define(ast.variable, eval(ast.expression, env));
    return nil();
}

}   //  namespace rose
