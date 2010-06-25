#include <boost/spirit/home/qi.hpp>
#include <boost/test/unit_test.hpp>

#include <map>

BOOST_AUTO_TEST_SUITE( misc_suite )

namespace qi = boost::spirit::qi;

BOOST_AUTO_TEST_CASE( int_test ) {
    int value = 0;
    std::string str( "123" );
    std::string::iterator begin = str.begin();

    BOOST_CHECK( qi::parse( begin, str.end(), qi::int_, value ) );
    BOOST_CHECK_EQUAL( value, 123 );
}

BOOST_AUTO_TEST_CASE( int_sequence_test ) {
    int a, b;
    std::string str( "1 2" );
    std::string::iterator begin = str.begin();

    bool result = qi::phrase_parse(
            begin, str.end(), qi::int_ >> qi::int_, qi::space, a, b );

    BOOST_CHECK( result );
    BOOST_CHECK_EQUAL( a, 1 );
    BOOST_CHECK_EQUAL( b, 2 );
}

BOOST_AUTO_TEST_SUITE_END()
