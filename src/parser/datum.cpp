#include "rose/parser/intertoken_space.hpp"
#include "rose/parser/impl/datum.ipp"

namespace rose {
namespace parser {

void instantiate_datum() {
    typedef
        std::string::const_iterator
        iterator_type;

    typedef
        intertoken_space<iterator_type>
        skipper_type;

    datum<iterator_type, skipper_type> d;
}

}   //  namespace parser
}   //  namespace rose
