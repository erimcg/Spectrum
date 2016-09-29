%{

#include "stdio.h" 
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "assert.h"

#include "struct.h"
#include "specdata.h"
#include "sym_tree.h"
#include "ground_lits.h"
#include "var_map.h"

#define DEBUG_PARSER_PRINT_GRAMMAR_TREE		0

#define MAXLITS          128        /* Maximum number of literals in a clause */
#define MAXTERMS          128        /* Maximum depth of a literal */
#define MAXVARS		128

extern "C" {

  int yyparse();
  int yylex(void);
  void yyerror(char*);
  int yywrap()
  {
    return 1;
  }

}

typedef struct parser_path_s {
	char *path;
	int arg_num;
}PathStruct;

/*********************************************
 * Global variables declared in main.cpp
 *********************************************/
extern SpecData *spec;

/*************************************
 * Other global variables used in parser
 ***************************************/

int cl_ct = 0;				/* Number of clauses currently added to spec->problem->clauses. */

Lit* lit_a[MAXLITS];		/* Array which temporarily holds literals while clause is being parsed. */
int lit_ct = 0;			/* Number of literals in lit_a. */

Term* term_a[MAXTERMS];		/* Array which temporarily holds the terms while literal is being parsed. */
int term_ct = 0;			/* Number of terms in term_a. */

int func_a[MAXTERMS];		/* Index for term_a of functors inserted in term_a (not vars & constants) */
int func_ct;				/* Number of indices in func_a */

PathStruct path_a[MAXTERMS];
int path_a_index = -1;
int cur_arg_num = 1;

bool not_equals = false;
bool parsed_eq = false;

%}


%union {
	int	ival;	/* attribute value of  */
	float rval;	/* attribute value of  */
	char	*sval;	/* attribute value of UPPER_WORD,LOWER_WORD */
}

%token FOF CNF TRUE FALSE INCLUDE 
%token DISTINCT_OBJECT DOLLAR_DOLLAR_WORD 

%token <sval> LOWER_WORD 
%token <sval> UPPER_WORD 
%token <sval> SINGLE_QUOTED
%token <rval> REAL
%token <ival> SIGNED_INTEGER
%token <ival> UNSIGNED_INTEGER

%type <sval> functor 
%type <sval> atomic_word 
%type <sval> constant 
%type <sval> constant_word 
%type <sval> plain_term 
%type <sval> variable
 

%%
TPTP_file:	TPTP_input
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("TPTP_file:TPTP_input\n");
	
			}
	| 	TPTP_file TPTP_input
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("TPTP_file:TPTP_file TPTP_input\n");
	
			}
	;

TPTP_input:	annotated_formula
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("TPTP_input:annotated_formula\n");
	
			}
	|	include		
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("TPTP_input:include\n");
				printf("SZS status InputError: include statement\n");
				exit(1);
	
			}
	;

annotated_formula:	cnf_annotated
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("annotated_formula:cnf_annotated\n");
	
			}
		;

cnf_annotated:	CNF '(' name ',' formula_role ',' cnf_formula annotations ')' '.'
			{
				/*
				 * An entire cnf clause has been parsed.  Data for lit_ct literals has 
				 * been stored in lit_a[]. 
				 */ 

				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("cnf_annotated:CNF(name,formula_role,cnf_formula annotations).\n");

				Clause* clause = new Clause;

				clause->num_lits = lit_ct;
				clause->ground = true;

				Lit** lits = (Lit**)calloc(lit_ct, sizeof(Lit*));
				clause->lits = lits;

				for (int i = 0; i < lit_ct; i++) {
					lit_a[i]->clause_num = cl_ct;
					if (lit_a[i]->atom->ground == false) 
						clause->ground = false;

					clause->lits[i] = lit_a[i];
				}

				set_g_str(clause);

				clause->signature = var_map_get_clause_signature();

				spec->problem->clauses[cl_ct] = clause;
 
				lit_ct = 0;
				cl_ct++;
			}
	;

