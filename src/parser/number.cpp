#include "rose/parser/impl/number.ipp"

namespace rose {
namespace parser {

void instantiate_number() {
    typedef std::string::const_iterator iterator_type;
    number<iterator_type>();
}

}   //  namespace parser
}   //  namespace rose
