/*
 * redundancy.cpp
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * February 21, 2009
 */

//#define REDUN_DEBUG

#include <iostream>
#include "string.h"
#include "assert.h"

#include "spectrum.h"
#include "specdata.h"
#include "resolution.h"
#include "maximal.h"
#include "redundancy.h"
#include "struct.h"
#include "instantiate.h"
#include "factor.h"
#include "skolem.h"
#include "unify.h"

/*******************
 * Private functions
 *******************/

bool equivalent(Clause *c, Clause *d)
{
	if (c->ground == true && d->ground == true) {
		if (strcmp(c->g_str,d->g_str) == 0) {
			#ifdef REDUN_DEBUG
				cout << "Redundant: Ground match." << endl;
			#endif

			return true;
		}
	}
	else if (c->ground == false && d->ground == false) {
		if (strcmp(c->g_str, d->g_str) == 0 &&
		    strcmp(c->signature, d->signature) == 0) {

			#ifdef REDUN_DEBUG
				cout << "Redundant: Non-ground match." << endl;
			#endif

			return true;
		}
	}

	return false;
}

bool tautology(Clause *c)
{
	for (int i = 0; i < c->num_lits; i++) {
		for (int j = i + 1; j < c->num_lits; j++) {
		
			if (c->lits[i]->atom->sym != c->lits[j]->atom->sym)
				continue;

			if (c->lits[i]->negated == c->lits[j]->negated)
				continue;

			if (strcmp(c->lits[i]->atom->str, c->lits[j]->atom->str) == 0)
				return true;
		}
	}

	return false;
}

/*******************
 * Public functions
 *******************/

bool strictly_theta_subsumes(Clause *c1, Clause *c2, SpecData *spec)
{
	#ifdef REDUN_DEBUG
		cout << "Checking strict theta subsumption between" << endl;
		print_clause(c1, SYM);
		print_clause(c2, SYM);
	#endif

	if (c1->num_lits > c2->num_lits)
		return false;

	Lit *lit1 = NULL;
	Lit *lit2 = NULL;
	bool rc = false;

	vector<Sub> *sk_mgu = new vector<Sub>;

	Clause *skolem_c2 = new_instance(c2, sk_mgu, spec); 
	skolemize(skolem_c2);

	free_mgu(sk_mgu);

	for (int i = 0; i < c1->num_lits; i++) {
		lit1 = c1->lits[i];

		for (int j = 0; j < skolem_c2->num_lits; j++) {
			lit2 = skolem_c2->lits[j];

     		if (lit1->atom->sym != lit2->atom->sym)
          		continue;

     		if (lit1->negated != lit2->negated)
          		continue;

     		#ifdef REDUN_DEBUG
          		cout << "Checking Unification on ";
          		cout << "("; print_lit(lit1, SYM);
          		cout << ","; print_lit(lit2, SYM); cout << ")" << endl;
     		#endif

		     vector<Sub> *mgu = new vector<Sub>;

     		if (unifiable(lit1, lit2, mgu) == false) {
          		free_mgu(mgu);
          		continue;
     		}

			if (c1->num_lits == 1) {
				free_mgu(mgu);
				return true;
			}

			Clause *temp_cl = new Clause;
			temp_cl->num_lits = c1->num_lits - 1;
			temp_cl->lits = (Lit**)calloc(temp_cl->num_lits, sizeof(Lit*));
			temp_cl->ground = true;

			int m = 0;
     		for (int k = 0; k < c1->num_lits; k++) {
				if (k == i)
					continue;
 
				temp_cl->lits[m++] = c1->lits[k];
			}

			Clause *c = new_instance(temp_cl, mgu, spec);

			free(temp_cl->lits);

			temp_cl->num_lits = skolem_c2->num_lits - 1;
			temp_cl->lits = (Lit**)calloc(temp_cl->num_lits, sizeof(Lit*));
			
			m = 0;
     		for (int k = 0; k < skolem_c2->num_lits; k++) {
				if (k == j)
					continue;
 
				temp_cl->lits[m++] = skolem_c2->lits[k];
			}

			Clause *d = new_instance(temp_cl, mgu, spec);

			free(temp_cl->lits);
			free(temp_cl);
			free_mgu(mgu);

			rc = strictly_theta_subsumes(c, d, spec);

			free_instance(c);
			free_instance(d);

			if (rc == false) {
				continue;
			}
			else {
				free_instance(skolem_c2);
				return true;
			}
		}
     }

	free_instance(skolem_c2);

	return false;
}

