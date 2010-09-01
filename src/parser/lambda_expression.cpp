#include "rose/parser/impl/expression.ipp"
#include "rose/parser/impl/lambda_expression.ipp"
#include "rose/parser/intertoken_space.hpp"

namespace rose {
namespace parser {

void instantiate_lambda_expression() {
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
        lambda_expression<iterator_type, skipper_type>
        lambda_expression_parser;

    expression_parser e;
    lambda_expression_parser l(&e);
}

}   //  namespace parser
}   //  namespace rose
