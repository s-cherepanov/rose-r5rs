#include "rose/generator/impl/program.ipp"

#include <iterator>

namespace rose {
namespace generator {

namespace ascii = boost::spirit::ascii;

void instantiate_program() {
    using ascii::space_type;

    typedef
        std::back_insert_iterator<std::string>
        iterator_type;

    program<iterator_type, space_type>();
    expression<iterator_type, space_type>();
}

}   //  namespace generator
}   //  namespace rose
