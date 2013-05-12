/* scanner for GML grammar */
%{
/* need this for the call to atof() below */
#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <vector>
using namespace std;
#define YY_DECL extern "C" int yylex()
#include "gml.tab.h"
//int yylineno = 1;
extern YYSTYPE yylval;

 int read_gml(const char*);
void yy_char_ptr(char *string);

%}
%option noyywrap
 //%option debug
ID      [A-Za-z0-9_\"]+
SPACE     [ \t\n]          /* eat up whitespace */


%%

		       /* open curly brace needs to be on same line as rule */
[ \t]+		{  continue; }
[\n]  { yylineno++; }
"#"[^\n]*\n 	   	{  yylineno++; continue; }  /*single line comment */


"[" {
  return '[';
  //return OPEN;
}
"]" {
  return ']';
  //return OPEN;
}




graph   {
  
  return GRAPH;
         }

node {
  
  return NODE;

          }
edge {
  
  return EDGE;

}


{ID}        { 
  yylval.sval = strdup(yytext); 
  return WORD; 
}


.           

%%

#ifdef LEXMAIN
#define
main(int argc, char **argv )
{
  if ( argc > 1 )
    yyin = fopen( argv[1], "r" );
  else
    yyin = stdin;
  
  //yylex();
  vector<string> nodes, edges;
  read_gml(argv[1], nodes, edges);
  printf("Parsed %d lines\n",yylineno+1);
}
#endif
