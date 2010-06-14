#include "rose/parser/impl/boolean.ipp"
#include "rose/parser/impl/character.ipp"
#include "rose/parser/impl/string.ipp"
#include "rose/parser/impl/token.ipp"
#include "rose/parser/intertoken_space.hpp"

namespace rose {
namespace parser {

void instantiate_token() {
    typedef
        std::string::const_iterator
        iterator_type;

    typedef
        rose::parser::intertoken_space<iterator_type>
        skipper_type;

    rose::parser::boolean<iterator_type>();
    rose::parser::character<iterator_type>();
    rose::parser::string<iterator_type>();
    rose::parser::token<iterator_type, skipper_type>();
}

}   //  namespace parser
}   //  namespace rose
