#include "rose/parser/impl/identifier.ipp"

namespace rose {
namespace parser {

void instantiate_identifier() {
    typedef
        std::string::const_iterator
        iterator_type;

    identifier<iterator_type>();
}

}   //  namespace parser
}   //  namespace rose
