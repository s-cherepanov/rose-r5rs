#ifndef __ROSE_AST_PAIR_HPP__
#define __ROSE_AST_PAIR_HPP__

#include "rose/ast/datum.hpp"

#include <boost/shared_ptr.hpp>

namespace rose {
namespace ast {

typedef boost::shared_ptr<datum> datum_ptr;
 
typedef std::pair<datum_ptr, datum_ptr> pair;

typedef boost::shared_ptr<pair> pair_ptr;

inline pair_ptr new_pair() {
    return pair_ptr(new pair);
}

inline pair_ptr new_pair(datum const& car) {
    pair_ptr p(new pair);
    p->first.reset(new datum(car));
    return p;
}

inline pair_ptr new_pair(datum const& car, datum const& cdr) {
    pair_ptr p(new pair);
    p->first.reset(new datum(car));
    p->second.reset(new datum(cdr));
    return p;
}

}   //  namespace ast
}   //  namespace rose

#endif  //  __ROSE_AST_PAIR_HPP__
