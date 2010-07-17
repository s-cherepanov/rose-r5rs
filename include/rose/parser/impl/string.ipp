#ifndef __ROSE_PARSER_IMPL_STRING_IPP__
#define __ROSE_PARSER_IMPL_STRING_IPP__

#include "rose/parser/string.hpp"

#include <boost/spirit/include/phoenix_operator.hpp>

namespace rose {
namespace parser {

namespace ascii = boost::spirit::ascii;
namespace qi = boost::spirit::qi;

template<typename Iterator>
string<Iterator>::string() :
    string::base_type(start)
{
    using ascii::graph;
    using ascii::space;
    using qi::attr;
    using qi::char_;
    using qi::lit;

    start
        =   '"' >> *(string_element - '"') >> '"'
        ;

    string_element
        =   ((graph | space) - char_("\"\\"))
        |   lit("\\\"") >> attr('"')
        |   lit("\\\\") >> attr('\\')
        |   lit("\\n")  >> attr('\n')
        |   lit("\\t")  >> attr('\t')
        ;
}

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_PARSER_IMPL_STRING_IPP__

// vim:ft=cpp et
