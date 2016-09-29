/*
 * spectrum.cpp
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * February 17, 2009 
 */

//#define SPEC_DEBUG

#include <iostream>

#include "struct.h"
#include "specdata.h"
#include "distribute.h"
#include "maximal.h"
#include "primal_pi.h"
#include "resolution.h"

SZS_Status run_spectrum(SpecData *spec)
{
	PPiRtnCode rc1 = PPI_INIT;
	ResRtnCode rc2 = RES_INIT; 

	/* 
	 * Partition clause set 
	 */

	distribute_spec_problem(spec);

	if (spec_message_type(SPEC_SOLUTION, spec) && spec_mode(SPEC_SUBSUMPTION, spec) == false) {
		cout << "Distribution Set" << endl;
		spec_print_data(spec);
	}

	/* 
	 * Run Spectrum algorithm 
	 */

	while (true) {

		if (spec_message_type(SPEC_VERBOSE, spec)) 
			cout << "Spectrum: Running PI" << endl;

		rc1 = run_primal_pi(spec);

		if (rc1 == PPI_UNSAT) {
			return SZS_P_UNSATISFIABLE;
		}
		else if (rc1 == PPI_CLAUSE_ADDED) {
			#ifdef SPEC_DEBUG
				cout << "PPI added new clause." << endl;
			#endif
		}
		else if (rc1 == PPI_NO_CLAUSE_ADDED) {
			#ifdef SPEC_DEBUG
				cout << "PPI did not add new clauses.  P is SAT." << endl;
			#endif
		}
		else {
			cout << "SZS: Error: Invalid PPiRtnCode" << endl;
			exit(1);
		}
		
		if (spec_message_type(SPEC_VERBOSE, spec)) 
			cout << "Spectrum: Running Resolution" << endl;

		rc2 = run_resolution(spec);

		if (rc2 == RES_UNSAT) {
			return SZS_R_UNSATISFIABLE;
		}
		else if (rc2 == RES_CLAUSE_ADDED) {
			#ifdef SPEC_DEBUG
				cout << "RES added new clause." << endl;
			#endif
			// continue
		}
		else if (rc2 == RES_NO_CLAUSE_ADDED) {
			if (rc1 == PPI_NO_CLAUSE_ADDED)
				return SZS_SATISFIABLE;
			// else PI added new clause, continue
		}
		else {
			cout << "SZS: Error: Invalid ResRtnCode" << endl;
			exit(1);
		}

	}
}


/* END OF FILE */
