#ifndef __UTILITIES_HPP__
#define __UTILITIES_HPP__

#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>

#include <iterator>
#include <string>

std::string load_file(std::string const& filename);

template<typename Generator>
std::string test_generator(Generator const& generator) {
    namespace karma = boost::spirit::karma;

    std::string output;
    std::back_insert_iterator<std::string> sink(output);
    karma::generate(sink, generator);
    return output;
}

template<typename Generator, typename Attribute>
std::string test_generator_attr(
        Generator const& generator,
        Attribute const& attribute)
{
    namespace karma = boost::spirit::karma;

    std::string output;
    std::back_insert_iterator<std::string> sink(output);
    karma::generate(sink, generator, attribute);
    return output;
}

template<typename Generator, typename Delimiter, typename Attribute>
std::string test_generator_attr_delim(
        Generator const& generator,
        Delimiter const& delimiter,
        Attribute const& attribute)
{
    namespace karma = boost::spirit::karma;

    std::string output;
    std::back_insert_iterator<std::string> sink(output);
    karma::generate_delimited(sink, generator, delimiter, attribute);
    return output;
}

template<typename Parser>
bool test_parser(Parser const& parser, std::string const& input) {
    namespace qi = boost::spirit::qi;

    typedef
        std::string::const_iterator
        iterator_type;

    iterator_type first = input.begin();
    iterator_type last = input.end();

    return qi::parse(first, last, parser) && first == last;
}

template<typename Parser, typename Attribute>
bool test_parser_attr(
        Parser const& parser, std::string const& input, Attribute& attribute)
{
    namespace qi = boost::spirit::qi;

    typedef
        std::string::const_iterator
        iterator_type;

    iterator_type first = input.begin();
    iterator_type last = input.end();

    bool match = qi::parse(first, last, parser, attribute);
    bool full_match = (match && first == last);

    return full_match;
}

template<typename Parser, typename Skipper>
bool test_phrase_parser(
        Parser const& parser,
        std::string const& input,
        Skipper const& skipper)
{
    namespace qi = boost::spirit::qi;

    typedef
        std::string::const_iterator
        iterator_type;

    iterator_type first = input.begin();
    iterator_type last = input.end();

    return qi::phrase_parse(first, last, parser, Skipper()) && first == last;
}

template<typename Parser, typename Skipper, typename Attribute>
bool test_phrase_parser_attr(
        Parser const& parser,
        std::string const& input,
        Skipper const& skipper,
        Attribute& attribute)
{
    namespace qi = boost::spirit::qi;

    typedef
        std::string::const_iterator
        iterator_type;

    iterator_type first = input.begin();
    iterator_type last = input.end();

    bool match = qi::phrase_parse(first, last, parser, skipper, attribute);
    bool full_match = (match && first == last);

    return full_match;
}

template<typename T1>
rose::ast_arguments make_arguments(T1 t1) {
    rose::ast_arguments args;
    args.push_back(t1);
    return args;
}

template<typename T1, typename T2>
rose::ast_arguments make_arguments(T1 const& t1, T2 const& t2) {
    rose::ast_arguments args;
    args.push_back(t1);
    args.push_back(t2);
    return args;
}

template<typename T1, typename T2, typename T3>
rose::ast_arguments make_arguments(
        T1 const& t1, T2 const& t2, T3 const& t3)
{
    rose::ast_arguments args;
    args.push_back(t1);
    args.push_back(t2);
    args.push_back(t3);
    return args;
}

template<typename T1, typename T2, typename T3, typename T4>
rose::ast_arguments make_arguments(
        T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4)
{
    rose::ast_arguments args;
    args.push_back(t1);
    args.push_back(t2);
    args.push_back(t3);
    args.push_back(t4);
    return args;
}

template<typename T1>
rose::ast_definitions make_definitions(T1 t1) {
    rose::ast_definitions defs;
    defs.push_back(t1);
    return defs;
}

