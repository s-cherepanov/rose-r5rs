#include "rose/gc/registry.hpp"
#include "rose/gc/handle.hpp"
#include "rose/gc/object.hpp"

#include <algorithm>
#include <iterator>
#include <vector>

namespace rose {
namespace gc {

bool registry::is_root_handle(handle_base const* handle) const {
    object_registry::const_iterator it =
        object_registry_.upper_bound(h2a(handle));

    if (object_registry_.begin() == it) {
        return true;
    }

    address_type address = *(--it);
    address_type obj_end = address + a2o(address)->size();
    return h2a(handle) > obj_end;
}

void registry::gc() {
    boost::recursive_mutex::scoped_lock obj_lock(object_registry_mutex_);
    boost::recursive_mutex::scoped_lock handle_lock(handle_registry_mutex_);

    mark();
    sweep();
    reset();
}

void registry::mark() {
    typedef
        std::vector<address_type>
        address_stack;

    // Finds out all the root handles.  Global, static and stack allocated
    // handles are called root handles.  Objects referred by a root handle must
    // be alive (reachable).

    address_stack stack;

    std::remove_copy_if(
            handle_registry_.begin(),
            handle_registry_.end(),
            std::back_inserter(stack),
            is_not_root);

    // Traverses all the handles that are referring to an alive (reachable)
    // object in a depth-frist way, starting from the root handle set.

    while (!stack.empty()) {
        address_type address = stack.back();
        stack.pop_back();

        // Mark an object as alive, and find out all the handles that are its
        // member variable.  All the objects referred by these handles are also
        // alive.  So push these handles onto the stack for further processing.

        a2h(address)->alive(true);
        address_set member_handles = find_member_handles(a2h(address));

        std::remove_copy_if(
                member_handles.begin(),
                member_handles.end(),
                back_inserter(stack),
                is_dead_handle);
    }
}

void registry::sweep() {
    address_set dead_objects;

    std::remove_copy_if(
            object_registry_.begin(),
            object_registry_.end(),
            std::inserter(dead_objects, dead_objects.begin()),
            is_alive_object);

    std::for_each(
            dead_objects.begin(),
            dead_objects.end(),
            delete_dead_object);
}

void registry::reset() {
    std::for_each(
            object_registry_.begin(),
            object_registry_.end(),
            reset_to_death);
}

/**
 * Find out all the handles resides in an object.
 *
 *            Linear address
 *                  |
 *  obj_begin ---->     +-------------------+       +---------------+
 *                  |   | Object A          |   +-->| Object B      |
 *                      |                   |   |   |               |   
 *                  |   | +---------------+ |   |   +---------------+
 *                      | | Handle<T>     +-----+
 *                  |   | +---------------+ |       +---------------+
 *                      |                   |   +-->| Object C      |
 *                  |   | +---------------+ |   |   |               |
 *                      | | Handle<U>     +-----+   +---------------+
 *                  |   | +---------------+ |       
 *                      |                   |       
 *                  |   | +---------------+ |
 *                      | | Other         | |
 *                  |   | +---------------+ |
 *                      +-------------------+
 *  obj_end   ----> |
 *                  V
 */
registry::address_set
    registry::find_member_handles(handle_base const* handle) const
{
    address_set result;
    address_type obj_begin = o2a(handle->get());
    address_type obj_end = obj_begin + handle->size();

    std::copy(
            handle_registry_.lower_bound(obj_begin),
            handle_registry_.upper_bound(obj_end),
            std::inserter(result, result.begin()));

    return result;
}

bool registry::is_not_root(address_type address) {
    return !(a2h(address)->is_root());
}

bool registry::is_dead_handle(address_type address) {
    return !a2h(address)->alive();
}

bool registry::is_alive_object(address_type address) {
    return a2o(address)->alive();
}

void registry::delete_dead_object(address_type address) {
    if (!is_alive_object(address)) {
        delete a2o(address);
    }
}

void registry::reset_to_death(address_type address) {
    a2o(address)->alive(false);
}

}   //  namespace gc
}   //  namespace rose
