/*
 * primial_pi.h
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * October 9, 2008
 */

#ifndef _PRIMAL_PI_H_
#define _PRIMAL_PI_H_

#include "struct.h"
#include "spectrum.h"

enum PPiRtnCode {
	PPI_INIT = 0,
	PPI_UNSAT,
	PPI_CLAUSE_ADDED,
	PPI_NO_CLAUSE_ADDED
};

PPiRtnCode run_primal_pi(SpecData *);

#endif
