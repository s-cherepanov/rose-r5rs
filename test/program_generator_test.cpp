#include "rose/generator/program.hpp"

#include <boost/test/unit_test.hpp>

namespace ast = rose::ast;
namespace ascii = boost::spirit::ascii;
namespace karma = boost::spirit::karma;

BOOST_AUTO_TEST_SUITE(program_generator_suite)

BOOST_AUTO_TEST_CASE(program_test) {
    using ascii::space;
    using ascii::space_type;

    typedef
        std::back_insert_iterator<std::string>
        iterator_type;

    ast::program p;
    ast::definition d(ast::variable("x"),
                      ast::datum(ast::variable("y")));

    p.push_back(d);

    std::string output;
    iterator_type sink(output);
    rose::generator::program<iterator_type, space_type> g;
    karma::generate_delimited(sink, g, space, p);
}

BOOST_AUTO_TEST_SUITE_END()
