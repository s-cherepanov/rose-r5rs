#include "rose/generator/token.hpp"
#include "rose/parser/intertoken_space.hpp"
#include "rose/parser/r5rs_grammar.hpp"
#include "rose/repl.hpp"

#include <boost/format.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>

#include <algorithm>
#include <iostream>
#include <stdexcept>

namespace rose {

namespace qi = boost::spirit::qi;

const std::string default_prompt("rose> ");

struct eval_datum : boost::static_visitor<std::string> {
    template<typename Type>
    std::string operator()(Type&) const {
        return "{D}";
    }

    std::string operator()(bool& v) const {
        return v ? "{b}#t" : "{b}#f";
    }

    std::string operator()(int& v) const {
        std::ostringstream oss;
        oss << "{n}" << v;
        return oss.str();
    }

    std::string operator()(char& v) const {
        namespace karma = boost::spirit::karma;

        typedef
            std::back_insert_iterator<std::string>
            iterator_type;

        std::string output;
        iterator_type sink(output);
        rose::generator::character<iterator_type> g;
        karma::generate(sink, g, v);

        return "{c}" + output;
    }

    std::string operator()(ast::string& v) const {
        namespace karma = boost::spirit::karma;

        typedef
            std::back_insert_iterator<std::string>
            iterator_type;

        std::string output;
        iterator_type sink(output);
        rose::generator::string<iterator_type> g;
        karma::generate(sink, g, v);

        return "{S}" + output;
    }

    std::string operator()(ast::identifier& v) const {
        return "{i}" + v;
    }

    std::string operator()(ast::symbol& v) const {
        return "{s}" + v;
    }

    std::string operator()(ast::variable& v) const {
        return "{v}" + v;
    }

};  //  struct eval_datum

struct eval_expression : boost::static_visitor<std::string> {
    template<typename Type>
    std::string operator()(Type&) const {
        return "{E}";
    }

    std::string operator()(ast::datum& v) const {
        return boost::apply_visitor(eval_datum(), v);
    }

    std::string operator()(ast::quotation& v) const {
        std::ostringstream oss;
        oss << boost::format("{Q}(quote %1%)")
               % boost::apply_visitor(eval_datum(), v.quoted);
        return oss.str();
    }

    std::string operator()(ast::conditional& v) const {
        std::ostringstream oss;

        if (v.alternate) {
            oss << boost::format("{C}(if %1% %2% %3%)")
                   % boost::apply_visitor(eval_expression(), v.test)
                   % boost::apply_visitor(eval_expression(), v.consequent)
                   % boost::apply_visitor(eval_expression(), *v.alternate);
        }
        else {
            oss << boost::format("{C}(if %1% %2%)")
                   % boost::apply_visitor(eval_expression(), v.test)
                   % boost::apply_visitor(eval_expression(), v.consequent);
        }

        return oss.str();
    }

    std::string operator()(ast::assignment& v) const {
        std::ostringstream oss;
        oss << boost::format("{A}(set! {v}%1% %2%)")
               % v.var
               % boost::apply_visitor(eval_expression(), v.expr);
        return oss.str();
    }

};  //  struct eval_expression

struct evaluator : boost::static_visitor<std::string> {
    std::string operator()(ast::expression& v) const {
        return boost::apply_visitor(eval_expression(), v);
    }

    std::string operator()(ast::definition& v) const {
        std::ostringstream oss;
        oss << boost::format("{D}(define {v}%1% %2%)")
               % v.var
               % boost::apply_visitor(eval_expression(), v.expr);
        return oss.str();
    }

};  //  struct evaluator

void evaluate(ast::command_or_definition& v) {
    std::cout << boost::apply_visitor(evaluator(), v) << std::endl;
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
