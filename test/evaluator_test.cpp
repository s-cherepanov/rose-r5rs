#include "rose/evaluator.hpp"

#include <gtest/gtest.h>

using namespace rose;

TEST(evaluator_test, eval_to) {
    ASSERT_EQ(evaluator().eval_to<int>("(define x 1) x"), 1);
}

TEST(evaluator_test, multiple_eval) {
    evaluator e;
    e.eval("(define x 1)");
    e.eval("(define y 2)");
    ASSERT_EQ(handle_cast<int>(e["x"]), 1);
    ASSERT_EQ(handle_cast<int>(e["y"]), 2);
}

TEST(evaluator_test, multiple_eval_to) {
    evaluator e;
    ASSERT_EQ(e.eval_to<int>("(define x 1) (+ x 1)"), 2);
    ASSERT_EQ(e.eval_to<int>("(define y 2) (+ x y)"), 3);
}
