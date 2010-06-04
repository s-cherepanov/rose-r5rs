#include "rose/parser/number.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( number_suite )

namespace qi = boost::spirit::qi;

typedef
    std::string::const_iterator
    iterator_type;

typedef
    rose::parser::number<iterator_type>
    number;

void check_number(
        std::string const& str,
        int expected,
        int initial_value = 0 )
{
    int actual = initial_value;
    iterator_type first = str.begin();
    number grammar;

    BOOST_CHECK( qi::parse( first, str.end(), grammar, actual ) );
    BOOST_CHECK( first == str.end() );
    BOOST_CHECK_EQUAL( expected, actual );
}

BOOST_AUTO_TEST_CASE( number_test ) {
    check_number( "0", 0, 1 );
    check_number( "10", 10 );
    check_number( "-10", -10 );
}

BOOST_AUTO_TEST_SUITE_END()
