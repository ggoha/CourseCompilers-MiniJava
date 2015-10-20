%option noyywrap
%{
#include <iostream>
#include "parser.tab.hpp"
using namespace std;
#define YY_DECL extern "C" int yylex()
%}

digit         [0-9]
letter        [a-zA-Z]

%%
"class" { return CLASS; }
"public" { return PUBLIC; }
"static" { return STATIC; }
"void" { return VOID; }
"main" { return MAIN; }
"string" { return STRING; }
"extends" { return EXTENDS; }
"return" { return RETURN; }
"boolean" {return BOOLEAN; }
"if" {return IF; }
"else" {return ELSE; }
"while " {return WHILE; }
"System.out.printLn" { return PRINTLN; }
"length" {return LENGTH; }
"true" {return TRUE; }
"false" {return FALSE; }
"this" {return THIS; }
"new" {return NEW; }
{letter}+({letter}|{digit}|\_)*		{ strcpy_s(yylval.sval, yytext); return ID; }
{digit}+  { yylval.ival = atoi( yytext ); return INTEGER_LITERAL; }
\&\&|<|\+|-|\*	{ return yytext[0]; }
(\/\/.*\n)|(\/\*.*\*\/)	{ return COMMENT; }
"int" { return INT; }
%%

