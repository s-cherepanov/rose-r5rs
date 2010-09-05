#include "generators.hpp"
#include "utilities.hpp"

#include <gtest/gtest.h>

TEST(boolean_generator_test, generate_true) {
    ASSERT_EQ(test_generator_attr_delim(boolean_g, delimiter_g, true), "#t ");
}

TEST(boolean_generator_test, generate_false) {
    ASSERT_EQ(test_generator_attr_delim(boolean_g, delimiter_g, false), "#f ");
}
