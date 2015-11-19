#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdexcept>
#include <iostream>
using std::invalid_argument;
using std::cout;
using std::endl;
extern "C" int yylex();
extern FILE* yyin;
int yyparse(int*);

int main(int argc, char** argv) {
	FILE* f = fopen("input.txt","r");
	yyin = f;
	yyparse((int*)f);
	return 0;
	std::string abv = "fd";
}