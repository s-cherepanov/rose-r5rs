#include "rose/ast/program.hpp"

#include <boost/test/unit_test.hpp>

using namespace rose;

BOOST_AUTO_TEST_SUITE(ast_expression_suite)

BOOST_AUTO_TEST_CASE(ast_expression_test) {
    ast_expression e1;
    ast_expression e2;
    BOOST_CHECK( e1 == e2 );
}

BOOST_AUTO_TEST_SUITE_END()
