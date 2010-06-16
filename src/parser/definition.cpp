#include "rose/parser/intertoken_space.hpp"
#include "rose/parser/impl/definition.ipp"

namespace rose {
namespace parser {

void instantiate_definition() {
    typedef
        std::string::const_iterator
        iterator_type;

    typedef
        intertoken_space<iterator_type>
        skipper_type;

    definition<iterator_type, skipper_type>();
}

}   //  namespace parser
}   //  namespace rose
