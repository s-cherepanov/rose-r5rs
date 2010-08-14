#ifndef __ROSE_GC_HANDLE_HPP__
#define __ROSE_GC_HANDLE_HPP__

#include "rose/gc/gc.hpp"
#include "rose/gc/object.hpp"
#include "rose/gc/registry.hpp"

#include <boost/logic/tribool.hpp>
#include <boost/static_assert.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace rose {
namespace gc {

class handle_base {
    friend class registry;

public:
    handle_base(object_base* obj) :
        object_(obj),
        is_root_(boost::indeterminate)
    {
        registry::instance().register_handle(this);
    }

    handle_base(handle_base const& rhs) :
        object_(rhs.object_)
    {}

    ~handle_base() {
        registry::instance().erase_handle(this);
        object_ = 0;
    }

    bool operator==(handle_base const& rhs) {
        return object_ == rhs.object_;
    }

protected:
    void copy(handle_base const& rhs) {
        object_ = rhs.object_;
    }

    object_base* get() {
        return object_;
    }

    object_base const* get() const {
        return object_;
    }

    bool is_root() const {
        boost::recursive_mutex::scoped_lock lock(is_root_mutex_);

        if (boost::indeterminate(is_root_)) {
            is_root_ = registry::instance().is_root_handle(this);
        }

        return is_root_;
    }

    bool alive() const {
        return !!object_ ? object_->alive() : false;
    }

    void alive(bool value) {
        if (object_) {
            object_->alive(value);
        }
    }

    std::size_t size() const {
        return !!object_ ? object_->size() : 0u;
    }

private:
    object_base* object_;

    mutable boost::recursive_mutex is_root_mutex_;
    mutable boost::tribool is_root_;

    void* operator new(std::size_t);
    void operator delete(void*);

};  //  class handle_base

namespace {

struct dummy {
    void nonnull() {}
};

typedef void (dummy::*safe_bool)();

}   //  anonymous namespace

template<typename Target>
class handle : public handle_base {
public:
    handle() :
        handle_base(0)
    {}

    handle(object<Target>* obj) :
        handle_base(obj)
    {}

    handle(handle const& rhs) :
        handle_base(rhs)
    {}

    handle& operator=(handle const& rhs) {
        if (*this == rhs) {
            return *this;
        }

        handle_base::copy(rhs);
        return *this;
    }

    Target& operator*() {
        typedef object<Target>* object_ptr;
        return static_cast<object_ptr>(get())->target();
    }

    Target const& operator*() const {
        typedef object<Target>* object_ptr;
        return static_cast<object_ptr>(get())->target();
    }

    Target* operator->() {
        return !!get() ? &(this->operator*()) : 0;
    }

    Target const* operator->() const {
        return !!get() ? &(this->operator*()) : 0;
    }

    bool operator!() const {
        return !!get();
    }

    operator safe_bool() const {
        return !!get() ? &dummy::nonnull : 0;
    }

    template<typename Other>
    operator handle<Other>() const {
        typedef
            boost::is_convertible<Target, Other>
            is_convertible;

        BOOST_STATIC_ASSERT(is_convertible::value);

        return handle<Other>(
                static_cast<object<Other>*>(
                    const_cast<object_base*>(get())));
    }

};  //  class handle

}   //  namespace gc
}   //  namespace rose

#endif  //  __ROSE_GC_HANDLE_HPP__
