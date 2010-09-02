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

    bool parse(std::string const& source);

    gc::handle<value> eval();

    gc::handle<value> eval(std::string const& source);

    template<typename ValueType>
    ValueType& eval_to();

    template<typename ValueType>
    ValueType& eval_to(std::string const& source);

    gc::handle<value> operator[](std::string const& var) const;

private:
    environment_ptr env_;
    ast_program ast_;
    gc::handle<value> last_result_;

};  //  class evaluator

template<typename ValueType>
inline ValueType& evaluator::eval_to() {
    eval();
    return handle_cast<ValueType>(last_result_);
}

template<typename ValueType>
inline ValueType& evaluator::eval_to(std::string const& source) {
    eval(source);
    return handle_cast<ValueType>(last_result_);
}

}   //  namespace rose

#endif  //  __ROSE_EVALUATOR_HPP__
