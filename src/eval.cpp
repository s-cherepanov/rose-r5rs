#include "rose/eval/evaluator.hpp"

namespace rose {

gc::handle<value> evaluate_program(
        ast_program const& program,
        environment_ptr env)
{
    gc::handle<value> return_value;

    try {
        ast_program::const_iterator next;

        for (next = program.begin(); next != program.end(); ++next) {
            return_value = eval(*next, env);
        }
    }
    catch(std::exception& e) {
        std::cout << "repl exception: " << e.what() << std::endl;
    }

    return return_value;
}

}   //  namespace rose
