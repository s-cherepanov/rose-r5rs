#include "rose/r5rs_lexer.hpp"
#include "rose/r5rs_grammar.hpp"

#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/program_options.hpp>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>

namespace lex = boost::spirit::lex;
namespace qi = boost::spirit::qi;
namespace mpl = boost::mpl;

using namespace boost::filesystem;
using namespace boost::program_options;

std::string load_file( std::string const& filename ) {
    std::ifstream in( filename.c_str() );
    if( !in ) {
        throw std::runtime_error( "cannot open file " + filename );
    }

    in.unsetf( std::ios::skipws );
    return std::string(
            std::istreambuf_iterator<char>( in.rdbuf() ),
            std::istreambuf_iterator<char>() );
}

void parse() {
    typedef
        lex::lexertl::token<
            std::string::iterator,
            mpl::vector<>
        >
        token_type;

    typedef
        lex::lexertl::actor_lexer<token_type>
        lexer_type;

    typedef
        rose::r5rs_tokens<lexer_type>
        r5rs_tokens;

    rose::r5rs_tokens<lexer_type> tokens;
    std::string str( load_file( "r5rs_lexer_test.input" ) );
    std::string::iterator first = str.begin();
    std::string::iterator last = str.end();

    typedef
        r5rs_tokens::iterator_type
        token_iterator_type;

    token_iterator_type begin = tokens.begin( first, last );
    token_iterator_type end = tokens.end();

    typedef
        rose::r5rs_grammar<token_iterator_type, r5rs_tokens::lexer_def>
        r5rs_grammar;

    r5rs_grammar grammar( tokens );
    bool result = phrase_parse(
            begin,
            end,
            grammar,
            qi::in_state( "WS" )[ tokens.self ] );

    if( result && first == last ) {
        std::cout << "ok" << std::endl;
    }
    else {
        std::cout
            << boost::format( "error: -->%1%<--" )
               % std::string( first, str.end() )
            << std::endl;
    }
}

int main( int argc, char** argv ) try {
    std::string working_dir;

    options_description cmdline_desc( "Available command line options" );
    cmdline_desc.add_options()
        ( "working-dir,w",
          value( &working_dir ),
          "Specify the working direcotory." )
        ;

    variables_map cmdline_vm;
    store( parse_command_line( argc, argv, cmdline_desc ), cmdline_vm );
    notify( cmdline_vm );

    if( cmdline_vm.count( "working-dir" ) ) {
        current_path( path( working_dir ) );
    }

    parse();

    return 0;
}
catch( std::exception& e ) {
    std::cout << "exception: " << e.what() << std::endl;
}
