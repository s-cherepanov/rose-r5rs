#include "rose/primitive.hpp"
#include "rose/environment.hpp"
#include "rose/exception.hpp"

#define NATIVE_PROCEDURE(name, args, rest)\
    rose::gc::handle<value> name(rose::arguments_type const& args,\
                                 rose::gc::handle<rose::value> rest)

namespace rose {

NATIVE_PROCEDURE(np_add, args, rest) {
    int result = 0;

    if (is_nil(rest)) {
        return make_value(result);
    }

    gc::handle<value> next = rest;
    while (!is_nil(next)) {
        result += handle_cast<int>(car(next));
        next = cdr(next);
    }

    return make_value(result);
}

NATIVE_PROCEDURE(np_minus, args, rest) {
    if (args.size() < 1) {
        BOOST_THROW_EXCEPTION(
                arity_mismatch()
                << errinfo_required_arg_num(1)
                << errinfo_has_rest(true)
                << errinfo_actual_arg_num(args.size()));
    }

    int result = handle_cast<int>(args[0]);

    if (is_nil(rest)) {
        return make_value(-result);
    }

    gc::handle<value> next = rest;
    while (!is_nil(next)) {
        result -= handle_cast<int>(car(next));
        next = cdr(next);
    }

    return make_value(result);
}

NATIVE_PROCEDURE(np_multiply, args, rest) {
    int result = 1;

    if (is_nil(rest)) {
        return make_value(result);
    }

    gc::handle<value> next = rest;
    while (!is_nil(next)) {
        result *= handle_cast<int>(car(next));
        next = cdr(next);
    }

    return make_value(result);
}

NATIVE_PROCEDURE(np_divide, args, rest) {
    if (args.size() < 1) {
        BOOST_THROW_EXCEPTION(
                arity_mismatch()
                << errinfo_required_arg_num(0)
                << errinfo_has_rest(true)
                << errinfo_actual_arg_num(args.size()));
    }

    int result = handle_cast<int>(car(rest));

    if (is_nil(rest)) {
        return make_value(1 / result);
    }

    gc::handle<value> next = rest;
    while (!is_nil(next)) {
        result /= handle_cast<int>(car(next));
        next = cdr(next);
    }

    return make_value(result);
}

NATIVE_PROCEDURE(np_eq, args, rest) {
    int lhs = handle_cast<int>(args[0]);
    int rhs = handle_cast<int>(args[1]);
    return make_value(lhs == rhs);
}

NATIVE_PROCEDURE(np_less, args, rest) {
    int lhs = handle_cast<int>(args[0]);
    int rhs = handle_cast<int>(args[1]);
    return make_value(lhs < rhs);
}

NATIVE_PROCEDURE(np_leq, args, rest) {
    int lhs = handle_cast<int>(args[0]);
    int rhs = handle_cast<int>(args[1]);
    return make_value(lhs <= rhs);
}

NATIVE_PROCEDURE(np_gr, args, rest) {
    int lhs = handle_cast<int>(args[0]);
    int rhs = handle_cast<int>(args[1]);
    return make_value(lhs > rhs);
}

NATIVE_PROCEDURE(np_geq, args, rest) {
    int lhs = handle_cast<int>(args[0]);
    int rhs = handle_cast<int>(args[1]);
    return make_value(lhs >= rhs);
}

NATIVE_PROCEDURE(np_pair_p, args, rest) {
    return !args[0] ?
        make_value(false) :
        make_value(!!boost::get<rs_pair>(&(*args[0])));
}

NATIVE_PROCEDURE(np_vector_p, args, rest) {
    return !args[0] ?
        make_value(false) :
        make_value(!!boost::get<rs_vector>(&(*args[0])));
}

NATIVE_PROCEDURE(np_string_p, args, rest) {
    return !args[0] ?
        make_value(false) :
        make_value(!!boost::get<rs_string>(&(*args[0])));
}

NATIVE_PROCEDURE(np_symbol_p, args, rest) {
    return make_value(!!boost::get<rs_symbol>(&(*args[0])));
}

NATIVE_PROCEDURE(np_car, args, rest) {
    return car(args[0]);
}

NATIVE_PROCEDURE(np_cdr, args, rest) {
    return cdr(args[0]);
}

NATIVE_PROCEDURE(np_set_car_x, args, rest) {
    set_car(args[0], args[1]);
    return none();
}

NATIVE_PROCEDURE(np_set_cdr_x, args, rest) {
    set_cdr(args[0], args[1]);
    return none();
}

NATIVE_PROCEDURE(np_list, args, rest) {
    return rest;
}

NATIVE_PROCEDURE(np_vector, args, rest) {
    rs_vector result;

    if (is_nil(rest)) {
        return make_value(result);
    }

    gc::handle<value> next = rest;
    while (!is_nil(next)) {
        result.push_back(car(next));
        next = cdr(next);
    }

    return make_value(result);
}

NATIVE_PROCEDURE(np_display, args, rest) {
    std::cout << args[0];
    return none();
}

NATIVE_PROCEDURE(np_display_line, args, rest) {
    std::cout << args[0] << std::endl;
    return none();
}

environment_ptr build_initial_env() {
    environment_ptr env(new environment);

    env->define("+",        rs_native_procedure(0, true,  np_add,       env));
    env->define("-",        rs_native_procedure(1, true,  np_minus,     env));
    env->define("*",        rs_native_procedure(0, true,  np_multiply,  env));
    env->define("/",        rs_native_procedure(0, true,  np_divide,    env));
    env->define("=",        rs_native_procedure(2, true,  np_eq,        env));
    env->define("<",        rs_native_procedure(2, true,  np_less,      env));
    env->define("<=",       rs_native_procedure(2, true,  np_leq,       env));
    env->define(">",        rs_native_procedure(2, true,  np_gr,        env));
    env->define(">=",       rs_native_procedure(2, true,  np_geq,       env));
    env->define("pair?",    rs_native_procedure(1, false, np_pair_p,    env));
    env->define("vector?",  rs_native_procedure(1, false, np_vector_p,  env));
    env->define("string?",  rs_native_procedure(1, false, np_string_p,  env));
    env->define("symbol?",  rs_native_procedure(1, false, np_symbol_p,  env));
    env->define("car",      rs_native_procedure(1, false, np_car,       env));
    env->define("cdr",      rs_native_procedure(1, false, np_cdr,       env));
    env->define("set-car!", rs_native_procedure(2, false, np_set_car_x, env));
    env->define("set-cdr!", rs_native_procedure(2, false, np_set_cdr_x, env));
    env->define("list",     rs_native_procedure(0, true,  np_list,      env));
    env->define("vector",   rs_native_procedure(0, true,  np_vector,    env));
    env->define("display",  rs_native_procedure(1, false, np_display,   env));

    env->define("display-line",
            rs_native_procedure(1, false, np_display_line, env));

    return env;
}

}   //  namespace rose
