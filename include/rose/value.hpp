#ifndef __ROSE_VALUE_HPP__
#define __ROSE_VALUE_HPP__

#include "rose/ast/program.hpp"
#include "rose/gc/handle.hpp"

#include <boost/variant.hpp>

#include <utility>
#include <vector>

namespace rose {

struct pair;
struct vector;

typedef
    boost::variant<
        bool,
        int,
        char,
        ast_string,
        ast_symbol,
        boost::recursive_wrapper<pair>,
        boost::recursive_wrapper<vector>
    >
    value;

struct pair :
    std::pair<gc::handle<value>, gc::handle<value> >
{};

struct vector :
    std::vector<gc::handle<value> >
{};

}   //  namespace rose

#endif  //  __ROSE_VALUE_HPP__
