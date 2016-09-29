/*
 * skolem.cpp
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * April 13, 2009
 */

#include <utility>
#include "assert.h"

#include "struct.h"

int skolem_ct = 0;

/*******************
 * Private functions
 *******************/

void skolemize_term(Term *t)
{
	if (t->type == variable) {
	
		char buf[128];
		sprintf(buf, "sk%d", skolem_ct++);

		free(t->sym);
		t->sym = strdup(buf);

		t->type = constant;
		t->ground = true;
		t->skolem = true;

		free(t->g_str);
		t->g_str = strdup(buf);
	}
	else if (t->type == function || t->type == atom) {
		for (int i = 0; i < t->num_args; i++)
			skolemize_term(t->args[i]);
	}

	return;
}

/*******************
 * Public functions
 *******************/

void skolemize(Clause *c)
{
	for (int i = 0; i < c->num_lits; i++)
		skolemize_term(c->lits[i]->atom); 

	skolem_ct = 0;

	return;
}

// END OF FILE
