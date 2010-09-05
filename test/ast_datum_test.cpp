#include "rose/ast.hpp"

#include <gtest/gtest.h>

using namespace rose;

TEST(ast_datum_test, number_eq) {
    ast_datum d1(1), d2(1);
    ASSERT_TRUE(d1 == d2);
}

TEST(ast_datum_test, number_ne) {
    ast_datum d1(1), d2(2);
    ASSERT_TRUE(!(d1 == d2));
}
