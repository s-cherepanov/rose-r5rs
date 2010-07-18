#ifndef __UTILITIES_HPP__
#define __UTILITIES_HPP__

#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>

#include <iterator>
#include <string>

std::string load_file( std::string const& filename );

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
    bool full_match = (first == last);

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
    bool full_match = (first == last);

    return full_match;
}

#endif  //  __UTILITIES_HPP__
