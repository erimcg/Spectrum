/*
 * resolution.cpp
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * February 17, 2009 
 */

//#define RES_DEBUG

#include <iostream>

#include "assert.h"

#include "specdata.h"
#include "resolution.h"
#include "struct.h"
#include "ground_lits.h"
#include "sym_tree.h"
#include "unify.h"
#include "distribute.h"
#include "factor.h"
#include "redundancy.h"
#include "instantiate.h"
#include "var_map.h"
#include "maximal.h"

/********************
 * Private functions
 ********************/

Clause * resolve(Clause *c1, int l1, Clause *c2, int l2, vector<Sub> *mgu, SpecData *spec)
{
	int num_lits = 0;
	Clause *temp_cl = NULL;

	assert(c1 != NULL && c2 != NULL);
	assert(c1->num_lits > 0 && c2->num_lits > 0);

	num_lits = c1->num_lits + c2->num_lits - 2;
	if (num_lits == 0)
		return NULL;

	temp_cl = new Clause;
	assert(temp_cl != NULL);

	temp_cl->num_lits = num_lits;
	temp_cl->ground = true;

	temp_cl->lits = (Lit**)calloc(num_lits, sizeof(Lit*));

	int k = 0;
	for (int i = 0; i < c1->num_lits; i++) {
		if (i != l1 ) {
			temp_cl->lits[k] = c1->lits[i];
			k++;
		}
	}

	for (int i = 0; i < c2->num_lits; i++) {
		if (i != l2) {
			temp_cl->lits[k] = c2->lits[i];
			k++;
		}
	}

	Clause *c = new_instance(temp_cl, mgu, spec);

	free(temp_cl->lits);
	free(temp_cl);

	return c;
}	

ResRtnCode run_res(ClauseSet *src1, int beg1, int end1, ClauseSet *src2, int beg2, int end2, SpecData *spec) 
{
	ClauseSet *P = spec->P;
	ClauseSet *R = spec->R;
	int P_orig_size = P->num_clauses;
	int R_orig_size = R->num_clauses;
	ClauseSet *target = NULL;

	bool factor_found = false;

	Lit * lit1 = NULL;
	Lit * lit2 = NULL;
	Clause *c = NULL;
	bool selected_lit_found;

	if (beg1 > end1 || beg2 > end2) {
		return RES_NO_CLAUSE_ADDED;
	}

	for (int i = beg1; i <= end1 ; i++) {

		selected_lit_found = false;

		for (int m = 0; m < src1->clauses[i]->num_lits; m++) {
			if (selected_lit_found == true)
				break;

			if (src1->clauses[i]->lits[m]->selected == false)
				continue;

			if (src1 == P) {
				beg2 = src1->clauses[i]->lits[m]->last_unresolved;
				selected_lit_found = true;
			}

			lit1 = src1->clauses[i]->lits[m];

			int j = beg2;

			if (src1 == src2 && beg2 < i)
				j = i;
	
			for (; j <= end2; j++) {
			//for (int j = beg1; j <= end2; j++) {
				for (int n = 0; n < src2->clauses[j]->num_lits; n++) {
					if (src2->clauses[j]->lits[n]->selected == false)
						continue;

					if ((src1 == src2) && (i == j) && (m == n))
						continue;

					lit2 = src2->clauses[j]->lits[n];

                         if (lit1->atom->sym != lit2->atom->sym)
                              continue;

                         if (lit1->negated == lit2->negated)
                              continue;

					#ifdef RES_DEBUG
						cout << "Checking Unification on ";
						cout << "("; print_lit(lit1, SYM); 
						cout << ","; print_lit(lit2, SYM); cout << ")" << endl;
					#endif

					vector<Sub> *mgu = new vector<Sub>;

					if (unifiable(lit1, lit2, mgu) == false) {
						free_mgu(mgu);
						continue;
					}

					#ifdef RES_DEBUG
						cout << "Resolving clauses [cl:" << i << " lit:" << m << ", cl:" << j << "lit:" << n <<"]" << endl;
					#endif 

					c = resolve(src1->clauses[i], m, src2->clauses[j], n, mgu, spec);
					free_mgu(mgu);

					if (c == NULL) {
						#ifdef RES_DEBUG
							cout << "Resolved the empty clause" << endl;
						#endif

						return RES_UNSAT;
					}

					if (spec_message_type(SPEC_VERBOSE, spec)) {
						cout << "\tResolving:\n\t";
						print_clause(src1->clauses[i], SYM);
						cout << "\t";
						print_clause(src2->clauses[j], SYM);
					}

					factor_found = false;

					if (src1 == spec->R)
						factor_found = safely_factors(c, c, NULL, spec);

					if (factor_found == true) {
						free_instance(c);
					}
					else {
						target = distribute_get_target(c, spec);
						insert_instance(c, target, spec);
					}
						

				}
			}
			
			if (src1 == P)
				lit1->last_unresolved = end2 + 1;
		}
	}

	if (P_orig_size < P->num_clauses || R_orig_size < R->num_clauses) {
		return RES_CLAUSE_ADDED;
	}
	else
		return RES_NO_CLAUSE_ADDED;
}

/*******************
 * Public functions
 *******************/

ResRtnCode run_resolution(SpecData *spec)
{
	ResRtnCode rc1 = RES_INIT;
	ResRtnCode rc2 = RES_INIT;

	ClauseSet *P = spec->P;
	ClauseSet *R = spec->R;
	int P_new = spec->P_new;
	int R_new = spec->R_new;
	int R_size = R->num_clauses;

	rc1 = run_res(R, 0, R_size-1, R, R_new, R_size-1, spec);

	spec->R_new = R_size;

	if (rc1 == RES_UNSAT)
		return RES_UNSAT;

	#ifdef RES_DEBUG
		cout << "Res(R,R) returned " << rc1 << endl;
	#endif

	rc2 = run_res(P, 0, P_new-1, R, 0, R_size-1, spec);

	if (rc2 == RES_UNSAT)
		return RES_UNSAT;

	#ifdef RES_DEBUG
		cout << "Res(R,P) returned " << rc2 << endl;
	#endif

	assert(rc1 != RES_INIT && rc2 != RES_INIT);

	if (rc1 == RES_CLAUSE_ADDED || rc2 == RES_CLAUSE_ADDED)
		return RES_CLAUSE_ADDED;
	else if (rc1 == RES_NO_CLAUSE_ADDED && rc2 == RES_NO_CLAUSE_ADDED)
		return RES_NO_CLAUSE_ADDED;
	else {
		cout << "SZS: Error: Invalid ResRtnCode (" << rc1 << ") (" << rc2 << ")" << endl;
		exit(1);
	}
}


// END OF FILE
