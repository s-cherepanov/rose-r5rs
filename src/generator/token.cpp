#include "rose/generator/impl/token.ipp"

#include <iterator>

namespace rose {
namespace generator {

namespace ascii = boost::spirit::ascii;

void instantiate_token() {
    using ascii::space_type;

    {
        typedef
            std::back_insert_iterator<std::string>
            iterator_type;

        boolean<iterator_type> b;
        number<iterator_type> n;
        character<iterator_type> c;
        string<iterator_type> s;
    }

    {
        typedef
            karma::ostream_iterator<char>
            iterator_type;

        boolean<iterator_type> b;
        number<iterator_type> n;
        character<iterator_type> c;
        string<iterator_type> s;
    }
}

}   //  namespace generator
}   //  namespace rose
