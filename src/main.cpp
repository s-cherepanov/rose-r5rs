#include "rose/intertoken_space.hpp"
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

namespace qi = boost::spirit::qi;
namespace mpl = boost::mpl;
namespace ascii = boost::spirit::ascii;

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

int main( int argc, char** argv ) try {
    std::string working_dir;
    std::string file;

    options_description cmdline_desc( "Available command line options" );
    cmdline_desc.add_options()
        ( "working-dir,w",
          value( &working_dir ),
          "Specify the working direcotory." )

        ( "input,i",
          value( &file ),
          "Input file." )
        ;

    variables_map cmdline_vm;
    store( parse_command_line( argc, argv, cmdline_desc ), cmdline_vm );
    notify( cmdline_vm );

    if( cmdline_vm.count( "working-dir" ) ) {
        current_path( path( working_dir ) );
    }

    std::string str( load_file( file ) );
    std::string::const_iterator first = str.begin();
    std::string::const_iterator last = str.end();

    typedef
        std::string::const_iterator
        iterator_type;

    typedef
        rose::intertoken_space<iterator_type>
        skipper_type;

    rose::r5rs_grammar<iterator_type, skipper_type> grammar;
    skipper_type skipper;
    bool result = phrase_parse( first, last, grammar, skipper );

    if( result && first == last ) {
        std::cout << "ok" << std::endl;
    }
    else {
        std::cout
            << boost::format( "error: -->%1%<--" )
               % std::string( first, last )
            << std::endl;
    }

    return 0;
}
catch( std::exception& e ) {
    std::cout << "exception: " << e.what() << std::endl;
}
