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

BOOST_AUTO_TEST_CASE( variable_test ) {
    BOOST_CHECK( is_expression( "abc" ) );
    BOOST_CHECK( is_expression( "+" ) );
    BOOST_CHECK( is_expression( "-" ) );
    BOOST_CHECK( is_expression( "a->b" ) );
    BOOST_CHECK( is_expression( "boolean?" ) );
}

BOOST_AUTO_TEST_CASE( literal_quotation_test ) {
    BOOST_CHECK( is_expression( "'a" ) );
    BOOST_CHECK( is_expression( "'(1 2 3)" ) );
    BOOST_CHECK( is_expression( "(quote (1 2 3))" ) );
}

BOOST_AUTO_TEST_CASE( literal_self_evaluating_boolean_test ) {
    BOOST_CHECK( is_expression( "#t" ) );
    BOOST_CHECK( is_expression( "#f" ) );
}

BOOST_AUTO_TEST_CASE( literal_self_evaluating_number_test ) {
    BOOST_CHECK( is_expression( "10" ) );
    BOOST_CHECK( is_expression( "-10" ) );
}

BOOST_AUTO_TEST_CASE( literal_self_evaluating_character_test ) {
    BOOST_CHECK( is_expression( "#\\a" ) );
    BOOST_CHECK( is_expression( "#\\newline" ) );
    BOOST_CHECK( is_expression( "#\\space" ) );
}

BOOST_AUTO_TEST_CASE( literal_self_evaluating_string_test ) {
    BOOST_CHECK( is_expression( "\"\"" ) );
    BOOST_CHECK( is_expression( "\"\\n\"" ) );
    BOOST_CHECK( is_expression( "\"abc\"" ) );
}

BOOST_AUTO_TEST_CASE( procedure_call_test ) {
    BOOST_CHECK( is_expression( "(+ a b)" ) );
    BOOST_CHECK( is_expression( "(symbol? 'a)" ) );
}

BOOST_AUTO_TEST_CASE( lambda_expression_test ) {
    BOOST_CHECK( is_expression( "(lambda (x) (+ x 1))" ) );
    BOOST_CHECK( is_expression( "(lambda x (+ x 1))" ) );
    BOOST_CHECK( is_expression( "(lambda () 1)" ) );
    BOOST_CHECK( is_expression( "(lambda (x y) (+ x 1))" ) );
    BOOST_CHECK( is_expression( "(lambda (x . y) (+ x y))" ) );
}

BOOST_AUTO_TEST_SUITE_END()
