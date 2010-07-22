#include "rose/parser/impl/expression.ipp"
#include "rose/parser/intertoken_space.hpp"

namespace rose {
namespace parser {

typedef
    std::string::const_iterator
    iterator_type;

typedef
    intertoken_space<iterator_type>
    skipper_type;

typedef
    expression<iterator_type, skipper_type>
    expression_parser;

expression_parser const* instantiate_expression() {
    static expression<iterator_type, skipper_type> e;
    return &e;
}

}   //  namespace parser
}   //  namespace rose
