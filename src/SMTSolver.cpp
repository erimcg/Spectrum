/*
 * Class SMTSolver.cpp
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * October 26, 2008
 */

#include <iostream>
#include "SMTSolver.h"
#include "yices_c.h"
#include "struct.h"

using namespace std;

SMTSolver::SMTSolver()
{
     ctx = yices_mk_context();
}

SMTSolver::~SMTSolver()
{
	yices_del_context(ctx);

}

void SMTSolver::reset_context()
{
	yices_reset(ctx);

	return;
}

void* SMTSolver::mk_fresh_bool_var()
{
     return yices_mk_fresh_bool_var(ctx);
}

void* SMTSolver::mk_not(void *expr)
{
     return yices_mk_not(ctx, expr);
}

void *SMTSolver::mk_or(void** args, int num_args)
{
     return yices_mk_or(ctx, args, num_args);
}

void SMTSolver::assert_expr(void *expr)
{
     yices_assert(ctx, expr);
}

bool SMTSolver::check()
{
     switch (yices_check(ctx)) {
          case l_true:
               is_sat = true;
               model = yices_get_model(ctx);
               return true;
          default:
               is_sat = false;
               return false;
     }
}

s_bool SMTSolver::eval_expr(void *expr)
{
	if (yices_evaluate_in_model(model, expr) == l_true)
		return s_true;
	else if (yices_evaluate_in_model(model, expr) == l_false)
		return s_false;
	else 
		return s_undef;
}

void SMTSolver::print_expr(void *expr)
{
     yices_pp_expr(expr);
}

void SMTSolver::print_model()
{
     yices_display_model(model);
}

/* END OF FILE */

