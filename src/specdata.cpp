/*
 * specdata.cpp
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * March 27, 2009 
 */

//#define DEBUG

#include <iostream>
#include "struct.h"
#include "specdata.h"
#include "sym_tree.h"
#include "ground_lits.h"
#include "instantiate.h"

void spec_print_data(SpecData *);

SpecData * new_spec_data()
{
	SpecData *spec = (SpecData *) new SpecData;

	spec->mode = SPEC_AUTO_SINGLE_SELECTED;
	spec->mssg = SPEC_STATUS;
	spec->depth = 0;

	spec->problem = (ClauseSet *) new ClauseSet;
	spec->problem->clauses = NULL;
	spec->problem->num_clauses = 0;

	spec->cl_ct = 0;

	spec->sym_tree = new_sym_tree();
	spec->glits = new_ground_lits();

	spec->smt = NULL;

	spec->P = (ClauseSet *) new ClauseSet;
	spec->P->clauses = NULL;
	spec->P->num_clauses = 0;
	spec->P_new = 0;

	spec->R = (ClauseSet *) new ClauseSet;
	spec->R->clauses = NULL;
	spec->R->num_clauses = 0;
	spec->R_new = 0;

//	spec_print_data(spec); 
	return spec;
}

SpecData * new_spec_data(int cl_ct)
{
	SpecData *spec = new_spec_data();
	spec->cl_ct = cl_ct;

	return spec;
}

void free_spec_data(SpecData *spec)
{
//	spec_print_data(spec); 

	for (int i = 0; i < spec->problem->num_clauses; i++)
          free_instance(spec->problem->clauses[i]);

	if (spec->problem->clauses != NULL)
	     free(spec->problem->clauses);

     free(spec->problem);

     for (int i = 0; i < spec->R->num_clauses; i++)
          free_instance(spec->R->clauses[i]);

	if (spec->R->clauses != NULL)
	     free(spec->R->clauses);

     free(spec->R);

     for (int i = 0; i < spec->P->num_clauses; i++) 
          free_instance(spec->P->clauses[i]);

	if (spec->P->clauses != NULL)
     	free(spec->P->clauses);

     free(spec->P);

     sym_tree_free(spec->sym_tree);
     glits_free(spec->glits);


	if (spec->smt != NULL) {
	//	cout << "FREEING SMT" << endl;
		delete spec->smt;
	}

     free(spec);

	return;
}

void spec_set_mode(SpecMode opt, SpecData *spec)
{
	spec->mode = opt;

	return; 
}

void spec_set_message_type(SpecMessageType mssg, SpecData *spec)
{
	spec->mssg = spec->mssg | mssg;

	return;
}

void spec_set_message_type(unsigned int mssg, SpecData *spec)
{
	spec->mssg = mssg;

	return;
}

void spec_set_problem(ClauseSet *prob, SpecData *spec)
{
	spec->problem = prob; 

	/* We do not set spec->cl_ct here.  We increment it when we distribute the clauses
	   out of spec->prob and into spec->P and spec->R */

	return;
}

bool spec_mode(SpecMode mode, SpecData *spec)
{
	return (spec->mode == mode);
}

bool spec_message_type(SpecMessageType mssg, SpecData *spec)
{
	if ((spec->mssg & mssg) == mssg)
		return true;
	else
		return false;
}

void spec_print_data(SpecData *spec) 
{
	cout << endl;
	cout << "---------" << endl;
	cout << "mode: " << spec->mode << ": ";
	switch (spec->mode){
		case SPEC_INTERACTIVE: cout << "Interactive" << endl; break;
		case SPEC_PPI_ONLY:  cout << "PI only" << endl; break;
		case SPEC_RES_ONLY: cout << "Res only" << endl; break;
		case SPEC_AUTO_SINGLE_SELECTED: cout << "Heuristic" << endl; break;
		case SPEC_SUBSUMPTION: cout << "Subsumption" << endl; break;
		default: cout << endl; break;
	}

	cout << "clause count: " << spec->cl_ct << endl;
	cout << "size of P: " << spec->P->num_clauses << endl;
	cout << "size of R: " << spec->R->num_clauses << endl;
	cout << "new clauses P: " << spec->P_new << endl;
	cout << "new clauses R: " << spec->R_new << endl;
	cout << "--- Problem ---" << endl;
	print_clause_set(spec->problem, SEL);
	cout << "--- P ---" << endl;
	print_clause_set(spec->P, SEL);
	cout << "--- R ---" << endl;
	print_clause_set(spec->R, SEL);
	cout << "---------" << endl;

	

}

/* END OF FILE */
