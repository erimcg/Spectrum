/*
 * var_map.cpp
 * Written by Eric McGregor (mcgregre@clarkson.edu)
 * November 26, 2008
 */

#include <iostream>
#include <vector>
#include <map>
#include <string.h>
#include <assert.h>
#include "var_map.h"
#include "struct.h"

using namespace std;

/*
 * var_map is a collection of data structures and methods used to create string representations of
 * the occurances its variables which we call 'clause signatures' (described below). 
 * Two clauses are renaming of each other if their ground strings (see struct.cpp) are identical 
 * and they have identical clause signatures. 
 *
 * VarMap uses a C++ map data structure to map variable names to Term structs.  Multiple instances 
 * of the same variable are represented by a single Term struct in memory. To determine if a
 * variable has been parsed prior, var_map_find(sym) is called. If the variable symbol is not found in the 
 * map data structure, NULL is returned.  The parser then creates a new Term struct, initializes it, 
 * and calls var_map_insert(term) to insert the newly created term into the variable map. 
 * Upon subsequent encounters of the variable when var_map_find(sym) is called, 
 * the pointer to the Term struct is returned.
 * 
 * The location of a variable in a clause can be described by its "path" in the parse tree for the
 * clause. The path of a variable is represented by a string of integers seperated 
 * by '-' and terminated by '0'.  For example in the clause P(X) | Q(f(Y),X), Y has a path 57-1-1-0.  
 * That is, reading the path backwards and skipping '0', Y is the first argument of the first arguement 
 * of the 57th literal (literals have unique identifiers).  It should be clear that we begin counting 
 * at 1 (not zero). There are two occurances of the  variable X, hence two paths.  
 *
 * The paths for a variable are stored in, term->paths, a sortable list in the Term data structure.  
 * Each time a variable is encountered and after the path has been determined, the path is added to the 
 * list using the pushback function (term->paths.push_back(strdup(path))).
 *
 * After a clause has been parsed, for each variable, V, the paths for V are sorted in lexicographical order.
 * We call a variable signature a string of paths seperated by '-'.  In the above example, X has two 
 * paths, 37-1-0 and 57-2-1-0 (assuming P is identified by 37 and Q is identified by 57)
 * thus has a variable signature 37-1-0-57-2-1-0. 
 *
 * A clause signature is a concatenation of lexicographically sorted variable signatures each surrounded by
 * parenthesis. The example clause above has the signature: ((37-1-0-57-2-1-0)(57-1-1-0)). This  
 * string tells us the number of occurances of a variable, what the predicates are, and their location
 * within an atom.  Thus if two clauses have identical ground strings and theirs signatures are identical,
 * we can infer that the clauses are renamings.
 * 
 * Since clauses are renamed apart, we only need to keep track of a given variable while its clause
 * is being parsed.  Therefore after a clause has been parsed and var_map_get_clause_signature() is called
 * the container is emptied. 
 */ 

int var_ct = 0;

struct strCmp {
	bool operator()( const char* s1, const char* s2 ) const {
		return (strcmp( s1, s2 ) < 0);
	}
};

map<const char*, Term*, strCmp> var_map;

/********************
 * Private functions
 ********************/

void set_variable_signature(Term *term)
{
	assert(term != NULL);

	strCmp compare;

	term->paths.sort(compare);

	list<char *>::iterator iter;

	int len = 0;	

	for( iter = term->paths.begin(); iter != term->paths.end(); ++iter ) {
		len += strlen(*iter);
	}

	len += (2 * (term->paths.size() + 2));
	char *str = (char*) malloc(len); 

	sprintf(str, "(");
	for( iter = term->paths.begin(); iter != term->paths.end(); ++iter ) {
		sprintf(str, "%s(%s)", str, *iter);
	}

	sprintf(str, "%s)", str);

	term->signature = str;

	return;
}

/*******************
 * Public functions
 *******************/

Term* var_map_find(char *sym)
{
	map<const char *, Term *>::iterator iter = var_map.find(sym);

	if( iter != var_map.end() )
		return iter->second;
	else 
		return NULL;
}

void var_map_insert(Term *t)
{
	t->id = var_ct++;
	var_map.insert( make_pair( t->sym, t ) );
	
}
char *var_map_get_clause_signature()
{
	if (var_map.size() == 0) {
		return NULL;
	}
	
	list<char *> temp_list;

	map<const char *, Term *>::iterator iter;

	for( iter = var_map.begin(); iter != var_map.end(); ++iter ) {
		Term *t = iter->second;

		set_variable_signature(t);
		temp_list.push_back(t->signature);
	}

	var_map.clear();

	strCmp compare;
	temp_list.sort(compare);

	int buf_size = 0;
	list<char *>::iterator it;

	for( it = temp_list.begin(); it != temp_list.end(); ++it ) {
		buf_size = buf_size + strlen(*it) + 2;
	}

	char *str = (char*) malloc(buf_size + 4);
	sprintf(str, "(");

	for( it = temp_list.begin(); it != temp_list.end(); ++it ) {
		sprintf(str, "%s(%s)", str, *it);
	}
	sprintf(str, "%s)", str);

	temp_list.clear();

	return str;
}

void clear_temp_paths(int id, int arg)
{
	map<const char *, Term *>::iterator iter;
	list<char *>::iterator iter2;
	char str[1024];

	if (arg == 0) {
		for( iter = var_map.begin(); iter != var_map.end(); ++iter ) {
			Term *t = iter->second;

			while (!t->temp_paths.empty()){
				sprintf(str, "%s", t->temp_paths.front());
				t->paths.push_back(strdup(str));

				free(t->temp_paths.front());
				t->temp_paths.pop_front();
			}
		}
	}					
	else {
		for( iter = var_map.begin(); iter != var_map.end(); ++iter ) {
			Term *t = iter->second;

			while (!t->temp_paths.empty()){
				
				char key[] = "-";
				char *pch = strpbrk(t->temp_paths.front(), key);

				if (pch != NULL) {
					pch = pch++;
					sprintf(str, "%d-%d-%s", id, arg, pch);
				}
				else {
					sprintf(str, "%d-%s", id, t->temp_paths.front());
				}
				t->paths.push_back(strdup(str));

				free(t->temp_paths.front());
				t->temp_paths.pop_front();
			}
		}

	}

	return;

}


/*** END OF FILE ***/



