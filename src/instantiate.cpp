/*
 * instantiate.cpp
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * November 13, 2008
 */

//#define INST_DEBUG

#include <iostream>
#include <vector>
#include <assert.h>
#include <string.h>

#include "maximal.h"
#include "redundancy.h"
#include "specdata.h"
#include "instantiate.h"
#include "unify.h"
#include "var_map.h"
#include "sym_tree.h"

using namespace std;

/*******************
 * Private functions
 *******************/

Term* new_functor(Term *, Clause *, vector<Sub> *, int, char *, int, SpecData *);

Term* new_constant(Term *t1, SpecData *spec)
{
	assert(t1 != NULL);

	Term *t = new Term;
	assert(t != NULL);

	t->type = constant;
	t->skolem = false;
	t->sym = sym_tree_insert_sym(t1->sym, spec->sym_tree);
	t->str = t->sym; 
	t->g_str = strdup(t1->g_str);
	t->ground = true;
	t->depth = 0;
	t->num_args = 0;
	t->args = NULL;
	t->signature = NULL;

	return t;
}

Term* new_variable(Term *t1, Clause *c, vector<Sub> *mgu, int new_cl_num, char *sig, int lit_num, SpecData *spec)
{
	assert(t1 != NULL);

	Sub *sub = mgu_get_sub(mgu, t1);

	if (sub != NULL) {
		switch (sub->range->type) {
			case function:
				return new_functor(sub->range, c, mgu, new_cl_num, sig, lit_num, spec);
			case constant:
				return new_constant(sub->range, spec);
			case variable:
				return new_variable(sub->range, c, mgu, new_cl_num, sig, lit_num, spec);
			default:
				cout << "SZS: ERROR (new_variable)" << endl;
				exit(1);
		}
	}
	
	char *sym = (char*)malloc(strlen(t1->sym) + 16);

	sprintf(sym, "%s-%d", t1->sym, new_cl_num);
	Term *t2 = var_map_find(sym);

	if (t2 == NULL) {
		t2 = new Term;
		t2->type = variable;
		t2->sym = strdup(sym);
		
		t2->str = t2->sym;
		t2->signature = NULL;

		t2->paths.push_back(strdup(sig));

		t2->ground = false;
		t2->skolem = false;
		t2->depth = 0;
	
		char g_str[2];
		sprintf(g_str, "?");
		t2->g_str = strdup(g_str);

		t2->num_args = 0;
		t2->args = NULL;
	
		var_map_insert(t2);
		c->vars.push_back(t2);
	}
	else {
		t2->paths.push_back(strdup(sig));
	}

	free(sym);

	int occurs = 0;
	map<int, int>::iterator iter = t2->occurs.find(lit_num);

	if (iter != t2->occurs.end() ) { 
		occurs = iter->second; 
		t2->occurs.erase(iter);
	}
	
	occurs = occurs + 1;
	t2->occurs.insert(make_pair(lit_num, occurs));

	return t2;
}
		
Term* new_functor(Term *t1, Clause *c, vector<Sub> *mgu, int new_cl_num, char *sig, int lit_num, SpecData *spec)
{
	assert(t1 != NULL);

    	Term *t2 = new Term;
    	assert(t2 != NULL);

    	t2->type = t1->type;
    	t2->sym = sym_tree_insert_sym(t1->sym, spec->sym_tree);
    	t2->ground = true;
	t2->depth = 0;

	t2->signature = strdup(sig);

	t2->num_args = t1->num_args;
    	t2->args = (Term **)calloc(t1->num_args, sizeof(Term*));

	int str_len = strlen(t1->sym) + 1;
	int g_str_len = strlen(t1->sym) + 1;

	char *arg_sig = (char *)malloc(strlen(sig) + 5);

    	for (int i = 0; i < t1->num_args; i++) {
		switch (t1->args[i]->type) {
			case function:	
				sprintf(arg_sig, "%s-%d", sig, i+1);
				t2->args[i] = new_functor(t1->args[i], c, mgu, new_cl_num, arg_sig, lit_num, spec);
				break;

			case constant:
				t2->args[i] = new_constant(t1->args[i], spec);
				break;

			case variable:
				sprintf(arg_sig, "%s-%d", sig, i+1);
				t2->args[i] = new_variable(t1->args[i], c, mgu, new_cl_num, arg_sig, lit_num, spec);
				break;

			case atom:
				cout << "SZS: ERROR (new_functor)" << endl;
				exit(1);
		}

		
		if (t2->args[i]->ground == false)
			t2->ground = false;

		if (t2->args[i]->depth > t2->depth)
			t2->depth = t2->args[i]->depth;

		str_len += (strlen(t2->args[i]->str) + 1);
		g_str_len += (strlen(t2->args[i]->g_str) + 1);
	}

	free(arg_sig);

	char *str = (char *)malloc(str_len + 1);
	char *g_str = (char *)malloc(g_str_len + 1);

	
	if (t1->num_args > 0) {
		sprintf(str, "%s(", t1->sym);
		sprintf(g_str, "%s(", t1->sym);
	}
	else {
		sprintf(str, "%s", t1->sym);
		sprintf(g_str, "%s", t1->sym);
	}

    	for (int i = 0; i < t1->num_args; i++){
		sprintf(str, "%s%s", str, t2->args[i]->str);
		sprintf(g_str, "%s%s", g_str, t2->args[i]->g_str);

		if (i + 1 < t1->num_args) {
			sprintf(str, "%s,", str);
			sprintf(g_str, "%s,", g_str);
		}
	}

	if (t1->num_args > 0) {
		sprintf(str, "%s)", str);
		sprintf(g_str, "%s)", g_str);
	}

	t2->str = strdup(str);
	t2->g_str = strdup(g_str);

	free(str);
	free(g_str);

	t2->depth++;

    	return t2;
}

