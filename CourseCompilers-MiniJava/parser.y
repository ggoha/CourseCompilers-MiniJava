/* ������ ������ ������ ����� ���� �� �������� �������, ����� ��� ����, ����� ���� ����������� ����� � ��������� ��, ��� ����� ������� */

/* ������ � �����, ������� ������� � ������.*/
%{
#include <iostream>
#include "CTypes.h"
#include "IRForest.h"
#include "IRVisitor.h"
#include "IRBuilder.h"
#include "CSymbolTable.h"
#include "CTypeChecker.h"
#include "PrettyPrinter.h"
#include "IRCanonisation.h"
#include "CodeGeneration.h"
extern FILE* yyin;
extern "C" int yylex();
void yyerror( CProgram* root, int*, const char* );
%}

/* ���� ��� ����� ������� �� ����������� Union
������ ������������ ��� �������� �������, ����������� �������������� ������. */
/* ��������� ������� �������. */
%parse-param { CProgram* root }
%parse-param { int* hasError }

%code requires { #include "CTypes.h" }

/* ����������� ��������� ����� ���������. */
%union{
	int ival;
	char sval[255];
	class CProgram* program;
	class IStatement* statement;
	class CClassDecls* classdecls; 
	class CClassDecl* classdecl; 
	class CMainClass* cmain;
	class CMethodDecl* cmethoddecl;
	class CMethodDecls* cmethoddecls;
	class CVarDecl* cvardecl;
	class CVarDecls* cvardecls;
	class CStatements* cstatements;
	class CFormalList* cformallist;
	class CFormalRests* cformalrests;
	class CFormalRest* cformalrest;
	class CType* ctype;
	class CExp* cexp;
	class CExpList* cexplist;
	class CExpRests* cexprests;
	class CExpRest* cexprest;
}

/* ����������� ����-��������������. ���������� ���� %right.
������� ���������� ����� - ��� ����� �������� ��������, ��� ������ ��� ���������.
� ������ ������ ��� ��������� ����-�������������, �� - ����� ����� ������� ���������, ��� & � |. */
%left '*'
%left '+' '-'
%left UMINUS
%left '[' ']'
%left '(' ')'
%left '!' 
%left '<'
%left '&'
%left '.'


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


%type<program> Program
%type<statement> Statement 
%type<classdecls> ClassDecls;
%type<classdecl> ClassDecl; 
%type<cmain> MainClass;
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
	MainClass {
	 $$ = new CProgram( $1 );
	 CPrettyPrinter pp;
	 pp.visit($$);
	 CSymbolTableBuilder symbolTableBuilder;
	 symbolTableBuilder.visit($$);
	 symbolTableBuilder.Print();
	 CTypeChecker typeChecker;
	 typeChecker.table = symbolTableBuilder.table;
	 typeChecker.visit($$);
	 IRForest iRForest;
	 iRForest.build($$,&symbolTableBuilder.table);
	 auto irpp = IRVisitor("main.txt");
	 irpp.visit((IRStmLIST*)iRForest.iRForest[0]);
	 vector<CInstrList*> blockInstructions;
	 GenerateCode(cout, iRForest.iRForest,blockInstructions);
	 }
	| MainClass ClassDecls {
	 $$ = new CProgram( $1, $2 );
	 CPrettyPrinter pp;
	 pp.visit($$);
	 CSymbolTableBuilder symbolTableBuilder;
	 symbolTableBuilder.visit($$);
	 symbolTableBuilder.Print();
	 CTypeChecker typeChecker;
	 typeChecker.table = symbolTableBuilder.table;
	 typeChecker.visit($$);
	 IRForest iRForest;
	 iRForest.build($$,&symbolTableBuilder.table);
	 
	 for(int i = 0; i < iRForest.iRForest.size();++i)
	 {
		auto irpp = IRVisitor(std::string( "IRTree_" )+iRForest.Frames[i]->frameName + std::string( ".dot" ));
		irpp.visit(iRForest.iRForest[i]);
		irpp.Devide();
		irpp.Flush();
	 }
	 for(int i = 0; i < iRForest.iRForest.size();++i)
	 {
		iRForest.iRForest[i] = canonize(iRForest.iRForest[i]);
	 }
	 for(int i = 0; i < iRForest.iRForest.size();++i)
	 {
		auto irpp = IRVisitor(std::string( "CononizedTree_" )+iRForest.Frames[i]->frameName + std::string( ".dot" ));
		irpp.visit(iRForest.iRForest[i]);
		irpp.Devide();
		irpp.Flush();
	 };
	 vector<CInstrList*> blockInstructions;
	 GenerateCode(cout, iRForest.iRForest,blockInstructions);
	}
	;
ClassDecls:
	ClassDecl { $$ = new CClassDecls($1); }
	| ClassDecls ClassDecl { $$ = $1; $1->addNext($2); }
	;
MainClass:
	CLASS ID '{' PUBLIC STATIC VOID MAIN '(' STRING '[' ']' ID ')' '{' Statements '}' '}' { $$ = new CMainClass( $2, $12, $15 );}	
	| CLASS ID '{' PUBLIC STATIC VOID MAIN '(' STRING '[' ']' ID ')' '{'  '}' '}' { $$ = new CMainClass( $2, $12, new CStatements() );}
	;
ClassDecl:
	CLASS ID '{'VarDecls MethodDecls'}' { $$ = new CClassDecl($2, $4, $5); }
	| CLASS ID '{'VarDecls'}' { $$ = new CClassDecl( $2, $4,0 ); }
	| CLASS ID '{'MethodDecls'}' { $$ = new CClassDecl( $2, 0,$4 );  }
	| CLASS ID '{''}' { $$ = new CClassDecl($2,0,0); }
	| CLASS ID EXTENDS ID '{'VarDecls MethodDecls'}' { $$ = new CClassDeclInheritance($2, $4, $6, $7); }
	| CLASS ID EXTENDS ID '{'VarDecls'}' { $$ = new CClassDeclInheritance($2, $4, $6,0); }
	| CLASS ID EXTENDS ID '{'MethodDecls'}' { $$ = new CClassDeclInheritance($2, $4, 0,$6); }
	| CLASS ID EXTENDS ID '{''}' { $$ = new CClassDeclInheritance($2, $4,0,0); }
	;
VarDecls:
	VarDecl { $$ = new CVarDecls($1); }
	| VarDecls VarDecl {$$ = $1; $1->addNext($2); }
	;
MethodDecls:
    MethodDecl { $$ = new CMethodDecls($1); } 
	| MethodDecls MethodDecl {$$ = $1; $1->addNext($2); }
	;
VarDecl:
	Type ID ';' { $$ = new CVarDecl($1, $2); }
	;
MethodDecl:
	PUBLIC Type ID '(' FormalList  ')' '{' VarDecls Statements RETURN Exp ';' '}' { $$ = new CMethodDecl( $2, $3, $5, $8, $9, $11 ); }
	| PUBLIC Type ID '(' FormalList  ')' '{' VarDecls RETURN Exp ';' '}' { $$ = new CMethodDecl( $2, $3, $5, $8,0, $10); }
	| PUBLIC Type ID '(' FormalList  ')' '{' Statements RETURN Exp ';' '}' { $$ = new CMethodDecl( $2, $3, $5, 0,$8, $10); }
	| PUBLIC Type ID '(' FormalList  ')' '{' RETURN Exp ';' '}' { $$ = new CMethodDecl( $2, $3, $5, 0,0,$9); }
	| PUBLIC Type ID '('   ')' '{' VarDecls Statements RETURN Exp ';' '}' { $$ = new CMethodDecl( $2, $3, 0, $7, $8, $10 ); }
	| PUBLIC Type ID '('   ')' '{' VarDecls RETURN Exp ';' '}' { $$ = new CMethodDecl( $2, $3, 0, $7,0, $9); }
	| PUBLIC Type ID '('   ')' '{' Statements RETURN Exp ';' '}' { $$ = new CMethodDecl( $2, $3,0, 0,$7, $9); }
	| PUBLIC Type ID '('   ')' '{' RETURN Exp ';' '}' { $$ = new CMethodDecl( $2, $3, 0, 0,0,$8); }
	;
Statements:
	Statement { $$ = new CStatements($1); }
	| Statements Statement { $$ = $1; $1->addNext($2) ; }
	;
FormalList:
	Type ID FormalRests { $$ = new CFormalList($1, $2, $3) ; }
	| Type ID { $$ = new CFormalList( $1, $2, 0 ); }
	;
FormalRests:
	FormalRest { $$ = new CFormalRests($1); }
	| FormalRests FormalRest {$$ = $1; $1->addNext($2); }
	;
FormalRest:
	',' Type ID { $$ = new CFormalRest($2,$3); }
	;
Type:
	INT '['']' {$$ = new CType( CType::_mas,string() ); }
	| BOOLEAN { $$ = new CType( CType::_bool,string() ); }
	| INT { $$ = new CType( CType::_int, string() ); }
	| ID { $$ = new CType( CType::_id, $1 );}
	;

Statement:
	'{''}' {$$ = new CStatementBRACKETS(new CStatements()); }
	| '{'Statements'}' {$$ = new CStatementBRACKETS($2); }
	| IF '(' Exp ')' Statement ELSE Statement { $$ = new CStatementIF($3,$5,$7); }
	| WHILE '(' Exp ')' Statement { $$ = new CStatementWHILE($3,$5); }
	| PRINTLN '(' Exp ')'';' {$$ = new CStatementPRINTLN($3); }
	| ID '=' Exp ';' { $$ = new CStatementASSIGNMENT($1,$3); }
	| ID '['Exp']' '=' Exp ';' { $$ = new CStatementSQUAREASSIGNMENT($1,$3,$6); }
	;
Exp:
	Exp '+' Exp { $$ = new CExpBinary($1,'+', $3); }
	| Exp '-' Exp { $$ = new CExpBinary($1,'-', $3); }
	| Exp '*' Exp { $$ = new CExpBinary($1,'*', $3); }
	| '-' Exp %prec UMINUS { $$ = new CExpUnaryMinus($2); }
	| Exp '&' Exp { $$ = new CExpBinary($1,'&', $3); }
	| Exp '<' Exp { $$ = new CExpBinary($1,'<', $3); }
	| Exp '[' Exp ']' { $$ = new CExpInSquareBrackets($1, $3); }
	| Exp'.' LENGTH { $$ = new CExpPointLENGTH($1); }
	| Exp '.' ID '(' ExpList ')' {$$ = new CExpPointID($1, $3, $5); }
	| Exp '.' ID '('')' {$$ = new CExpPointID($1, $3, 0); }
	| INTEGER_LITERAL { $$ = new CExpINTEGER_LITERAL( $1 ); }
	| TRUE { $$ = new CExpSingleOp(true); }
	| FALSE { $$ = new CExpSingleOp(false); }
	| ID { $$ = new CExpID($1); }
	| THIS { $$ = new CExpTHIS(); }
	| NEW INT '[' Exp ']' { $$ = new CExpNEWINT($4); }
	| NEW ID '(' ')' { $$ = new CExpNEWID($2); }
	| '!' Exp { $$ = new CExpExclamationMark($2); }
	| '(' Exp ')' { $$ = new CExpCircleBrackets($2); }
	;
ExpList:
	Exp ExpRests { $$ = new CExpList($1, $2); }
	| Exp {$$ = new CExpList($1); }
	;
ExpRests:
	ExpRest { $$ = new CExpRests($1); }
	| ExpRests ExpRest {$$ = $1; $1->addNext($2); }
	; 
ExpRest:
	',' Exp { $$ = new CExpRest($2); }
	;
%%
/* ������� ��������� ������. */
void yyerror( CProgram* root, int*, const char* str )
{
	std::cout << str << std::endl;
}