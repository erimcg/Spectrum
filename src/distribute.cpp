/*
 * distribute.cpp
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * March 26, 2009 
 */

//#define DEBUG

#include <iostream>
#include "assert.h"

#include "struct.h"
#include "specdata.h"
#include "maximal.h"

/********************
 * Private functions
 ********************/

ClauseSet * single_selected_heuristic(Clause *c, SpecData *spec)
{
	/* This heuristic is based on whether or not the clause contains a 
	   single selected literal when terms are ordered with kbo. If so
	   we put the clause in R, otherwise we put it in P. */

	/* If clause is ground then we put it in P, since kbo is
	   total on ground terms. */

	if (c->ground == true)
		return spec->P;
 
	/* Count the number of selected literals in the clause. 
	   If clause has one selected literal then put it in R, 
	   otherwise put it in P */

	set_maximal_literals(c);
	int count = 0;

	for (int j = 0; j < c->num_lits; j++) {
		 if (c->lits[j]->selected == true)
			count++;
	}

	assert(count > 0);

	if (count == 1) 
		return spec->R;
	else
		return spec->P;

}


ClauseSet * ground_heuristic(Clause *c, SpecData *spec)
{
	set_maximal_literals(c);

	if (c->ground == true)
		return spec->P;
	else
		return spec->R;
}


/********************
 * Public functions
 ********************/

ClauseSet * distribute_get_target(Clause *c, SpecData *spec)
{
	switch(spec->mode) {
		case SPEC_SUBSUMPTION:
			return spec->R;

		case SPEC_PPI_ONLY:
			return spec->P;

		case SPEC_RES_ONLY:
			return spec->R;

		case SPEC_AUTO_GROUND:
			return ground_heuristic(c, spec);

		case SPEC_AUTO_SINGLE_SELECTED:
			return single_selected_heuristic(c, spec);

		default:
			cout << "SZS Error: Invalid spectrum mode." << endl;
			exit(1);				
	}
}


void distribute_spec_problem(SpecData *spec)
{
	ClauseSet *target;

	for(int i = spec->problem->num_clauses - 1; i >= 0; i--) {
		target = distribute_get_target(spec->problem->clauses[i], spec);

		assert(target == spec->P || target == spec->R);

		insert_clause(spec->problem->clauses[i], target, &spec->cl_ct);

		remove_clause(i, spec->problem);
	}	
	
	if (target == spec->R)
		set_maximal_literals(spec->R);

	return;
}

/* END OF FILE */
