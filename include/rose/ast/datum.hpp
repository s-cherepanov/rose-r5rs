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
namespace ast {

struct string_tag     {};
struct identifier_tag {};
struct symbol_tag     {};
struct variable_tag   {};

typedef tagged_string<string_tag>     string;
typedef tagged_string<identifier_tag> identifier;
typedef tagged_string<symbol_tag>     symbol;
typedef tagged_string<variable_tag>   variable;

struct list;
struct vector;

typedef
    boost::variant<
        bool, int, char,
        string, symbol, identifier, variable,
        boost::recursive_wrapper<list>,
        boost::recursive_wrapper<vector>
    >
    datum;

struct list {
    typedef std::list<datum> impl_type;

    typedef impl_type::iterator iterator;

    typedef impl_type::const_iterator const_iterator;

    impl_type proper;

    boost::optional<datum> improper;

    bool operator==(list const& rhs) const {
        return proper == rhs.proper && improper == rhs.improper;
    }

};  //  struct list

struct vector : std::vector<datum> {};

}   //  namespace ast
}   //  namespace rose

namespace boost {

template<typename T>
inline T get(rose::ast::list const& v) {
    typedef std::list<rose::ast::datum> base_type;
    return boost::get<T>(static_cast<base_type>(v));
}

template<typename T>
inline T get(rose::ast::vector const& v) {
    typedef std::vector<rose::ast::datum> base_type;
    return boost::get<T>(static_cast<base_type>(v));
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

BOOST_FUSION_ADAPT_STRUCT(
    rose::ast::list,
    (rose::ast::list::impl_type, proper)
    (boost::optional<rose::ast::datum>, improper)
)

#endif  //  __ROSE_AST_DATUM_HPP__
