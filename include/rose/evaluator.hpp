#ifndef __ROSE_EVALUATOR_HPP__
#define __ROSE_EVALUATOR_HPP__

#include "rose/gc/handle.hpp"
#include "rose/value.hpp"

namespace rose {

struct environment;
typedef boost::shared_ptr<environment> environment_ptr;

class evaluator {
public:
    evaluator(environment_ptr env);

    bool parse(std::string const& source);

    gc::handle<value> eval();

    std::pair<bool, gc::handle<value> >
        operator[](std::string const& var) const;

private:
    environment_ptr env_;
    ast_program ast_;

};  //  class evaluator

}   //  namespace rose

#endif  //  __ROSE_EVALUATOR_HPP__
