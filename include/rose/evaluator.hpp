#ifndef __ROSE_EVALUATOR_HPP__
#define __ROSE_EVALUATOR_HPP__

#include "rose/gc/handle.hpp"
#include "rose/value.hpp"

namespace rose {

struct environment;
typedef boost::shared_ptr<environment> environment_ptr;

class evaluator {
public:
    evaluator();

    evaluator(environment_ptr env);

    gc::handle<value> eval(std::string const& source);

    template<typename ValueType>
    ValueType eval_to(std::string const& source);

    gc::handle<value> operator[](std::string const& var) const;

private:
    bool parse(std::string const& source, ast_program& ast);

    environment_ptr env_;

};  //  class evaluator

template<typename ValueType>
inline ValueType evaluator::eval_to(std::string const& source) {
    return handle_cast<ValueType>(eval(source));
}

}   //  namespace rose

#endif  //  __ROSE_EVALUATOR_HPP__
