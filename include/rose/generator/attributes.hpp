#ifndef __ROSE_GENERATOR_ATTRIBUTES_HPP__
#define __ROSE_GENERATOR_ATTRIBUTES_HPP__

#include "rose/ast/datum.hpp"
#include "rose/ast/program.hpp"

#include <boost/spirit/include/karma.hpp>

namespace boost {
namespace spirit {
namespace traits {

using rose::ast::identifier;

template<>
struct transform_attribute<identifier const, std::string> {
    typedef std::string type;
    static type pre(identifier const& i) {
        return static_cast<std::string>(i);
    }
};

using rose::ast::symbol;

template<>
struct transform_attribute<symbol const, std::string> {
    typedef std::string type;
    static type pre(symbol const& s) {
        return static_cast<std::string>(s);
    }
};

using rose::ast::variable;

template<>
struct transform_attribute<variable const, std::string> {
    typedef std::string type;
    static type pre(variable const& v) {
        return static_cast<std::string>(v);
    }
};

using rose::ast::datum;
using rose::ast::quotation;

template<>
struct transform_attribute<quotation const, datum> {
    typedef datum type;
    static type pre(quotation const& q) {
        return q.quoted;
    }
};

}   //  namespace traits
}   //  namespace spirit
}   //  namespace boost

#endif  //  __ROSE_GENERATOR_ATTRIBUTES_HPP__
