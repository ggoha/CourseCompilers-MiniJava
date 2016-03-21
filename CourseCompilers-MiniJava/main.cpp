#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdexcept>
#include <iostream>
#include "parser.tab.hpp"
#include "PrettyPrinter.h"
#include "CSymbolTable.h"
#include "CTypeChecker.h"
using std::invalid_argument;
using std::cout;
using std::endl;
extern "C" int yylex();
extern FILE* yyin;
int yyparse(CProgram*, int*);

int main(int argc, char** argv) {
	FILE* f = fopen("input.txt","r");
	yyin = f;
	CProgram* root = 0;
	int hasError = 0;
	yyparse(root, &hasError);
	return 0;
	std::string abv = "fd";
}