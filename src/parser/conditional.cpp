#include "rose/parser/expression.hpp"
#include "rose/parser/impl/conditional.ipp"
#include "rose/parser/intertoken_space.hpp"

namespace rose {
namespace parser {

void instantiate_conditional() {
    typedef
        std::string::const_iterator
        iterator_type;

    typedef
        intertoken_space<iterator_type>
        skipper_type;

    typedef
        expression<iterator_type, skipper_type>
        expression_parser;

    typedef
        conditional<iterator_type, skipper_type>
        conditional_parser;

    expression_parser const* instantiate_expression();

    conditional_parser d(instantiate_expression());
}

}   //  namespace parser
}   //  namespace rose
