#ifndef __ROSE_AST_TAGGED_STRING_HPP__
#define __ROSE_AST_TAGGED_STRING_HPP__

#include <string>

namespace rose {

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

}   //  namespace rose

#endif  //  __ROSE_AST_TAGGED_STRING_HPP__
