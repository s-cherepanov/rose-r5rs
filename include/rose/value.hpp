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

inline std::ostream& operator<<(
        std::ostream& out, pair const& p)
{
    return out << "(a-list)";
}

struct vector :
    std::vector<gc::handle<value> >
{};

inline std::ostream& operator<<(
        std::ostream& out, vector const& v)
{
    if (v.empty()) {
        return out << "#()";
    }

    vector::const_iterator it = v.begin();
    out << "#(" << *it++;

    for (; it != v.end(); ++it) {
        out << ' ' << *it;
    }

    return out << ')';
}

inline std::ostream& operator<<(
        std::ostream& out,
        gc::handle<value> const& handle)
{
    if (!!handle) {
        return out << (*handle);
    }
    else {
        return out;
    }
}

}   //  namespace rose

#endif  //  __ROSE_VALUE_HPP__