annotations: 	null	
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("annotations:null\n");
	
			}
	|	',' source optional_info
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("annotations:,source optional_info\n");
	
			}
	;

formula_role:	LOWER_WORD
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("\nformula_role:LOWER_WORD\n");
	
			}
	;

cnf_formula:	'(' disjunction ')'
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("cnf_formula:(disjunction)\n");
	
			}
	|	disjunction
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("cnf_formula:disjunction\n");
	
			}
	;

disjunction:	literal 
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("disjunction:literal\n");
	
			}
	|	literal more_disjunction
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("disjunction:literal more_disjunction\n");
	
			}
	;

more_disjunction:	'|' literal
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("more_disjunction:|literal\n");
	
			}
		| 	'|' literal more_disjunction
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("more_disjunction:|literal more_disjunction\n");
	
			}
		;

literal:	atomic_formula
			{
				/*
				 * An entire literal has been parsed.  Data for it's symbol and arguements 
				 * has been stored in are in term_a[0]. This literal has positive polarity.
				 * Below is for literals with negative polarity. 
				 */
	 
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("literal:atomic_formula\n");
				
				assert(term_ct == 1);

				/*
				 * The contents of term_a[0] are copied into lit_a[lit_ct]
				 * and the literals polarity is set.
				 */

				Lit* lit = new Lit;

				if (not_equals == true) {
					lit->negated = true;
					not_equals = false;
				}
				else
					lit->negated = false;

				lit->selected = false;
				lit->atom = term_a[0];
				lit->atom->type = atom;
				lit->last_unresolved = 0;
					
				char g_str[256];

				if (lit->negated == true)
					sprintf(g_str, "~%s", lit->atom->g_str);
				else
					sprintf(g_str, "%s", lit->atom->g_str);

				lit->g_str = strdup(g_str);
				lit->smt_var = insert_ground_lit(lit, spec->glits);

				lit_a[lit_ct] = lit;
	
				clear_temp_paths(0, 0);

				term_ct = 0;
				func_ct = 0;
				lit_ct++;
			}			 
	|	'~' atomic_formula 
			{
				/*
				 * An entire literal has been parsed.  Data for it's term and arguements 
				 * has been stored in are in term_a[0]. 
				 */
	 
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("literal:~atomic_formula\n");
 
				assert(term_ct == 1);

				/*
				 * The contents of term_a[0] are copied into lit_a[lit_ct]
				 * and the literals polarity is set.
				 */

				Lit* lit = new Lit;

				if (not_equals == true) {
					lit->negated = false; 
					not_equals = false;
				}
				else
					lit->negated = true;

				lit->selected = false;
				lit->atom = term_a[0];
				lit->atom->type = atom;
				lit->last_unresolved = 0;

				char g_str[256];

				if (lit->negated == true)
					sprintf(g_str, "~%s", lit->atom->g_str);
				else
					sprintf(g_str, "%s", lit->atom->g_str);

				lit->g_str = strdup(g_str);
				lit->smt_var = insert_ground_lit(lit, spec->glits);

				lit_a[lit_ct] = lit;
	
				clear_temp_paths(0, 0);

				term_ct = 0;
				func_ct = 0;
				lit_ct++;
			}			 
	;

atomic_formula:	plain_atom
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("atomic_formula:plain_atom\n");
	
			}
	|	defined_atom
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("atomic_formula:defined_atom\n");
	
			}
	|	system_atom
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("atomic_formula:system_atom\n");
	
			}
	;

plain_atom:	plain_term
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("plain_atom:plain_term\n");
	
			}
	;

arguments:	term
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("arguments:term\n");
				
			}
	|	term ',' arguments
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("arguments:term,arguments\n");

			}
	;

