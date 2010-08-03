#ifndef __PARSERS_HPP__
#define __PARSERS_HPP__

#include "rose/parser/datum.hpp"
#include "rose/parser/expression.hpp"
#include "rose/parser/intertoken_space.hpp"
#include "rose/parser/program.hpp"
#include "rose/parser/token.hpp"

typedef
    std::string::const_iterator
    input_iterator;

typedef
    rose::parser::intertoken_space<input_iterator>
    skipper_type;

typedef
    rose::parser::datum<input_iterator, skipper_type>
    datum_parser;

typedef
    rose::parser::expression<input_iterator, skipper_type>
    expression_parser;

typedef
    rose::parser::program<input_iterator, skipper_type>
    program_parser;

typedef
    rose::parser::token<input_iterator, skipper_type>
    token_parser;

extern skipper_type      skipper_p;
extern datum_parser      datum_p;
extern expression_parser expression_p;
extern program_parser    program_p;
extern token_parser      token_p;

#endif  //  __PARSERS_HPP__
