#include "rose/parser/impl/character.ipp"
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

    rose::parser::token<iterator_type, skipper_type> t;
    rose::parser::character<iterator_type> c;
}

}   //  namespace parser
}   //  namespace rose
