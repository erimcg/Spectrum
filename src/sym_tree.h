/*
 * sym_tree.h
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * November 12, 2008
 */

#ifndef _SYM_TREE_H_
#define _SYM_TREE_H_

typedef struct sym_tree_node {
	char *sym;
	int id;
	struct sym_tree_node* lchild;
	struct sym_tree_node* rchild;
}SymTreeNode;

typedef struct sym_tree {
	SymTreeNode *root;
	int sym_ct;
} SymTree;

SymTree *new_sym_tree();
void sym_tree_free(SymTree *);

char *sym_tree_insert_sym(char *, SymTree *);
int sym_tree_get_id(char *, SymTree *);
void sym_tree_print(SymTree *);

#endif
