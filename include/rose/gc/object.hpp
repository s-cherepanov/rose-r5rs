#ifndef __ROSE_GC_OBJECT_HPP__
#define __ROSE_GC_OBJECT_HPP__

#include "rose/gc/registry.hpp"

#include <cstddef>

namespace rose {
namespace gc {

class object_base {
    friend class registry;

public:
    object_base() :
        alive_(false)
    {
        registry::instance().register_object(this);
    }

    bool alive() const {
        return alive_;
    }

    void alive(bool value) {
        alive_ = value;
    }

    virtual std::size_t size() const = 0;

protected:
    virtual ~object_base() {
        registry::instance().erase_object(this);
    }

private:
    bool alive_;

};  //  class object_base

template<typename Target>
class object : public object_base {
public:
    object() :
        target_()
    {}

    explicit object(Target const& target) :
        target_(target)
    {}

    virtual ~object() {
    }

    virtual std::size_t size() const {
        return sizeof(object<Target>);
    }

    Target& target() {
        return target_;
    }

    Target const& target() const {
        return target_;
    }

private:
    Target target_;

};  //  class object

}   //  namespace gc
}   //  namespace rose

#endif  //  __ROSE_GC_OBJECT_HPP__
