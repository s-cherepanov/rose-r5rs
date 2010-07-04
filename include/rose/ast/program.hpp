#ifndef __ROSE_AST_EXPRESSION_HPP__
#define __ROSE_AST_EXPRESSION_HPP__

#include "rose/ast/datum.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/optional.hpp>
#include <boost/variant.hpp>

#include <algorithm>

namespace rose {

struct ast_lambda_expression;
struct ast_assignment;
struct ast_conditional;
struct ast_procedure_call;

struct nil {};

inline bool operator==(nil const&, nil const&) {
    return true;
}

inline bool operator<(nil const&, nil const&) {
    return false;
}

struct ast_quotation {
    ast_quotation() :
        quoted()
    {}

    ast_quotation(ast_datum const& quoted) :
        quoted(quoted)
    {}

    ast_datum quoted;

    bool operator==(ast_quotation const& rhs) const {
        return quoted == rhs.quoted;
    }

};  //  struct ast_quotation

typedef
    boost::variant<
        nil,
        bool,
        int,
        char,
        ast_string,
        ast_variable,
        ast_quotation,
        boost::recursive_wrapper<ast_lambda_expression>,
        boost::recursive_wrapper<ast_procedure_call>,
        boost::recursive_wrapper<ast_conditional>,
        boost::recursive_wrapper<ast_assignment>
    >
    ast_expression;

struct ast_procedure_call {
    ast_procedure_call() :
        procedure(),
        arguments()
    {}

    ast_procedure_call(
            ast_expression const& procedure,
            std::vector<ast_expression> const& arguments)
    :
        procedure(procedure),
        arguments(arguments)
    {}

    ast_procedure_call(ast_expression const& procedure) :
        procedure(procedure)
    {}

    bool operator==(ast_procedure_call const& rhs) const {
        return procedure == rhs.procedure && arguments == rhs.arguments;
    }

    ast_expression procedure;
    std::vector<ast_expression> arguments;

};  //  struct ast_procedure_call

struct ast_conditional {
    ast_conditional() :
        test(),
        consequent(),
        alternate()
    {}

    ast_conditional(
            ast_expression const& test,
            ast_expression const& consequent)
    :
        test(test),
        consequent(consequent),
        alternate()
    {}

    ast_conditional(
            ast_expression const& test,
            ast_expression const& consequent,
            ast_expression const& alternate)
    :
        test(test),
        consequent(consequent),
        alternate(alternate)
    {}

    bool operator==(ast_conditional const& rhs) const {
        return test == rhs.test &&
            consequent == rhs.consequent &&
            alternate == rhs.alternate;
    }

    ast_expression test;
    ast_expression consequent;
    boost::optional<ast_expression> alternate;

};  //  struct ast_conditional

struct ast_assignment {
    ast_assignment() :
        variable(),
        expression()
    {}

    ast_assignment(
            ast_variable const& var,
            ast_expression const& expr)
    :
        variable(var),
        expression(expr)
    {}

    bool operator==(ast_assignment const& rhs) const {
        return variable == rhs.variable &&
               expression == rhs.expression;
    }

    ast_variable variable;
    ast_expression expression;

};  //  struct ast_assignment

struct ast_definition {
    ast_definition() :
        variable(),
        expression()
    {}

    ast_definition(
            ast_variable const& var,
            ast_expression const& expr)
    :
        variable(var),
        expression(expr)
    {}

    bool operator==(ast_definition const& rhs) const {
        return variable == rhs.variable &&
            expression == rhs.expression;
    }

    ast_variable variable;
    ast_expression expression;

};  //  struct definition

typedef
    std::vector<ast_expression>
    ast_sequence;

struct ast_body {
    bool operator==(ast_body const& rhs) const {
        return definitions == rhs.definitions &&
               sequence== rhs.sequence;
    }

    std::vector<ast_definition> definitions;
    ast_sequence sequence;

};  //  struct body

typedef
    std::vector<ast_variable>
    ast_formals;

struct ast_lambda_expression {
    ast_lambda_expression() :
        formals(),
        body()
    {}

    ast_lambda_expression(
            ast_formals const& formals,
            ast_body const& body)
    :
        formals(formals),
        body(body)
    {}

    bool operator==(ast_lambda_expression const& rhs) const {
        return formals == rhs.formals && body == rhs.body;
    }

    ast_formals formals;
    ast_body body;

};  //  struct lambda_expression

typedef
    boost::variant<ast_definition, ast_expression>
    ast_command_or_definition;

typedef
    std::vector<ast_command_or_definition>
    ast_program;

}   //  namespace rose

BOOST_FUSION_ADAPT_STRUCT(
    rose::ast_quotation,
    (rose::ast_datum, quoted))

BOOST_FUSION_ADAPT_STRUCT(
    rose::ast_procedure_call,
    (rose::ast_expression, procedure)
    (std::vector<rose::ast_expression>, arguments))

BOOST_FUSION_ADAPT_STRUCT(
    rose::ast_conditional,
    (rose::ast_expression, test)
    (rose::ast_expression, consequent)
    (boost::optional<rose::ast_expression>, alternate))

BOOST_FUSION_ADAPT_STRUCT(
    rose::ast_assignment,
    (rose::ast_variable, variable)
    (rose::ast_expression, expression))

BOOST_FUSION_ADAPT_STRUCT(
    rose::ast_definition,
    (rose::ast_variable, variable)
    (rose::ast_expression, expression))

BOOST_FUSION_ADAPT_STRUCT(
    rose::ast_body,
    (std::vector<rose::ast_definition>, definitions)
    (rose::ast_sequence, sequence))

BOOST_FUSION_ADAPT_STRUCT(
    rose::ast_lambda_expression,
    (rose::ast_formals, formals)
    (rose::ast_body, body))

#endif  //  __ROSE_AST_EXPRESSION_HPP__
