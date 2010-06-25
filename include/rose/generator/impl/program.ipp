#ifndef __ROSE_GENERATOR_IMPL_PROGRAM_IPP__
#define __ROSE_GENERATOR_IMPL_PROGRAM_IPP__

#include "rose/generator/program.hpp"

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
using rose::ast::symbol;
using rose::ast::variable;

template<>
struct transform_attribute<identifier const, std::string> {
    typedef std::string type;
    static type pre(identifier const& i) {
        return static_cast<std::string>(i);
    }
};

template<>
struct transform_attribute<symbol const, std::string> {
    typedef std::string type;
    static type pre(symbol const& s) {
        return static_cast<std::string>(s);
    }
};

template<>
struct transform_attribute<variable const, std::string> {
    typedef std::string type;
    static type pre(variable const& v) {
        return static_cast<std::string>(v);
    }
};

}   //  namespace traits
}   //  namespace spirit
}   //  namespace boost

namespace rose {
namespace generator {

template<
    typename OutputIterator,
    typename Delimiter
>
program<OutputIterator, Delimiter>::program() :
    program::base_type(start)
{
    using karma::int_;
    using karma::lit;
    using karma::string;

    start
        =   +(command | definition)
        ;

    command
        =   expression.alias()
        ;

    definition
        =   lit('(') << "define"
            << variable
            << expression
            << ')'
        ;

    variable
        =   karma::attr_cast(string)
        ;

    expression
        =   datum
        |   quotation
        |   lambda_expression
        |   procedure_call
        |   conditional
        |   assignment
        ;

    datum
        =   boolean_
        |   int_
        |   character_
        |   string_
        |   symbol
        |   identifier
        |   variable
        |   list
        |   vector
        ;

    quotation
        =   karma::attr_cast(string)
        ;

    lambda_expression
        =   karma::attr_cast(string)
        ;

    procedure_call
        =   karma::attr_cast(string)
        ;

    conditional
        =   karma::attr_cast(string)
        ;

    assignment
        =   karma::attr_cast(string)
        ;
}

}   //  namespace generator
}   //  namespace rose

#endif  //  __ROSE_GENERATOR_IMPL_PROGRAM_IPP__

// vim:ft=cpp et
