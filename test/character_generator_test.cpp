#include "rose/generator/token.hpp"

#include <boost/test/unit_test.hpp>

namespace ascii = boost::spirit::ascii;
namespace karma = boost::spirit::karma;

namespace generator = rose::generator;

BOOST_AUTO_TEST_SUITE(character_generator_suite)

std::string generate(char ch) {
    using ascii::space;
    using ascii::space_type;

    typedef
        std::back_insert_iterator<std::string>
        iterator_type;

    std::string output;
    iterator_type sink(output);
    generator::character<iterator_type, space_type> g;
    karma::generate_delimited(sink, g, space, ch);

    return output;
}

BOOST_AUTO_TEST_CASE(character_name_test) {
    BOOST_CHECK_EQUAL(generate(' '),  "#\\space ");
    BOOST_CHECK_EQUAL(generate('\n'), "#\\newline ");
    BOOST_CHECK_EQUAL(generate('\t'), "#\\tab ");
}

BOOST_AUTO_TEST_CASE(graph_test) {
    BOOST_CHECK_EQUAL(generate('a'),  "#\\a ");
    BOOST_CHECK_EQUAL(generate('b'),  "#\\b ");
    BOOST_CHECK_EQUAL(generate('"'),  "#\\\" ");
    BOOST_CHECK_EQUAL(generate('\''), "#\\' ");
    BOOST_CHECK_EQUAL(generate('.'),  "#\\. ");
}

BOOST_AUTO_TEST_SUITE_END()
