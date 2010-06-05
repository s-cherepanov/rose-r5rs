#ifndef __ROSE_IMPL_EXPRESSION_IPP__
#define __ROSE_IMPL_EXPRESSION_IPP__

#include "rose/parser/expression.hpp"

#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;
namespace spirit = boost::spirit;
namespace phoenix = boost::phoenix;

template<
    typename Iterator,
    typename Skipper
>
expression<Iterator, Skipper>::expression() :
    expression::base_type(expression_)
{
    using qi::char_;
    using qi::no_case;

    using namespace qi::labels;

    using phoenix::at_c;
    using phoenix::push_back;

    expression_
       %=   variable
        |   literal
        |   lambda_expression
        |   procedure_call
        |   conditional
        |   assignment
        ;

    variable
       %=   token.identifier
        ;

    literal
       %=   quotation
        |   self_evaluating
        ;

    self_evaluating
       %=   token.boolean
        |   token.number
        |   token.character
        |   token.string
        ;

    quotation
        =   token.single_quote >> datum
        |   token.lparen
            >> no_case["quote"] >> datum    [_val = _1]
            >> token.rparen
        ;

    procedure_call
        =   token.lparen
            >> operator_                    [at_c<0>(_val) = _1]
            >> *operand                     [push_back(at_c<1>(_val), _1)]
            >> token.rparen
        ;

    operator_
       %=   expression_.alias()
        ;

    operand
       %=   expression_.alias()
        ;

    lambda_expression
        =   token.lparen
            >> no_case["lambda"]
            >> formals                      [at_c<0>(_val) = _1]
            >> body                         [at_c<1>(_val) = _1]
            >> token.rparen
        ;

    formals
        =   token.lparen
            >> *variable                    [push_back(_val, _1)]
            >> token.rparen
        ;

    body
        =   *definition                     [push_back(at_c<0>(_val), _1)]
            >> sequence                     [at_c<1>(_val) = _1]
        ;

    definition
        =   token.lparen
            >> no_case["define"]
            >> variable                     [at_c<0>(_val) = _1]
            >> expression_                  [at_c<1>(_val) = _1]
            >> token.rparen
        ;

    def_formals
        =   *variable
            >>  -(token.dot >> variable)
        ;

    sequence
        =   +command                        [push_back(_val, _1)]
        ;

    command
       %=   expression_.alias()
        ;

    conditional
        =   token.lparen
            >> no_case["if"]
            >> test                         [at_c<0>(_val) = _1]
            >> consequent                   [at_c<1>(_val) = _1]
            >> -alternate                   [at_c<2>(_val) = _1]
            >> token.rparen
        ;

    test
        =   expression_.alias()
        ;

    consequent
        =   expression_.alias()
        ;

    alternate
        =   expression_.alias()
        ;

    assignment
        =   token.lparen
            >> no_case["set!"] >> variable >> expression_
            >> token.rparen
        ;

    expression_      .name("expression");
    variable         .name("variable");
    literal          .name("literal");
    self_evaluating  .name("self_evaluating");
    quotation        .name("quotation");
    procedure_call   .name("procedure_call");
    operator_        .name("operator");
    operand          .name("operand");
    lambda_expression.name("lambda_expression");
    formals          .name("formals");
    body             .name("body");
    definition       .name("definition");
    sequence         .name("sequence");
    command          .name("command");
    conditional      .name("conditional");
    test             .name("test");
    consequent       .name("consequent");
    alternate        .name("alternate");
    assignment       .name("assignment");
}

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_IMPL_EXPRESSION_IPP__

// vim:ft=cpp et
