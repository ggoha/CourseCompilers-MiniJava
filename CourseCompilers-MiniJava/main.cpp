#include <stdio.h>
#include <stdexcept>
#include <iostream>
using std::invalid_argument;
using std::cout;
using std::endl;
extern "C" int yylex();
extern FILE* yyin;
extern int yyparse();

int main(int argc, char** argv) {
	FILE* f = fopen("input.txt","r");
	yyin = f;
	yyparse();
	return 0;
}
/*
class CClassDeclList {
	CClassDecl* cur;
	CClassDeclList* tail;
};
*/