#include "rose/parser/intertoken_space.hpp"
#include "rose/parser/impl/expression.ipp"

namespace rose {
namespace parser {

void instantiate_expression() {
    typedef
        std::string::const_iterator
        iterator_type;

    typedef
        intertoken_space<iterator_type>
        skipper_type;

    expression<iterator_type, skipper_type> e;
}

}   //  namespace parser
}   //  namespace rose
