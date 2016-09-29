/*
 * unify.cpp
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * Last Modified on October 16, 2008
 */

//#define DEBUG

#include <vector>
#include <iostream>
#include <assert.h>
#include "unify.h"
#include "struct.h"
#include "sym_tree.h"
#include "ground_lits.h"

using namespace std;

Term* dup_term(Term *t1)
{
     assert(t1 != NULL);

     Term *t2 = new Term;
     assert(t2 != NULL);

     t2->type = t1->type;
     t2->sym = t1->sym;
     t2->num_args = t1->num_args;

     if (t2->num_args > 0)
          t2->args = (Term **)calloc(t2->num_args, sizeof(Term*));
     else
          t2->args = NULL;

     t2->depth = 0;
     t2->weight = 0;
     t2->ground = 0;
     t2->g_str = t1->g_str;
     t2->signature = NULL;
     t2->id = 0;

     for (int i = 0; i < t2->num_args; i++)
          t2->args[i] = dup_term(t1->args[i]);

     return t2;
}

void free_dup(Term *t)
{
     assert(t != NULL);

     for (int i = 0; i < t->num_args; i++)
          free_dup(t->args[i]);
    
     free(t->args);

     free(t);

     return;
}


/*
 * occurs() returns true if the variable s occurs in term t otherwise returns false.
 * s is assumed to be a variable and t is any term.
 */

bool occurs(Term *s, Term *t)
{
	if (t->type == constant)
		return false;

	if (t->type == variable) {
		if (t->sym != s->sym)
			return false;
		else
			return true;
	}

	for (int i = 0; i < t->num_args; i++)
          if (occurs(s, t->args[i]) == true)
               return true;

     return false;
}

void replace(Term *to_replace, Term *replace_with, Term **replace_in)
{
	assert(to_replace->type == variable);
	assert(occurs(to_replace, replace_with) == false);

     if(to_replace->sym == (*replace_in)->sym) {
          free_dup(*replace_in);
          *replace_in = dup_term(replace_with);
		return;
     }

	for (int i = 0; i < (*replace_in)->num_args; i++)
          replace(to_replace, replace_with, &(*replace_in)->args[i]);
}

void replace_terms(Term *to_replace, Term *replace_with, vector <Sub> *mgu)
{
	#ifdef DEBUG
		cout << "Replace "; print_term(to_replace, SYM); 
		cout << " with "; print_term(replace_with, SYM); cout << endl;
		print_unifier(mgu, SYM);
	#endif

     for(vector<Sub>::iterator head = mgu->begin(); head != mgu->end(); head++) {
          replace(to_replace, replace_with, &(head->domain));
          replace(to_replace, replace_with, &(head->range));
     }

	#ifdef DEBUG
		print_unifier(mgu, SYM);
	#endif
}

bool mgu_is_renaming(vector<Sub> *mgu)
{
	bool is_renaming = true;

     for(vector<Sub>::iterator head = mgu->begin(); head != mgu->end(); head++) {
		if (head->range->type != variable)
			is_renaming = false;
	}

	return is_renaming;
}

void clear_mgu_vector(vector<Sub> U)
{
	Sub E;

     while(!U.empty()) {
		E = U.back();
          free_dup(E.domain);
          free_dup(E.range);
		U.pop_back();
	}
}

bool unifiable(Lit* t1, Lit* t2, vector<Sub> *mgu)
{
     vector <Sub> U;
     Sub E;
     E.domain = dup_term(t1->atom);
     E.range = dup_term(t2->atom);
     U.push_back(E);

     while(!U.empty()) {
          vector<Sub>::iterator head = U.begin();
          Term *s = head->domain;
          Term *t = head->range;

          /*
           * If the domain s is a term of the form f(s1,...,sn) then we either
           *   a) swap s and t IF t is a variable or
           *   b) return false IF t is a term with a different function symbol else
           *   c) check the unifiability of the arguments of s and t
           */

          if( s->type != variable ) {
               if( t->type == variable ) {
                    U.erase(head);
                    E.domain = t;
                    E.range = s;
                    U.push_back(E);
               }
               else {
                    assert(s->sym != NULL && t->sym != NULL);

                    if(s->sym != t->sym){
					clear_mgu_vector(U);

                         return false;
                    }
                    else {
                         U.erase(head);

					assert(s->num_args == t->num_args);

					for(int i = 0; i < s->num_args; i++) {
                              E.domain = dup_term(s->args[i]);
                              E.range = dup_term(t->args[i]);
                              U.push_back(E);
					}

                         free_dup(s);
                         free_dup(t);
                    }
               }
          }

          /*
           * If the domain s is a variable then we
           *   a) process the next pair of terms IF t is the same variable or
           *   b) return false IF s occurs in t or
           *   c) replace all instances of s in U and mgu with t AND add s = t to mgu.
           */

          else {

               if(s->sym == t->sym) {
                    U.erase(head);
                    free_dup(s);
                    free_dup(t);
               }
               else if(occurs(s,t)) {
				clear_mgu_vector(U);

                    return false;
               }
               else {
                    U.erase(head);

                    replace_terms(s, t, &U);
                    replace_terms(s, t, mgu);

                    E.domain = s;
                    E.range = t;
                    mgu->push_back(E);

               }
          }
     }

	clear_mgu_vector(U);
	return true;
}

Sub *mgu_get_sub(vector<Sub> *mgu, Term *t)
{
	if (mgu == NULL)
		return NULL;

     for(vector<Sub>::iterator head = mgu->begin(); head != mgu->end(); head++)
		if (head->domain->sym == t->sym)
			return &(*head);

	return NULL;	
}

void free_mgu(vector<Sub> *mgu)
{
	assert(mgu != NULL);

	clear_mgu_vector(*mgu);
	free(mgu);
}

/* END OF FILE */
