#include "rose/ast/datum.hpp"

#include <boost/test/unit_test.hpp>

using namespace rose::ast;

BOOST_AUTO_TEST_SUITE(ast_datum_suite)

BOOST_AUTO_TEST_CASE(ast_datum_number_equality_test) {
    datum d1(1), d2(1);
    BOOST_CHECK(d1 == d2);
}

BOOST_AUTO_TEST_CASE(ast_datum_number_inequality_test) {
    datum d1(1), d2(2);
    BOOST_CHECK(!(d1 == d2));
}

BOOST_AUTO_TEST_SUITE_END()
