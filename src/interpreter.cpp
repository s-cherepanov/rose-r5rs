#include "rose/environment.hpp"
#include "rose/evaluator.hpp"
#include "rose/interpreter.hpp"
#include "rose/parser/intertoken_space.hpp"
#include "rose/parser/program.hpp"

#include <boost/spirit/include/qi.hpp>

namespace rose {

namespace qi = boost::spirit::qi;

interpreter::interpreter(environment_ptr env) :
    env_(env)
{}

bool interpreter::parse(std::string const& source) {
    typedef
        std::string::const_iterator
        iterator_type;

    typedef
        rose::parser::intertoken_space<iterator_type>
        skipper_type;

    iterator_type first = source.begin();
    iterator_type last = source.end();

    typedef
        rose::parser::program<iterator_type, skipper_type>
        parser_type;

    parser_type parser;
    skipper_type skipper;

    bool match = qi::phrase_parse(first, last, parser, skipper, ast_);
    return match && first == last;
}

gc::handle<value> interpreter::eval() {
    return rose::eval(ast_, env_);
}

std::pair<bool, gc::handle<value> >
    interpreter::operator[](std::string const& var) const
{
    return env_->lookup(var);
}

}   //  namespace rose
