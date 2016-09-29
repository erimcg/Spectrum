/*
 * struct.h
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * Last Modified: October 1, 2008
 */

#ifndef _STRUCT_H_
#define _STRUCT_H_

#define PrintMode unsigned int 

#include <vector>
#include <list>
#include <map>

using namespace std;

enum	s_bool { 
	s_false = -1, 
	s_undef, 
	s_true  
};

enum TermType {
	variable,
	constant,
	function,
	atom
};

enum PMode {
	TVAL		= 0x02,	// lit->smt_var->truth_val
	SEL		= 0x04,  	// lit->selected
	SYM		= 0x08,	// term->sym
	TYPE 	= 0x10,	// term->type
	GRND		= 0x20,	// lit->atom->ground
	GSTR		= 0x40,	// lit->atom->g_str
	DPTH		= 0x80,	// lit->atom->depth
	SMT		= 0x100,	// lit->smt_var->smt_expr
	OCC		= 0x200,  // lit->occurs
	VSIG		= 0x400,  // clause->signature
	ALL		= 0xFFFF,	// ALL
}; 

typedef struct term_s {
	TermType type;
	char *sym;
	int num_args;			// functors only
	struct term_s **args;	// functors only
	int depth;		
	int weight;
	bool ground;
	bool skolem;
	char *str;
	char *g_str;
	char *signature;
	int id;			
	list<char *> paths;
	list<char *> temp_paths;
	map<int, int> occurs;
}Term;

typedef struct smt_var_s {
	int num_lits;
     void *smt_expr;
     s_bool truth_val;
}SMTVar;

typedef struct sub_s {
 	Term *domain;
	Term *range;
}Sub;

typedef struct lit_s {
	int clause_num;
	bool negated;
	Term *atom;
	char *g_str;
	SMTVar *smt_var;
	bool selected;
	int last_unresolved;
}Lit;

typedef struct cl_s {
	bool ground;
	char *g_str;
	char *signature;
	int num_lits;
	Lit **lits;
	list<Term *> vars;
}Clause;

typedef struct cs_s {
	int num_clauses;
	Clause **clauses;
}ClauseSet;

void print_sub (Sub *, PrintMode);
void print_unifier (vector<Sub> *, PrintMode);
void print_complements (Lit *, PrintMode);
void print_term (Term *, PrintMode);
void print_smt_var (SMTVar *, PrintMode);
void print_occurs(Term *, PrintMode);

void print_lit (Lit *, PrintMode);
void print_clause (Clause *, PrintMode);
void print_clause_set (ClauseSet *, PrintMode);

void insert_clause(Clause *, ClauseSet *, int*);
void remove_clause(int, ClauseSet *);

void set_g_str(Clause *);
void set_lit_str(Lit *);

#endif

