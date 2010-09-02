#include "rose/datum_evaluator.hpp"

#include <boost/bind.hpp>
#include <boost/range/algorithm/transform.hpp>

#include <algorithm>
#include <iterator>

namespace rose {

using namespace boost;

datum_evaluator::datum_evaluator(environment_ptr env) :
    evaluator_base(env)
{}

evaluator_base::result_type
    datum_evaluator::operator()(ast_list const& ast) const
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

evaluator_base::result_type
    datum_evaluator::operator()(ast_vector const& ast) const
{
    rs_vector result;
    range::transform(
            ast,
            std::back_inserter(result),
            bind(&eval<ast_datum>, _1, env));

    return make_value(result);
}

template<>
gc::handle<value> eval<ast_datum>(
        ast_datum const& ast, environment_ptr env)
{
    return boost::apply_visitor(datum_evaluator(env), ast);
}

}   //  namespace rose
