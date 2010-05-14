#ifndef __ROSE_AST_EXPRESSION_HPP__
#define __ROSE_AST_EXPRESSION_HPP__

#include "rose/ast/datum.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>

namespace rose {
namespace ast {

struct assignment;
struct conditional;
struct procedure_call;

struct nil {};

struct quotation {
    quotation() :
        value()
    {}

    quotation(datum const& value) :
        value(value)
    {}

    datum value;

};  //  struct quotation

struct expression {
    typedef
        boost::variant<
            nil,
            datum,
            quotation,
            boost::recursive_wrapper<procedure_call>,
            boost::recursive_wrapper<conditional>,
            boost::recursive_wrapper<assignment>
        >
        type;

    expression() :
        expr(nil())
    {}

    template<typename Expression>
    expression(Expression const& e) :
        expr(e)
    {}

    type expr;

};  // struct expression

struct procedure_call {
    procedure_call() :
        procedure(),
        arguments()
    {}

    procedure_call(
            expression const& procedure,
            std::vector<expression> const& arguments)
    :
        procedure(procedure),
        arguments(arguments)
    {}

    procedure_call(expression const& procedure) :
        procedure(procedure)
    {}

    expression procedure;
    std::vector<expression> arguments;

};  //  struct procedure_call

struct conditional {
    conditional() :
        test(),
        consequent(),
        alternate()
    {}

    conditional(
            expression const& test,
            expression const& consequent)
    :
        test(test),
        consequent(consequent),
        alternate()
    {}

    conditional(
            expression const& test,
            expression const& consequent,
            expression const& alternate)
    :
        test(test),
        consequent(consequent),
        alternate(alternate)
    {}

    expression test;
    expression consequent;
    expression alternate;

};  //  struct conditional

struct assignment {
    assignment() :
        variable(),
        expr()
    {}

    assignment(
            std::string const& variable,
            expression const& expr)
    :
        variable(variable),
        expr(expr)
    {}

    std::string variable;
    expression expr;

};  //  struct assignment

struct definition {
    definition() :
        variable(),
        expr()
    {}

    definition(
            std::string const& variable,
            expression const& expr)
    :
        variable(variable),
        expr(expr)
    {}

    std::string variable;
    expression expr;

};  //  struct definition

}   //  namespace ast
}   //  namespace rose

namespace boost {

template<typename T>
inline T get(rose::ast::expression const& expr) {
    return boost::get<T>(expr.expr);
}

namespace spirit {
namespace traits {

template<typename T>
struct not_is_variant;

template<>
struct not_is_variant<rose::ast::expression> : mpl::false_ {};

}   //  namespace traits
}   //  namespace spirit
}   //  namespace boost

BOOST_FUSION_ADAPT_STRUCT(
    rose::ast::quotation,
    (rose::ast::datum, value)
)

BOOST_FUSION_ADAPT_STRUCT(
    rose::ast::procedure_call,
    (rose::ast::expression, procedure)
    (std::vector<rose::ast::expression>, arguments)
)

BOOST_FUSION_ADAPT_STRUCT(
    rose::ast::conditional,
    (rose::ast::expression, test)
    (rose::ast::expression, consequent)
    (rose::ast::expression, alternate)
)

BOOST_FUSION_ADAPT_STRUCT(
    rose::ast::assignment,
    (std::string, variable)
    (rose::ast::expression, expr)
)

BOOST_FUSION_ADAPT_STRUCT(
    rose::ast::definition,
    (std::string, variable)
    (rose::ast::expression, expr)
)

#endif  //  __ROSE_AST_EXPRESSION_HPP__
