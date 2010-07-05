#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>

std::string read_from_stream( std::istream& in );

std::string load_file( std::string const& filename ) {
    std::ifstream in( filename.c_str() );
    if( !in ) {
        throw std::runtime_error( "cannot open file " + filename );
    }

    return read_from_stream( in );
}

std::string read_from_stream( std::istream& in ) {
    in.unsetf( std::ios::skipws );
    return std::string(
            std::istreambuf_iterator<char>( in.rdbuf() ),
            std::istreambuf_iterator<char>() );
}
