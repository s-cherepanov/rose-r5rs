#include "rose/repl.hpp"
#include "rose/ast/expression.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>

int main(int argc, char** argv) try {
    using rose::ast::expression;
    using rose::ast::procedure_call;

    expression add("+");
    expression one(1);
    expression two(2);

    std::vector<expression> args;
    args.push_back(one);
    args.push_back(two);

    procedure_call call(add, args);
    expression e(call);

    rose::repl();
    return 0;
}
catch(std::exception& e) {
    std::cout << "exception: " << e.what() << std::endl;
}
