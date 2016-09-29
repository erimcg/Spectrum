/*
 * ground_lits.h
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * October 26, 2008
 */

#ifndef _GROUND_LITS_H_
#define _GROUND_LITS_H_

#include "struct.h"
#include "SMTSolver.h"

typedef struct smt_data_s {
     char *g_str;
     SMTVar *pos_var;
     SMTVar *neg_var;
}SMTData;

typedef struct prop_link_s {
     SMTData *smt_data;
     struct prop_link_s *next;
}PropLink;

typedef struct prop_node {
	SMTData *smt_data;
	struct prop_node *lchild;
	struct prop_node *rchild;
}PropNode;

typedef struct ground_lits_s {
     PropNode *root;
     PropLink *undeclared;
}GLits;


GLits *new_ground_lits();
void glits_free(GLits *);

SMTVar* insert_ground_lit(Lit*, GLits *);
void set_smt_expr(SMTSolver*, GLits *);
void set_smt_truth_val(SMTSolver*, GLits *);
void print_ground_lits(GLits *);

#endif
