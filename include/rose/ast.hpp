#ifndef __ROSE_AST_HPP__
#define __ROSE_AST_HPP__

#include "rose/detail/tagged_string.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/optional.hpp>
#include <boost/variant.hpp>

#include <algorithm>
#include <iterator>
#include <list>
#include <string>
#include <vector>

namespace rose {

typedef detail::tagged_string<struct string_tag>     ast_string;
typedef detail::tagged_string<struct identifier_tag> ast_identifier;
typedef detail::tagged_string<struct symbol_tag>     ast_symbol;
typedef detail::tagged_string<struct variable_tag>   ast_variable;

struct ast_list;
struct ast_vector;

typedef
    boost::variant<
        bool,
        int,
        char,
        ast_string,
        ast_symbol,
        boost::recursive_wrapper<ast_list>,
        boost::recursive_wrapper<ast_vector>
    >
    ast_datum;

struct ast_list {
    typedef std::vector<ast_datum> container_type;
    typedef container_type::iterator iterator;
    typedef container_type::const_iterator const_iterator;

    container_type elements;
    boost::optional<ast_datum> dotted_element;

    bool operator==(ast_list const& rhs) const {
        return elements == rhs.elements &&
            dotted_element == rhs.dotted_element;
    }

};  //  struct ast_list

struct ast_vector : std::vector<ast_datum> {};

struct ast_lambda_expression;
struct ast_assignment;
struct ast_conditional;
struct ast_procedure_call;

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

typedef std::vector<ast_expression> ast_arguments;

struct ast_procedure_call {
    ast_procedure_call() :
        procedure(),
        arguments()
    {}

    ast_procedure_call(
            ast_expression const& procedure,
            ast_arguments const& arguments)
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
    ast_arguments arguments;

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

};  //  struct ast_definition

typedef std::vector<ast_definition> ast_definitions;

typedef std::vector<ast_expression> ast_sequence;

struct ast_body {
    ast_body() :
        definitions(),
        sequence()
    {}

    ast_body(ast_definitions const& definitions,
             ast_sequence const& sequence)
    :
        definitions(definitions),
        sequence(sequence)
    {}

    ast_body(ast_sequence const& sequence) :
        definitions(),
        sequence(sequence)
    {}

    bool operator==(ast_body const& rhs) const {
        return definitions == rhs.definitions &&
               sequence== rhs.sequence;
    }

    ast_definitions definitions;
    ast_sequence sequence;

};  //  struct ast_body

typedef std::vector<ast_variable> ast_formal_args;

struct ast_formals {
    ast_formals() {
    }

    ast_formals(ast_formal_args const& formal_args) :
        formal_args(formal_args)
    {}

    ast_formals(
            ast_formal_args const& formal_args,
            ast_variable const& formal_rest)
    :
        formal_args(formal_args),
        formal_rest(formal_rest)
    {}

    bool operator==(ast_formals const& rhs) const {
        return formal_args == rhs.formal_args &&
            formal_rest == rhs.formal_rest;
    }

    ast_formal_args formal_args;
    boost::optional<ast_variable> formal_rest;

};  //  struct ast_formals

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

};  //  struct ast_lambda_expression

typedef
    boost::variant<ast_definition, ast_expression>
    ast_command_or_definition;

typedef
    std::vector<ast_command_or_definition>
    ast_program;

}   //  namespace rose

BOOST_FUSION_ADAPT_STRUCT(
        rose::ast_list,
        (rose::ast_list::container_type, elements)
        (boost::optional<rose::ast_datum>, dotted_element))

BOOST_FUSION_ADAPT_STRUCT(
        rose::ast_quotation,
        (rose::ast_datum, quoted))

BOOST_FUSION_ADAPT_STRUCT(
        rose::ast_procedure_call,
        (rose::ast_expression, procedure)
        (rose::ast_arguments, arguments))

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
        rose::ast_formals,
        (rose::ast_formal_args, formal_args)
        (boost::optional<rose::ast_variable>, formal_rest))

BOOST_FUSION_ADAPT_STRUCT(
        rose::ast_body,
        (rose::ast_definitions, definitions)
        (rose::ast_sequence, sequence))

BOOST_FUSION_ADAPT_STRUCT(
        rose::ast_lambda_expression,
        (rose::ast_formals, formals)
        (rose::ast_body, body))

#endif  //  __ROSE_AST_HPP__
