#include "rose/parser/impl/program.ipp"
#include "rose/parser/intertoken_space.hpp"

namespace rose {
namespace parser {

void instantiate_r5rs_grammar() {
    typedef
        std::string::const_iterator
        iterator_type;

    typedef
        intertoken_space<iterator_type>
        skipper_type;

    program<iterator_type, skipper_type> p;
}

}   //  namespace parser
}   //  namespace rose
