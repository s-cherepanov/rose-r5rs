#include "rose/generator/impl/token.ipp"

#include <iterator>

namespace rose {
namespace generator {

namespace ascii = boost::spirit::ascii;

void instantiate_character() {
    using ascii::space_type;

    typedef
        std::back_insert_iterator<std::string>
        iterator_type;

    boolean<iterator_type, space_type>();
    number<iterator_type, space_type>();
    character<iterator_type, space_type>();
    string<iterator_type, space_type>();
}

}   //  namespace generator
}   //  namespace rose
