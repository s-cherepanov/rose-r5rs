#include "rose/parser/character.hpp"

#include <boost/spirit/include/qi_parse.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( character_suite )

namespace qi = boost::spirit::qi;

typedef
    std::string::const_iterator
    iterator_type;

typedef
    rose::parser::character<iterator_type>
    character;

void check_character( std::string const& input, char expected ) {
    char actual = '\0';
    iterator_type begin = input.begin();
    character grammar;

    BOOST_CHECK( qi::parse( begin, input.end(), grammar, actual ) );
    BOOST_CHECK( begin == input.end() );
    BOOST_CHECK_EQUAL( expected, actual );
}

BOOST_AUTO_TEST_CASE( test_any_character ) {
    check_character( "#\\a", 'a' );
    check_character( "#\\?", '?' );
}

BOOST_AUTO_TEST_CASE( test_character_name ) {
    check_character( "#\\space", ' ' );
    check_character( "#\\newline", '\n' );
}

BOOST_AUTO_TEST_SUITE_END()
