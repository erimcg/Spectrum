/*
 * var_map.h
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * November 26, 2008
 */

#ifndef _VAR_MAP_H_
#define _VAR_MAP_H_

#include "struct.h"

Term* var_map_find(char *);
void var_map_insert(Term *);
char *var_map_get_clause_signature();
void clear_temp_paths(int, int);

#endif
