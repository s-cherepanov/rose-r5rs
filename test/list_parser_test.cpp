#include "rose/parser/datum.hpp"
#include "rose/parser/intertoken_space.hpp"

#include <boost/spirit/include/qi.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(list_test_suite)

namespace qi = boost::spirit::qi;

using namespace rose;

typedef
    std::string::const_iterator
    iterator_type;

typedef
    rose::parser::intertoken_space<iterator_type>
    skipper_type;

typedef
    rose::parser::datum<iterator_type, skipper_type>
    parser_type;

BOOST_AUTO_TEST_CASE(list_test) {
    std::string input = "(#t #f #t)";
    iterator_type first = input.begin();
    iterator_type last = input.end();
    parser_type parser;
    skipper_type skipper;
    ast_list list;

    bool match = qi::phrase_parse(
            first, last, parser, skipper, list);

    BOOST_CHECK(match);
    BOOST_CHECK(first == last);

    // BOOST_CHECK_EQUAL(list.proper.size(), 3u);
    // BOOST_CHECK(list.proper[0] == ast_datum(1));
    // BOOST_CHECK(list.proper[1] == ast_datum(2));
    // BOOST_CHECK(list.proper[2] == ast_datum(3));
    // BOOST_CHECK(list.improper == 0);
}

BOOST_AUTO_TEST_SUITE_END()
