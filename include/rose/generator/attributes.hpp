#ifndef __ROSE_GENERATOR_ATTRIBUTES_HPP__
#define __ROSE_GENERATOR_ATTRIBUTES_HPP__

#include "rose/ast/datum.hpp"
#include "rose/ast/program.hpp"

#include <boost/spirit/include/karma.hpp>

namespace boost {
namespace spirit {
namespace traits {

using rose::ast::datum;
using rose::ast::expression;
using rose::ast::quotation;
using rose::ast::lambda_expression;
using rose::ast::procedure_call;
using rose::ast::conditional;
using rose::ast::assignment;
using rose::ast::list;
using rose::ast::vector;

#define ENABLE_ATTR_CAST(target, repr)\
    template<>\
    struct transform_attribute<target const, std::string> {\
        typedef std::string type;\
        static type pre(target const&) {\
            return repr;\
        }\
    };

ENABLE_ATTR_CAST(datum, "{D}")
ENABLE_ATTR_CAST(expression, "{E}")
ENABLE_ATTR_CAST(quotation, "{Q}")
ENABLE_ATTR_CAST(lambda_expression, "{L}")
ENABLE_ATTR_CAST(procedure_call, "{P}")
ENABLE_ATTR_CAST(conditional, "{C}")
ENABLE_ATTR_CAST(assignment, "{A}")
ENABLE_ATTR_CAST(list, "{Li}")
ENABLE_ATTR_CAST(vector, "{V}")

#undef ENABLE_ATTR_CAST

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
