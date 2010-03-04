#include "rose/intertoken_space.hpp"
#include "rose/impl/expression.ipp"

namespace rose {

void instantiate_expression() {
    typedef
        std::string::const_iterator
        iterator_type;

    typedef
        intertoken_space<iterator_type>
        skipper_type;

    expression<iterator_type, skipper_type> e;
}

}   //  namespace rose
