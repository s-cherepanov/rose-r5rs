#include "rose/impl/intertoken_space.ipp"

namespace rose {

void instantiate_intertoken_space() {
    typedef std::string::const_iterator iterator_type;
    intertoken_space<iterator_type> space;
}

}   //  namespace rose
