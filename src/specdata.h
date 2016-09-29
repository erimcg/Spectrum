/*
 * specdata.h
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * March 27, 2009
 */

#ifndef _SPECDATA_H_
#define _SPECDATA_H_

#include "struct.h"
#include "sym_tree.h"
#include "ground_lits.h"
#include "SMTSolver.h"

enum SpecMode {
	SPEC_INTERACTIVE 			= 0x1,
	SPEC_PPI_ONLY				= 0x2,
	SPEC_RES_ONLY				= 0x4,
	SPEC_AUTO_SINGLE_SELECTED 	= 0x8,
	SPEC_AUTO_GROUND			= 0x10,
	SPEC_SUBSUMPTION			= 0x20
};

enum SpecMessageType {
	SPEC_STATUS				= 0x0,
	SPEC_SOLUTION				= 0x1,
	SPEC_NEW_CLAUSES			= 0x2,
	SPEC_VERBOSE				= 0xFF
};

typedef struct spec_t {
	SpecMode mode;
	int mssg;
	int depth;

	ClauseSet *problem;
	int cl_ct;

	SMTSolver *smt;
	SymTree *sym_tree;
	GLits *glits;

	ClauseSet *P;
	int P_new;

	ClauseSet *R;
	int R_new;
}SpecData;

SpecData * new_spec_data();
SpecData * new_spec_data(int);
void free_spec_data(SpecData *);

void spec_set_mode(SpecMode, SpecData *);
void spec_set_message_type(SpecMessageType, SpecData *);
void spec_set_message_type(unsigned int, SpecData *);
void spec_set_problem(ClauseSet *, SpecData *);

bool spec_mode(SpecMode, SpecData *);
bool spec_message_type(SpecMessageType, SpecData *);
void spec_print_data(SpecData *);

#endif
