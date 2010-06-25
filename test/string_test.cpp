#include "rose/parser/intertoken_space.hpp"
#include "rose/parser/token.hpp"

#include <boost/spirit/include/qi_auxiliary.hpp>
#include <boost/spirit/include/qi_parse.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( string_suite )

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

bool is_string(
        std::string const& str,
        std::string const& expected )
{
    iterator_type first = str.begin();
    iterator_type last = str.end();
    std::string actual;
    token_type token;
    skipper_type skipper;

    bool match = qi::phrase_parse(
            first, last, token.string, skipper, actual );

    BOOST_CHECK_EQUAL( expected, actual );
    return match && first == last;
}

BOOST_AUTO_TEST_CASE( string_test ) {
    BOOST_CHECK( is_string( "\"abc\"", "abc" ) );
    BOOST_CHECK( is_string( "\"\\\"\"", "\"" ) );
    BOOST_CHECK( is_string( "\"\\\\\"", "\\" ) );
    BOOST_CHECK( is_string( "\" \"", " " ) );
    BOOST_CHECK( is_string( "\"\n\"", "\n" ) );
}

BOOST_AUTO_TEST_SUITE_END()
