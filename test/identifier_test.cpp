#include "rose/parser/identifier.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( identifier_suite )

namespace qi = boost::spirit::qi;

typedef
    std::string::const_iterator
    iterator_type;

typedef
    rose::parser::identifier<iterator_type>
    identifier_grammar;

bool is_identifier( std::string const& str ) {
    iterator_type first = str.begin();
    iterator_type last = str.end();
    std::string actual;
    identifier_grammar grammar;

    bool result = qi::parse( first, last, grammar, actual );
    return result && first == last && str == actual;
}

BOOST_AUTO_TEST_CASE( peculiar_identifier_test ) {
    BOOST_CHECK( is_identifier( "+" ) );
    BOOST_CHECK( is_identifier( "-" ) );
    BOOST_CHECK( is_identifier( "..." ) );
}

BOOST_AUTO_TEST_CASE( test_special_initial ) {
    BOOST_CHECK( is_identifier( "!" ) );
    BOOST_CHECK( is_identifier( "$" ) );
    BOOST_CHECK( is_identifier( "%" ) );
    BOOST_CHECK( is_identifier( "&" ) );
    BOOST_CHECK( is_identifier( "*" ) );
    BOOST_CHECK( is_identifier( "/" ) );
    BOOST_CHECK( is_identifier( ":" ) );
    BOOST_CHECK( is_identifier( "<" ) );
    BOOST_CHECK( is_identifier( "=" ) );
    BOOST_CHECK( is_identifier( ">" ) );
    BOOST_CHECK( is_identifier( "?" ) );
    BOOST_CHECK( is_identifier( "^" ) );
    BOOST_CHECK( is_identifier( "_" ) );
    BOOST_CHECK( is_identifier( "~" ) );
}

BOOST_AUTO_TEST_CASE( test_special_subsequent ) {
    BOOST_CHECK( is_identifier( "a+" ) );
    BOOST_CHECK( is_identifier( "a-" ) );
    BOOST_CHECK( is_identifier( "a." ) );
    BOOST_CHECK( is_identifier( "a@" ) );
}

BOOST_AUTO_TEST_CASE( test_mixed ) {
    BOOST_CHECK( is_identifier( "abc" ) );
    BOOST_CHECK( is_identifier( "!abc" ) );
    BOOST_CHECK( is_identifier( "abc!" ) );
    BOOST_CHECK( is_identifier( "a->b" ) );
}

BOOST_AUTO_TEST_SUITE_END()
