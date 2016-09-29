/*
 * primal_pi.cpp
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * February 17, 2009
 */

//#define DEBUG_PROCESS
//#define DEBUG_DATA

#include <iostream>
#include <set>
#include <utility>

#include "assert.h"

#include "specdata.h"
#include "primal_pi.h"
#include "redundancy.h"
#include "instantiate.h"
#include "ground_lits.h"
#include "sym_tree.h"
#include "SMTSolver.h"
#include "limits.h"
#include "unify.h"

using namespace std;

struct lit_pair_comp {
	bool operator() (const pair<Lit *, Lit *>& p1, const pair<Lit *, Lit *>& p2) const
  		{return ((p1.first < p2.first) ||  (p1.first == p2.first && p1.second < p2.second));}
};

set<pair<Lit *, Lit *>, lit_pair_comp> checked_lits; 

void assert_problem(SpecData *spec)
{
	ClauseSet *P = spec->P;
	SMTSolver *smt = spec->smt;
	int P_new = spec->P_new;

     for (int i = P_new; i < P->num_clauses; i++) {
          if (P->clauses[i]->num_lits == 1) {
               smt->assert_expr(P->clauses[i]->lits[0]->smt_var->smt_expr);
               continue;
          }
    
          void **args = (void **)calloc(sizeof(void*), P->clauses[i]->num_lits);

          for (int j = 0; j < P->clauses[i]->num_lits; j++) {

               assert(P->clauses[i]->lits[j]->smt_var != NULL);

               args[j] = P->clauses[i]->lits[j]->smt_var->smt_expr;
          }

          void *e = smt->mk_or(args, P->clauses[i]->num_lits);
          smt->assert_expr(e);

		free(args);
     }
	
	spec->P_new = P->num_clauses;
}

bool instantiate(ClauseSet *P, int index, vector<Sub> *mgu, SpecData *spec)
{
     Clause *c = new_instance(P->clauses[index], mgu, spec);

	#ifdef DEBUG_PROCESS
		cout << "Created new clause. " << endl;
	#endif

	bool clause_added = insert_instance(c, P, spec);

	#ifdef DEBUG_PROCESS
		cout << "Instantiation complete." << endl;
	#endif

     return clause_added;
}


bool find_conflict(SpecData *spec)
{
	ClauseSet *P = spec->P;
	Lit *i_lit;
	Lit *k_lit;
	int cur_depth = 1;
	bool skipped_lit;
	bool conflict_found = false;
	int initial_size_of_P = P->num_clauses;

	while (true) {
		skipped_lit = false;

     	for (int i = 0; i < initial_size_of_P; i++) {
          	for (int j = 0; j < P->clauses[i]->num_lits; j++) {
			
				if (P->clauses[i]->lits[j]->smt_var->truth_val == s_false)
					continue;

				i_lit = P->clauses[i]->lits[j];

				if (i_lit->atom->depth > cur_depth ) {
					skipped_lit = true;
					break;
				}

				/* * Compare with satisfiers in other clauses */

     			for (int k = i + 1; k < initial_size_of_P; k++) {
          			for (int m = 0; m < P->clauses[k]->num_lits; m++) {

						if (P->clauses[k]->lits[m]->smt_var->truth_val == s_false)
							continue;

						/* * Found clause satisfier. Check for cur_depth-conflict.  */

						k_lit = P->clauses[k]->lits[m];
	
						if (k_lit->atom->depth > cur_depth ) {
							skipped_lit = true;
							break;
						}

						if (i_lit->atom->sym != k_lit->atom->sym)
							break;

						if (i_lit->negated == k_lit->negated)
							break;

						/* 
						 * Check if Pair of lits has been considered before.
						 * TODO: There must be a better way!
						 */
					
						pair<Lit *, Lit *> lits;

						if (k_lit < i_lit)
							lits = make_pair(k_lit, i_lit);
						else
							lits = make_pair(i_lit, k_lit);

						set<pair<Lit *, Lit *> >::iterator it;

						it = checked_lits.find(lits);
	
						if (it != checked_lits.end()) {
							#ifdef DEBUG_PROCESS
								cout << "Skipping lits: lits encountered prior." << endl;
							#endif

							#ifdef DEBUG_DATA
								print_lit((*it).first, SYM);
								cout << endl;
								print_lit((*it).second, SYM);
								cout << endl;
							#endif
	
							break;
						}
						else {
							#ifdef DEBUG_PROCESS
								cout << "Inserting pair of literals." << endl;
							#endif
							checked_lits.insert(lits);
						}
		
			               vector<Sub> *mgu = new vector<Sub>;

			               bool is_unifiable = unifiable(i_lit, k_lit, mgu);

						if (is_unifiable == false) {
							free_mgu(mgu);
							break;
						}
						else if (is_unifiable == true && mgu_is_renaming(mgu) == true) {
							free_mgu(mgu); 
							break;
						}

						#ifdef DEBUG_PROCESS
							cout << "Found conflicting satisfiers." << endl;
						#endif

						if (spec_message_type(SPEC_VERBOSE, spec)) {
							cout << "\tInst-Gen:\n\t";
							print_clause(P->clauses[i], SYM);
							cout << "\t";
							print_clause(P->clauses[k], SYM);
						}

						bool success1 = false;
						bool success2 = false;

						//print_unifier(link->mgu, SYM);
							
	 					success1 = instantiate(P, i, mgu, spec);
						success2 = instantiate(P, k, mgu, spec);
	
						free_mgu(mgu);
 
						if (success1 == true || success2 == true) {
							#ifdef DEBUG_PROCESS
								cout << "Instantiated at least one new clause." << endl;
							#endif
					
							conflict_found = true;
						}

						/* * Clause k satisfier found. Check next clause. */

						break;
					}
				}

				/* *  Clause i satisfier found.  Check next clause. */
				break;
			}
		}

		if (skipped_lit == false && conflict_found == true) 
			return true;
		else if (skipped_lit == false && conflict_found == false)
			return false;
		else
			cur_depth++;
	}

	if (conflict_found == true)
		return true;
	else
		return false;
}

