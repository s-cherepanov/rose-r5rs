#include "rose/repl.hpp"

#include <iostream>
#include <stdexcept>

int main( int argc, char** argv ) try {
    rose::repl();
    return 0;
}
catch( std::exception& e ) {
    std::cout << "exception: " << e.what() << std::endl;
}