defined_atom:	TRUE
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("\ndefined_atom:TRUE\n");
	
			}
	|	FALSE
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("\ndefined_atom:FALSE\n");
	
			}
	|	term defined_infix_pred term
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("defined_atom:term defined_infix_pred term\n");
	
				Term *term = new Term;
				term->ground = true;

                    char buf[1024];
				sprintf(buf, "equals");
				term->sym = sym_tree_insert_sym(buf, spec->sym_tree);
				clear_temp_paths(sym_tree_get_id(buf, spec->sym_tree), 2);

				term->num_args = 2;
                    Term** args = (Term**)calloc(term->num_args, sizeof(Term*));

                    sprintf(buf, "equals(");

                    int d = 0;
                    for(int i = 0; i < term->num_args; i++) {
                         args[i] = term_a[i];

                         if (args[i]->ground == false)
                              term->ground = false;

                         if (args[i]->depth > d)
                              d = args[i]->depth;

                         sprintf(buf, "%s%s", buf, args[i]->g_str);

                         if (i + 1 < term->num_args)
                              sprintf(buf, "%s,", buf);
                    }
                    sprintf(buf, "%s)", buf);
                    term->g_str = strdup(buf);

                    term->depth = ++d;
                    term->args = args;
		
				term_a[0] = term;

				term_ct = 1;

                    cur_arg_num = 1;
                    path_a_index = -1;
				parsed_eq  = false;

			}
	;

defined_infix_pred:	'='	
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("defined_infix_pred:=\n");
				
                    char buf[1024];
				sprintf(buf, "equals");
				sym_tree_insert_sym(buf, spec->sym_tree);
				clear_temp_paths(sym_tree_get_id(buf, spec->sym_tree), 1);	
			
				parsed_eq = true;

			}
		|	'!' '='	
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("defined_infix_pred:!=\n");

                    char buf[1024];
				sprintf(buf, "equals");
				sym_tree_insert_sym(buf, spec->sym_tree);
				clear_temp_paths(sym_tree_get_id(buf, spec->sym_tree), 1);	

				not_equals = true;
				parsed_eq = true;
	
			}
		;

system_atom:	system_term
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("system_atom:system_term\n");
	
			}
	;

term:		function_term
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("term:function_term\n");
				

			}
	|	variable
			{
				/*
				 * An entire varible has been parsed.
				 */

				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("term:variable\n");
				
				/*
				 * Assert that there is text in the buffer.
				 */

				assert($1 != NULL);
			
				/*
				 * Create string which consists of the clause index prefixed
				 * to the string in the buffer.
				 */

                    char sym[128];
                    sprintf(sym, "%s-%d", $1, cl_ct);

				char path[1024];

				if (func_ct == 0 && parsed_eq == false)
					sprintf(path, "1");
				else if (func_ct == 0 && parsed_eq == true)
					sprintf(path, "2");
				else	
					sprintf(path, "%s-%d", path_a[path_a_index].path, cur_arg_num);

				Term *t = var_map_find(sym);
				
				if (t == NULL) {
					t = new Term;

				     t->type = variable;
				     t->sym = strdup(sym);

					t->temp_paths.push_back(strdup(path));

					t->signature = NULL;

				     t->ground = false;
					t->depth = 0;

				     char g_str[2];
				     sprintf(g_str, "?");
				     t->g_str = strdup(g_str);
	
				     t->num_args = 0;
				     t->args = NULL;

					var_map_insert(t);
				} 
				else {
					t->temp_paths.push_back(strdup(path));
				}

				int occurs = 0;	
				map<int, int>::iterator iter = t->occurs.find(lit_ct);

				if (iter != t->occurs.end() ) {
					occurs = iter->second;
					t->occurs.erase(iter);
				}
 
				occurs = occurs + 1;
				t->occurs.insert(make_pair(lit_ct, occurs));

				term_a[term_ct] = t;
				term_ct++;
				cur_arg_num++;
			}
	;

