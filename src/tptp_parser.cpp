/*
 * tptp_parser.cpp
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * Last Modified: September 30, 2008
 */

#include <iostream>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <getopt.h>
#include <string.h>
#include <sys/time.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>

#include "specdata.h"
#include "struct.h"

#define YYOUT_ERROR_FILE      "/tmp/yyout.errors"
#define BUFSIZE 1024

extern "C"
{
  int yyparse();
}

extern FILE *yyin;
extern FILE *yyout;
//extern int yydebug;

extern SpecData *spec;

extern char theorem_file[];
extern char theorem_name[];

using namespace std;

/***********************************************************************
 * tptp_parser()
 ***********************************************************************/

int tptp_parser()
{
     char line[BUFSIZE];

     FILE *fp = fopen(theorem_file, "r");

     if (fp == NULL){
	cout << "Begin " << endl;
          printf("SZS status Error for %s: can not open %s for reading\n", theorem_name, theorem_file);
     }

     while (fgets(line, BUFSIZE, fp) != NULL)
          if (strncmp(line, "cnf", 3) == 0)
               spec->problem->num_clauses++;

     fclose(fp);
	
     /*****************************
      * Allocate memory for clauses 
      *****************************/

     spec->problem->clauses = (Clause**)calloc(spec->problem->num_clauses, sizeof(Clause*));

     /************************
      * Parse the theorem file
      ************************/

     if ((yyin = fopen(theorem_file, "r")) == NULL)
     {
          cout << "SZS status Error for " << theorem_name << " : can not open theorem file" << endl;
          return 1;
     }

     if ((yyout = fopen(YYOUT_ERROR_FILE, "w")) == NULL)
     {
          cout << "SZS status Error for " << theorem_name << " : can not open " << YYOUT_ERROR_FILE << endl;
          fclose(yyin);
          return 1;
     }

     if (yyparse() != 0) {
          cout << "SZS status SyntaxError for " << theorem_name << endl;
          fclose(yyin);
          fclose(yyout);
          remove(YYOUT_ERROR_FILE);
          return 1;
     }

     fclose(yyin);
     fclose(yyout);
     remove(YYOUT_ERROR_FILE);

     return 0;
}


