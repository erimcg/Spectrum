/*
 * Class SMTSolver.h
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * October 26, 2008
 */

#ifndef _SMTSOLVER_H_
#define _SMTSOLVER_H_

#include "yices_c.h"
#include "struct.h"

class SMTSolver {
	void *ctx;
	bool is_sat;
	void *model;

	public:
		SMTSolver();
		 ~SMTSolver();

		void* mk_fresh_bool_var();
		void* mk_not(void*);
		void* mk_or(void**, int);

		void reset_context();		
		void assert_expr(void*);
		bool check();
		s_bool eval_expr(void*);

		void print_expr(void*);
		void print_model();
};

#endif
	
