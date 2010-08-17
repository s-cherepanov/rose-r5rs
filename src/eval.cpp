#include "rose/eval/evaluator.hpp"

#include <algorithm>
#include <functional>

namespace rose {

struct evaluate_one :
    std::binary_function<
        ast_command_or_definition,
        environment_ptr,
        void
    >
{
    mutable gc::handle<value> result;

    void operator()(
            ast_command_or_definition const& ast,
            environment_ptr env) const
    {
        result = eval(ast, env);
    }

};  //  struct evaluate_one

gc::handle<value> evaluate_program(
        ast_program const& program,
        environment_ptr env)
{
    gc::handle<value> return_value;
    evaluate_one eval;

    try {
        std::for_each(
                program.begin(),
                program.end(),
                std::bind2nd(eval, env));
    }
    catch(std::exception& e) {
        std::cout << "repl exception: " << e.what() << std::endl;
    }

    return eval.result;
}

}   //  namespace rose