bool subsumes(Clause *c1, Clause *c2, SpecData *spec)
{
	#ifdef REDUN_DEBUG
		cout << "Checking subsumption between" << endl;
		print_clause(c1, SYM);
		print_clause(c2, SYM);
	#endif

	if (c1->ground == false || c2->ground == false)
		return false;

	if (c1->num_lits > c2->num_lits)
		return false;

	SpecData *new_spec = new_spec_data(spec->cl_ct);
	spec_set_mode(SPEC_SUBSUMPTION, new_spec);
	spec_set_message_type(spec->mssg, new_spec);

	vector<Sub> *mgu = new vector<Sub>;
	
	Clause *new_c1 = new_instance(c1, mgu, new_spec); 

     insert_clause(new_c1, new_spec->R, &new_spec->cl_ct);

     if (spec_message_type(SPEC_VERBOSE, spec)) {
		cout << "(S) ";
		print_clause(new_c1, SYM);
     }

	Clause *new_c2 = new_instance(c2, mgu, new_spec); 
	skolemize(new_c2);

	Clause *c = new Clause;
	c->num_lits = 1;
	c->lits = (Lit**)calloc(1, sizeof(Lit*));
	c->ground = true;

     for (int i = 0; i < new_c2->num_lits; i++) {
		c->lits[0] = new_c2->lits[i];

		if (c->lits[0]->negated == true)
			c->lits[0]->negated = false;
		else 
			c->lits[0]->negated = true;

		Clause *n = new_instance(c, mgu, new_spec);

		insert_clause(n, new_spec->R, &new_spec->cl_ct);
     
		if (spec_message_type(SPEC_VERBOSE, spec)) {
			cout << "(S) ";
			print_clause(n, SYM);
     	}
	}

	set_maximal_literals(new_spec->R);

	free(c->lits);
	free(c);
	free_mgu(mgu);
	free_instance(new_c2);

     /*
      * Partition clause set
      */

	if (spec_message_type(SPEC_VERBOSE, spec)) {
          cout << "Distribution Set" << endl;
          spec_print_data(new_spec);
	}

     ResRtnCode rc = RES_CLAUSE_ADDED;

	while(rc == RES_CLAUSE_ADDED)
		rc = run_resolution(new_spec);

	free_spec_data(new_spec);

	if (rc == RES_UNSAT)
		return true;
	else 	
		return false;
}

bool redundant(Clause *c, ClauseSet *target, SpecData *spec)
{
	if (tautology(c) == true) {
//		cout << "Tautology Found" << endl;
//		print_clause(c, SYM);
		return true;
	}

	for(int i = target->num_clauses - 1; i >= 0; i--) {

		if (equivalent(c, target->clauses[i]) == true)
			return true;

		if (target == spec->P)
			continue;

		/*
		 * Forward subsumption. 
 		 */ 
	
		if (spec->mode == SPEC_SUBSUMPTION)
			continue;	

		if (strictly_theta_subsumes(target->clauses[i], c, spec) == true) {

			#ifdef REDUN_DEBUG
				cout << "Redundant: Strictly Theta Subsumed." << endl;
			#endif

			return true;
		}

		#ifdef REDUN_DEBUG
			cout << "Not Redundant: Not Strictly Theta Subsumed." << endl;
		#endif

	}

	return false;
}

// END OF FILE
