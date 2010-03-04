#include "rose/expression.hpp"
#include "rose/intertoken_space.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( expression_suite )

namespace qi = boost::spirit::qi;

typedef
    std::string::const_iterator
    iterator_type;

typedef
    rose::intertoken_space<iterator_type>
    skipper_type;

typedef
    rose::expression<iterator_type, skipper_type>
    expression;

bool is_expression( std::string const& input ) {
    iterator_type begin = input.begin();
    iterator_type end = input.end();
    skipper_type skipper;
    expression grammar;

    bool result = qi::phrase_parse( begin, end, grammar, skipper );
    return result && begin == end;
}

BOOST_AUTO_TEST_CASE( expression_test ) {
    // variable
    BOOST_CHECK( is_expression( "abc" ) );
    BOOST_CHECK( is_expression( "+" ) );
    BOOST_CHECK( is_expression( "-" ) );
    BOOST_CHECK( is_expression( "a->b" ) );
    BOOST_CHECK( is_expression( "boolean?" ) );

    // literal/quotation
    BOOST_CHECK( is_expression( "'a" ) );
    BOOST_CHECK( is_expression( "'(1 2 3)" ) );
    BOOST_CHECK( is_expression( "(quote (1 2 3))" ) );

    // literal/self_evaluating/boolean
    BOOST_CHECK( is_expression( "#t" ) );
    BOOST_CHECK( is_expression( "#f" ) );

    // literal/self_evaluating/number
    BOOST_CHECK( is_expression( "10" ) );
    BOOST_CHECK( is_expression( "-10" ) );

    // literal/self_evaluating/character
    BOOST_CHECK( is_expression( "#\\a" ) );
    BOOST_CHECK( is_expression( "#\\newline" ) );
    BOOST_CHECK( is_expression( "#\\space" ) );

    // literal/self_evaluating/string
    BOOST_CHECK( is_expression( "\"\"" ) );
    BOOST_CHECK( is_expression( "\"\\n\"" ) );
    BOOST_CHECK( is_expression( "\"abc\"" ) );
}

BOOST_AUTO_TEST_SUITE_END()
