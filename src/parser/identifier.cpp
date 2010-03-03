#include "rose/impl/identifier.ipp"

namespace rose {

void instantiate_identifier() {
    typedef std::string::const_iterator iterator_type;
    identifier<iterator_type> i;
}

}   //  namespace rose
