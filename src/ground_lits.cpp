/*
 * ground_lits.cpp
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * October 26, 2008
 */

#include <iostream>
#include <string.h>
#include "assert.h"

#include "struct.h"
#include "ground_lits.h"
//#include "yices_c.h"

using namespace std;

/*
 * In Partial Instantiation, variants are considered equivalent as propositional variables.
 * For each literal, we determine its ground string. MORE LATER ...
 */

/********************
 * Private functions
 *******************/

void insert_prop_link(PropLink* &link, SMTData *smt_data) 
{
	
	PropLink *l = new PropLink;
	l->smt_data = smt_data;

	if (link == NULL)
		l->next = NULL;
	else
		l->next = link;

	link = l;

	return;	
}

SMTVar* insert_prop_node(PropNode* &prop_node, Lit* lit, GLits *glits) 
{
	if(prop_node == NULL) {
		prop_node = new PropNode;

		SMTData *smt_data = new SMTData;

		SMTVar *neg_var = new SMTVar;
		neg_var->num_lits = 0;
		neg_var->smt_expr = NULL;
		neg_var->truth_val = s_false;

		SMTVar *pos_var = new SMTVar;
		pos_var->num_lits = 0;
		pos_var->smt_expr = NULL;
		pos_var->truth_val = s_false;

		smt_data->g_str = lit->atom->g_str;

		smt_data->neg_var = neg_var;
		smt_data->pos_var = pos_var;

		prop_node->smt_data = smt_data;
		prop_node->lchild = NULL;
		prop_node->rchild = NULL;
	
		insert_prop_link(glits->undeclared, smt_data);

		if (lit->negated == true) {
			neg_var->num_lits++;
			return neg_var;
		}
		else {
			pos_var->num_lits++;
			return pos_var;
		}
	}

	int val = strcmp(prop_node->smt_data->g_str, lit->atom->g_str);

	if (val == 0) {
		char *temp = lit->atom->g_str;
		lit->atom->g_str = prop_node->smt_data->g_str;

		if (temp != NULL)
			free(temp);

		if (lit->negated == false) {
			prop_node->smt_data->pos_var->num_lits++;
			return prop_node->smt_data->pos_var;
		}
		else {
			if (prop_node->smt_data->neg_var->num_lits == 0)
				insert_prop_link(glits->undeclared, prop_node->smt_data);

			prop_node->smt_data->neg_var->num_lits++;
			return prop_node->smt_data->neg_var;
		}
	}
	else if (val < 0) 
		return insert_prop_node(prop_node->rchild, lit, glits);
	else 
		return insert_prop_node(prop_node->lchild, lit, glits);	

}

void set_truth_val(PropNode *p, SMTSolver *smt)
{
	if (p == NULL)
		return;

	p->smt_data->pos_var->truth_val = smt->eval_expr(p->smt_data->pos_var->smt_expr);

	if (p->smt_data->neg_var->smt_expr != NULL) 
		p->smt_data->neg_var->truth_val = smt->eval_expr(p->smt_data->neg_var->smt_expr);
	else
		p->smt_data->neg_var->truth_val = s_undef;

	set_truth_val(p->lchild, smt);
	set_truth_val(p->rchild, smt);
}

void print_smt_data(SMTData *smt_data)
{
	if (smt_data == NULL)
		return;

	cout << smt_data->g_str << " : " << &(smt_data->g_str) << endl;

	print_smt_var(smt_data->pos_var, SMT);
	print_smt_var(smt_data->neg_var, SMT);

	return;
}

void print_prop_link(PropLink *link)
{
	while (link != NULL) {
		print_smt_data(link->smt_data);
		link = link->next;
	}

	return;
}

void print_prop_node(PropNode* node)
{
	if (node == NULL)
		return;

	print_prop_node(node->lchild);
	print_smt_data(node->smt_data);
	print_prop_node(node->rchild);

	return;
}

void glits_delete_smt_data(SMTData *data)
{
	assert(data != NULL);

	if (data->pos_var != NULL) {
		free(data->pos_var->smt_expr);
		free(data->pos_var);
	}

	if (data->neg_var != NULL) {
		free(data->neg_var->smt_expr);
		free(data->neg_var);
	}

	assert(data->g_str != NULL);
	
	free(data->g_str);

	free(data);
}

void glits_delete_prop_link(PropLink *link)
{
	if (link->next != NULL)
		glits_delete_prop_link(link->next);

	/* link->smt_data is freed when prop nodes are freed */

	free(link);
}

void glits_delete_prop_node(PropNode *node) 
{
	assert(node != NULL);

	if (node->lchild != NULL)
		glits_delete_prop_node(node->lchild);

	if (node->rchild != NULL)
	glits_delete_prop_node(node->rchild);

	if (node->smt_data != NULL)
		glits_delete_smt_data(node->smt_data);

	free(node);

	return;
}


/******************
 * Public functions
 *******************/

GLits *new_ground_lits()
{
	GLits *glits = new GLits;
	assert(glits != NULL);

	glits->root = NULL;
	glits->undeclared = NULL;

	return glits;
}

SMTVar* insert_ground_lit(Lit* lit, GLits *glits) 
{
	return insert_prop_node(glits->root, lit, glits);
}

void set_smt_expr(SMTSolver *smt, GLits *glits)
{
     if (glits == NULL)
          return;

     PropLink *link = glits->undeclared;
     PropLink *temp = NULL;

     while (link != NULL) {
		if (link->smt_data->pos_var->smt_expr == NULL) {
	          link->smt_data->pos_var->smt_expr = smt->mk_fresh_bool_var();
		}

		if (link->smt_data->neg_var->num_lits > 0) {
          	link->smt_data->neg_var->smt_expr = smt->mk_not(link->smt_data->pos_var->smt_expr);
		}

          temp = link;
          link = link->next;
          free(temp);
     }

	glits->undeclared = NULL;

     return;
}

void set_smt_truth_val(SMTSolver *smt, GLits *glits) 
{
	if (smt == NULL || glits == NULL)
		return;

	set_truth_val(glits->root, smt);
	
	return;
}

void print_ground_lits(GLits *glits)
{
	if (glits == NULL) {
		cout << "No Ground Literals Defined" << endl;
		return;
	} 
	else { 
     	cout << "/*** Ground Literals ***/" << endl;
	}

     if (glits->undeclared != NULL) {
          cout << "Undeclared SMT Variables" << endl;
		print_prop_link(glits->undeclared);
	}

     if (glits->root != NULL) {
          cout << "All Ground Literals" << endl;
          print_prop_node(glits->root);
     }

     cout << endl;
	return;
}

void glits_free(GLits *glits)
{
	if (glits->root != NULL)
		glits_delete_prop_node(glits->root);

	if (glits->undeclared != NULL)
		glits_delete_prop_link(glits->undeclared);

	free(glits);
}


/* END OF FILE */

