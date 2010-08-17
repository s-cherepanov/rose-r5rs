#include "rose/eval/evaluator.hpp"

namespace rose {

environment_ptr build_initial_env() {
    return environment_ptr(new environment);
}

gc::handle<value> evaluate_program(ast_program const& program) {
    typedef
        command_or_definition_evaluator
        evaluator_type;

    gc::handle<value> return_value;

    try {
        ast_program::const_iterator next = program.begin();
        for (next = program.begin(); next != program.end(); ++next) {
            return_value = eval(*next, build_initial_env());
        }
    }
    catch(std::exception& e) {
        std::cout << "repl exception: " << e.what() << std::endl;
    }

    return return_value;
}

}   //  namespace rose
