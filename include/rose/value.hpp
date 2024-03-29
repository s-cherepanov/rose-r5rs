#ifndef __ROSE_VALUE_HPP__
#define __ROSE_VALUE_HPP__

#include "rose/ast.hpp"
#include "rose/exception.hpp"
#include "rose/gc/handle.hpp"

#include <boost/function.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/variant.hpp>

#include <utility>
#include <vector>

namespace rose {

typedef ast_string rs_string;
typedef ast_symbol rs_symbol;

struct rs_nil;
struct rs_pair;
struct rs_vector;
struct rs_procedure;
struct rs_native_procedure;

typedef
    boost::variant<
        rs_nil,
        bool,
        int,
        char,
        rs_string,
        rs_symbol,
        boost::recursive_wrapper<rs_pair>,
        boost::recursive_wrapper<rs_vector>,
        boost::recursive_wrapper<rs_procedure>,
        boost::recursive_wrapper<rs_native_procedure>
    >
    value;

struct rs_nil {
    bool operator==(rs_nil const&) const {
        return true;
    }

};  //  struct rs_nil

std::ostream& operator<<(std::ostream& out, rs_nil const&);

gc::handle<value> nil();

bool is_nil(gc::handle<value> val);

gc::handle<value> none();

bool is_none(gc::handle<value> val);

struct rs_pair : std::pair<gc::handle<value>, gc::handle<value> > {
    typedef gc::handle<value> value_type;

    typedef std::pair<value_type, value_type> base_type;

    rs_pair() :
        base_type(nil(), nil())
    {}

    rs_pair(value_type const& first) :
        base_type(first, nil())
    {}

    rs_pair(value_type const& first, value_type const& second) :
        base_type(first, second)
    {}

};  //  struct rs_pair

std::ostream& operator<<(std::ostream& out, rs_pair const& p);

class environment;
typedef boost::shared_ptr<environment> environment_ptr;

typedef std::vector<gc::handle<value> > arguments_type;

struct arity_info {
    arity_info(std::size_t required = 0u, bool has_rest = false) :
        required(required),
        has_rest(has_rest)
    {}

    std::size_t required;
    bool has_rest;

};  //  struct arity_info

class rs_procedure {
public:
    rs_procedure(
            ast_lambda_expression const& ast,
            environment_ptr parent);

    arity_info const& arity() const;

    ast_lambda_expression ast;
    environment_ptr env;

private:
    arity_info arity_;

};  //  struct procedure

std::ostream& operator<<(std::ostream& out, rs_procedure const& p);

typedef
    boost::function<
        gc::handle<value>(arguments_type, gc::handle<value>)
    >
    procedure_fn;

class rs_native_procedure {
public:
    rs_native_procedure(
            std::string const& name,
            arity_info const& airty,
            procedure_fn const& procedure,
            environment_ptr parent);

    arity_info const& arity() const;

    std::string name;
    procedure_fn procedure;
    environment_ptr env;

private:
    arity_info arity_;

};  //  struct native_procedure

std::ostream& operator<<(std::ostream& out, rs_native_procedure const& p);

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
    return boost::get<ValueType>(&(**val));
}

template<typename ValueType>
ValueType const* handle_cast(gc::handle<value> const* val) {
    return boost::get<ValueType>(&(**val));
}

template<typename ValueType>
ValueType& ensure_handle_cast(gc::handle<value>& val) {
    ValueType* result = handle_cast<ValueType>(&val);

    if (!result) {
        BOOST_THROW_EXCEPTION(
                type_error()
                << errinfo_expected_type(typeid(ValueType).name()));
    }

    return *result;
}

template<typename ValueType>
ValueType const& ensure_handle_cast(gc::handle<value> const& val) {
    ValueType const* result = handle_cast<ValueType>(&val);

    if (!result) {
        BOOST_THROW_EXCEPTION(
                type_error()
                << errinfo_expected_type(typeid(ValueType).name()));
    }

    return *result;
}

template<typename ValueType>
ValueType* ensure_handle_cast(gc::handle<value>* val) {
    ValueType* result = handle_cast<ValueType>(val);

    if (!result) {
        BOOST_THROW_EXCEPTION(
                type_error()
                << errinfo_expected_type(typeid(ValueType).name()));
    }

    return result;
}

template<typename ValueType>
ValueType const* ensure_handle_cast(gc::handle<value> const* val) {
    ValueType const* result = handle_cast<ValueType>(val);

    if (!result) {
        BOOST_THROW_EXCEPTION(
                type_error()
                << errinfo_expected_type(typeid(ValueType).name()));
    }

    return result;
}

struct rs_vector :
    std::vector<gc::handle<value> >
{};

std::ostream& operator<<(std::ostream& out, rs_vector const& v);

std::ostream& operator<<(std::ostream& out, gc::handle<value> const& handle);

template<typename InputIterator>
gc::handle<value> make_list(InputIterator begin, InputIterator end) {
    BOOST_STATIC_ASSERT((
            boost::is_same<
                typename InputIterator::value_type,
                gc::handle<value>
            >::value));

    if (0u == std::distance(begin, end)) {
        return nil();
    }

    typedef gc::handle<value> result_type;

    result_type result = make_value(rs_pair());
    result_type last = result;
    InputIterator next = begin;

    set_car(result, *next);

    while (end != ++next) {
        rs_pair p;
        p.first = *next;
        set_cdr(last, make_value(p));
        last = cdr(last);
    }

    cdr(last) = nil();
    return result;
}

template<typename Range>
gc::handle<value>make_list(Range const& range) {
    return make_list(boost::begin(range), boost::end(range));
}

}   //  namespace rose

#endif  //  __ROSE_VALUE_HPP__
