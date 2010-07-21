#ifndef __GENERATORS_HPP__
#define __GENERATORS_HPP__

#include "rose/generator/datum.hpp"
#include "rose/generator/expression.hpp"
#include "rose/generator/program.hpp"
#include "rose/generator/token.hpp"

typedef
    std::back_insert_iterator<std::string>
    output_iterator;

typedef
    boost::spirit::ascii::space_type
    delimiter_type;

typedef
    rose::generator::datum<output_iterator, delimiter_type>
    datum_generator;

typedef
    rose::generator::expression<output_iterator, delimiter_type>
    expression_generator;

typedef
    rose::generator::program<output_iterator, delimiter_type>
    program_generator;

typedef
    rose::generator::boolean<output_iterator, delimiter_type>
    boolean_generator;

typedef
    rose::generator::number<output_iterator, delimiter_type>
    number_generator;

typedef
    rose::generator::character<output_iterator, delimiter_type>
    character_generator;

typedef
    rose::generator::string<output_iterator, delimiter_type>
    string_generator;

extern delimiter_type       delimiter_g;
extern datum_generator      datum_g;
extern expression_generator expression_g;
extern program_generator    program_g;
extern boolean_generator    boolean_g;
extern number_generator     number_g;
extern character_generator  character_g;
extern string_generator     string_g;

#endif  //  __GENERATORS_HPP__