template<typename T1, typename T2>
rose::ast_definitions make_definitions(T1 const& t1, T2 const& t2) {
    rose::ast_definitions defs;
    defs.push_back(t1);
    defs.push_back(t2);
    return defs;
}

template<typename T1, typename T2, typename T3>
rose::ast_definitions make_definitions(
        T1 const& t1, T2 const& t2, T3 const& t3)
{
    rose::ast_definitions defs;
    defs.push_back(t1);
    defs.push_back(t2);
    defs.push_back(t3);
    return defs;
}

template<typename T1, typename T2, typename T3, typename T4>
rose::ast_definitions make_definitions(
        T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4)
{
    rose::ast_definitions defs;
    defs.push_back(t1);
    defs.push_back(t2);
    defs.push_back(t3);
    defs.push_back(t4);
    return defs;
}

template<typename T1>
rose::ast_sequence make_sequence(T1 t1) {
    rose::ast_sequence seq;
    seq.push_back(t1);
    return seq;
}

template<typename T1, typename T2>
rose::ast_sequence make_sequence(T1 const& t1, T2 const& t2) {
    rose::ast_sequence seq;
    seq.push_back(t1);
    seq.push_back(t2);
    return seq;
}

template<typename T1, typename T2, typename T3>
rose::ast_sequence make_sequence(
        T1 const& t1, T2 const& t2, T3 const& t3)
{
    rose::ast_sequence seq;
    seq.push_back(t1);
    seq.push_back(t2);
    seq.push_back(t3);
    return seq;
}

template<typename T1, typename T2, typename T3, typename T4>
rose::ast_sequence make_sequence(
        T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4)
{
    rose::ast_sequence seq;
    seq.push_back(t1);
    seq.push_back(t2);
    seq.push_back(t3);
    seq.push_back(t4);
    return seq;
}

template<typename T1>
rose::ast_formal_args make_formal_args(T1 t1) {
    rose::ast_formal_args formal_args;
    formal_args.push_back(t1);
    return formal_args;
}

template<typename T1, typename T2>
rose::ast_formal_args make_formal_args(T1 const& t1, T2 const& t2) {
    rose::ast_formal_args formal_args;
    formal_args.push_back(t1);
    formal_args.push_back(t2);
    return formal_args;
}

template<typename T1, typename T2, typename T3>
rose::ast_formal_args make_formal_args(
        T1 const& t1, T2 const& t2, T3 const& t3)
{
    rose::ast_formal_args formal_args;
    formal_args.push_back(t1);
    formal_args.push_back(t2);
    formal_args.push_back(t3);
    return formal_args;
}

template<typename T1, typename T2, typename T3, typename T4>
rose::ast_formal_args make_formal_args(
        T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4)
{
    rose::ast_formal_args formal_args;
    formal_args.push_back(t1);
    formal_args.push_back(t2);
    formal_args.push_back(t3);
    formal_args.push_back(t4);
    return formal_args;
}

template<typename T1>
rose::ast_program make_program(T1 t1) {
    rose::ast_program program;
    program.push_back(t1);
    return program;
}

template<typename T1, typename T2>
rose::ast_program make_program(T1 const& t1, T2 const& t2) {
    rose::ast_program program;
    program.push_back(t1);
    program.push_back(t2);
    return program;
}

template<typename T1, typename T2, typename T3>
rose::ast_program make_program(
        T1 const& t1, T2 const& t2, T3 const& t3)
{
    rose::ast_program program;
    program.push_back(t1);
    program.push_back(t2);
    program.push_back(t3);
    return program;
}

template<typename T1, typename T2, typename T3, typename T4>
rose::ast_program make_program(
        T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4)
{
    rose::ast_program program;
    program.push_back(t1);
    program.push_back(t2);
    program.push_back(t3);
    program.push_back(t4);
    return program;
}

#endif  //  __UTILITIES_HPP__
