#include "rose/eval/expression_evaluator.hpp"

#include <boost/bind.hpp>
#include <boost/circular_buffer.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/range/algorithm/transform.hpp>

#include <algorithm>
#include <iterator>
#include <utility>

namespace rose {

expression_evaluator::expression_evaluator(environment_ptr env) :
    evaluator_base(env)
{}

expression_evaluator::result_type
    expression_evaluator::operator()(ast_variable const& ast) const
{
    result_type val = env->lookup(ast);
    if (!val) {
        throw std::runtime_error("undefined variable");
    }

    return val;
}

evaluator_base::result_type
    expression_evaluator::operator()(ast_quotation const& ast) const
{
    return eval(ast.quoted, env);
}

evaluator_base::result_type
    expression_evaluator::operator()(ast_lambda_expression const& ast) const
{
    procedure proc(ast, env);
    return make_value(procedure(ast, env));
}

gc::handle<value> apply(
        gc::handle<value> operator_,
        arguments_type const& args,
        arguments_type const& rest_args)
{
    using namespace boost;

    procedure& proc = handle_cast<procedure>(operator_);
    range::transform(
            proc.ast.formals,
            args,
            std::inserter(*proc.env, proc.env->begin()),
            &std::make_pair<ast_variable, gc::handle<value> >);

    range::for_each(
            proc.ast.body.definitions,
            bind(eval<ast_definition>, _1, proc.env));

    circular_buffer<gc::handle<value> > result(1);

    range::transform(
            proc.ast.body.sequence,
            std::back_inserter(result),
            bind(&eval<ast_expression>, _1, proc.env));

    return result.size() ? result[0] : nil();
}

gc::handle<value> apply(
        gc::handle<value> operator_,
        arguments_type const& args)
{
    arguments_type rest_args;
    return apply(operator_, args, rest_args);
}

gc::handle<value> apply(gc::handle<value> operator_) {
    arguments_type args;
    arguments_type rest_args;
    return apply(operator_, args, rest_args);
}

evaluator_base::result_type
    expression_evaluator::operator()(ast_procedure_call const& ast) const
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

evaluator_base::result_type
    expression_evaluator::operator()(ast_conditional const& ast) const
{
    result_type test = eval(ast.test, env);

    if (is_true(*test)) {
        return eval(ast.consequent, env);
    }

    if (!!ast.alternate) {
        return eval(*ast.alternate, env);
    }

    return nil();
}

evaluator_base::result_type
    expression_evaluator::operator()(ast_assignment const& ast) const
{
    env->assign(ast.variable, eval(ast.expression, env));
    return nil();
}

bool expression_evaluator::is_true(value const& val) const {
    // Any Scheme value other than #f can be implicitly converted to #t.
    bool const* ptr = boost::get<bool>(&val);
    return !ptr || (*ptr == true);
}

template<>
gc::handle<value> eval<ast_expression>(
        ast_expression const& ast, environment_ptr env)
{
    return boost::apply_visitor(expression_evaluator(env), ast);
}

}   //  namespace rose
