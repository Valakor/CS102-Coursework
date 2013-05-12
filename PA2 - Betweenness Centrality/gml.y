%{
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

 int yyerror(string s);//void yyerror(const char *s);

%}
%debug
%union {
  char * sval;
};
%token WORD GRAPH NODE EDGE OPEN CLOSE
%type <sval> WORD


%{
  vector<string> yynodeStrs;
  vector<string> yyedgeStrs;
  stringstream yygmlss;
  extern int yylineno;
%}

%%
gr : GRAPH '[' body_list ']'  {   }

body_list : body_item { } 
| body_list body_item { }
;

body_item : NODE '[' word_list ']' { yynodeStrs.push_back(yygmlss.str()); yygmlss.clear(); yygmlss.str(""); }
| EDGE '[' word_list ']' { yyedgeStrs.push_back(yygmlss.str()); yygmlss.clear(); yygmlss.str(""); }
| WORD {  }
;
word_list: WORD { yygmlss << $1 << " "; }
| word_list WORD { yygmlss << $2 << " "; }
;

%%

int yyerror(string s)
{
  extern int yylineno;	// defined and maintained in lex.c
  extern char *yytext;	// defined and maintained in lex.c
  
  cerr << "ERROR: " << s << " at symbol \"" << yytext;
  cerr << "\" on line " << yylineno << endl;
  exit(1);
}

int yyerror(char *s)
{
  return yyerror(string(s));
}

int 
read_gml(const char *fn, vector<std::string>& nodes, vector<std::string>& edges)
{
  extern FILE *yyin;
  int ret;
  extern int yylineno;
  yydebug = 0;
  extern int yy_flex_debug;
  //yy_flex_debug = 1;
  yyin=fopen(fn,"r");
  if(yyin==NULL){
     cerr << "Cannot open " << fn << endl;
     return 1;
  }
  char *current_file=(char*)fn;
  yylineno=1;  
  //yylex();
  if(yyparse()==0){
     
    //cerr << "\nParsing OK!\n";
     ret=0;
  }else{
     cerr << "\nGML Syntax Problem!\n";
     return 1;
  }
  nodes = yynodeStrs;
  edges = yyedgeStrs;
  fclose(yyin);
  return ret;
}
