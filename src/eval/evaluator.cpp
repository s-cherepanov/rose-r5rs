#include "rose/eval/evaluator.hpp"

namespace rose {

evaluator_base::evaluator_base(environment_ptr env) :
    env(env)
{}

datum_evaluator::datum_evaluator(environment_ptr env) :
    evaluator_base(env)
{}

evaluator_base::result_type
    datum_evaluator::operator()(ast_list const& ast) const
{
    result_type result = make_value(pair());

    if (ast.elements.empty()) {
        return result;
    }

    ast_list::const_iterator next = ast.elements.begin();
    result_type last = result;

    set_car(result, eval(*next, env));

    while (ast.elements.end() != ++next) {
        pair p;
        p.first = eval(*next, env);
        set_cdr(last, make_value(p));
        last = cdr(last);
    }

    if (!!ast.dotted_element) {
        set_cdr(last, eval(*(ast.dotted_element), env));
    }

    return result;
}

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
    return nil();
}

evaluator_base::result_type
    expression_evaluator::operator()(ast_procedure_call const& ast) const
{
    return nil();
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

command_or_definition_evaluator::
    command_or_definition_evaluator(environment_ptr env) :
    evaluator_base(env)
{}

evaluator_base::result_type
    command_or_definition_evaluator::operator()(ast_definition const& ast) const
{
    env->define(ast.variable, eval(ast.expression, env));
    return nil();
}

command_or_definition_evaluator::result_type
    command_or_definition_evaluator::operator()(ast_expression const& ast) const
{
    return eval(ast, env);
}

}   //  namespace rose
