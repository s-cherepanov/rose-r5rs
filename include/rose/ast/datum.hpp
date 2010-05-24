#ifndef __ROSE_AST_DATUM_HPP__
#define __ROSE_AST_DATUM_HPP__

#include "rose/ast/tagged_string.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>

#include <iostream>
#include <list>
#include <string>
#include <vector>

namespace rose {
namespace ast {

struct list;
struct vector;

struct string_tag     {};
struct identifier_tag {};
struct symbol_tag     {};

typedef tagged_string<string_tag>     string;
typedef tagged_string<identifier_tag> identifier;
typedef tagged_string<symbol_tag>     symbol;

typedef
    boost::variant<
        bool, int, char, string, identifier, symbol,
        boost::recursive_wrapper<list>,
        boost::recursive_wrapper<vector>
    >
    datum;

template<typename Container>
struct container {
    typedef Container container_type;

    typedef typename container_type::value_type value_type; 

    typedef typename container_type::iterator iterator;

    typedef typename container_type::const_iterator const_iterator;

    typedef container<container_type> this_type;

    void push_back(value_type const& d) {
        value.push_back(d);
    }

    bool operator==(this_type const& rhs) const {
        return value == rhs.value;
    }

    container_type value;

};  //  struct container

struct list : public container<std::list<datum> > {};

struct vector : public container<std::vector<datum> > {};

}   //  namespace ast
}   //  namespace rose

namespace boost {

template<typename T>
inline T get(rose::ast::list const& l) {
    return boost::get<T>(l.value);
}

template<typename T>
inline T get(rose::ast::vector const& v) {
    return boost::get<T>(v.value);
}

namespace spirit {
namespace traits {

template<typename T>
struct not_is_variant;

template<>
struct not_is_variant<rose::ast::list> : mpl::false_ {};

template<>
struct not_is_variant<rose::ast::vector> : mpl::false_ {};

}   //  namespace traits
}   //  namespace spirit
}   //  namespace boost

#endif  //  __ROSE_AST_DATUM_HPP__
