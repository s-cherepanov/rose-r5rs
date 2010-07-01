#ifndef __ROSE_GENERATOR_ATTRIBUTES_HPP__
#define __ROSE_GENERATOR_ATTRIBUTES_HPP__

#include "rose/ast/datum.hpp"
#include "rose/ast/program.hpp"

#include <boost/spirit/include/karma.hpp>

namespace boost {
namespace spirit {
namespace traits {

using rose::ast_identifier;

template<>
struct transform_attribute<ast_identifier const, std::string> {
    typedef std::string type;
    static type pre(ast_identifier const& i) {
        return static_cast<std::string>(i);
    }
};

using rose::ast_symbol;

template<>
struct transform_attribute<ast_symbol const, std::string> {
    typedef std::string type;
    static type pre(ast_symbol const& s) {
        return static_cast<std::string>(s);
    }
};

using rose::ast_variable;

template<>
struct transform_attribute<ast_variable const, std::string> {
    typedef std::string type;
    static type pre(ast_variable const& v) {
        return static_cast<std::string>(v);
    }
};

using rose::ast_datum;
using rose::ast_quotation;

template<>
struct transform_attribute<ast_quotation const, ast_datum> {
    typedef ast_datum type;
    static type pre(ast_quotation const& q) {
        return q.quoted;
    }
};

}   //  namespace traits
}   //  namespace spirit
}   //  namespace boost

#endif  //  __ROSE_GENERATOR_ATTRIBUTES_HPP__
