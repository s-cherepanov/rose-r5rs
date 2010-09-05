#include "rose/environment.hpp"
#include "rose/generator/token.hpp"
#include "rose/value.hpp"

#include <boost/spirit/include/karma.hpp>

namespace rose {

namespace karma = boost::spirit::karma;

rs_procedure::rs_procedure(
        ast_lambda_expression const& ast,
        environment_ptr parent)
:
    ast(ast),
    env(new environment(parent)),
    arity_(ast.formals.formal_args.size(), !!ast.formals.formal_rest)
{}

arity_info const& rs_procedure::arity() const {
    return arity_;
}

rs_native_procedure::rs_native_procedure(
        arity_info const& arity,
        procedure_fn const& procedure,
        environment_ptr parent)
:
    procedure(procedure),
    env(new environment(parent)),
    arity_(arity)
{}

arity_info const& rs_native_procedure::arity() const {
    return arity_;
}

gc::handle<value> nil() {
    static gc::handle<value> n(make_value(rs_nil()));
    return n;
}

bool is_nil(gc::handle<value> val) {
    return !!val ? (!!handle_cast<rs_nil>(&val)) : false;
}

gc::handle<value> none() {
    static gc::handle<value> n;
    return n;
}

bool is_none(gc::handle<value> val) {
    return !val;
}

gc::handle<value> car(gc::handle<value> p) {
    return (boost::get<rs_pair>(*p)).first;
}

gc::handle<value> cdr(gc::handle<value> p) {
    return (boost::get<rs_pair>(*p)).second;
}

void set_car(gc::handle<value> p, gc::handle<value> val) {
    (boost::get<rs_pair>(*p)).first = val;
}

void set_cdr(gc::handle<value> p, gc::handle<value> val) {
    (boost::get<rs_pair>(*p)).second = val;
}

bool is_pair(gc::handle<value> val) {
    return !!boost::get<rs_pair>(&(*val));
}

std::ostream& operator<<(std::ostream& out, rs_nil const&) {
    return out << "()";
}

void print_cdr(std::ostream& out, gc::handle<value> val) {
    if (is_pair(val)) {
        rs_pair const& p(handle_cast<rs_pair>(val));
        out << " " << p.first;
        print_cdr(out, p.second);
    }
    else if (!is_nil(val)) {
        out << " . " << *(val);
    }
}

std::ostream& operator<<(std::ostream& out, rs_pair const& p) {
    out << '(' << p.first;
    print_cdr(out, p.second);
    return out << ')';
}

std::ostream& operator<<(std::ostream& out, rs_vector const& v) {
    if (v.empty()) {
        return out << "#()";
    }

    rs_vector::const_iterator it = v.begin();
    out << "#(" << *it++;

    for (; it != v.end(); ++it) {
        out << ' ' << *it;
    }

    return out << ')';
}

std::ostream& operator<<(std::ostream& out, rs_procedure const& p) {
    return out << "#<procedure>";
}

std::ostream& operator<<(std::ostream& out, rs_native_procedure const& p) {
    return out << "#<native-procedure>";
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

    result_type operator()(rs_string const& val) const {
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
    return (is_nil(h)) ?
        out << "()" :
        boost::apply_visitor(value_printer(out), *h);
}

}   //  namespace rose
