#include "rose/token.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( boolean_suite )

namespace qi = boost::spirit::qi;

typedef
    std::string::const_iterator
    iterator_type;

typedef
    rose::boolean<iterator_type>
    boolean;

void check_boolean(
        std::string const& str,
        bool expected,
        bool initial_value )
{
    bool actual = initial_value;
    iterator_type first = str.begin();
    boolean grammar;

    BOOST_CHECK( qi::parse( first, str.end(), grammar, actual ) );
    BOOST_CHECK( first == str.end() );
    BOOST_CHECK_EQUAL( expected, actual );
}

BOOST_AUTO_TEST_CASE( boolean_test ) {
    check_boolean( "#t", true, false );
    check_boolean( "#f", false, true );
}

BOOST_AUTO_TEST_SUITE_END()
