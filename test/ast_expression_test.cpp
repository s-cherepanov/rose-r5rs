#include "rose/ast/expression.hpp"

#include <boost/test/unit_test.hpp>

using namespace rose::ast;

BOOST_AUTO_TEST_SUITE(ast_expression_suite)

BOOST_AUTO_TEST_CASE(ast_expression_test) {
    expression e1;
    expression e2;
    BOOST_CHECK( e1.expr == e2.expr );
}

BOOST_AUTO_TEST_SUITE_END()
