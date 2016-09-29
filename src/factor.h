#ifndef _FACTOR_H
#define _FACTOR_H

#include "struct.h"
#include "specdata.h"

Clause * safe_factor(Clause *, SpecData *);
void insert_all_factors(Clause *, SpecData *);
bool safely_factors(Clause *, Clause *, ClauseSet *, SpecData *);

#endif
