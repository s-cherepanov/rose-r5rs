#ifndef __ROSE_AST_DATUM_HPP__
#define __ROSE_AST_DATUM_HPP__

#include "rose/ast/tagged_string.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/optional.hpp>
#include <boost/variant.hpp>

#include <iostream>
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

    container_type proper;
    boost::optional<ast_datum> improper;

    bool operator==(ast_list const& rhs) const {
        return proper == rhs.proper && improper == rhs.improper;
    }

};  //  struct ast_list

struct ast_vector : std::vector<ast_datum> {};

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
    (rose::ast_list::container_type, proper)
    (boost::optional<rose::ast_datum>, improper)
)

#endif  //  __ROSE_AST_DATUM_HPP__