function_term:	plain_term
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("function_term:plain_term\n");
	
			}
	|	defined_term
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("function_term:defined_term\n");
	
			}
	|	system_term
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("function_term:system_term\n");
	
			}
	;

plain_term:	constant
			{	
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("plain_term:constant\n");

			}
	|	functor '(' arguments ')' 
			{
				/*
				 * A function or literal with arguments has been parsed.
				 */

				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("plain_term:functor(arguments)\n");
			
				int last_func_index = func_a[func_ct-1];
				int num_args = (term_ct - 1) - last_func_index;

				term_a[last_func_index]->num_args = num_args;

				Term** args = (Term**)calloc(num_args, sizeof(Term*));

				char buf[1024];
				sprintf(buf, "%s(", term_a[last_func_index]->sym);

				int d = 0;
				for(int i = 0; i < num_args; i++) {
					args[i] = term_a[(last_func_index+1) + i];

					if (args[i]->ground == false)
						term_a[last_func_index]->ground = false;
					
					if (args[i]->depth > d)
						d = args[i]->depth;
	
					sprintf(buf, "%s%s", buf, args[i]->g_str);

					if (i + 1 < num_args)
						sprintf(buf, "%s,", buf);
				}
				sprintf(buf, "%s)", buf);
				term_a[last_func_index]->g_str = strdup(buf);

				term_a[last_func_index]->depth = ++d;
				term_a[last_func_index]->args = args;

				func_ct--;
				term_ct = term_ct - num_args;

				cur_arg_num = path_a[path_a_index].arg_num;
				cur_arg_num++;
				path_a_index--;
			}
	;

constant:	constant_word
			{
				/*
				 * A constant has been parsed.
				 */

				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("constant:constant_word\n");
				
				/*
				 * Assert that there is text in the buffer.
				 */

				assert($1 != NULL);

				Term* t = new Term;

		 		t->type = constant;
				t->sym = sym_tree_insert_sym($1, spec->sym_tree);
				t->g_str = strdup($1);
				t->ground = true;
				t->depth = 0;
				t->num_args = 0;
				t->args = NULL;
				t->signature = NULL;

				term_a[term_ct] = t;
				term_ct++;
				cur_arg_num++;
			} 
	;

functor:	atomic_word 
			{
				/*
				 * A function symbol or a predicate symbol has been parsed.
				 */

				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("functor:atomic_word\n");

				assert($1 != NULL);

				Term* term = new Term;

			 	term->type = function;
				term->sym = sym_tree_insert_sym($1, spec->sym_tree);
				term->ground = true;
				term->g_str = strdup($1);
				term->num_args = 0;
				term->args = NULL;

				term_a[term_ct] = term;
				func_a[func_ct] = term_ct;
				term_ct++;
				func_ct++;
				
				char buf[1024];
				path_a_index++;

				if (path_a_index == 0) {
					sprintf(buf, "%d", sym_tree_get_id($1, spec->sym_tree));
					path_a[path_a_index].path = strdup(buf);
					path_a[path_a_index].arg_num = cur_arg_num;
				}	
				else { 
					sprintf(buf, "%s-%d", path_a[path_a_index-1].path, cur_arg_num);
					path_a[path_a_index].path = strdup(buf); 
					path_a[path_a_index].arg_num = cur_arg_num;
				} 
				
				cur_arg_num = 1;
			}
	;

defined_term:	number
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("defined_term:number\n");
	
			}
	|	DISTINCT_OBJECT	
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("\ndefined_term:DISTINCT_OBJECT\n");
	
			}
	;

system_term:	system_constant
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("system_term:system_constant\n");
	
			}
	|	system_functor '(' arguments ')'
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("system_term:system_functor(arguments)\n");
	
			}
	;

system_functor:	atomic_system_word
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("system_functor:atomic_system_word\n");
	
			}
	;

system_constant:	atomic_system_word
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("system_constant:atomic_system_word\n");
	
			}
	;

variable:	UPPER_WORD 
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("\nvariable:UPPER_WORD\n");
	
			}	
	;

