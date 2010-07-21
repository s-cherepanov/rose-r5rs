#include "generators.hpp"
#include "utilities.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(character_generator_suite)

void check(char ch, std::string const& expected) {
    BOOST_CHECK_EQUAL(
            test_generator_attr_delim(character_g, delimiter_g, ch),
            expected);
}

BOOST_AUTO_TEST_CASE(character_name_test) {
    check(' ', "#\\space ");
    check('\t', "#\\tab ");
    check('\n', "#\\newline ");
}

BOOST_AUTO_TEST_CASE(graph_test) {
    check('a', "#\\a ");
    check('"', "#\\\" ");
    check('"', "#\\\" ");
    check('\'', "#\\' ");
    check('.', "#\\. ");
}

BOOST_AUTO_TEST_SUITE_END()
