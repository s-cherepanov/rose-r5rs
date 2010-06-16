#ifndef __ROSE_AST_PAIR_HPP__
#define __ROSE_AST_PAIR_HPP__

#include "rose/ast/datum.hpp"

#include <boost/shared_ptr.hpp>

namespace rose {
namespace ast {

typedef boost::shared_ptr<datum> datum_ptr;

typedef std::pair<datum_ptr, datum_ptr> pair;

typedef boost::shared_ptr<pair> pair_ptr;

}   //  namespace ast
}   //  namespace rose

#endif  //  __ROSE_AST_PAIR_HPP__
