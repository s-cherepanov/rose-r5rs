#include "rose/gc/registry.hpp"
#include "rose/gc/handle.hpp"
#include "rose/gc/object.hpp"

#include <algorithm>
#include <deque>
#include <iterator>

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

void registry::mark() {
    typedef
        std::deque<address_type>
        address_stack;

    address_stack stack;

    address_set root_set = find_root_set();
    std::copy(
            root_set.begin(),
            root_set.end(),
            std::front_inserter(stack));

    while (!stack.empty()) {
        address_type address = stack.front();
        stack.pop_front();

        a2h(address)->alive(true);
        address_set member_handles = find_member_handles(a2h(address));

        std::remove_copy_if(
                member_handles.begin(),
                member_handles.end(),
                front_inserter(stack),
                is_dead_handle);
    }
}

bool registry::is_dead_handle(address_type address) {
    return !a2h(address)->alive();
}

void registry::sweep() {
    address_set dead_objects;

    std::remove_copy_if(
            instance().object_registry_.begin(),
            instance().object_registry_.end(),
            std::inserter(dead_objects, dead_objects.begin()),
            is_dead_object);

    std::for_each(
            dead_objects.begin(),
            dead_objects.end(),
            delete_dead_object);
}

bool registry::is_dead_object(address_type address) {
    return !(a2o(address)->alive());
}

void registry::delete_dead_object(address_type address) {
    delete a2o(address);
}

void registry::reset() {
    std::for_each(
            instance().object_registry_.begin(),
            instance().object_registry_.end(),
            reset_to_death);
}

void registry::reset_to_death(address_type address) {
    a2o(address)->alive(false);
}

registry::address_set registry::find_root_set() const {
    address_set result;

    std::remove_copy_if(
            registry::instance().handle_registry_.begin(),
            registry::instance().handle_registry_.end(),
            std::inserter(result, result.begin()),
            is_not_root);

    return result;
}

bool registry::is_not_root(address_type address) {
    return !(a2h(address)->is_root());
}

}   //  namespace gc
}   //  namespace rose
