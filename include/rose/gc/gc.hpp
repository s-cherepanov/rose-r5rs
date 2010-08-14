#ifndef __ROSE_GC_GC_HPP__
#define __ROSE_GC_GC_HPP__

#include "rose/gc/registry.hpp"

namespace rose {
namespace gc {

inline void force_gc() {
    registry::instance().gc();
}

}   //  namespace gc
}   //  namespace rose

#endif  //  __ROSE_GC_GC_HPP__
