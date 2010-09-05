#ifndef __ROSE_PRIMITIVE_HPP__
#define __ROSE_PRIMITIVE_HPP__

#include "rose/value.hpp"

#define DECLARE_NATIVE_PROCEDURE(name)\
        rose::gc::handle<value> name(\
                rose::arguments_type const& args,\
                rose::gc::handle<rose::value> rest)

#define DEFINE_NATIVE_PROCEDURE DECLARE_NATIVE_PROCEDURE

namespace rose {

environment_ptr init_env(environment_ptr env = environment_ptr());

DECLARE_NATIVE_PROCEDURE(np_add);
DECLARE_NATIVE_PROCEDURE(np_minus);
DECLARE_NATIVE_PROCEDURE(np_multiply);
DECLARE_NATIVE_PROCEDURE(np_divide);
DECLARE_NATIVE_PROCEDURE(np_eq);
DECLARE_NATIVE_PROCEDURE(np_less);
DECLARE_NATIVE_PROCEDURE(np_leq);
DECLARE_NATIVE_PROCEDURE(np_gr);
DECLARE_NATIVE_PROCEDURE(np_geq);
DECLARE_NATIVE_PROCEDURE(np_pair_p);
DECLARE_NATIVE_PROCEDURE(np_vector_p);
DECLARE_NATIVE_PROCEDURE(np_string_p);
DECLARE_NATIVE_PROCEDURE(np_symbol_p);
DECLARE_NATIVE_PROCEDURE(np_procedure_p);
DECLARE_NATIVE_PROCEDURE(np_car);
DECLARE_NATIVE_PROCEDURE(np_cdr);
DECLARE_NATIVE_PROCEDURE(np_set_car_x);
DECLARE_NATIVE_PROCEDURE(np_set_cdr_x);
DECLARE_NATIVE_PROCEDURE(np_list);
DECLARE_NATIVE_PROCEDURE(np_vector);
DECLARE_NATIVE_PROCEDURE(np_display);
DECLARE_NATIVE_PROCEDURE(np_display_line);

}   //  namespace rose

#endif  //  __ROSE_PRIMITIVE_HPP__
