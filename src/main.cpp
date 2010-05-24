#include "rose/repl.hpp"
#include "rose/ast/expression.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>

int main(int argc, char** argv) try {
    rose::repl();
    return 0;
}
catch(std::exception& e) {
    std::cout << "exception: " << e.what() << std::endl;
}
