#ifndef __ROSE_AST_PAIR_HPP__
#define __ROSE_AST_PAIR_HPP__

#include "rose/ast/datum.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/shared_ptr.hpp>

namespace rose {
namespace ast {

struct pair {
    typedef datum value_type;

    pair() :
        head(), tail()
    {}

    pair(pair const& that) :
        head(that.head),
        tail(that.tail)
    {}

    pair(datum const& head) :
        head(new datum(head)),
        tail()
    {}

    pair(datum const& head, datum const& tail) :
        head(new datum(head)),
        tail(new datum(tail))
    {}

    boost::shared_ptr<datum> head;

    boost::shared_ptr<datum> tail;

    bool operator==(pair const& rhs) const {
        return *head == *(rhs.head) && *tail == *(rhs.tail);
    }

    // TODO: Provide push_back/insert/end

};  //  struct pair

}   //  namespace ast
}   //  namespace rose

#endif  //  __ROSE_AST_PAIR_HPP__
