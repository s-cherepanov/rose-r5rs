#include "rose/token.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( string_suite )

namespace qi = boost::spirit::qi;

typedef
    std::string::const_iterator
    iterator_type;

typedef
    rose::string<iterator_type>
    string;

void check_string(
        std::string const& str,
        std::string const& expected )
{
    iterator_type first = str.begin();
    std::string actual;
    string grammar;

    BOOST_CHECK( qi::parse( first, str.end(), grammar, actual ) );
    BOOST_CHECK( first == str.end() );
    BOOST_CHECK_EQUAL( expected, actual );
}

BOOST_AUTO_TEST_CASE( string_test ) {
    check_string( "\"abc\"", "abc" );
    check_string( "\"\\\"\"", "\"" );
    check_string( "\"\\\\\"", "\\" );
    check_string( "\" \"", " " );
    check_string( "\"\n\"", "\n" );
}

BOOST_AUTO_TEST_SUITE_END()
