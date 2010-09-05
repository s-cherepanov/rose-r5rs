#include "rose/detail/eval.hpp"
#include "rose/environment.hpp"
#include "rose/evaluator.hpp"
#include "rose/parser/intertoken_space.hpp"
#include "rose/parser/program.hpp"
#include "rose/base.hpp"

#include <boost/spirit/include/qi.hpp>

namespace rose {

namespace qi = boost::spirit::qi;

evaluator::evaluator() :
    env_(init_env())
{}

evaluator::evaluator(environment_ptr env) :
    env_(env)
{}

bool evaluator::parse(std::string const& source, ast_program& ast) {
    typedef
        std::string::const_iterator
        iterator_type;

    iterator_type first = source.begin();
    iterator_type last = source.end();

    typedef
        rose::parser::intertoken_space<iterator_type>
        skipper_type;

    typedef
        rose::parser::program<iterator_type, skipper_type>
        parser_type;

    parser_type parser;
    skipper_type skipper;

    bool match = qi::phrase_parse(first, last, parser, skipper, ast);
    return match && first == last;
}

gc::handle<value> evaluator::eval(std::string const& source) {
    ast_program ast;
    return parse(source, ast) ? detail::eval(ast, env_) : none();
}

gc::handle<value> evaluator::operator[](std::string const& var) const {
    return env_->lookup(var);
}

}   //  namespace rose
