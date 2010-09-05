#include "rose/detail/eval.hpp"
#include "rose/environment.hpp"
#include "rose/exception.hpp"

#include <boost/bind.hpp>
#include <boost/circular_buffer.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/range/algorithm/transform.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>

namespace rose {
namespace detail {

eval_visitor<ast_expression>::eval_visitor(environment_ptr env) :
    eval_base(env)
{}

eval_base::result_type
    eval_visitor<ast_expression>::operator()(ast_variable const& ast) const
{
    result_type result = env->lookup(ast);
    if (!result) {
        BOOST_THROW_EXCEPTION(
                undefined_variable()
                << errinfo_variable_name(ast));
    }

    return result;
}

eval_base::result_type
    eval_visitor<ast_expression>::operator()(ast_quotation const& ast) const
{
    return eval(ast.quoted, env);
}

eval_base::result_type
    eval_visitor<ast_expression>::operator()(ast_lambda_expression const& ast) const
{
    return make_value(rs_procedure(ast, env));
}

struct proc_application : boost::static_visitor<gc::handle<value> > {
    proc_application(arguments_type const& args) :
        args(args)
    {}

    result_type operator()(rs_procedure const& proc) const {
        using namespace boost;

        check_arity(proc);

        ast_formal_args const& formal_args = proc.ast.formals.formal_args;

        proc.env->clear();
        range::transform(
                formal_args,
                args,
                std::inserter(*proc.env, proc.env->begin()),
                &std::make_pair<ast_variable, gc::handle<value> >);

        if (proc.arity().has_rest) {
            gc::handle<value> rest_list = make_list(
                    args.begin() + proc.arity().required, args.end());
            proc.env->define(*proc.ast.formals.formal_rest, rest_list);
        }

        range::for_each(
                proc.ast.body.definitions,
                bind(eval<ast_definition>, _1, proc.env));

        circular_buffer<gc::handle<value> > result(1);

        range::transform(
                proc.ast.body.sequence,
                std::back_inserter(result),
                bind(&eval<ast_expression>, _1, proc.env));

        return result.size() ? result[0] : none();
    }

    result_type operator()(rs_native_procedure const& proc) const {
        check_arity(proc);

        arguments_type::const_iterator
            rest_begin = args.begin() + proc.arity().required,
            rest_end = args.end();

        arguments_type formal_args;
        std::copy(args.begin(), rest_begin, std::back_inserter(formal_args));

        gc::handle<value> rest_list(nil());
        if (proc.arity().has_rest) {
            rest_list = make_list(rest_begin, rest_end);
        }

        return proc.procedure(formal_args, rest_list);
    }

    template<typename ValueType>
    result_type operator()(ValueType const& val) const {
        BOOST_THROW_EXCEPTION(wrong_type_to_apply());
        return none();
    }

    template<typename Procedure>
    void check_arity(Procedure const& p) const {
        if (args.size() < p.arity().required ||
                (args.size() > p.arity().required &&
                 !p.arity().has_rest))
        {
            BOOST_THROW_EXCEPTION(
                    arity_mismatch()
                    << errinfo_required_arg_num(p.arity().required)
                    << errinfo_has_rest(p.arity().has_rest)
                    << errinfo_actual_arg_num(args.size()));
        }
    }

    arguments_type args;

};  //  struct apply_visitor

gc::handle<value> apply(
        gc::handle<value> operator_,
        arguments_type const& args)
{
    return boost::apply_visitor(proc_application(args), *operator_);
}

gc::handle<value> apply(gc::handle<value> operator_) {
    arguments_type args;
    return apply(operator_, args);
}

eval_base::result_type
    eval_visitor<ast_expression>::operator()(ast_procedure_call const& ast) const
{
    using namespace boost;

    result_type operator_ = eval(ast.procedure, env);
    std::vector<result_type> args;

    range::transform(
            ast.arguments,
            std::back_inserter(args),
            bind(&eval<ast_expression>, _1, env));

    return apply(operator_, args);
}

eval_base::result_type
    eval_visitor<ast_expression>::operator()(ast_conditional const& ast) const
{
    result_type test = eval(ast.test, env);

    if (is_true(*test)) {
        return eval(ast.consequent, env);
    }

    return (!!ast.alternate) ? eval(*ast.alternate, env) : none();
}

eval_base::result_type
    eval_visitor<ast_expression>::operator()(ast_assignment const& ast) const
{
    env->assign(ast.variable, eval(ast.expression, env));
    return none();
}

bool eval_visitor<ast_expression>::is_true(value const& val) const {
    // Any Scheme value other than #f can be implicitly converted to #t.
    bool const* ptr = boost::get<bool>(&val);
    return !ptr || (*ptr == true);
}

}   //  namespace detail
}   //  namespace rose
