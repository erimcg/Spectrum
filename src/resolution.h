/*
 * resolution.h
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * February 17, 2009 
 */

#ifndef _RESOLUTION_H_
#define _RESOLUTION_H_

#include "struct.h"
#include "spectrum.h"

enum ResRtnCode {
	RES_INIT = 0,
	RES_UNSAT,
	RES_CLAUSE_ADDED,
	RES_NO_CLAUSE_ADDED
};

ResRtnCode run_resolution(SpecData *);

#endif
