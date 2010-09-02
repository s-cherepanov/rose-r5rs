#include "rose/detail/eval.hpp"

#include <boost/bind.hpp>
#include <boost/circular_buffer.hpp>
#include <boost/range/algorithm/transform.hpp>

#include <algorithm>

namespace rose {
namespace detail {

template<>
gc::handle<value> eval<ast_program>(
        ast_program const& program, environment_ptr env)
{
    using namespace boost;

    circular_buffer<gc::handle<value> > result(1);

    // try {
        range::transform(
                program,
                std::back_inserter(result),
                bind(&eval<ast_command_or_definition>, _1, env));
    /*}
    catch(std::exception& e) {
        std::cout << "repl-exception: " << e.what() << std::endl;
    }*/

    return result.size() ? result[0] : none();
}

}   //  namespace detail
}   //  namespace rose