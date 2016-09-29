/*
 * instantiate.h
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * November 13, 2008
 */

#ifndef _INSTANTIATE_H_
#define _INSTANTIATE_H_

#include "struct.h"
#include "specdata.h"

Clause* new_instance(Clause *, vector<Sub> *, SpecData *);
bool insert_instance(Clause *, ClauseSet *, SpecData*);
void free_instance(Clause *);

#endif
