#include "rose/impl/character.ipp"
#include "rose/impl/token.ipp"
#include "rose/intertoken_space.hpp"

namespace rose {

void instantiate_token() {
    typedef
        std::string::const_iterator
        iterator_type;

    typedef
        rose::intertoken_space<iterator_type>
        skipper_type;

    rose::token<iterator_type, skipper_type> t;
    rose::character<iterator_type> c;
}

}   //  namespace rose
