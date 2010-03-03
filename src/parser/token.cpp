#include "rose/impl/character.ipp"
#include "rose/impl/token.ipp"

namespace rose {

void instantiate_token() {
    typedef
        std::string::const_iterator
        iterator_type;

    boolean<iterator_type> b;
    character<iterator_type> c;
    string<iterator_type> s;
}

}   //  namespace rose
