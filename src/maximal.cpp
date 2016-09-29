/*
 * maximal.cpp
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * February 27, 2009
 */

#include <iostream>
#include <map>
#include "assert.h"
#include "struct.h"
#include "string.h"

/*******************
 * Private functions
 *******************/

bool terms_equal(Term *t1, Term *t2)
{
     if (t1->sym != t2->sym)
          return false;
    
     if (t1->type == variable || t1->type == constant)
          return true;

     for (int i = 0; i < t1->num_args; i++)
          if (terms_equal(t1->args[i], t2->args[i]) == false)
               return false;

     return true;
}

void calculate_term_weights(ClauseSet *R)
{
	return;
}

bool occurs_in(Term *t1, Term *t2)
{
	assert(t1->type == variable);

	if (t2->type == variable) {
		if (t1 == t2)
			return true;
		else 
			return false;
	}

	for (int i = 0; i < t2->num_args; i++) {
		if (occurs_in(t1, t2->args[i]) == true)
			return true;
	}

	return false;
}

bool sym_order_gt(char *sym1, char *sym2)
{
	if (strcmp(sym1, sym2) > 0)
		return true;

	return false;
}

bool var_subset(Term *t, int l1, int l2) 
{
	if (t->type == variable) {

		map<int, int>::iterator iter1 = t->occurs.find(l1);
		map<int, int>::iterator iter2 = t->occurs.find(l2);

		//print_occurs(t, OCC);

		assert(iter1 != t->occurs.end());

		if (iter2 == t->occurs.end())
			return false;
		else if (iter1->second <= iter2->second)
			return true;
		else
			return false;

	}
	else {
		for (int i = 0; i < t->num_args; i++)
			if (var_subset(t->args[i], l1, l2) == false)
				return false;

	}
	
	return true;
}

bool kbo_gt(Term *t1, int j, Term *t2, int k) 
{
	if (var_subset(t2, k, j) == false)
		return false;

	if (t1->weight > t2->weight)
		return true;
	
	if (t1->weight < t2->weight)
		return false;

	assert(t1->weight == t2->weight);

	if (t1->type == variable)
		return false;

	if (t1->type == function && t2->type == variable && occurs_in(t2, t1) == true)
		return true;

	if (t2->type == variable)
		return false;	

	if (sym_order_gt(t1->sym, t2->sym) == true)
		return true; 
	 
	if (t1->sym == t2->sym) {
		for (int i = 0; i < t1->num_args; i++) {
			if (terms_equal(t1->args[i], t2->args[i]) == true) 
				continue;
			
			if (kbo_gt(t1->args[i], j, t2->args[i], k) == true)
				return true;
			else
				return false;
		}
	}

     return false;
}

int get_symbol_weight(char *sym)
{

	return 1;
}

void set_term_weight(Term *t)
{
	if (t->type == variable) { 
		t->weight = 1;
	}
	else if (t->type == constant) {
		t->weight = get_symbol_weight(t->sym);
	}
	else {
		t->weight = get_symbol_weight(t->sym);

		for (int i = 0; i < t->num_args; i++) {
			set_term_weight(t->args[i]);
			t->weight += t->args[i]->weight;
		}
	}
}

/*******************
 * Public functions
 *******************/

void set_maximal_literals(Clause *C)
{
     Lit * lit1;
     Lit * lit2;

	for (int j = 0; j < C->num_lits; j++)
		set_term_weight(C->lits[j]->atom);

	for (int j = 0; j < C->num_lits; j++) {
		lit1 = C->lits[j];
		lit1->selected = true;  //i.e. lit is maximal

		for (int k = 0; k < C->num_lits; k++) {
			if (k == j)
				continue;

			lit2 = C->lits[k];
			if (kbo_gt(lit2->atom, k, lit1->atom, j) == true) {
				lit1->selected = false;
				break;
			}
		}
	}
	
	return;
}

void set_maximal_literals(ClauseSet *R)
{
	calculate_term_weights(R);

     for (int i = 0; i < R->num_clauses; i++) 
		set_maximal_literals(R->clauses[i]);

	return;
}

// END OF FILE
