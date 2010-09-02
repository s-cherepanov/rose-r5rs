#include "rose/detail/eval.hpp"
#include "rose/environment.hpp"

namespace rose {
namespace detail {

template<>
gc::handle<value> eval(ast_definition const& ast, environment_ptr env) {
    env->define(ast.variable, eval(ast.expression, env));
    return none();
}

}   //  namespace detail
}   //  namespace rose
