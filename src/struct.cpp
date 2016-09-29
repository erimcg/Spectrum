/*
 * struct.cpp
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * Last Modified: September 30, 2008
 */

#include <iostream>
#include <assert.h>
#include <vector>
#include <list>

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "struct.h"

using namespace std;

struct strCmp {
     bool operator()( const char* s1, const char* s2 ) const {
          return (strcmp( s1, s2 ) < 0);
     }
};

/***********************************************************************
 * Functions which print to struct data to stdout. 
 ***********************************************************************/

void print_sub(Sub *s, PrintMode mode)
{
	cout << "\t\t\t";
	print_term(s->domain, mode);
	cout << " = ";
	print_term(s->range, mode);
	cout << endl;

	return;
}

void print_unifier(vector<Sub> *mgu, PrintMode mode)
{
	vector<Sub> subs = *mgu;

     for(unsigned int i = 0; i < subs.size(); i++)
		print_sub(&subs[i], SYM);
}

void print_term(Term *t, PrintMode mode)
{
	assert(t->sym != NULL);

	if (t->type == variable)
		cout << t->id;
	else
		cout << t->sym;

	if ((mode & OCC) > 0)
		print_occurs(t, mode);

	if (t->num_args > 0) {
		cout << "("; 
		for (int i = 0; i < t->num_args;) {
			print_term(t->args[i], mode);
 
			if (++i < t->num_args)
				cout << ",";
		}
		cout << ")";
	}
		
	return;
}
void print_occurs(Term *t, PrintMode mode)
{
	if ((t->type == variable) && ((mode & OCC) > 0)) {
		cout << endl;

		for (map<int, int>::iterator iter = t->occurs.begin(); iter != t->occurs.end(); ++iter ) {
			cout << "\t" << t->id;
			cout << " occurs in lit :" << (*iter).first << " (" << (*iter).second <<  " times)" << endl;
		}
	}
}

void print_smt_var(SMTVar* v, PrintMode mode)
{
	if (v->smt_expr == NULL)
		cout << "\t" << "null = ";
	else
		cout << "\t" << v->smt_expr << " = ";
 
	if (v->truth_val == s_true)
		cout << "T" << endl;
	else if (v->truth_val == s_false)
		cout << "F" << endl;
	if (v->truth_val == s_undef)
		cout << "?" << endl;
}

void print_lit(Lit *l, PrintMode mode)
{
	if (l->negated == true)
		cout << "~";

	print_term(l->atom, mode);

	if ((mode & SEL) > 0) {
		if (l->selected == true)
			cout << "*";
	}

	if ((mode & TVAL) > 0) {
		if (l->smt_var != NULL) {
			if (l->smt_var->truth_val == s_true) 
				cout << " [T] ";
			else if (l->smt_var->truth_val == s_false) 
				cout << " [F] ";
			else
				cout << " [?] ";
		}
	}

	if (mode <= SYM) 
		return;

	cout << "\t" << "clause_num: " << l->clause_num << endl;
 
	if ((mode & GRND) > 0) {
		cout << "\t" << "ground: ";
 
		if (l->atom->ground == true)
			cout << "T" << endl;
		else 
			cout << "F" << endl;
	}

	if ((mode & GSTR) > 0) {
		cout << "\t" << "grnd str: ";
	
		if (l->g_str == NULL)
			cout << "null" << endl;
		else 
			cout << l->g_str << endl;
	}

	if ((mode & DPTH) > 0) {
		cout << "\t" << "depth: " << l->atom->depth << endl;
	}

	if ((mode & SMT) > 0) {
		cout << "\t" << "smt_expr: ";

		if (l->smt_var == NULL)
			cout << "null" << endl;
		else if (l->smt_var->smt_expr == NULL)
			cout << "null" << endl;
		else
			cout << l->smt_var->smt_expr << endl;
	
		cout << "\t" << "truth_val: ";

		if (l->smt_var == NULL)
			cout << "null" << endl;
		else if (l->smt_var->truth_val == s_true) 
			cout << "T" << endl; 
		else if (l->smt_var->truth_val == s_false) 
			cout << "F" << endl; 
		else
			cout << "?" << endl; 

	}

	return;
}

void print_clause(Clause *c, PrintMode mode)
{
	if ((mode & VSIG) > 0) {
		cout << "g_str: ";
		if (c->g_str != NULL)
			cout << c->g_str << endl;
		else
			cout << "null" << endl;

		cout << "v_sig: ";
		if (c->signature != NULL)
		 	cout << c->signature << endl;
		else
			cout << "null" << endl;

		cout << "ground: ";
		if (c->ground == true)
			cout << "T" << endl;
		else if (c->ground == false)
			cout << "F" << endl;
		else
			cout << "?" << endl;
	}

	if (mode == VSIG)
		return;

	for (int i = 0; i < c->num_lits;) {	 	
		print_lit(c->lits[i], mode);

		if (++i < c->num_lits)
			cout << " | ";
	}
	cout << endl;
}

void print_clause_set(ClauseSet *cs, PrintMode mode)
{
	if (cs != NULL) {
		for (int i = 0; i < cs->num_clauses; i++)
			print_clause(cs->clauses[i], mode);
	}
}


/*********************************************
 * Modify data structures
 **************************************************/

void insert_clause(Clause *c, ClauseSet *cs, int *cl_ct)
{
	assert(cs != NULL && c != NULL);
	
	Clause **clauses = (Clause**)calloc(cs->num_clauses + 1, sizeof(Clause*));

	int i = 0;
	for (; i < cs->num_clauses; i++) 
		clauses[i] = cs->clauses[i];

	for (int j = 0; j < c->num_lits; j++)
		c->lits[j]->clause_num = i;
	clauses[i] = c;

	cs->num_clauses++;
	(*cl_ct)++;

	if (cs->clauses != NULL)
		free(cs->clauses);
	cs->clauses = clauses;

	return;
}

void set_g_str(Clause *clause)
{
     strCmp compare;
	list<char *> g_str_list;
	int g_str_len = 0;
	char *g_str;
	list<char *>::iterator it;

	assert(clause->num_lits > 0);

	for (int i = 0; i < clause->num_lits; i++) {
		g_str_len = g_str_len + strlen(clause->lits[i]->g_str) + 1;
		g_str_list.push_back(clause->lits[i]->g_str);
	}
	
     g_str_list.sort(compare);

	g_str = (char *)calloc(g_str_len +1, sizeof(char));	

	for( it = g_str_list.begin(); it != g_str_list.end(); ++it ) {
		sprintf(g_str, "%s|%s", g_str, *it);
	}

	//cout << "G_STR: " << g_str << endl;

	clause->g_str = g_str;

	/*
	 * TODO: find out why when uncommenting the above line, we get a segfault
	 */

	return;
}

void remove_clause(int index, ClauseSet *cs)
{
	assert(cs != NULL);
	assert(index >= 0 && index < cs->num_clauses);

	Clause **clauses = (Clause**)calloc(cs->num_clauses -1 , sizeof(Clause*));

	int j = 0;
	for (int i = 0; i < cs->num_clauses; i++) {
		if (i != index) {
			clauses[j] = cs->clauses[i];
			j++;
		}
	}

	cs->num_clauses--;
	/* Note: we do not alter spec->cl_ct so as 
	   to not break variables renamed apart. */

	free(cs->clauses);
	cs->clauses = clauses;

	return;
}

/* END OF FILE */