source:		general_term
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("source:general_term\n");
	
			}
	;

optional_info:	',' useful_info
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("optional_info:,useful_info\n");
	
			}
	|	null
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("optional_info:null\n");
	
			}
	;

useful_info:	general_term_list
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("useful_info:general_term_list\n");
	
			}
	;

include:	INCLUDE '(' file_name formula_selection ')' '.'
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("INCLUDE(file_name formula_selection).\n");
	
			}
	;

formula_selection:	',' '[' name_list ']'
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("formula_selection:,[name_list]\n");
	
			}
		|	null
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("formula_selection:null\n");
	
			}
		;

name_list:	name
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("name_list:name\n");
	
			}
	|	name ',' name_list
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("name_list:name,name_list\n");
	
			}
	;

general_term:	general_data
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("general_term:general_data\n");
	
			}
	|	general_data ':' general_term
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("general_term:general_data:general_term\n");
	
			}
	|	general_list
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("general_term:general_list\n");
	
			}
	;

general_data:	general_word
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("general_data:general_word\n");
	
			}
	|	general_word '(' general_arguments ')'
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("general_data:general_word\n");
	
			}
	|	number
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("general_data:number\n");
	
			}
	|	DISTINCT_OBJECT
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("\ngeneral_data:DISTINCT_OBJECT\n");
	
			}
	;

general_arguments:	general_term
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("general_arguments:general_term\n");
	
			}
		|	general_term ',' general_arguments
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("general_arguments:general_term\n");
	
			}
		;

general_list:	'[' ']'
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("[]\n");
	
			}
	|	'[' general_term_list ']'
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("general_list:[general_term_list]\n");
	
			}
	;

general_term_list:	general_term
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("general_term_list:general_term\n");
	
			}
		|	general_term ',' general_term_list
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("general_term_list:general_term , general_term_list\n");
	
			}
		;

name:		name_word
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("name:name_word\n");
	
			}
	|	UNSIGNED_INTEGER
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("\nname:UNSIGNED_INTEGER\n");
	
			}
	;

atomic_word:	LOWER_WORD 
		{
			if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
				printf("\natomic_word:LOWER_WORD\n");

		}
	|	SINGLE_QUOTED 
		{
			if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
				printf("\natomic_word:SINGLE_QUOTED\n");

		}
	;


constant_word:	LOWER_WORD
		{
			if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
				printf("\nconstant_word:SINGLE_QUOTED\n");

		}
	|	SINGLE_QUOTED 
		{
			if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
				printf("\nconstant_word:SINGLE_QUOTED\n");

		}
	;

general_word:	LOWER_WORD
		{
			if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
				printf("\ngeneral_word:SINGLE_QUOTED\n");

		}
	|	SINGLE_QUOTED
		{
			if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
				printf("\ngeneral_word:SINGLE_QUOTED\n");
		
		}
	;

name_word:	LOWER_WORD 
		{
			if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
				printf("\nname_word:SINGLE_QUOTED\n");

		}
	|	SINGLE_QUOTED
		{
			if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
				printf("\nname_word:SINGLE_QUOTED\n");
		
		}
	;

atomic_system_word:	DOLLAR_DOLLAR_WORD
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("\natomic_system_word:DOLLAR_DOLLAR_WORD\n");
		
			}
			
		;

number:		REAL
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("\nnumber:REAL\n");
		
			}

	|	SIGNED_INTEGER
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("\nnumber:SIGNED_INTEGER\n");
		
			}
	|	UNSIGNED_INTEGER
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("\nnumber:UNSIGNED_INTEGER\n");
		
			}
	;

file_name:	atomic_word
			{
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("\nfile_name:atomic_word\n");
		
			}
	;

null:		
	;
%%

void yyerror(char *s)
{
	fprintf(stderr, "%s\n",s);
}



/*--------------END OF FILE-------------------*/
