/* ������ ������ ������ ����� ���� �� �������� �������, ����� ��� ����, ����� ���� ����������� ����� � ��������� ��, ��� ����� ������� */

/* ������ � �����, ������� ������� � ������.*/
%{
#include <iostream>
extern "C" int yylex();
void yyerror( int*, const char* );
%}

/* ���� ��� ����� ������� �� ����������� Union
������ ������������ ��� �������� �������, ����������� �������������� ������. */
/* ��������� ������� �������. */
%parse-param { int* hasError }

/* ����������� ��������� ����� ���������. */
%union{
	int ival;
	char sval[255];
	CProgram* program;
	CStatement* statement;
	CClassDecls * classdecls; 
	CMain* cmain;
	CClassDeclInheritance* cclassdeclinheritance;
	CMethodDecl* cmethoddecl;
	CMethodDecls* cmethoddecls;
	CVarDecl* cvardecl;
	CVarDecls* cvardecls;
	CStatements* cstatements;
	CFormalList* cformallist;
	CFormalRests* cformalrests;
	CFormalRest* cformalrest;
	CType* ctype;
	CExp* cexp;
	CExpList* cexplist;
	CExpRests* cexprests;
	CexpRest* cexprest;
}

/* ����������� ����-��������������. ���������� ���� %right.
������� ���������� ����� - ��� ����� �������� ��������, ��� ������ ��� ���������.
� ������ ������ ��� ��������� ����-�������������, �� - ����� ����� ������� ���������, ��� & � |. */
%left '+' '-'
%left '*'
%left UMINUS
%left '[' ']'
%left '(' ')'
%left '.'
%left '!' '&' '<'

/* ����������� �������. ����� ������ ������������� � ������� ��� �� Union. */
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

/* ��������� ��� �� union � ������ �������. */

>
%type<program> Program
%type<statement> Statement 
%type<classdecls> ClassDecls; 
%type<cmain> Main;
%type<cclassdeclinheritance> ClassDeclInheritance;
%type<cmethoddecl> MethodDecl;
%type<cmethoddecls> MethodDecls;
%type<cvardecl> VarDecl;
%type<cvardecls> VarDecls;
%type<cstatements> Statements;
%type<cformallist> FormalList;
%type<cformalrests> FormalRests;
%type<cformalrest> FormalRest;
%type<ctype> Type;
%type<cexp> Exp;
%type<cexplist>  ExpList;
%type<cexprests> ExpRests;
%type<cexprest> ExpRest;


/* ������ � ��������� ������ �������. */
%%
Program:
	MainClass { $$ = new CProgram( $1 ) }
	| MainClass ClassDecls {$$ = new CProgram( $1, $2 ); }
	;
ClassDecls:
	ClassDecl { $$ = new CClassDecls($1); }
	| ClassDecls ClassDecl { $1->addNext($2); }
	;
MainClass:
	CLASS ID '{' PUBLIC STATIC VOID MAIN '(' STRING '[' ']' ID ')' '{' Statement '}' '}' { $$ = new CMain( $2, $12, $15 )}
	;
ClassDecl:
	CLASS ID '{'VarDecls MethodDecls'}' { $$ = new CClassDecl($2, $3, $4) }
	| CLASS ID '{'VarDecls'}' { $$ = new CClassDecl( $2, $4 ) }
	| CLASS ID '{'MethodDecls'}' { $$ = new CClassDecl( $2, $4 )  }
	| CLASS ID '{''}' { $$ = new CClassDecl($2) }
	| CLASS ID EXTENDS ID '{'VarDecls MethodDecls'}' { $$ = new CClassDeclsInheritance($2, $4, $6, $7) }
	| CLASS ID EXTENDS ID '{'VarDecls'}' { $$ = new CClassDeclsInheritance($2, $4, $6) }
	| CLASS ID EXTENDS ID '{'MethodDecls'}' { $$ = new CClassDeclsInheritance($2, $4, $6) }
	| CLASS ID EXTENDS ID '{''}' { $$ = new CClassDeclsInheritance($2, $4) }
	;
VarDecls:
	VarDecl { $$ = new CVardecls($1) }
	| VarDecls VarDecl { $1->addNext($2) }
	;
MethodDecls:
    MethodDecl { $$ = new CMethodDecls($1) } 
	| MethodDecls MethodDecl { $1->addNext($2) }
	;
VarDecl:
	Type ID ';' { $$ = new CVarDecl($1, $2) }
	;
MethodDecl:
	PUBLIC Type ID '(' FormalList  ')' '{' VarDecls Statements RETURN Exp ';' '}' { $$ = new CMethodDecls( $2, $3, $5, $8, $9, $11 ) }
	| PUBLIC Type ID '(' FormalList  ')' '{' VarDecls RETURN Exp ';' '}' { $$ = new CMethodDecls( $2, $3, $5, $8, $10 }
	| PUBLIC Type ID '(' FormalList  ')' '{' Statements RETURN Exp ';' '}' { $$ = new CMethodDecls( $2, $3, $5, $8, $10 }
	| PUBLIC Type ID '(' FormalList  ')' '{' RETURN Exp ';' '}' { $$ = new CMethodDecls( $2, $3, $5, $9 }
	;
Statements:
	Statement { $$ = new CStatements($1) }
	| Statements Statement {$1->addNext($2)  }
	;
FormalList:
	Type ID FormalRests { $$ = new CFormalList($1, $2, $3)  }
	| Type ID { $$ = new CFormalList( $1, $2 ) }
	;
FormalRests:
	FormalRest { $$ = new CFormalRests($1) }
	| FormalRests FormalRest { $1->addNext($2) }
	;
FormalRest:
	',' Type ID { $$ = new CFormalRest($2,$3); }
	;
Type:
	INT '['']' {$$ = new CType( CType::_mas, $1 ) }
	| BOOLEAN { $$ = new CType( CType::_bool, $1 ) }
	| INT { $$ = new CType( CType::_int, $1 ) }
	| ID { $$ = new CType( CType::_id, $1 )}
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
	Exp ExpRests { $$ = new CExpList($1, $2) }
	| Exp {$$ = new CExpList($1)}
	;
ExpRests:
	ExpRest { $$ = new CExpRest($1)}
	| ExpRests ExpRest { $1->addNext($2)} 
ExpRest:
	',' Exp { $$ = new CExpRest($2) }
	;
%%
/* ������� ��������� ������. */
void yyerror( int*, const char* str )
{
	std::cout << str << std::endl;
}