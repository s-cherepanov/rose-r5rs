#ifndef __ROSE_EXCEPTION_HPP__
#define __ROSE_EXCEPTION_HPP__

#include <boost/exception/all.hpp>

namespace rose {

typedef
    boost::error_info<struct tag_variable_name, std::string>
    errinfo_variable_name;

typedef
    boost::error_info<struct tag_wrong_type, std::string>
    errinfo_wrong_type;

typedef
    boost::error_info<struct tag_expected_type, std::string>
    errinfo_expected_type;

typedef
    boost::error_info<struct tag_required_arg_num, std::size_t>
    errinfo_required_arg_num;

typedef
    boost::error_info<struct tag_has_rest, bool>
    errinfo_has_rest;

typedef
    boost::error_info<struct tag_actual_arg_num, bool>
    errinfo_actual_arg_num;

struct exception_base :
    virtual boost::exception,
    virtual std::exception
{};

struct io_error              : virtual exception_base {};
struct file_not_found        : virtual io_error       {};
struct runtime_error         : virtual exception_base {};
struct duplicated_definition : virtual runtime_error  {};
struct undefined_variable    : virtual runtime_error  {};
struct arity_mismatch        : virtual runtime_error  {};
struct type_error            : virtual runtime_error  {};
struct wrong_type_to_apply   : virtual type_error     {};

}   //  namespace rose

#endif  //  __ROSE_EXCEPTION_HPP__
