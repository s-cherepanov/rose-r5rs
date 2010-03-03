#include "load_file.hpp"
#include "rose/identifier.hpp"
#include "rose/intertoken_space.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( identifier_suite )

namespace qi = boost::spirit::qi;

struct identifier_fixture {
    typedef
        std::string::const_iterator
        iterator_type;

    typedef
        rose::identifier<iterator_type>
        identifier;

    identifier grammar;

    void check_identifier( std::string const& str ) {
        iterator_type first = str.begin();
        std::string id;
        BOOST_CHECK( qi::parse( first, str.end(), grammar, id ) );
        BOOST_CHECK( first == str.end() );
        BOOST_CHECK_EQUAL( str, id );
    }

};  //  struct identifier_fixture

BOOST_FIXTURE_TEST_CASE(
        peculiar_identifier_test,
        identifier_fixture )
{
    check_identifier( "+" );
    check_identifier( "-" );
    check_identifier( "..." );
}

BOOST_FIXTURE_TEST_CASE(
        test_special_initial,
        identifier_fixture )
{
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

BOOST_FIXTURE_TEST_CASE(
        test_special_subsequent,
        identifier_fixture )
{
    check_identifier( "a+" );
    check_identifier( "a-" );
    check_identifier( "a." );
    check_identifier( "a@" );
}

BOOST_FIXTURE_TEST_CASE(
        test_mixed,
        identifier_fixture )
{
    check_identifier( "abc" );
    check_identifier( "!abc" );
    check_identifier( "abc!" );
    check_identifier( "a->b" );
}

BOOST_AUTO_TEST_SUITE_END()
