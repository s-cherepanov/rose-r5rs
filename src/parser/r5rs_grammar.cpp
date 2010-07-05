#include "rose/parser/impl/r5rs_grammar.ipp"
#include "rose/parser/intertoken_space.hpp"

namespace rose {
namespace parser {

void instantiate_r5rs_grammar() {
    typedef
        std::string::const_iterator
        iterator_type;

    typedef
        intertoken_space<iterator_type>
        skipper_type;

    r5rs_grammar<iterator_type, skipper_type>();
}

}   //  namespace parser
}   //  namespace rose
