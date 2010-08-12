#include "rose/gc/object.hpp"
#include "rose/gc/registry.hpp"

namespace rose {
namespace gc {

object_base::object_base() :
    alive_(false)
{
    registry::instance().register_object(this);
}

object_base::~object_base() {
    registry::instance().erase_object(this);
}

}   //  namespace gc
}   //  namespace rose
