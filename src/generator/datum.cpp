#include "rose/generator/impl/datum.ipp"

#include <iterator>

namespace rose {
namespace generator {

namespace ascii = boost::spirit::ascii;

void instantiate_datum() {
    using ascii::space_type;

    typedef
        std::back_insert_iterator<std::string>
        iterator_type;

    datum<iterator_type, space_type> d;
}

}   //  namespace generator
}   //  namespace rose
