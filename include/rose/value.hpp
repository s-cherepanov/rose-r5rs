#ifndef __ROSE_VALUE_HPP__
#define __ROSE_VALUE_HPP__

#include "rose/ast/program.hpp"
#include "rose/gc/handle.hpp"

#include <boost/variant.hpp>

#include <utility>
#include <vector>

namespace rose {

struct pair;
struct vector;
struct procedure;

typedef
    boost::variant<
        bool,
        int,
        char,
        ast_string,
        ast_symbol,
        boost::recursive_wrapper<pair>,
        boost::recursive_wrapper<vector>,
        boost::recursive_wrapper<procedure>
    >
    value;

struct pair : std::pair<gc::handle<value>, gc::handle<value> > {
    typedef gc::handle<value> value_type;

    typedef std::pair<value_type, value_type> base_type;

    pair() {}

    pair(value_type const& first, value_type const& second) :
        base_type(first, second)
    {}

};  //  struct pair

struct environment;

typedef boost::shared_ptr<environment> environment_ptr;

typedef std::vector<gc::handle<value> > arguments_type;

struct procedure {
    procedure(
            ast_lambda_expression const& ast,
            environment_ptr parent);

    gc::handle<value> apply(
            arguments_type const& args,
            arguments_type const& rest_args);

    ast_lambda_expression ast;
    environment_ptr env;

};  //  struct procedure

gc::handle<value> nil();

gc::handle<value> car(gc::handle<value> p);

gc::handle<value> cdr(gc::handle<value> p);

void set_car(gc::handle<value> p, gc::handle<value> val);

void set_cdr(gc::handle<value> p, gc::handle<value> val);

template<typename ValueType>
gc::handle<value> make_value(ValueType const& val) {
    return gc::handle<value>(new gc::object<value>(value(val)));
}

bool is_pair(gc::handle<value> val);

template<typename ValueType>
ValueType& handle_cast(gc::handle<value>& val) {
    return boost::get<ValueType>(*val);
}

template<typename ValueType>
ValueType const& handle_cast(gc::handle<value> const& val) {
    return boost::get<ValueType>(*val);
}

template<typename ValueType>
ValueType* handle_cast(gc::handle<value>* val) {
    return boost::get<ValueType>(&(*val));
}

template<typename ValueType>
ValueType const* handle_cast(gc::handle<value> const* val) {
    return boost::get<ValueType>(&(*val));
}

std::ostream& operator<<(std::ostream& out, pair const& p);

struct vector :
    std::vector<gc::handle<value> >
{};

std::ostream& operator<<(std::ostream& out, vector const& v);

std::ostream& operator<<(std::ostream& out, procedure const& p);

std::ostream& operator<<(std::ostream& out, gc::handle<value> const& handle);

}   //  namespace rose

#endif  //  __ROSE_VALUE_HPP__
