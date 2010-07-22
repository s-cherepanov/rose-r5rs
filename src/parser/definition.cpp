#include "rose/parser/expression.hpp"
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

    expression_parser const* instantiate_expression();

    lambda_expression_parser l(instantiate_expression());
}

}   //  namespace parser
}   //  namespace rose
