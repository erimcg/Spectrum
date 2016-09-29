/*
 * spectrum.h
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * October 9, 2008
 */

#ifndef _SPECTRUM_H_
#define _SPECTRUM_H_

#include "specdata.h"

enum SZS_Status {
	SZS_P_UNSATISFIABLE = 0,
	SZS_R_UNSATISFIABLE,
	SZS_SATISFIABLE
};

SZS_Status run_spectrum(SpecData *);

#endif
