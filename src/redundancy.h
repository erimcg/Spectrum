#ifndef _REDUN_H
#define _REDUN_H

#include "struct.h"
#include "specdata.h"

bool subsumes(Clause *, Clause *, SpecData *);
bool redundant(Clause *, ClauseSet *, SpecData *spec);
bool is_tautology(Clause *);

#endif
