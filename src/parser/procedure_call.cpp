#include "rose/parser/impl/expression.ipp"
#include "rose/parser/impl/procedure_call.ipp"
#include "rose/parser/intertoken_space.hpp"

namespace rose {
namespace parser {

void instantiate_procedure_call() {
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
        procedure_call<iterator_type, skipper_type>
        procedure_call_parser;

    expression_parser e;
    procedure_call_parser p(&e);
}

}   //  namespace parser
}   //  namespace rose
