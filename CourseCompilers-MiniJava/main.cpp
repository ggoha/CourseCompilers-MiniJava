#include <stdio.h>
#include <stdexcept>
#include <iostream>
using std::invalid_argument;
using std::cout;
using std::endl;
extern "C" int yylex();
int yyparse(int*);

int main(int argc, char** argv) {
	while (yyparse(0));
	return 0;
}
/*
class CClassDeclList {
	CClassDecl* cur;
	CClassDeclList* tail;
};
*/