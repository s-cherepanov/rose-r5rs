#include "rose/parser/intertoken_space.hpp"
#include "rose/parser/r5rs_grammar.hpp"
#include "rose/repl.hpp"

#include <boost/format.hpp>
#include <boost/spirit/include/qi.hpp>

#include <algorithm>
#include <iostream>

namespace rose {

namespace qi = boost::spirit::qi;

const std::string default_prompt("rose> ");

struct evaluator : boost::static_visitor<> {
    void operator()(ast::expression& e) const {
        std::cout
            <<  boost::format( "expression: %1%" )
                % "*expression-placeholder*"
            << std::endl;
    }

    void operator()(ast::definition& d) const {
        std::cout
            <<  boost::format("definition: var={%1%}, expr={%2%}")
                % d.var
                % "*expression-placeholder*"
            <<  std::endl;
    }

};  //  struct evaluator

template<typename T>
void evalutate(T& t) {
    boost::apply_visitor(evaluator(), t);
}

void repl() {
    typedef
        std::string::const_iterator
        iterator_type;

    typedef
        rose::parser::intertoken_space<iterator_type>
        skipper_type;

    std::string prompt = default_prompt;
    std::string line;
    std::string source;

    while (std::cout << prompt, std::getline(std::cin, line)) {
        source.append(line);
        iterator_type first = source.begin();
        iterator_type last = source.end();

        typedef
            rose::parser::r5rs_grammar<iterator_type, skipper_type>
            r5rs_grammar;

        r5rs_grammar grammar;
        skipper_type skipper;
        ast::program program;

        bool match = qi::phrase_parse(first,last, grammar, skipper, program);
        bool full_match = match && first == last;

        source.clear();

        if (!full_match) {
            std::cerr << "error" << std::endl;
        }
        else {
            std::for_each(program.begin(), program.end(), &evaluate);
        }
    }
}

}   //  namespace rose
