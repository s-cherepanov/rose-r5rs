#include "rose/generator/impl/token.ipp"

#include <iterator>

namespace rose {
namespace generator {

void instantiate_character() {
    typedef
        std::back_insert_iterator<std::string>
        iterator_type;

    character<iterator_type> c;
    string<iterator_type> s;
}

}   //  namespace generator
}   //  namespace rose
