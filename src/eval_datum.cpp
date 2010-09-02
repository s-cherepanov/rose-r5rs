#include "rose/detail/eval.hpp"
#include "rose/environment.hpp"

#include <boost/bind.hpp>
#include <boost/range/algorithm/transform.hpp>

#include <algorithm>
#include <iterator>

namespace rose {
namespace detail {

using namespace boost;

eval_visitor<ast_datum>::eval_visitor(environment_ptr env) :
    eval_base(env)
{}

eval_base::result_type
    eval_visitor<ast_datum>::operator()(ast_list const& ast) const
{
    result_type result;

    if (ast.elements.empty()) {
        return result;
    }

    ast_list::const_iterator next = ast.elements.begin();
    result = make_value(rs_pair());
    result_type last = result;

    set_car(result, eval(*next, env));

    while (ast.elements.end() != ++next) {
        rs_pair p;
        p.first = eval(*next, env);
        set_cdr(last, make_value(p));
        last = cdr(last);
    }

    if (!!ast.dotted_element) {
        set_cdr(last, eval(*(ast.dotted_element), env));
    }

    return result;
}

eval_base::result_type
    eval_visitor<ast_datum>::operator()(ast_vector const& ast) const
{
    rs_vector result;
    range::transform(
            ast,
            std::back_inserter(result),
            bind(&eval<ast_datum>, _1, env));

    return make_value(result);
}

}   //  namespace detail
}   //  namespace rose
