#include "rose/generator/token.hpp"
#include "rose/value.hpp"

#include <boost/spirit/include/karma.hpp>

namespace rose {

namespace karma = boost::spirit::karma;

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

struct value_printer : boost::static_visitor<std::ostream&> {
    typedef
        karma::ostream_iterator<char>
        output_iterator;

    std::ostream& out;

    value_printer(std::ostream& out) :
        out(out)
    {}

    result_type operator()(bool val) const {
        return out << (val ? "#t" : "#f");
    }

    result_type operator()(char val) const {
        typedef
            generator::character<output_iterator>
            character_generator;

        character_generator g;
        return out << karma::format(g, val);
    }

    result_type operator()(ast_string const& val) const {
        typedef
            generator::string<output_iterator>
            string_generator;

        string_generator g;
        return out << karma::format(g, val);
    }

    template<typename ValueType>
    result_type operator()(ValueType const& val) const {
        return out << val;
    }

};  //  struct value_printer

std::ostream& operator<<(std::ostream& out, gc::handle<value> const& h) {
    return !!h ? boost::apply_visitor(value_printer(out), *h) : out;
}

}   //  namespace rose
