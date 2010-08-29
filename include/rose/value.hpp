#ifndef __ROSE_VALUE_HPP__
#define __ROSE_VALUE_HPP__

#include "rose/ast/program.hpp"
#include "rose/gc/handle.hpp"

#include <boost/function.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/variant.hpp>

#include <utility>
#include <vector>

namespace rose {

struct pair;
struct vector;
struct procedure;
struct native_procedure;

typedef
    boost::variant<
        bool,
        int,
        char,
        ast_string,
        ast_symbol,
        boost::recursive_wrapper<pair>,
        boost::recursive_wrapper<vector>,
        boost::recursive_wrapper<procedure>,
        boost::recursive_wrapper<native_procedure>
    >
    value;

struct pair : std::pair<gc::handle<value>, gc::handle<value> > {
    typedef gc::handle<value> value_type;

    typedef std::pair<value_type, value_type> base_type;

    pair() {}

    pair(value_type const& first) :
        base_type(first, value_type())
    {}

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

    std::pair<std::size_t, bool> arity() const;

    ast_lambda_expression ast;
    environment_ptr env;

};  //  struct procedure

struct native_procedure {
    typedef
        boost::function<
            gc::handle<value>(arguments_type, gc::handle<value>)
        >
        procedure_fn;

    native_procedure(
            std::size_t min_arity,
            bool with_rest,
            procedure_fn const& procedure,
            environment_ptr env);

    std::pair<std::size_t, bool> arity() const;

    std::pair<std::size_t, bool> arity_;
    procedure_fn procedure;
    environment_ptr env;

};  //  struct native_procedure

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

std::ostream& operator<<(std::ostream& out, native_procedure const& p);

std::ostream& operator<<(std::ostream& out, gc::handle<value> const& handle);

template<typename InputIterator>
gc::handle<value> make_list(InputIterator first, InputIterator last) {
    BOOST_STATIC_ASSERT((
            boost::is_same<
                typename InputIterator::value_type,
                gc::handle<value>
            >::value));

    typedef gc::handle<value> result_type;

    result_type result = make_value(pair());

    InputIterator next = first;
    result_type last_one = result;

    set_car(result, *next);

    while (last != ++next) {
        pair p;
        p.first = *next;
        set_cdr(last_one, make_value(p));
        last_one = cdr(last_one);
    }

    return result;
}

}   //  namespace rose

#endif  //  __ROSE_VALUE_HPP__
