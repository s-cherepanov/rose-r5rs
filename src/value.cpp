#include "rose/generator/token.hpp"
#include "rose/value.hpp"

#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>

#include <iterator>
#include <string>

namespace rose {

gc::handle<value> nil() {
    static gc::handle<value> n;
    return n;
}

gc::handle<value> car(gc::handle<value> p) {
    return (boost::get<pair>(*p)).first;
}

gc::handle<value> cdr(gc::handle<value> p) {
    return (boost::get<pair>(*p)).second;
}

void set_car(
        gc::handle<value> p, gc::handle<value> val)
{
    (boost::get<pair>(*p)).first = val;
}

void set_cdr(
        gc::handle<value> p, gc::handle<value> val)
{
    (boost::get<pair>(*p)).second = val;
}

bool is_pair(gc::handle<value> val) {
    return !!boost::get<pair>(&(*val));
}

void print_cdr(std::ostream& out, gc::handle<value> p) {
    if (p == nil()) {
        return;
    }

    if (is_pair(p)) {
        pair const& cdr(handle_cast<pair>(p));
        out << " " << cdr.first;
        print_cdr(out, cdr.second);
    }
    else {
        out << " . " << *(p);
    }
}

std::ostream& operator<<(
        std::ostream& out, pair const& p)
{
    if (p.first == nil() && p.second == nil()) {
        return out << "()";
    }

    out << '(' << p.first;
    print_cdr(out, p.second);
    return out << ')';
}

std::ostream& operator<<(std::ostream& out, vector const& v) {
    if (v.empty()) {
        return out << "#()";
    }

    vector::const_iterator it = v.begin();
    out << "#(" << *it++;

    for (; it != v.end(); ++it) {
        out << ' ' << *it;
    }

    return out << ')';
}

namespace karma = boost::spirit::karma;

struct value_printer : boost::static_visitor<> {
    typedef
        std::back_insert_iterator<std::string>
        output_iterator;

    typedef
        boost::spirit::ascii::space_type
        delimiter_type;

    std::ostream& out;

    value_printer(std::ostream& out) :
        out(out)
    {}

    void operator()(bool val) const {
        out << (val ? "#t" : "#f");
    }

    void operator()(char val) const {
        typedef
            generator::character<output_iterator, delimiter_type>
            character_generator;

        std::string output;
        std::back_insert_iterator<std::string> sink(output);
        character_generator generator;

        karma::generate_delimited(
                sink, generator, delimiter_type(), val);

        out << output;
    }

    void operator()(ast_string const& val) const {
        typedef
            generator::string<output_iterator, delimiter_type>
            string_generator;

        std::string output;
        std::back_insert_iterator<std::string> sink(output);
        string_generator generator;

        karma::generate_delimited(
                sink, generator, delimiter_type(), val);

        out << output;
    }

    template<typename ValueType>
    void operator()(ValueType const& val) const {
        out << val;
    }

};  //  struct value_printer

std::ostream& operator<<(std::ostream& out, gc::handle<value> const& handle) {
    if (!!handle) {
        boost::apply_visitor(value_printer(out), *handle);
    }

    return out;
}

}   //  namespace rose
