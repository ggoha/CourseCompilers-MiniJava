/* Данный пример скорее всего даже не является рабочим, нужен для того, чтобы была возможность найти и загуглить то, что нужно гуглить */

/* Секция с кодом, который попадет в парсер.*/
%{
#include <iostream>
extern "C" int yylex();
void yyerror( int*, const char* );
%}

/* Этот код будет помещен до определения Union
Обычно используется для описания классов, реализующих синтаксическое дерево. */
/* Параметры функции парсера. */
%parse-param { int* hasError }

/* Определение возможных типов выражения. */
%union{
	int ival;
	char sval[255];
	CProgram* program;
}

/* Определение лево-ассоцитивности. Аналогично есть %right.
Порядок объявление важен - чем позже объявлен оператор, тем больше его приоритет.
В данном случае оба оператора лево-ассоциативные, но - имеет более высокий приоритет, чем & и |. */
%left '+' '-'
%left '*'
%left UMINUS
%left '[' ']'
%left '(' ')'
%left '.'
%left '!' '&' '<'

/* Определение токенов. Можно задать ассоциируемый с токеном тип из Union. */
%token<ival> INTEGER_LITERAL
%token CLASS
%token BINARY_OPERATOR
%token COMMENT
%token<sval> ID
%token PUBLIC
%token STATIC
%token VOID
%token MAIN
%token STRING
%token EXTENDS
%token BOOLEAN
%token IF
%token ELSE
%token WHILE
%token PRINTLN
%token LENGTH
%token TRUE
%token FALSE
%token THIS
%token NEW 
%token RETURN
%token INT
%type<CProgram> Program
%type<CStatement> Statement
%type< CStar<CStatement> > Statements
%type<CExp> Exp
/* Связываем тип из union и символ парсера. */

/* Секция с описанием правил парсера. */
%%
Program:
	MainClass {}
	| MainClass ClassDecls {$$ = new CProgram( $1, $2 ); }
	;
ClassDecls:
	ClassDecl { $$ = new CClassDecls($1); }
	| ClassDecls ClassDecl { $1->addNext($2); }
	;
MainClass:
	CLASS ID '{' PUBLIC STATIC VOID MAIN '(' STRING '[' ']' ID ')' '{' Statement '}' '}' {}
	;
ClassDecl:
	CLASS ID '{'VarDecls MethodDecls'}' {}
	| CLASS ID '{'VarDecls'}' {}
	| CLASS ID '{'MethodDecls'}' {}
	| CLASS ID '{''}' {}
	| CLASS ID EXTENDS ID '{'VarDecls MethodDecls'}' {}
	| CLASS ID EXTENDS ID '{'VarDecls'}' {}
	| CLASS ID EXTENDS ID '{'MethodDecls'}' {}
	| CLASS ID EXTENDS ID '{''}' {}
	;
VarDecls:
	VarDecl {}
	| VarDecls VarDecl {}
	;
MethodDecls:
    MethodDecl {} 
	| MethodDecls MethodDecl {}
	;
VarDecl:
	Type ID ';' {}
	;
MethodDecl:
	PUBLIC Type ID '(' FormalList  ')' '{' VarDecls Statements RETURN Exp ';' '}' {}
	| PUBLIC Type ID '(' FormalList  ')' '{' VarDecls RETURN Exp ';' '}' {}
	| PUBLIC Type ID '(' FormalList  ')' '{' Statements RETURN Exp ';' '}' {}
	| PUBLIC Type ID '(' FormalList  ')' '{' RETURN Exp ';' '}' {}
	;
Statements:
	Statement {}
	| Statements Statement {}
	;
FormalList:
	Type ID FormalRests {}
	| Type ID {}
	;
FormalRests:
	FormalRest {}
	| FormalRests FormalRest {}
	;
FormalRest:
	',' Type ID {}
	;
Type:
	INT '['']' {}
	| BOOLEAN {}
	| INT {}
	| ID {}
	;
Statement:
	'{'Statement'}' {$$ = new CStatementBRACKETS($1); }
	| IF '(' Exp ')' Statement ELSE Statement { $$ = new CStatementIF($3,$5,$7); }
	| WHILE '(' Exp ')' Statement { $$ = new CStatementWHILE($3,$5); }
	| PRINTLN '(' Exp ')'';' {$$ = new CStatementPRINTLN($3); }
	| ID '=' Exp ';' { $$ = new CStatementASIGNMENT($1,$3); }
	| ID '['Exp']' '=' Exp ';' { $$ = new CStatementSQUEREASIGNMENT($1,$3,$6); }
	;
Exp:
	Exp '+' Exp { $$ = new CExpBinary($1,'+', $3); }
	| Exp '-' Exp { $$ = new CExpBinary($1,'-', $3); }
	| Exp '*' Exp { $$ = new CExpBinary($1,'*', $3); }
	| '-' Exp %prec UMINUS { }
	| Exp '&' '&' Exp { $$ = new CExpBinary($1,'&', $4); }
	| Exp '<' Exp { $$ = new CExpBinary($1,'+', $3); }
	| Exp '[' Exp ']' { $$ = new CExpInSquareBrackets($1, $3)}
	| Exp'.' LENGTH { $$ = new CExpPointLENGTH($1, $3) }
	| Exp '.' ID '(' ExpList ')' {$$ = new CExpPointID($1, $3, $5) }
	| INTEGER_LITERAL { $$ = new CExpINTEGER_LITERAL( $1 )  }
	| TRUE { $$ = new CExpSingleOp($1) }
	| FALSE { $$ = new CExpSingleOp($1) }
	| ID { $$ = new CExpID($1) }
	| THIS { $$ = new CExpTHIS($1) }
	| NEW INT '[' Exp ']' { $$ = new CExpNEWINT($1,$2,$4) }
	| NEW ID '(' ')' { $$ = new CExpNEWID($1,$2) }
	| '!' Exp { $$ = new CExpExclamationMark($2)}
	| '(' Exp ')' { $$ = new CExpCircleBrackets($2) }
	;
ExpList:
	Exp ExpRests {}
	| Exp {}
	;
ExpRests:
	ExpRest {}
	| ExpRests ExpRest {} 
ExpRest:
	',' Exp {}
	;
%%
/* Функция обработки ошибки. */
void yyerror( int*, const char* str )
{
	std::cout << str << std::endl;
}