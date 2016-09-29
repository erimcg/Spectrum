/*
 * sym_tree.cpp
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * November 12, 2008
 */

/*
 * The purposes of a SymTree is twofold.  
 *
 * The first purpose is to reduce the memory used by the solver by creating only
 * a single pointer for each symbol in a problem.  When a problem is parsed, each time a new symbol 
 * (constant, predicate, or function) is parsed, sym_tree_insert_sym(sym, tree) is called with 
 * the symbol and the tree as arguments.  If the symbol has not found in the tree then sym is duplicated 
 * on the heap and its pointer inserted into the tree and returned. If the symbol already occurs in the 
 * tree, the pointer to the symbol stored in the tree is returned.  Variable symbols are not stored
 * in SymTree (but exist only once in memory too, see var_map.cpp).
 *
 * The second purpose of a SymTree is to define a unique integer for each predicate symbol.  These
 * integer values are used to create clause signatures (see var_map.cpp).  Rather then
 * differentiating nodes according to types, when a new node in the sym_tree is added, every node is
 * given a unique integer. 
 *
 */

#include <iostream>
#include <string.h>
#include <assert.h>
#include "sym_tree.h"

using namespace std;

/********************
 * Private functions
 ********************/

char *sym_tree_insert_sym(char *sym, SymTreeNode *&node, SymTree *sym_tree)
{
	if (node == NULL) {
		node = new SymTreeNode;

		node->sym = strdup(sym);
		node->id = sym_tree->sym_ct;
		sym_tree->sym_ct++;

		node->lchild = NULL;
		node->rchild = NULL;

		return node->sym;
	}

	int val = strcmp(node->sym, sym);

	if (val == 0)
		return node->sym;
	else if (val < 0)
		return sym_tree_insert_sym(sym, node->lchild, sym_tree);
	else
		return sym_tree_insert_sym(sym, node->rchild, sym_tree);
}

SymTreeNode* sym_tree_get_node(char *sym, SymTreeNode* node)
{
	if (node == NULL)
		return NULL;

	int val = strcmp(node->sym, sym);

	if (val == 0) {
		return node;
	}
	else if (val < 0) 
		return sym_tree_get_node(sym, node->lchild);
	else 
		return sym_tree_get_node(sym, node->rchild);	
}

void sym_tree_print_node(SymTreeNode* node) {
	if (node == NULL) 
		return;

	sym_tree_print_node(node->lchild);

	cout << "(" << node->sym << ": " << node->id << ")" << endl;

	sym_tree_print_node(node->rchild);
	return;
}

void sym_tree_delete_node(SymTreeNode *node)
{
	if (node->lchild != NULL)
		sym_tree_delete_node(node->lchild);

	if (node->rchild != NULL)
		sym_tree_delete_node(node->rchild);

	free(node->sym);
	free(node);

	return;
}	

/********************
 * Public functions
 ********************/

SymTree *new_sym_tree()
{
	SymTree *sym_tree = new SymTree;
	assert(sym_tree != NULL);
	
	sym_tree->root = NULL;
	sym_tree->sym_ct = 0;

	return sym_tree;
}

char *sym_tree_insert_sym(char *sym, SymTree *sym_tree)
{
	return sym_tree_insert_sym(sym, sym_tree->root, sym_tree);
}

int sym_tree_get_id(char *sym, SymTree *sym_tree)
{
	SymTreeNode *node = sym_tree_get_node(sym, sym_tree->root);
	
	assert(node != NULL);

	return node->id;
}

void sym_tree_print(SymTree *sym_tree) 
{
     cout << "/*** Symbol Tree ***/" << endl;

     sym_tree_print_node(sym_tree->root);
}

void sym_tree_free(SymTree *sym_tree)
{
	sym_tree_delete_node(sym_tree->root);
	free(sym_tree);
}
 
/*** END OF FILE ***/

