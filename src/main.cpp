/*
 * main.cpp
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * October 26, 2008
 */

#include <map>
#include <string>
#include <iostream>

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <getopt.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h> 

#include "struct.h"
#include "tptp_parser.h"
#include "specdata.h"
#include "spectrum.h"
#include "sym_tree.h"

#define VERSION_NUMBER 		"1.0.0"

using namespace std;

/*******************************************************
 * Global data structures used in multiple source files. 
 *******************************************************/
SpecData *spec = NULL;

char theorem_file[128];					
char theorem_name[128];					

/************
 * Help menu
 ************/

void print_help(char *program_name) {
	cout << program_name << "[OPTION]... FILE" << endl;
	cout << endl;
	cout << "  -v,    \tprint verbose messaging" << endl;
	cout << "  --help \tdisplay this help and exit" << endl;
	cout << endl;
	cout << "  Report bugs to mcgregre@clarkson.edu" << endl;
	exit(0);
} 

/****************************************************
 * Signal handler
 ****************************************************/

static void timout_interupt_handler(int signo)
{
	cout << "SZS status TimeOut for " << theorem_name << endl;
	exit(0);
}

static void segv_interupt_handler(int signo)
{
	cout << "SZS status Error for " << theorem_name << ": bounds exceeded" << endl;
	exit(1);
}

/************************************
 * Gracefully exit program 
 ************************************/

void remove_files_and_exit()
{

	exit(0);
}

/****************************************************
 * Parse the file name from the path.
 * Both theorem_file and theorem_name are global vars
 *****************************************************/
void set_file_name()
{
     char *last_tok = NULL;
     struct stat buf;

	memset(&theorem_name, '\0', sizeof(theorem_name));

     if (theorem_file == NULL)
          return;

     if (stat(theorem_file, &buf) < 0)
          return;

     if (!S_ISREG(buf.st_mode))
          return;

     char *tmp = strdup(theorem_file);
     char *tok = strtok(tmp, "/");

     if (tok == NULL) {
		strcpy(theorem_name, tmp);
		free(tmp);
          return;
	}
     else
          last_tok = tok;

     while ((tok = strtok(NULL, "/")) != NULL)
          last_tok = tok;

	strcpy(theorem_name, last_tok);
	free(tmp);
     return;
}

int main (int argc, char *argv[])
{
	//yydebug = 1;
	
	int c;								/* option variable 				*/
	opterr = 0;							/* getopt error 				*/

	spec = new_spec_data();

	/************************************************
	 * Make sure we can intercept SIGALRM and SIGXCPU
	 ************************************************/

	if (signal(SIGXCPU, timout_interupt_handler) == SIG_ERR) {
		cout << "SZS status Error: SIGXCPU not catchable" << endl;
		exit(1);
	}
	
	if (signal(SIGALRM, timout_interupt_handler) == SIG_ERR) {
		cout << "SZS status Error: SIGALRM not catchable" << endl;
		exit(1);
	}

	if (signal(SIGSEGV, segv_interupt_handler) == SIG_ERR) {
		cout << "SZS status Error: SIGSEGV not catchable" << endl;
		exit(1);
	}

	/************************ 
	 * Parse the command line 
	 ************************/

	if (argc == 1) {
		cout << "SZS status InputError: too few arguments" << endl;
		exit(1);
	}

	while (1) {
		static struct option long_options[] = {	
			{"help", no_argument, 0, 0},
			{0,0,0,0}
		};

		int option_index = 0;

		c = getopt_long(argc, argv, "rpvsg", long_options, &option_index);

		/*
		 * Options:
		 * p - All clauses in P. Partial Instantiation only.
		 * r - All clauses in R. Resolution only.
		 * g-  All ground in P, others in R.
		 * v - print verbose messaging
		 * s - print initial distribution set and solution
		 */
 

		if (c == -1)
			break;
	
		switch(c) {
			case 0:
				print_help(argv[0]);
				break;
			case 'p':
				spec_set_mode(SPEC_PPI_ONLY, spec);
				break;
			case 'r':
				spec_set_mode(SPEC_RES_ONLY, spec);
				break;
			case 'g':
				spec_set_mode(SPEC_AUTO_GROUND, spec);
				break;
			case 'v':
				spec_set_message_type(SPEC_VERBOSE, spec);
				break;
			case 's':
				spec_set_message_type(SPEC_SOLUTION, spec);
				break;
			
			case '?':
				if (isprint(optopt))
					printf("SZS status InputError: unknown option '-%c'.\n", optopt);
				else
					printf("SZS status InputError: unknown option character '\\x%x'.\n", optopt);
				return 1;
			default:
				abort();
		}
	}

	/*********************** 
	 * Get theorem file name 
	 ***********************/

	if (optind == argc) {
		cout << "SZS status InputError: too few arguements" << endl;
		return 1;
	}		

	strcpy(theorem_file, argv[optind]);
	
	set_file_name();

	if (strlen(theorem_name) == 0) {
		cout << "SZS status InputError: invalid file name" << endl;
		return 1;
	}

	if (spec_message_type(SPEC_VERBOSE, spec)) {
		cout << "Theorem File: " << theorem_file << endl;
	}

	/***********************
	 * Parse TPTP file
	 **********************/

	if (tptp_parser() != 0)
		exit(1);
	
	//sym_tree_print(spec->sym_tree);
	//print_clause_set(spec->problem, VSIG);

	/************************************
	 * Run Spectrum Algorithm.
      ************************************/
	
	SZS_Status status = run_spectrum(spec);

	if (spec_message_type(SPEC_SOLUTION, spec))
		spec_print_data(spec);

	if (status == SZS_P_UNSATISFIABLE)
		cout << "SZS: UNSATISFIABLE: (P)" << endl;
	else if (status == SZS_R_UNSATISFIABLE)
		cout << "SZS: UNSATISFIABLE: (R)" << endl;
	else if (status == SZS_SATISFIABLE)
		cout << "SZS: SATISFIABLE" << endl;

//	free_spec_data(spec);

	return 0;
}

/*--------------END OF FILE-------------------*/
