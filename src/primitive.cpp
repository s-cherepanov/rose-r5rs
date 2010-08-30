#include "rose/eval/primitive.hpp"
#include "rose/environment.hpp"

#define DEFINE_PRIMITIVE(name, args, rest)\
    rose::gc::handle<value> name(rose::arguments_type const& args,\
                                 rose::gc::handle<rose::value> rest)

namespace rose {

DEFINE_PRIMITIVE(rs_add, args, rest) {
    int result = 0;

    if (!rest) {
        return make_value(result);
    }

    gc::handle<value> next = rest;
    while (!!next) {
        result += handle_cast<int>(car(next));
        next = cdr(next);
    }

    return make_value(result);
}

DEFINE_PRIMITIVE(rs_minus, args, rest) {
    if (!rest) {
        throw std::runtime_error("wrong number of arguments");
    }

    int result = handle_cast<int>(car(rest));

    if (!cdr(rest)) {
        return make_value(-result);
    }

    gc::handle<value> next = cdr(rest);
    while (!!next) {
        result -= handle_cast<int>(car(next));
        next = cdr(next);
    }

    return make_value(result);
}

DEFINE_PRIMITIVE(rs_multiply, args, rest) {
    int result = 1;

    if (!rest) {
        return make_value(result);
    }

    gc::handle<value> next = rest;
    while (!!next) {
        result *= handle_cast<int>(car(next));
        next = cdr(next);
    }

    return make_value(result);
}

DEFINE_PRIMITIVE(rs_divide, args, rest) {
    if (!rest) {
        throw std::runtime_error("wrong number of arguments");
    }

    int result = handle_cast<int>(car(rest));

    if (!cdr(rest)) {
        return make_value(1 / result);
    }

    gc::handle<value> next = cdr(rest);
    while (!!next) {
        result /= handle_cast<int>(car(next));
        next = cdr(next);
    }

    return make_value(result);
}

DEFINE_PRIMITIVE(rs_eq, args, rest) {
    int lhs = handle_cast<int>(args[0]);
    int rhs = handle_cast<int>(args[1]);
    return make_value(lhs == rhs);
}

DEFINE_PRIMITIVE(rs_less, args, rest) {
    int lhs = handle_cast<int>(args[0]);
    int rhs = handle_cast<int>(args[1]);
    return make_value(lhs < rhs);
}

DEFINE_PRIMITIVE(rs_leq, args, rest) {
    int lhs = handle_cast<int>(args[0]);
    int rhs = handle_cast<int>(args[1]);
    return make_value(lhs <= rhs);
}

DEFINE_PRIMITIVE(rs_gr, args, rest) {
    int lhs = handle_cast<int>(args[0]);
    int rhs = handle_cast<int>(args[1]);
    return make_value(lhs > rhs);
}

DEFINE_PRIMITIVE(rs_geq, args, rest) {
    int lhs = handle_cast<int>(args[0]);
    int rhs = handle_cast<int>(args[1]);
    return make_value(lhs >= rhs);
}

DEFINE_PRIMITIVE(rs_pair_p, args, rest) {
    return !!args[0] ?
        make_value(!!boost::get<pair>(&(*args[0]))) :
        make_value(false);
}

DEFINE_PRIMITIVE(rs_vector_p, args, rest) {
    return !!args[0] ?
        make_value(!!boost::get<vector>(&(*args[0]))) :
        make_value(false);
}

DEFINE_PRIMITIVE(rs_string_p, args, rest) {
    return !!args[0] ?
        make_value(!!boost::get<ast_string>(&(*args[0]))) :
        make_value(false);
}

DEFINE_PRIMITIVE(rs_symbol_p, args, rest) {
    return make_value(!!boost::get<ast_symbol>(&(*args[0])));
}

DEFINE_PRIMITIVE(rs_car, args, rest) {
    return car(args[0]);
}

DEFINE_PRIMITIVE(rs_cdr, args, rest) {
    return cdr(args[0]);
}

DEFINE_PRIMITIVE(rs_set_car_x, args, rest) {
    set_car(args[0], args[1]);
    return nil();
}

DEFINE_PRIMITIVE(rs_set_cdr_x, args, rest) {
    set_cdr(args[0], args[1]);
    return nil();
}

DEFINE_PRIMITIVE(rs_list, args, rest) {
    return rest;
}

DEFINE_PRIMITIVE(rs_vector, args, rest) {
    vector result;

    if (!rest) {
        return make_value(result);
    }

    gc::handle<value> next = rest;
    while (!!next) {
        result.push_back(car(next));
        next = cdr(next);
    }

    return make_value(result);
}

DEFINE_PRIMITIVE(rs_display, args, rest) {
    std::cout << args[0] << std::endl;
    return nil();
}

environment_ptr build_initial_env() {
    environment_ptr env(new environment);

    env->define("+",        native_procedure(0, true,  rs_add,       env));
    env->define("-",        native_procedure(0, true,  rs_minus,     env));
    env->define("*",        native_procedure(0, true,  rs_multiply,  env));
    env->define("/",        native_procedure(0, true,  rs_divide,    env));
    env->define("=",        native_procedure(2, true,  rs_eq,        env));
    env->define("<",        native_procedure(2, true,  rs_less,      env));
    env->define("<=",       native_procedure(2, true,  rs_leq,       env));
    env->define(">",        native_procedure(2, true,  rs_gr,        env));
    env->define(">=",       native_procedure(2, true,  rs_geq,       env));
    env->define("pair?",    native_procedure(1, false, rs_pair_p,    env));
    env->define("vector?",  native_procedure(1, false, rs_vector_p,  env));
    env->define("string?",  native_procedure(1, false, rs_string_p,  env));
    env->define("symbol?",  native_procedure(1, false, rs_symbol_p,  env));
    env->define("car",      native_procedure(1, false, rs_car,       env));
    env->define("cdr",      native_procedure(1, false, rs_cdr,       env));
    env->define("set-car!", native_procedure(2, false, rs_set_car_x, env));
    env->define("set-cdr!", native_procedure(2, false, rs_set_cdr_x, env));
    env->define("list",     native_procedure(0, true,  rs_list,      env));
    env->define("vector",   native_procedure(0, true,  rs_vector,    env));
    env->define("display",  native_procedure(1, false, rs_display,   env));

    return env;
}

}   //  namespace rose
