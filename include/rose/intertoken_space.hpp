#ifndef __ROSE_INTERTOKEN_SPACE_HPP__
#define __ROSE_INTERTOKEN_SPACE_HPP__

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/repository/include/qi_confix.hpp>

namespace rose {

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace repository = boost::spirit::repository;

template<typename Iterator>
struct intertoken_space : qi::grammar<Iterator> {
    intertoken_space() :
        intertoken_space::base_type( start )
    {
        using ascii::char_;
        using ascii::alpha;
        using qi::eol;

        start
            =   +atmosphere
            ;

        atmosphere
            =   whitespace | comment
            ;

        whitespace
            =   char_( " \n" )
            ;

        comment
            =   ';' >> *( char_ - eol ) >> eol
            ;

        start       .name( "intertoken_space" );
        atmosphere  .name( "atmosphere" );
        whitespace  .name( "whitespace" );
        comment     .name( "comment" );

        qi::debug( start );
        qi::debug( atmosphere );
        qi::debug( whitespace );
        qi::debug( comment );
    }

    qi::rule<Iterator> start;
    qi::rule<Iterator> atmosphere;
    qi::rule<Iterator> whitespace;
    qi::rule<Iterator> comment;

};  //  struct intertoken_space

}   //  namespace rose

#endif  //  __ROSE_INTERTOKEN_SPACE_HPP__
