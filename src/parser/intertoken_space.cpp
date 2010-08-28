#include "rose/parser/impl/intertoken_space.ipp"

namespace rose {
namespace parser {

void instantiate_intertoken_space() {
    typedef std::string::const_iterator iterator_type;
    intertoken_space<iterator_type> i;
}

}   //  namespace parser
}   //  namespace rose
