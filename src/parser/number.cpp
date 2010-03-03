#include "rose/impl/number.ipp"

namespace rose {

void instantiate_number() {
    typedef std::string::const_iterator iterator_type;
    number<iterator_type> n;
}

}   //  namespace rose
