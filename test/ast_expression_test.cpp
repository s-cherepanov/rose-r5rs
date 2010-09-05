#include "rose/ast.hpp"

#include <gtest/gtest.h>

using namespace rose;

TEST(ast_expression_test, empty_expression) {
    ast_expression e1;
    ast_expression e2;
    ASSERT_TRUE(e1 == e2);
}
