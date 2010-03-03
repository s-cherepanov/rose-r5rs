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
        bool initial_value,
        bool expected )
{
    bool actual = initial_value;
    iterator_type first = str.begin();

    BOOST_CHECK( qi::parse( first, str.end(), boolean(), actual ) );
    BOOST_CHECK( first == str.end() );
    BOOST_CHECK_EQUAL( expected, actual );
}

BOOST_AUTO_TEST_CASE( boolean_test ) {
    check_boolean( "#t", false, true );
    check_boolean( "#f", true, false );
}

BOOST_AUTO_TEST_SUITE_END()
