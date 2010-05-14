#ifndef __ROSE_AST_DATUM_HPP__
#define __ROSE_AST_DATUM_HPP__

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>

#include <list>
#include <string>
#include <vector>

namespace rose {
namespace ast {

struct list;
struct vector;

template<typename Tag>
struct tagged_string : public std::string {
    typedef Tag tag;

    tagged_string() :
        std::string()
    {}

    tagged_string(std::string const& s) :
        std::string(s)
    {}

    tagged_string& operator=(std::string const& that) {
        if (this != &that) {
            *static_cast<std::string*>(this) = that;
        }

        return *this;
    }

};  //  struct tagged_string

struct string_tag {};
struct identifier_tag {};
struct symbol_tag {};

typedef tagged_string<string_tag> string;
typedef tagged_string<identifier_tag> identifier;
typedef tagged_string<symbol_tag> symbol;

typedef
    boost::variant<
        bool, int, char, string, identifier, symbol,
        boost::recursive_wrapper<list>,
        boost::recursive_wrapper<vector>
    >
    datum;

struct list {
    std::list<datum> value;

    void push_back(datum const& d) {
        value.push_back(d);
    }

};

struct vector {
    std::vector<datum> value;

    void push_back(datum const& d) {
        value.push_back(d);
    }

};

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
