%{
#include "stdio.h"
#include "string.h"

#include "y.tab.h"

%}

COMMENT_LINE	([%][^\n]*)
COMMENT_BLOCK	([/][*]([^*]*[*][*]*[^/*])*[^*]*[*][*]*[/])
SINGLE_QUOTED	([']([^\\']|[\\][']|[\\][\\])*['])
DISTINCT_OBJECT	(["]([^\\"]|[\\]["]|[\\][\\])*["])

SIGN	([+-])
NUMERIC	([0-9])
NON_ZERO_NUMERIC	([1-9])
LOWER_ALPHA	([a-z])
UPPER_ALPHA	([A-Z])
DOLLAR_DOLLAR	([$][$])
ALPHA_NUMERIC	([a-z]|[A-Z]|[0-9]|[_])
LOWER_WORD	([a-z]([a-z]|[A-Z]|[0-9]|[_])*)
UPPER_WORD	([A-Z]([a-z]|[A-Z]|[0-9]|[_])*)

SIGNED_INTEGER	([+-]([0]|[1-9][0-9]*))
UNSIGNED_INTEGER	([0]|[1-9][0-9]*)
SIGNED_DECIMAL	([+-]([0]|[1-9][0-9]*))
UNSIGNED_DECIMAL	([0]|[1-9][0-9]*)
FRACTIONAL_DECIMAL	([.][0-9][0-9]*)

%x COMMENT

%%
"/*"            { BEGIN(COMMENT); }
<COMMENT>.      |
<COMMENT>\n     { ; }
<COMMENT>"*/"   { BEGIN(INITIAL); }
"//"[^\n]*      { ; }


"$true"		{return TRUE;}
"$false"	{return FALSE;}
"cnf"		{return CNF;}
"include"	{return INCLUDE;}

({COMMENT_LINE}|{COMMENT_BLOCK})	{;}

({SINGLE_QUOTED})	{yylval.sval = strdup( yytext ); return SINGLE_QUOTED;}

({DISTINCT_OBJECT})	{yylval.sval = strdup( yytext ); return DISTINCT_OBJECT;}

({DOLLAR_DOLLAR}{LOWER_WORD})	{yylval.sval = strdup( yytext ); return DOLLAR_DOLLAR_WORD;}

({UPPER_WORD})	{yylval.sval = strdup( yytext ); return UPPER_WORD;}	

({LOWER_WORD})	{yylval.sval = strdup( yytext ); return LOWER_WORD;}

(({SIGNED_DECIMAL}|{UNSIGNED_DECIMAL}){FRACTIONAL_DECIMAL})	{yylval.rval = atof( yytext ); return REAL;}

({SIGNED_INTEGER})	{yylval.ival = atoi( yytext ); return SIGNED_INTEGER;}

({UNSIGNED_INTEGER})	{yylval.ival = atoi( yytext ); return UNSIGNED_INTEGER;}

([ \t])	;	

.	{return yytext[0];}	/* this may be a bug */

%%




