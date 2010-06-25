#include "rose/parser/intertoken_space.hpp"
#include "rose/parser/token.hpp"

#include <boost/spirit/include/qi_parse.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( boolean_suite )

namespace qi = boost::spirit::qi;

typedef
    std::string::const_iterator
    iterator_type;

typedef
    rose::parser::intertoken_space<iterator_type>
    skipper_type;

typedef
    rose::parser::token<iterator_type, skipper_type>
    token_type;

bool is_boolean(
        std::string const& str,
        bool expected,
        bool initial_value )
{
    bool actual = initial_value;
    iterator_type first = str.begin();
    iterator_type last = str.end();
    token_type token;
    skipper_type skipper;

    bool match = qi::phrase_parse(
            first, last, token.boolean, skipper, actual );
    return match && first == last && expected == actual;
}

BOOST_AUTO_TEST_CASE( boolean_test ) {
    BOOST_CHECK( is_boolean( "#t", true, false ) );
    BOOST_CHECK( is_boolean( "#f", false, true ) );
}

BOOST_AUTO_TEST_SUITE_END()
