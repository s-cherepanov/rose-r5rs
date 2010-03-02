#include "rose/intertoken_space.hpp"
#include "rose/impl/r5rs_grammar.ipp"

namespace rose {

void instantiate_r5rs_grammar() {
    typedef
        std::string::const_iterator
        iterator_type;

    typedef
        intertoken_space<iterator_type>
        skipper_type;

    r5rs_grammar<iterator_type, skipper_type> grammar;
}

}   //  namespace rose
