#ifndef __ROSE_AST_EXPRESSION_HPP__
#define __ROSE_AST_EXPRESSION_HPP__

#include "rose/ast/datum.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/optional.hpp>
#include <boost/variant.hpp>

#include <algorithm>

namespace rose {
namespace ast {

struct lambda_expression;
struct assignment;
struct conditional;
struct procedure_call;

struct nil {};

inline bool operator==(nil const&, nil const&) {
    return true;
}

inline bool operator<(nil const&, nil const&) {
    return false;
}

struct quotation {
    quotation() :
        quoted()
    {}

    quotation(datum const& quoted) :
        quoted(quoted)
    {}

    datum quoted;

    bool operator==(quotation const& rhs) const {
        return quoted == rhs.quoted;
    }

};  //  struct quotation

typedef
    boost::variant<
        nil,
        datum,
        quotation,
        boost::recursive_wrapper<lambda_expression>,
        boost::recursive_wrapper<procedure_call>,
        boost::recursive_wrapper<conditional>,
        boost::recursive_wrapper<assignment>
    >
    expression;

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

    bool operator==(procedure_call const& rhs) const {
        return procedure == rhs.procedure && arguments == rhs.arguments;
    }

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

    bool operator==(conditional const& rhs) const {
        return test == rhs.test &&
            consequent == rhs.consequent &&
            alternate == rhs.alternate;
    }

    expression test;
    expression consequent;
    boost::optional<expression> alternate;

};  //  struct conditional

struct assignment {
    assignment() :
        var(),
        expr()
    {}

    assignment(
            variable const& var,
            expression const& expr)
    :
        var(var),
        expr(expr)
    {}

    bool operator==(assignment const& rhs) const {
        return var == rhs.var && expr == rhs.expr;
    }

    variable var;
    expression expr;

};  //  struct assignment

struct definition {
    definition() :
        var(),
        expr()
    {}

    definition(
            variable const& var,
            expression const& expr)
    :
        var(var),
        expr(expr)
    {}

    bool operator==(definition const& rhs) const {
        return var == rhs.var && expr == rhs.expr;
    }

    variable var;
    expression expr;

};  //  struct definition

struct body {
    bool operator==(body const& rhs) const {
        return definitions == rhs.definitions &&
            sequence == rhs.sequence;
    }

    std::vector<definition> definitions;
    std::vector<expression> sequence;

};  //  struct body

struct lambda_expression {
    lambda_expression() :
        formals(),
        body()
    {}

    lambda_expression(
            std::vector<identifier> const& formals,
            rose::ast::body const& body)
    :
        formals(formals),
        body(body)
    {}

    bool operator==(lambda_expression const& rhs) const {
        return formals == rhs.formals && body == rhs.body;
    }

    std::vector<identifier> formals;
    rose::ast::body body;

};  //  struct lambda_expression

typedef
    boost::variant<ast::definition, ast::expression>
    command_or_definition;

typedef
    std::vector<command_or_definition>
    program;

}   //  namespace ast
}   //  namespace rose

BOOST_FUSION_ADAPT_STRUCT(
    rose::ast::quotation,
    (rose::ast::datum, quoted)
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
    (boost::optional<rose::ast::expression>, alternate)
)

BOOST_FUSION_ADAPT_STRUCT(
    rose::ast::assignment,
    (rose::ast::variable, var)
    (rose::ast::expression, expr)
)

BOOST_FUSION_ADAPT_STRUCT(
    rose::ast::definition,
    (rose::ast::variable, var)
    (rose::ast::expression, expr)
)

BOOST_FUSION_ADAPT_STRUCT(
    rose::ast::body,
    (std::vector<rose::ast::definition>, definitions)
    (std::vector<rose::ast::expression>, sequence)
)

BOOST_FUSION_ADAPT_STRUCT(
    rose::ast::lambda_expression,
    (std::vector<rose::ast::identifier>, formals)
    (rose::ast::body, body)
)

#endif  //  __ROSE_AST_EXPRESSION_HPP__
