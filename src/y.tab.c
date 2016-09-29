
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"


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



/* Line 189 of yacc.c  */
#line 140 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     FOF = 258,
     CNF = 259,
     TRUE = 260,
     FALSE = 261,
     INCLUDE = 262,
     DISTINCT_OBJECT = 263,
     DOLLAR_DOLLAR_WORD = 264,
     LOWER_WORD = 265,
     UPPER_WORD = 266,
     SINGLE_QUOTED = 267,
     REAL = 268,
     SIGNED_INTEGER = 269,
     UNSIGNED_INTEGER = 270
   };
#endif
/* Tokens.  */
#define FOF 258
#define CNF 259
#define TRUE 260
#define FALSE 261
#define INCLUDE 262
#define DISTINCT_OBJECT 263
#define DOLLAR_DOLLAR_WORD 264
#define LOWER_WORD 265
#define UPPER_WORD 266
#define SINGLE_QUOTED 267
#define REAL 268
#define SIGNED_INTEGER 269
#define UNSIGNED_INTEGER 270




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 68 "parser.y"

	int	ival;	/* attribute value of  */
	float rval;	/* attribute value of  */
	char	*sval;	/* attribute value of UPPER_WORD,LOWER_WORD */



/* Line 214 of yacc.c  */
#line 214 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 226 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   142

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  27
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  84
/* YYNRULES -- Number of states.  */
#define YYNSTATES  126

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   270

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    23,     2,     2,     2,     2,     2,     2,
      16,    18,     2,     2,    17,     2,    19,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    26,     2,
       2,    22,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    24,     2,    25,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    20,     2,    21,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    25,    27,
      31,    33,    37,    39,    41,    44,    47,    51,    53,    56,
      58,    60,    62,    64,    66,    70,    72,    74,    78,    80,
      83,    85,    87,    89,    91,    93,    95,    97,   102,   104,
     106,   108,   110,   112,   117,   119,   121,   123,   125,   128,
     130,   132,   139,   144,   146,   148,   152,   154,   158,   160,
     162,   167,   169,   171,   173,   177,   180,   184,   186,   190,
     192,   194,   196,   198,   200,   202,   204,   206,   208,   210,
     212,   214,   216,   218,   220
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      28,     0,    -1,    29,    -1,    28,    29,    -1,    30,    -1,
      57,    -1,    31,    -1,     4,    16,    65,    17,    33,    17,
      34,    32,    18,    19,    -1,    73,    -1,    17,    54,    55,
      -1,    10,    -1,    16,    35,    18,    -1,    35,    -1,    37,
      -1,    37,    36,    -1,    20,    37,    -1,    20,    37,    36,
      -1,    38,    -1,    21,    38,    -1,    39,    -1,    41,    -1,
      43,    -1,    46,    -1,    44,    -1,    44,    17,    40,    -1,
       5,    -1,     6,    -1,    44,    42,    44,    -1,    22,    -1,
      23,    22,    -1,    50,    -1,    45,    -1,    53,    -1,    46,
      -1,    49,    -1,    50,    -1,    47,    -1,    48,    16,    40,
      18,    -1,    67,    -1,    66,    -1,    71,    -1,     8,    -1,
      52,    -1,    51,    16,    40,    18,    -1,    70,    -1,    70,
      -1,    11,    -1,    60,    -1,    17,    56,    -1,    73,    -1,
      64,    -1,     7,    16,    72,    58,    18,    19,    -1,    17,
      24,    59,    25,    -1,    73,    -1,    65,    -1,    65,    17,
      59,    -1,    61,    -1,    61,    26,    60,    -1,    63,    -1,
      68,    -1,    68,    16,    62,    18,    -1,    71,    -1,     8,
      -1,    60,    -1,    60,    17,    62,    -1,    24,    25,    -1,
      24,    64,    25,    -1,    60,    -1,    60,    17,    64,    -1,
      69,    -1,    15,    -1,    10,    -1,    12,    -1,    10,    -1,
      12,    -1,    10,    -1,    12,    -1,    10,    -1,    12,    -1,
       9,    -1,    13,    -1,    14,    -1,    15,    -1,    66,    -1,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    93,    93,    99,   107,   113,   123,   131,   168,   174,
     182,   190,   196,   204,   210,   218,   224,   232,   282,   333,
     339,   345,   353,   361,   367,   375,   381,   387,   437,   450,
     466,   474,   481,   558,   564,   570,   578,   584,   633,   665,
     708,   714,   722,   728,   736,   744,   752,   760,   768,   774,
     782,   790,   798,   804,   812,   818,   826,   832,   838,   846,
     852,   858,   864,   872,   878,   886,   892,   900,   906,   914,
     920,   928,   934,   943,   949,   957,   963,   971,   977,   985,
     994,  1001,  1007,  1015,  1023
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FOF", "CNF", "TRUE", "FALSE", "INCLUDE",
  "DISTINCT_OBJECT", "DOLLAR_DOLLAR_WORD", "LOWER_WORD", "UPPER_WORD",
  "SINGLE_QUOTED", "REAL", "SIGNED_INTEGER", "UNSIGNED_INTEGER", "'('",
  "','", "')'", "'.'", "'|'", "'~'", "'='", "'!'", "'['", "']'", "':'",
  "$accept", "TPTP_file", "TPTP_input", "annotated_formula",
  "cnf_annotated", "annotations", "formula_role", "cnf_formula",
  "disjunction", "more_disjunction", "literal", "atomic_formula",
  "plain_atom", "arguments", "defined_atom", "defined_infix_pred",
  "system_atom", "term", "function_term", "plain_term", "constant",
  "functor", "defined_term", "system_term", "system_functor",
  "system_constant", "variable", "source", "optional_info", "useful_info",
  "include", "formula_selection", "name_list", "general_term",
  "general_data", "general_arguments", "general_list", "general_term_list",
  "name", "atomic_word", "constant_word", "general_word", "name_word",
  "atomic_system_word", "number", "file_name", "null", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,    40,    44,    41,    46,
     124,   126,    61,    33,    91,    93,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    27,    28,    28,    29,    29,    30,    31,    32,    32,
      33,    34,    34,    35,    35,    36,    36,    37,    37,    38,
      38,    38,    39,    40,    40,    41,    41,    41,    42,    42,
      43,    44,    44,    45,    45,    45,    46,    46,    47,    48,
      49,    49,    50,    50,    51,    52,    53,    54,    55,    55,
      56,    57,    58,    58,    59,    59,    60,    60,    60,    61,
      61,    61,    61,    62,    62,    63,    63,    64,    64,    65,
      65,    66,    66,    67,    67,    68,    68,    69,    69,    70,
      71,    71,    71,    72,    73
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,    10,     1,     3,
       1,     3,     1,     1,     2,     2,     3,     1,     2,     1,
       1,     1,     1,     1,     3,     1,     1,     3,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     4,     1,     1,
       1,     1,     1,     4,     1,     1,     1,     1,     2,     1,
       1,     6,     4,     1,     1,     3,     1,     3,     1,     1,
       4,     1,     1,     1,     3,     2,     3,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     2,     4,     6,     5,     0,     0,
       1,     3,    77,    78,    70,     0,    69,    71,    72,    83,
      84,     0,     0,     0,    53,    10,     0,     0,     0,     0,
       0,    54,    51,    25,    26,    41,    79,    73,    46,    74,
      80,    81,    82,     0,     0,    84,    12,    13,    17,    19,
      20,    21,     0,    31,    22,    36,     0,    34,    30,     0,
      42,    32,    39,    38,    45,    40,    52,     0,     0,    18,
       0,     0,     8,     0,    14,    28,     0,     0,     0,     0,
      55,    11,    62,    75,    76,     0,    84,    47,    56,    58,
      59,    61,     0,    15,    29,    27,    33,    35,     0,    23,
       0,    65,    67,     0,     0,     9,    49,     0,     0,     7,
      16,    37,     0,    43,     0,    66,    48,    50,    57,    63,
       0,    24,    68,     0,    60,    64
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    71,    26,    45,    46,    74,
      47,    48,    49,    98,    50,    77,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    86,   105,   116,
       7,    23,    30,   102,    88,   120,    89,   103,    31,    62,
      63,    90,    16,    64,    65,    20,    24
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -101
static const yytype_int8 yypact[] =
{
      42,   -11,    -7,    43,  -101,  -101,  -101,  -101,    81,    21,
    -101,  -101,  -101,  -101,  -101,    -4,  -101,  -101,  -101,  -101,
       4,    22,    24,    54,  -101,  -101,    67,    81,    73,    14,
      85,    94,  -101,  -101,  -101,  -101,  -101,    96,  -101,    97,
    -101,  -101,  -101,    65,    92,    98,  -101,    99,  -101,  -101,
    -101,  -101,    59,  -101,    72,  -101,   100,  -101,    86,   101,
    -101,  -101,  -101,  -101,   102,  -101,  -101,    81,   103,  -101,
      75,   104,  -101,    65,  -101,  -101,   105,    52,    52,    52,
    -101,  -101,  -101,  -101,  -101,    44,   106,  -101,    88,  -101,
     108,  -101,   107,    99,  -101,  -101,  -101,  -101,   110,   112,
     113,  -101,   115,    95,    75,  -101,  -101,    75,    75,  -101,
    -101,  -101,    52,  -101,    75,  -101,  -101,  -101,  -101,   116,
     117,  -101,  -101,    75,  -101,  -101
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -101,  -101,   122,  -101,  -101,  -101,  -101,  -101,    87,    41,
      63,    93,  -101,   -76,  -101,  -101,  -101,   -71,  -101,   -67,
    -101,  -101,  -101,   -61,  -101,  -101,  -101,  -101,  -101,  -101,
    -101,  -101,    71,   -68,  -101,    16,  -101,  -100,   132,   133,
    -101,  -101,  -101,  -101,   -70,  -101,   -44
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -73
static const yytype_int8 yytable[] =
{
      91,    72,    87,   100,   117,     8,    95,    99,    99,     9,
      96,    96,    96,    21,   122,    91,    97,    97,    97,    33,
      34,    22,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    17,    25,    18,    91,    44,   121,    91,    91,   118,
     119,    99,   106,    10,    91,    96,     1,     1,    27,     2,
       2,    97,    82,    91,    83,   119,    84,    40,    41,    42,
      35,    36,    37,    38,    39,    40,    41,    42,    85,   101,
      33,    34,    28,    35,    36,    37,    38,    39,    40,    41,
      42,    75,    76,    82,    29,    83,    44,    84,    40,    41,
      42,    12,    32,    13,   -33,   -33,    14,    33,    34,    85,
      35,    36,    37,    38,    39,    40,    41,    42,   -35,   -35,
      66,    67,   -71,   -72,   107,    70,    78,    79,   -44,    73,
     115,    81,    92,   104,   108,    11,   109,    94,   111,   112,
      68,   113,   114,   123,   110,   124,    93,    69,    80,   125,
      15,     0,    19
};

static const yytype_int8 yycheck[] =
{
      70,    45,    70,    79,   104,    16,    77,    78,    79,    16,
      77,    78,    79,    17,   114,    85,    77,    78,    79,     5,
       6,    17,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    10,    10,    12,   104,    21,   112,   107,   108,   107,
     108,   112,    86,     0,   114,   112,     4,     4,    24,     7,
       7,   112,     8,   123,    10,   123,    12,    13,    14,    15,
       8,     9,    10,    11,    12,    13,    14,    15,    24,    25,
       5,     6,    18,     8,     9,    10,    11,    12,    13,    14,
      15,    22,    23,     8,    17,    10,    21,    12,    13,    14,
      15,    10,    19,    12,    22,    23,    15,     5,     6,    24,
       8,     9,    10,    11,    12,    13,    14,    15,    22,    23,
      25,    17,    16,    16,    26,    17,    16,    16,    16,    20,
      25,    18,    18,    17,    16,     3,    19,    22,    18,    17,
      43,    18,    17,    17,    93,    18,    73,    44,    67,   123,
       8,    -1,     9
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     7,    28,    29,    30,    31,    57,    16,    16,
       0,    29,    10,    12,    15,    65,    69,    10,    12,    66,
      72,    17,    17,    58,    73,    10,    33,    24,    18,    17,
      59,    65,    19,     5,     6,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    21,    34,    35,    37,    38,    39,
      41,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    66,    67,    70,    71,    25,    17,    35,    38,
      17,    32,    73,    20,    36,    22,    23,    42,    16,    16,
      59,    18,     8,    10,    12,    24,    54,    60,    61,    63,
      68,    71,    18,    37,    22,    44,    46,    50,    40,    44,
      40,    25,    60,    64,    17,    55,    73,    26,    16,    19,
      36,    18,    17,    18,    17,    25,    56,    64,    60,    60,
      62,    40,    64,    17,    18,    62
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 94 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("TPTP_file:TPTP_input\n");
	
			}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 100 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("TPTP_file:TPTP_file TPTP_input\n");
	
			}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 108 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("TPTP_input:annotated_formula\n");
	
			}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 114 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("TPTP_input:include\n");
				printf("SZS status InputError: include statement\n");
				exit(1);
	
			}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 124 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("annotated_formula:cnf_annotated\n");
	
			}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 132 "parser.y"
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
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 169 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("annotations:null\n");
	
			}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 175 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("annotations:,source optional_info\n");
	
			}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 183 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("\nformula_role:LOWER_WORD\n");
	
			}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 191 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("cnf_formula:(disjunction)\n");
	
			}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 197 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("cnf_formula:disjunction\n");
	
			}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 205 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("disjunction:literal\n");
	
			}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 211 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("disjunction:literal more_disjunction\n");
	
			}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 219 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("more_disjunction:|literal\n");
	
			}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 225 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("more_disjunction:|literal more_disjunction\n");
	
			}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 233 "parser.y"
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
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 283 "parser.y"
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
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 334 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("atomic_formula:plain_atom\n");
	
			}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 340 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("atomic_formula:defined_atom\n");
	
			}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 346 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("atomic_formula:system_atom\n");
	
			}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 354 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("plain_atom:plain_term\n");
	
			}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 362 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("arguments:term\n");
				
			}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 368 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("arguments:term,arguments\n");

			}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 376 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("\ndefined_atom:TRUE\n");
	
			}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 382 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("\ndefined_atom:FALSE\n");
	
			}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 388 "parser.y"
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
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 438 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("defined_infix_pred:=\n");
				
                    char buf[1024];
				sprintf(buf, "equals");
				sym_tree_insert_sym(buf, spec->sym_tree);
				clear_temp_paths(sym_tree_get_id(buf, spec->sym_tree), 1);	
			
				parsed_eq = true;

			}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 451 "parser.y"
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
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 467 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("system_atom:system_term\n");
	
			}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 475 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("term:function_term\n");
				

			}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 482 "parser.y"
    {
				/*
				 * An entire varible has been parsed.
				 */

				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("term:variable\n");
				
				/*
				 * Assert that there is text in the buffer.
				 */

				assert((yyvsp[(1) - (1)].sval) != NULL);
			
				/*
				 * Create string which consists of the clause index prefixed
				 * to the string in the buffer.
				 */

                    char sym[128];
                    sprintf(sym, "%s-%d", (yyvsp[(1) - (1)].sval), cl_ct);

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
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 559 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("function_term:plain_term\n");
	
			}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 565 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("function_term:defined_term\n");
	
			}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 571 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("function_term:system_term\n");
	
			}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 579 "parser.y"
    {	
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("plain_term:constant\n");

			}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 585 "parser.y"
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
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 634 "parser.y"
    {
				/*
				 * A constant has been parsed.
				 */

				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("constant:constant_word\n");
				
				/*
				 * Assert that there is text in the buffer.
				 */

				assert((yyvsp[(1) - (1)].sval) != NULL);

				Term* t = new Term;

		 		t->type = constant;
				t->sym = sym_tree_insert_sym((yyvsp[(1) - (1)].sval), spec->sym_tree);
				t->g_str = strdup((yyvsp[(1) - (1)].sval));
				t->ground = true;
				t->depth = 0;
				t->num_args = 0;
				t->args = NULL;
				t->signature = NULL;

				term_a[term_ct] = t;
				term_ct++;
				cur_arg_num++;
			}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 666 "parser.y"
    {
				/*
				 * A function symbol or a predicate symbol has been parsed.
				 */

				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("functor:atomic_word\n");

				assert((yyvsp[(1) - (1)].sval) != NULL);

				Term* term = new Term;

			 	term->type = function;
				term->sym = sym_tree_insert_sym((yyvsp[(1) - (1)].sval), spec->sym_tree);
				term->ground = true;
				term->g_str = strdup((yyvsp[(1) - (1)].sval));
				term->num_args = 0;
				term->args = NULL;

				term_a[term_ct] = term;
				func_a[func_ct] = term_ct;
				term_ct++;
				func_ct++;
				
				char buf[1024];
				path_a_index++;

				if (path_a_index == 0) {
					sprintf(buf, "%d", sym_tree_get_id((yyvsp[(1) - (1)].sval), spec->sym_tree));
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
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 709 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("defined_term:number\n");
	
			}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 715 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("\ndefined_term:DISTINCT_OBJECT\n");
	
			}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 723 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("system_term:system_constant\n");
	
			}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 729 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("system_term:system_functor(arguments)\n");
	
			}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 737 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("system_functor:atomic_system_word\n");
	
			}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 745 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("system_constant:atomic_system_word\n");
	
			}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 753 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("\nvariable:UPPER_WORD\n");
	
			}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 761 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("source:general_term\n");
	
			}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 769 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("optional_info:,useful_info\n");
	
			}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 775 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("optional_info:null\n");
	
			}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 783 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("useful_info:general_term_list\n");
	
			}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 791 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("INCLUDE(file_name formula_selection).\n");
	
			}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 799 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("formula_selection:,[name_list]\n");
	
			}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 805 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("formula_selection:null\n");
	
			}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 813 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("name_list:name\n");
	
			}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 819 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("name_list:name,name_list\n");
	
			}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 827 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("general_term:general_data\n");
	
			}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 833 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("general_term:general_data:general_term\n");
	
			}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 839 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("general_term:general_list\n");
	
			}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 847 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("general_data:general_word\n");
	
			}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 853 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("general_data:general_word\n");
	
			}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 859 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("general_data:number\n");
	
			}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 865 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("\ngeneral_data:DISTINCT_OBJECT\n");
	
			}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 873 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("general_arguments:general_term\n");
	
			}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 879 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("general_arguments:general_term\n");
	
			}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 887 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("[]\n");
	
			}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 893 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("general_list:[general_term_list]\n");
	
			}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 901 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("general_term_list:general_term\n");
	
			}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 907 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("general_term_list:general_term , general_term_list\n");
	
			}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 915 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("name:name_word\n");
	
			}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 921 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("\nname:UNSIGNED_INTEGER\n");
	
			}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 929 "parser.y"
    {
			if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
				printf("\natomic_word:LOWER_WORD\n");

		}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 935 "parser.y"
    {
			if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
				printf("\natomic_word:SINGLE_QUOTED\n");

		}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 944 "parser.y"
    {
			if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
				printf("\nconstant_word:SINGLE_QUOTED\n");

		}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 950 "parser.y"
    {
			if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
				printf("\nconstant_word:SINGLE_QUOTED\n");

		}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 958 "parser.y"
    {
			if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
				printf("\ngeneral_word:SINGLE_QUOTED\n");

		}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 964 "parser.y"
    {
			if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
				printf("\ngeneral_word:SINGLE_QUOTED\n");
		
		}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 972 "parser.y"
    {
			if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
				printf("\nname_word:SINGLE_QUOTED\n");

		}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 978 "parser.y"
    {
			if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
				printf("\nname_word:SINGLE_QUOTED\n");
		
		}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 986 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("\natomic_system_word:DOLLAR_DOLLAR_WORD\n");
		
			}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 995 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("\nnumber:REAL\n");
		
			}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 1002 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("\nnumber:SIGNED_INTEGER\n");
		
			}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 1008 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("\nnumber:UNSIGNED_INTEGER\n");
		
			}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 1016 "parser.y"
    {
				if (DEBUG_PARSER_PRINT_GRAMMAR_TREE)
					printf("\nfile_name:atomic_word\n");
		
			}
    break;



/* Line 1455 of yacc.c  */
#line 2793 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 1025 "parser.y"


void yyerror(char *s)
{
	fprintf(stderr, "%s\n",s);
}



/*--------------END OF FILE-------------------*/

