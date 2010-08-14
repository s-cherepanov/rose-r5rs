#ifndef __ROSE_GC_REGISTRY_HPP__
#define __ROSE_GC_REGISTRY_HPP__

#include <boost/integer.hpp>

#include <climits>
#include <set>

namespace rose {
namespace gc {

class handle_base;
class object_base;

class registry {
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

    bool is_root_handle(handle_base const* handle) const;

    void mark();

    void sweep();

    void reset();

private:
    handle_registry handle_registry_;
    object_registry object_registry_;

    object_registry::iterator objects_begin() {
        return object_registry_.begin();
    }

    object_registry::const_iterator objects_begin() const {
        return object_registry_.begin();
    }

    handle_registry::iterator handles_begin() {
        return handle_registry_.begin();
    }

    handle_registry::const_iterator handles_begin() const {
        return handle_registry_.begin();
    }

    static address_type h2a(handle_base const* handle) {
        return reinterpret_cast<address_type>(handle);
    }

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

    static bool is_dead_object(address_type address);

    static bool is_dead_handle(address_type address);

    static bool is_alive_object(address_type address);

    static void delete_dead_object(address_type address);

    static void reset_to_death(address_type address);

    address_set find_root_set() const;

    address_set find_member_handles(handle_base const* handle) const;

};  //  class registry

}   //  namespace gc
}   //  namespace rose

#endif  //  __ROSE_GC_REGISTRY_HPP__