void set_selected_lits(ClauseSet *P)
{
	bool selected_lit_found;

     for (int i = 0; i < P->num_clauses; i++) {
		selected_lit_found = false;

          for (int j = 0; j < P->clauses[i]->num_lits; j++) {
			if (selected_lit_found == true) {
				P->clauses[i]->lits[j]->selected = false; 
			}
			else if (P->clauses[i]->lits[j]->smt_var->truth_val == s_false) {
					P->clauses[i]->lits[j]->selected = false;
			} 
			else {
				P->clauses[i]->lits[j]->selected = true;
				selected_lit_found = true; 
			}
		}
		
		assert(selected_lit_found == true);
	}
	
	return;
}


PPiRtnCode run_primal_pi(SpecData* spec)
{
	ClauseSet *P = spec->P;

	if(P->num_clauses == 0)
		return PPI_NO_CLAUSE_ADDED;

	if (spec->smt == NULL)
		spec->smt = new SMTSolver;

	SMTSolver *smt = spec->smt;

	bool is_sat = false;
	bool conflict_found = false;

	#ifdef DEBUG_PROCESS
		cout << "Setting SMT expressions for ground strings ..." << endl;
	#endif

	set_smt_expr(smt, spec->glits);

	#ifdef DEBUG_PROCESS
		cout << "Asserting problem in SMT solver ..." << endl;
	#endif

	assert_problem(spec);

	#ifdef DEBUG_PROCESS
		cout << "Checking satisfiability ..." <<endl;
	#endif

    	is_sat = smt->check();

	if (is_sat == false)
		return PPI_UNSAT;

	#ifdef DEBUG_PROCESS
		cout << "SMT solver returned satisfiable." << endl;
		cout << "Setting ground string truth values ..." << endl;
	#endif

    	set_smt_truth_val(smt, spec->glits);

	#ifdef DEBUG_PROCESS
		cout << "Setting selected literals ..." << endl;
	#endif

	set_selected_lits(P);

	conflict_found = find_conflict(spec);

	if (conflict_found == false) {
		#ifdef DEBUG_PROCESS
			cout << "No conflicts at any depth found." << endl;
		#endif

		return PPI_NO_CLAUSE_ADDED;
	}
	else {	
		#ifdef DEBUG_PROCESS
			cout << "Conflicts found." << endl;
		#endif

		return PPI_CLAUSE_ADDED;
	}
}


/* END OF FILE */
