#include "rose/identifier.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( identifier_suite )

namespace qi = boost::spirit::qi;

typedef
    std::string::const_iterator
    iterator_type;

typedef
    rose::identifier<iterator_type>
    identifier;

void check_identifier( std::string const& str ) {
    iterator_type first = str.begin();
    std::string actual;

    BOOST_CHECK( qi::parse( first, str.end(), identifier(), actual ) );
    BOOST_CHECK( first == str.end() );
    BOOST_CHECK_EQUAL( str, actual );
}

BOOST_AUTO_TEST_CASE( peculiar_identifier_test ) {
    check_identifier( "+" );
    check_identifier( "-" );
    check_identifier( "..." );
}

BOOST_AUTO_TEST_CASE( test_special_initial ) {
    check_identifier( "!" );
    check_identifier( "$" );
    check_identifier( "%" );
    check_identifier( "&" );
    check_identifier( "*" );
    check_identifier( "/" );
    check_identifier( ":" );
    check_identifier( "<" );
    check_identifier( "=" );
    check_identifier( ">" );
    check_identifier( "?" );
    check_identifier( "^" );
    check_identifier( "_" );
    check_identifier( "~" );
}

BOOST_AUTO_TEST_CASE( test_special_subsequent ) {
    check_identifier( "a+" );
    check_identifier( "a-" );
    check_identifier( "a." );
    check_identifier( "a@" );
}

BOOST_AUTO_TEST_CASE( test_mixed ) {
    check_identifier( "abc" );
    check_identifier( "!abc" );
    check_identifier( "abc!" );
    check_identifier( "a->b" );
}

BOOST_AUTO_TEST_SUITE_END()
