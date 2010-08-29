#include "rose/eval/primitive.hpp"
#include "rose/environment.hpp"

namespace rose {

gc::handle<value> add(arguments_type const& args, gc::handle<value> rest) {
    return make_value(1);
}

gc::handle<value> minus(arguments_type const& args, gc::handle<value> rest) {
    return make_value(1);
}

gc::handle<value> multiply(arguments_type const& args, gc::handle<value> rest) {
    return make_value(1);
}

gc::handle<value> devide(arguments_type const& args, gc::handle<value> rest) {
    return make_value(1);
}

environment_ptr build_initial_env() {
    environment_ptr env(new environment);

    env->define(ast_variable("+"), make_value(native_procedure(0, true, add, env)));
    env->define(ast_variable("-"), make_value(native_procedure(0, true, minus, env)));
    env->define(ast_variable("*"), make_value(native_procedure(0, true, multiply, env)));
    env->define(ast_variable("/"), make_value(native_procedure(0, true, devide, env)));

    return env;
}

}   //  namespace rose
