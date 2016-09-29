/*
 * unify.h
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * Last Modified on October 16, 2008
 */

#ifndef _UNIFY_H_
#define _UNIFY_H_

#include <vector>
#include "struct.h"

using namespace std;

bool mgu_is_renaming(vector<Sub> *);
bool unifiable(Lit *, Lit *, vector<Sub> *);
Sub* mgu_get_sub(vector<Sub> *, Term *);
void free_mgu(vector<Sub> *);

#endif
