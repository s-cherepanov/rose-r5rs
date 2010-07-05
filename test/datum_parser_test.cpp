#include "rose/parser/datum.hpp"
#include "rose/parser/intertoken_space.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(datum_suite)

namespace qi = boost::spirit::qi;

typedef
    std::string::const_iterator
    iterator_type;

typedef
    rose::parser::intertoken_space<iterator_type>
    skipper_type;

typedef
    rose::parser::datum<iterator_type, skipper_type>
    datum;

bool is_datum( std::string const& input ) {
    iterator_type begin = input.begin();
    skipper_type skipper;
    datum grammar;

    bool result = qi::phrase_parse(
            begin, input.end(), grammar, skipper );
    return result && begin == input.end();
}

BOOST_AUTO_TEST_CASE( simple_datum_test ) {
    // boolean
    BOOST_CHECK( is_datum( "#t" ) );
    BOOST_CHECK( is_datum( "#f" ) );

    // number
    BOOST_CHECK( is_datum( "10" ) );
    BOOST_CHECK( is_datum( "-10" ) );

    // character
    BOOST_CHECK( is_datum( "#\\a" ) );
    BOOST_CHECK( is_datum( "#\\space" ) );
    BOOST_CHECK( is_datum( "#\\newline" ) );

    // string
    BOOST_CHECK( is_datum( "\"hello world\n!\"" ) );

    // symbol
    BOOST_CHECK( is_datum( "hello" ) );
    BOOST_CHECK( is_datum( "+" ) );
    BOOST_CHECK( is_datum( "-" ) );
    BOOST_CHECK( is_datum( "a->b" ) );
}

BOOST_AUTO_TEST_CASE( compound_datum_test ) {
    // list
    BOOST_CHECK( is_datum( "(1 2 3)" ) );
    BOOST_CHECK( is_datum( "(1 2 . 3)" ) );

    // nested list
    BOOST_CHECK( is_datum( "(1 (2 3) 4)" ) );
    BOOST_CHECK( is_datum( "(1 (2 3) 4)" ) );
    BOOST_CHECK( is_datum( "(lambda (x) (* x 2))" ) );

    // vector
    BOOST_CHECK( is_datum( "#(a b c)" ) );

    // // abbreviation
    // BOOST_CHECK( is_datum( "'(a b c)" ) );
    // BOOST_CHECK( is_datum( "`(a b c)" ) );
    // BOOST_CHECK( is_datum( ",(a b c)" ) );
    // BOOST_CHECK( is_datum( ",@(a b c)" ) );
}

BOOST_AUTO_TEST_SUITE_END()
