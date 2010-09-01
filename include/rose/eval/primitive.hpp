#ifndef __ROSE_PRIMITIVE_HPP__
#define __ROSE_PRIMITIVE_HPP__

#include "rose/value.hpp"

namespace rose {

gc::handle<value> add(arguments_type const& args, gc::handle<value> rest);

gc::handle<value> minus(arguments_type const& args, gc::handle<value> rest);

gc::handle<value> multiply(arguments_type const& args, gc::handle<value> rest);

gc::handle<value> devide(arguments_type const& args, gc::handle<value> rest);

environment_ptr build_initial_env();

}   //  namespace rose

#endif  //  __ROSE_PRIMITIVE_HPP__
