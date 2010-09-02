#ifndef __ROSE_DETAIL_EVAL_DATUM_HPP__
#define __ROSE_DETAIL_EVAL_DATUM_HPP__

#include "rose/environment.hpp"
#include "rose/eval.hpp"
#include "rose/gc/handle.hpp"
#include "rose/value.hpp"

#include <boost/variant.hpp>

namespace rose {

template<>
struct eval_visitor<ast_datum> : eval_base {
    eval_visitor(environment_ptr env);

    result_type operator()(ast_list const& ast) const;

    result_type operator()(ast_vector const& ast) const;

    template<typename Ast>
    result_type operator()(Ast const& ast) const {
        return make_value(ast);
    }

};  //  struct eval_visitor<ast_datum>

}   //  namespace rose

#endif  //  __ROSE_DETAIL_EVAL_DATUM_HPP__
