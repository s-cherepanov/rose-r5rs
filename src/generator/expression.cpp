#include "rose/generator/impl/expression.ipp"

#include <iterator>

namespace rose {
namespace generator {

namespace ascii = boost::spirit::ascii;

void instantiate_expression() {
    using ascii::space_type;

    typedef
        std::back_insert_iterator<std::string>
        iterator_type;

    expression<iterator_type, space_type> e;
}

}   //  namespace generator
}   //  namespace rose
