#ifndef __ROSE_AST_DATUM_HPP__
#define __ROSE_AST_DATUM_HPP__

#include "rose/ast/tagged_string.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/optional.hpp>
#include <boost/variant.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <vector>

namespace rose {

struct string_tag     {};
struct identifier_tag {};
struct symbol_tag     {};
struct variable_tag   {};

typedef tagged_string<string_tag>     ast_string;
typedef tagged_string<identifier_tag> ast_identifier;
typedef tagged_string<symbol_tag>     ast_symbol;
typedef tagged_string<variable_tag>   ast_variable;

struct ast_list;
struct ast_vector;

typedef
    boost::variant<
        bool,
        int,
        char,
        ast_string,
        ast_symbol,
        boost::recursive_wrapper<ast_list>,
        boost::recursive_wrapper<ast_vector>
    >
    ast_datum;

struct ast_list {
    typedef std::vector<ast_datum> container_type;
    typedef container_type::iterator iterator;
    typedef container_type::const_iterator const_iterator;

    container_type elements;
    boost::optional<ast_datum> dotted_element;

    bool operator==(ast_list const& rhs) const {
        return elements == rhs.elements &&
            dotted_element == rhs.dotted_element;
    }

};  //  struct ast_list

inline std::ostream& operator<<(std::ostream& out, ast_list const& list) {
    out << '(';
    std::copy(list.elements.begin(),
              list.elements.end(),
              std::ostream_iterator<ast_datum>(out, " "));

    if (list.dotted_element) {
        out << ". " << *(list.dotted_element);
    }

    return out << ')';
}

struct ast_vector : std::vector<ast_datum> {};

inline std::ostream& operator<<(std::ostream& out, ast_vector const& vec) {
    out << "#(";
    std::copy(vec.begin(), vec.end(),
              std::ostream_iterator<ast_datum>(out, " "));
    return out << ')';
}

}   //  namespace rose

namespace boost {

template<typename T>
inline T get(rose::ast_list const& v) {
    typedef std::list<rose::ast_datum> base_type;
    return boost::get<T>(static_cast<base_type>(v));
}

template<typename T>
inline T get(rose::ast_vector const& v) {
    typedef std::vector<rose::ast_datum> base_type;
    return boost::get<T>(static_cast<base_type>(v));
}

namespace spirit {
namespace traits {

template<typename T>
struct not_is_variant;

template<>
struct not_is_variant<rose::ast_list> : mpl::false_ {};

template<>
struct not_is_variant<rose::ast_vector> : mpl::false_ {};

}   //  namespace traits
}   //  namespace spirit
}   //  namespace boost

BOOST_FUSION_ADAPT_STRUCT(
    rose::ast_list,
    (rose::ast_list::container_type, elements)
    (boost::optional<rose::ast_datum>, dotted_element))

#endif  //  __ROSE_AST_DATUM_HPP__
