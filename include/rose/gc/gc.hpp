#ifndef __ROSE_GC_GC_HPP__
#define __ROSE_GC_GC_HPP__

#include "rose/gc/registry.hpp"

namespace rose {
namespace gc {

inline void force_gc() {
    registry::instance().mark();
    registry::instance().sweep();
    registry::instance().reset();
}

}   //  namespace gc
}   //  namespace rose

#endif  //  __ROSE_GC_GC_HPP__
