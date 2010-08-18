#include "rose/eval/evaluator.hpp"

#include <boost/bind.hpp>

#include <algorithm>

namespace rose {

void evaluate_one(
        ast_command_or_definition const& ast,
        environment_ptr env,
        gc::handle<value>& result)
{
    result = eval(ast, env);
}

gc::handle<value> evaluate_program(
        ast_program const& program, environment_ptr env)
{
    using namespace boost;

    gc::handle<value> result;

    try {
        std::for_each(program.begin(), program.end(),
                bind(&evaluate_one, _1, env, ref(result)));
    }
    catch(std::exception& e) {
        std::cout << "repl-exception: " << e.what() << std::endl;
    }

    return result;
}

}   //  namespace rose
