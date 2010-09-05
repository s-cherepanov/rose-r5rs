#include "rose/base.hpp"
#include "rose/environment.hpp"
#include "rose/exception.hpp"

namespace rose {

DEFINE_NATIVE_PROCEDURE(np_add) {
    int result = 0;

    if (is_nil(rest)) {
        return make_value(result);
    }

    gc::handle<value> next = rest;
    while (!is_nil(next)) {
        result += ensure_handle_cast<int>(car(next));
        next = cdr(next);
    }

    return make_value(result);
}

DEFINE_NATIVE_PROCEDURE(np_minus) {
    int result = ensure_handle_cast<int>(args[0]);

    if (is_nil(rest)) {
        return make_value(-result);
    }

    gc::handle<value> next = rest;
    while (!is_nil(next)) {
        result -= ensure_handle_cast<int>(car(next));
        next = cdr(next);
    }

    return make_value(result);
}

DEFINE_NATIVE_PROCEDURE(np_multiply) {
    int result = 1;

    if (is_nil(rest)) {
        return make_value(result);
    }

    gc::handle<value> next = rest;
    while (!is_nil(next)) {
        result *= ensure_handle_cast<int>(car(next));
        next = cdr(next);
    }

    return make_value(result);
}

DEFINE_NATIVE_PROCEDURE(np_divide) {
    int result = ensure_handle_cast<int>(args[0]);

    if (is_nil(rest)) {
        return make_value(1 / result);
    }

    gc::handle<value> next = rest;
    while (!is_nil(next)) {
        result /= ensure_handle_cast<int>(car(next));
        next = cdr(next);
    }

    return make_value(result);
}

DEFINE_NATIVE_PROCEDURE(np_eq) {
    int lhs = ensure_handle_cast<int>(args[0]);
    int rhs = ensure_handle_cast<int>(args[1]);
    return make_value(lhs == rhs);
}

DEFINE_NATIVE_PROCEDURE(np_less) {
    int lhs = ensure_handle_cast<int>(args[0]);
    int rhs = ensure_handle_cast<int>(args[1]);
    return make_value(lhs < rhs);
}

DEFINE_NATIVE_PROCEDURE(np_leq) {
    int lhs = ensure_handle_cast<int>(args[0]);
    int rhs = ensure_handle_cast<int>(args[1]);
    return make_value(lhs <= rhs);
}

DEFINE_NATIVE_PROCEDURE(np_gr) {
    int lhs = ensure_handle_cast<int>(args[0]);
    int rhs = ensure_handle_cast<int>(args[1]);
    return make_value(lhs > rhs);
}

DEFINE_NATIVE_PROCEDURE(np_geq) {
    int lhs = ensure_handle_cast<int>(args[0]);
    int rhs = ensure_handle_cast<int>(args[1]);

    return make_value(lhs >= rhs);
}

DEFINE_NATIVE_PROCEDURE(np_pair_p) {
    return !args[0] ?
        make_value(false) :
        make_value(!!handle_cast<rs_pair>(&args[0]));
}

DEFINE_NATIVE_PROCEDURE(np_vector_p) {
    return !args[0] ?
        make_value(false) :
        make_value(!!handle_cast<rs_vector>(&args[0]));
}

DEFINE_NATIVE_PROCEDURE(np_string_p) {
    return !args[0] ?
        make_value(false) :
        make_value(!!handle_cast<rs_string>(&args[0]));
}

DEFINE_NATIVE_PROCEDURE(np_symbol_p) {
    return !args[0] ?
        make_value(false) :
        make_value(!!handle_cast<rs_symbol>(&args[0]));
}

DEFINE_NATIVE_PROCEDURE(np_procedure_p) {
    return !args[0] ?
        make_value(false) :
        make_value(
                handle_cast<rs_procedure>(&args[0]) ||
                handle_cast<rs_native_procedure>(&args[0]));
}

DEFINE_NATIVE_PROCEDURE(np_car) {
    return car(args[0]);
}

DEFINE_NATIVE_PROCEDURE(np_cdr) {
    return cdr(args[0]);
}

DEFINE_NATIVE_PROCEDURE(np_set_car_x) {
    set_car(args[0], args[1]);
    return none();
}

DEFINE_NATIVE_PROCEDURE(np_set_cdr_x) {
    set_cdr(args[0], args[1]);
    return none();
}

DEFINE_NATIVE_PROCEDURE(np_list) {
    return rest;
}

DEFINE_NATIVE_PROCEDURE(np_vector) {
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

DEFINE_NATIVE_PROCEDURE(np_display) {
    std::cout << args[0];
    return none();
}

DEFINE_NATIVE_PROCEDURE(np_display_line) {
    std::cout << args[0] << std::endl;
    return none();
}

environment_ptr init_env(environment_ptr env) {
    if (!env) {
        env.reset(new environment);
    }

    env->define()
        ("+",            0, true,  np_add)
        ("-",            1, true,  np_minus)
        ("*",            0, true,  np_multiply)
        ("/",            1, true,  np_divide)
        ("=",            2, true,  np_eq)
        ("<",            2, true,  np_less)
        ("<=",           2, true,  np_leq)
        (">",            2, true,  np_gr)
        (">=",           2, true,  np_geq)
        ("pair?",        1, false, np_pair_p)
        ("vector?",      1, false, np_vector_p)
        ("string?",      1, false, np_string_p)
        ("symbol?",      1, false, np_symbol_p)
        ("procedure?",   1, false, np_procedure_p)
        ("car",          1, false, np_car)
        ("cdr",          1, false, np_cdr)
        ("set-car!",     2, false, np_set_car_x)
        ("set-cdr!",     2, false, np_set_cdr_x)
        ("list",         0, true,  np_list)
        ("vector",       0, true,  np_vector)
        ("display",      1, false, np_display)
        ("display-line", 1, false, np_display_line)
        ;

    return env;
}

}   //  namespace rose
