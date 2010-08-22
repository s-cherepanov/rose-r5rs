#include "rose/value.hpp"

namespace rose {


gc::handle<value> nil() {
    static gc::handle<value> n;
    return n;
}

gc::handle<value> car(gc::handle<value> p) {
    return (boost::get<pair>(*p)).first;
}

gc::handle<value> cdr(gc::handle<value> p) {
    return (boost::get<pair>(*p)).second;
}

void set_car(
        gc::handle<value> p, gc::handle<value> val)
{
    (boost::get<pair>(*p)).first = val;
}

void set_cdr(
        gc::handle<value> p, gc::handle<value> val)
{
    (boost::get<pair>(*p)).second = val;
}

bool is_pair(gc::handle<value> val) {
    return !!boost::get<pair>(&(*val));
}

void print_cdr(std::ostream& out, gc::handle<value> p) {
    if (p == nil()) {
        return;
    }

    if (is_pair(p)) {
        pair const& cdr(handle_cast<pair>(p));
        out << " " << *(cdr.first);
        print_cdr(out, cdr.second);
    }
    else {
        out << " . " << *(p);
    }
}

std::ostream& operator<<(
        std::ostream& out, pair const& p)
{
    if (p.first == nil() && p.second == nil()) {
        return out << "()";
    }

    out << '(' << *(p.first);
    print_cdr(out, p.second);
    return out << ')';
}

std::ostream& operator<<(std::ostream& out, vector const& v) {
    if (v.empty()) {
        return out << "#()";
    }

    vector::const_iterator it = v.begin();
    out << "#(" << *(*it++);

    for (; it != v.end(); ++it) {
        out << ' ' << **it;
    }

    return out << ')';
}

std::ostream& operator<<(std::ostream& out, gc::handle<value> const& handle) {
    if (!!handle) {
        return out << (*handle);
    }
    else {
        return out;
    }
}

}   //  namespace rose
