#include "rose/intertoken_space.hpp"
#include "rose/impl/datum.ipp"

namespace rose {

void instantiate_datum() {
    typedef
        std::string::const_iterator
        iterator_type;

    typedef
        intertoken_space<iterator_type>
        skipper_type;

    datum<iterator_type, skipper_type> d;
}

}   //  namespace rose
