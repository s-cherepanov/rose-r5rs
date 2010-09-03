#include "rose/evaluator.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(evaluator_suite)

using namespace rose;

BOOST_AUTO_TEST_CASE(evaluator_simple_test) {
    BOOST_CHECK_EQUAL(evaluator().eval_to<int>("(define x 1) x"), 1);
}

BOOST_AUTO_TEST_CASE(evaluator_test) {
    evaluator e;
    e.eval("(define x 1)");
    BOOST_CHECK_EQUAL(handle_cast<int>(e["x"]), 1);
}

BOOST_AUTO_TEST_SUITE_END()
