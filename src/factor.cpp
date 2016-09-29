/*
 * factor.cpp
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * April 8, 2009
 */

//#define FACT_DEBUG

#include <iostream>
#include "string.h"
#include "assert.h"
#include "stdlib.h"

#include "struct.h"
#include "specdata.h"
#include "distribute.h"
#include "redundancy.h"
#include "instantiate.h"
#include "unify.h"
#include "maximal.h"

/*******************
 * Private functions
 *******************/

Clause *new_factor(Clause *c, int j, vector<Sub> *mgu, SpecData *spec)
{
     assert(c != NULL);
     assert(j >= 0 && j < c->num_lits);

     Clause *subset_of_c = new Clause;
     assert(subset_of_c != NULL);

     subset_of_c->lits = (Lit**)calloc(c->num_lits - 1, sizeof(Lit*));

     subset_of_c->num_lits = c->num_lits - 1;
     subset_of_c->ground = true;

     int k = 0;
     for (int i = 0; i < c->num_lits; i++) {
          if (i != j) {
               subset_of_c->lits[k] = c->lits[i];
               k++;
          }
     }

     Clause *factor = new_instance(subset_of_c, mgu, spec);

     free(subset_of_c->lits);
     free(subset_of_c);

	return factor;
}

/*******************
 * Public functions
 *******************/

bool safely_factors(Clause *f, Clause *c, ClauseSet *target, SpecData *spec)
{
	Lit *lit1;
	Lit *lit2;

	assert(c != NULL);
	assert(f != NULL);
	assert(f->num_lits > 0);

	Clause *new_f = NULL;
	vector<Sub> *mgu;

	#ifdef FACT_DEBUG
		cout << "Safely_factor" << endl;
		print_clause(f, SYM);
		print_clause(c, SYM);
		cout << endl;
	#endif

     for (int i = 0; i < f->num_lits; i++) {
		lit1 = f->lits[i];

          for (int j = i + 1; j < f->num_lits; j++) {
			lit2 = f->lits[j];

               mgu = new vector<Sub>;

			if (lit1->negated != lit2->negated) {
				free_mgu(mgu);	
				continue;
			}

               if (unifiable(lit1, lit2, mgu) == false) {
				free_mgu(mgu);	
				continue;
			}

			new_f = new_factor(f, j, mgu, spec);
			free_mgu(mgu);

			#ifdef FACT_DEBUG
				cout << "new factor: ";
				print_clause(new_f, SYM); 
				cout << " of " << endl;
				print_clause(f, SYM);
			#endif
			
			if (safely_factors(new_f, c, target, spec) == true) {
				if (f != c)
					free_instance(f);
			
				return true;	
			}
          }
     }

	if (f == c)
		return false;

	if (target == NULL)
		target = distribute_get_target(f, spec);

	insert_instance(f, target, spec);

	if (spec_mode(SPEC_SUBSUMPTION, spec) == true) 
		return false;
	else if (subsumes(f, c, spec) == true)
		return true;
	else 
		return false;
}


// END OF FILE
