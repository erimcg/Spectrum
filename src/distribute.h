#ifndef _DISTRIB_H
#define _DISTRIB_H

#include "struct.h"

ClauseSet * distribute_get_target(Clause *, SpecData *); 
void distribute_spec_problem(SpecData *);

#endif
