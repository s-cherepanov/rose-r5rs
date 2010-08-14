#ifndef __ROSE_GC_REGISTRY_HPP__
#define __ROSE_GC_REGISTRY_HPP__

#include <boost/integer.hpp>
#include <boost/noncopyable.hpp>

#include <climits>
#include <iostream>
#include <set>

namespace rose {
namespace gc {

class handle_base;
class object_base;

class registry : private boost::noncopyable {
public:
    typedef
        boost::uint_t<sizeof(void*) * CHAR_BIT>::exact
        address_type;

    typedef
        std::set<address_type>
        handle_registry;

    typedef
        std::set<address_type>
        object_registry;

    typedef
        std::set<address_type>
        address_set;

    static registry& instance() {
        static registry one;
        return one;
    }

    ~registry() {
        gc();
    }

    void register_handle(handle_base const* handle) {
        handle_registry_.insert(h2a(handle));
    }

    void erase_handle(handle_base const* handle) {
        handle_registry_.erase(h2a(handle));
    }

    void register_object(object_base const* obj) {
        object_registry_.insert(o2a(obj));
    }

    void erase_object(object_base const* obj) {
        object_registry_.erase(o2a(obj));
    }

    /// Whether a handle is a root handle.
    bool is_root_handle(handle_base const* handle) const;

    void gc();

private:
    handle_registry handle_registry_;
    object_registry object_registry_;

    address_set find_member_handles(handle_base const* handle) const;

    static address_type h2a(handle_base const* handle) {
        return reinterpret_cast<address_type>(handle);
    }

    /// Marks all alive (reachable) objects.
    void mark();

    /// Sweeps out all dead (unreachable) objects.
    void sweep();

    /// Marks all objects as dead (unreachable).
    void reset();

    static handle_base* a2h(address_type address) {
        return reinterpret_cast<handle_base*>(address);
    }

    static address_type o2a(object_base const* obj) {
        return reinterpret_cast<address_type>(obj);
    }

    static object_base* a2o(address_type address) {
        return reinterpret_cast<object_base*>(address);
    }

    static bool is_not_root(registry::address_type address);

    static bool is_dead_handle(address_type address);

    static bool is_alive_object(address_type address);

    static void delete_dead_object(address_type address);

    static void reset_to_death(address_type address);

};  //  class registry

}   //  namespace gc
}   //  namespace rose

#endif  //  __ROSE_GC_REGISTRY_HPP__