Lit* new_lit (Lit *l1, Clause *c, vector<Sub> *mgu, int new_cl_num, int lit_num, SpecData *spec)
{
     assert(l1 != NULL);

	Lit *l2 = new Lit;
	assert(l2 != NULL);

     l2->clause_num = new_cl_num;
     l2->negated = l1->negated;
	l2->last_unresolved = 0;
	l2->selected = false;

	sym_tree_insert_sym(l1->atom->sym, spec->sym_tree);

	char sig[1024];
	sprintf(sig, "%d", sym_tree_get_id(l1->atom->sym, spec->sym_tree));

     l2->atom = new_functor(l1->atom, c, mgu, new_cl_num, sig, lit_num, spec);

     l2->smt_var = NULL;

	char *g_str = (char*)malloc(strlen(l2->atom->g_str) + 2);

	if (l2->negated == true) 
		sprintf(g_str, "~%s", l2->atom->g_str);
	else
		sprintf(g_str, "%s", l2->atom->g_str);

	l2->g_str = strdup(g_str);
	free(g_str);

     return l2;
}

void free_term_instance(Term *);

void free_term_instance(Term *t)
{
	if (t == NULL)
		return;

	/* variables exist once in memory and are freed when we free c->vars */

	if (t->type == variable || (t->type == constant && t->skolem == true))
		return;

	/* t->sym will be freed when freeing the symbol tree */

	for (int i = 0; i < t->num_args; i++)
		free_term_instance(t->args[i]);

	if (t->args != NULL)
		free(t->args);

	if (t->type != atom) {

		/* atoms share g_str.  They are freed when ground_lits is freed */

		if (t->g_str != NULL)
			free(t->g_str);
	}

	if (t->type == function || t->type == atom)
		free(t->str);

	if (t->signature != NULL)
		free(t->signature);

	assert(t->paths.empty());
	assert(t->temp_paths.empty());
	assert(t->occurs.empty()); 

	free(t);

	return;
}

void free_variable_instance(Term *t)
{
	free(t->sym);
	
	if (t->g_str != NULL)
		free(t->g_str);

	if (t->signature != NULL)
		free(t->signature);

	while (!t->paths.empty()) {
		free(t->paths.front());
		t->paths.pop_front();
	}

	assert(t->temp_paths.empty());

	t->occurs.clear();

	free(t);
}



/*******************
 * Public functions
 *******************/

Clause* new_instance (Clause *c1, vector<Sub> *mgu, SpecData *spec)
{
     assert(c1 != NULL);

     Clause *c2 = new Clause;
     assert(c2 != NULL);

	c2->num_lits = c1->num_lits;
	c2->lits = (Lit**)calloc(c1->num_lits, sizeof(Lit*));
	c2->ground = true;
	c2->g_str = NULL;
	c2->signature = NULL;

	for (int i = 0; i < c2->num_lits; i++) {
 		c2->lits[i] = new_lit(c1->lits[i], c2, mgu, spec->cl_ct, i, spec);

		if (c2->lits[i]->atom->ground == false)
			c2->ground = false;
	}

	set_g_str(c2);

	c2->signature = var_map_get_clause_signature();

//	print_clause(c2, ALL);

     return c2;
}

void free_instance(Clause *c)
{
	if (c == NULL)
		return;

	for (int i = 0; i < c->num_lits; i++) { 
		free_term_instance(c->lits[i]->atom);

		if (c->lits[i]->g_str != NULL)
			free(c->lits[i]->g_str);	

		/* lits share smt_var. smt_var is deleted when deleting ground_lits */

		free(c->lits[i]);
	}

	free(c->lits);

	if (c->g_str != NULL)
		free(c->g_str);

	if (c->signature != NULL)
		free(c->signature);
	
	while (!c->vars.empty()) {
		free_variable_instance(c->vars.front());
		c->vars.pop_front();
	}

	free(c);

	return;
}

bool insert_instance(Clause *c, ClauseSet *target, SpecData *spec) 
{
	#ifdef INST_DEBUG
          cout << "Checking Redundancy..." << endl;
     #endif

	if (redundant(c, target, spec) == true) {
          #ifdef RES_DEBUG
               cout << "Found redundancy. Not adding clause..." << endl;
          #endif

		free_instance(c);
          return false;
     }

     #ifdef INST_DEBUG
          cout << "Inserting Instance ..." << endl;
     #endif


     insert_clause(c, target, &spec->cl_ct);

	if (spec_message_type(SPEC_VERBOSE, spec)) {
		if (spec->mode == SPEC_SUBSUMPTION)
			cout << "\t<SUB>";
		if (target == spec->P)
			cout << "(P) ";
		else
			cout << "(r) ";
		print_clause(c, SYM);
	}
		
     for (int l = 0; l < c->num_lits; l++) {
		c->lits[l]->selected = false;
          c->lits[l]->smt_var = insert_ground_lit(c->lits[l], spec->glits);
          assert(c->lits[l]->smt_var != NULL);
     }

     if (target == spec->R) {
          set_maximal_literals(c);
     }

	return true;
}

/* END OF FILE */
