#include "rose/generator/token.hpp"

#include <boost/test/unit_test.hpp>

namespace karma = boost::spirit::karma;

BOOST_AUTO_TEST_SUITE(character_generator_suite)

std::string generate(char ch) {
    typedef
        std::back_insert_iterator<std::string>
        iterator_type;

    std::string output;
    iterator_type sink(output);
    rose::generator::character<iterator_type> g;
    karma::generate(sink, g, ch);

    return output;
}

BOOST_AUTO_TEST_CASE(character_name_test) {
    BOOST_CHECK_EQUAL(generate(' '),  "#\\space");
    BOOST_CHECK_EQUAL(generate('\n'), "#\\newline");
    BOOST_CHECK_EQUAL(generate('\t'), "#\\tab");
}

BOOST_AUTO_TEST_CASE(graph_test) {
    BOOST_CHECK_EQUAL(generate('a'),  "#\\a");
    BOOST_CHECK_EQUAL(generate('b'),  "#\\b");
    BOOST_CHECK_EQUAL(generate('"'),  "#\\\"");
    BOOST_CHECK_EQUAL(generate('\''), "#\\'");
    BOOST_CHECK_EQUAL(generate('.'),  "#\\.");
}

BOOST_AUTO_TEST_SUITE_END()
