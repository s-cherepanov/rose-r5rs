#ifndef __ROSE_EVAL_DATUM_EVALUATOR_HPP__
#define __ROSE_EVAL_DATUM_EVALUATOR_HPP__

#include "rose/environment.hpp"
#include "rose/evaluator.hpp"
#include "rose/gc/handle.hpp"
#include "rose/value.hpp"

#include <boost/variant.hpp>

namespace rose {

template<>
gc::handle<value> eval<ast_datum>(
        ast_datum const& ast, environment_ptr env);

struct datum_evaluator : evaluator_base {
    datum_evaluator(environment_ptr env);

    result_type operator()(ast_list const& ast) const;

    result_type operator()(ast_vector const& ast) const;

    template<typename Ast>
    result_type operator()(Ast const& ast) const {
        return make_value(ast);
    }

};  //  struct datum_evaluator

}   //  namespace rose

#endif  //  __ROSE_EVAL_DATUM_EVALUATOR_HPP__
