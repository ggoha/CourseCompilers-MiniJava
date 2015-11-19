#pragma once
#include <iostream>
#include <vector>
#include "Visitor.h"
using namespace std;
class CExp;
class IStatement;

class IRoot
{
public:
	virtual void accept(IVisitor* v) = 0;
};

class IStatement : public IRoot
{
public:
	IStatement() {};
};

class CVarDecls :public IRoot {
public:
	std::vector<CVarDecl*> vars;
	CVarDecls() {
	};
	CVarDecls( CVarDecl * Var ) {
		vars.push_back( Var );
	}
	void addNext( CVarDecl * Var ) {
		vars.push_back( Var );
	};
	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};

class CClassDecls :public IRoot {
public:
	std::vector<CClassDecl*> classes;
	CClassDecls() {
	};
	CClassDecls( CClassDecl * Class ) {
		classes.push_back( Class );
	}
	void addNext( CClassDecl * Class ) {
		classes.push_back( Class );
	};
	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};

class CMethodDecls :public IRoot {
public:
	std::vector<CMethodDecl*> methods;
	CMethodDecls() {
	};
	CMethodDecls( CMethodDecl * Method ) {
		methods.push_back( Method );
	}
	void addNext( CMethodDecl * Method ) {
		methods.push_back( Method );
	};
	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};


class CStatements :public IRoot {
public:
	std::vector<IStatement*> statements;
	CStatements() {
	};
	CStatements( IStatement * Statement ) {
		statements.push_back(Statement);
	}
	void addNext(IStatement * Statement) {
		statements.push_back(Statement);
	};
	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};

};


class CFormalRests :public IRoot {
public:
	std::vector<CFormalRest*> parametrs;
	CFormalRests() {
	};
	CFormalRests( CFormalRest * Parametr ) {
		parametrs.push_back(Parametr);
	}
	void addNext(CFormalRest * Parametr) {
		parametrs.push_back(Parametr);
	};
	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};

class CExpRests :public IRoot {
public:
	std::vector<CExpRest*> expressions;
	CExpRests(){
	};
	CExpRests(CExpRest * Expression) {
		expressions.push_back(Expression);
	}
	void addNext(CExpRest * Expression) {
		expressions.push_back(Expression);
	};
	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};

class CProgram : public IRoot {
public:
	CMainClass *mainClass;
	CClassDecls *classDecls;
	CProgram( CMainClass* _mainClass, CClassDecls * _classDecls ) {
		mainClass = _mainClass;
		classDecls = _classDecls;
	}
	CProgram( CMainClass * _mainClass ) {
		mainClass = _mainClass;
		classDecls = new CClassDecls();
	}
	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};
class CMainClass :public IRoot {
public:
	string id;
	string idParams;
	CStatements * statements;
	CMainClass( string _id, string _idParams, CStatements* _statements ) {
		id = _id;
		idParams = _idParams;
		statements = _statements;
	};
	virtual void accept(IVisitor* v) {
		v->visit(this);
	};
};
class CClassDecl :public IRoot{
public:
	string id;
	string id2; 	//есть подозрение, что не нужна
	CMethodDecls* methodDecls;
	CVarDecls* varDecls;
	CClassDecl(string _id, CVarDecls* _varDecls, CMethodDecls* _methodDecls) :
		id(_id)
	{
		id2 = "";
		if (_varDecls == 0)
			varDecls = new CVarDecls();
		else
			varDecls = _varDecls;
		if (_methodDecls == 0)
			methodDecls = new CMethodDecls();
		else
			methodDecls = _methodDecls;
	};

	virtual void accept(IVisitor* v){
		v->visit(this);
	};
};

class CClassDeclInheritance :public CClassDecl {
public:
	string idParent, id;
	CClassDeclInheritance(string _id, string _idParent, CVarDecls* _varDecls, CMethodDecls* _methodDecls) :
		CClassDecl(_id, _varDecls, _methodDecls) , idParent(_idParent),id(_id)
	{}
	virtual void accept(IVisitor* v){
		v->visit(this);
	};
};
class CVarDecl :public IRoot{
public:
	CType* type;
	string id;
	CVarDecl(CType* _type,string _id ) : id(_id), type(_type)
	{};
	virtual void accept(IVisitor* v){
		v->visit(this);
	};
};
class CMethodDecl :public IRoot{
public:
	CType* type;
	string id;
	CFormalList* formalList;
	CVarDecls* varDecls;
	CStatements* statements;
	CExp* exp;
	CMethodDecl(CType* _type, string _id, CFormalList* _formalList, CVarDecls* _varDecls, CStatements* _statements, CExp* _exp) :
		type(_type), id(_id), formalList(_formalList), exp(_exp)
	{
		if (_varDecls == 0)
			varDecls = new CVarDecls();
		else
			varDecls = _varDecls;
		if (_statements == 0)
			statements = new CStatements();
		else
			statements = _statements;
	};
	virtual void accept(IVisitor* v){
		v->visit(this);
	};
};

class CFormalList :public IRoot{
public:
	CType* type;
	string id;
	CFormalRests* formalRests;
	CFormalList(CType* _type, string _id, CFormalRests* _formalRests) :
		type(_type), id(_id) {
		if (_formalRests == 0)
			formalRests = new CFormalRests();
		else
			formalRests = _formalRests;
	};
	virtual void accept(IVisitor* v){
		v->visit(this);
	};
};
class CFormalRest : IRoot{
public:
	CType* type;
	string id;
	CFormalRest( CType* _type, string _id) :
		id(_id), type(_type) {};
	virtual void accept(IVisitor* v){
		v->visit(this);
	};
};
class CType{
public:
	static const int  _mas = 0;
	static const int  _bool = 1;
	static const int  _int = 2;
	static const int  _id = 3;
	int inputType;
	string id;
	CType(int _type, string ID = "") : inputType(_type), id(ID) {
		if (inputType == _bool)
			id = "boolean";
		if (inputType == _int)
			id = "int";
		if (inputType == _mas)
			id = "int[]";
	};

	virtual void accept(IVisitor* v){
		v->visit(this);
	};
};

class CStatementIF : public IStatement
{
public:
	CExp* exp;
	IStatement* statementIf;
	IStatement* statementElse;
	CStatementIF(CExp* _exp, IStatement* _statementIf, IStatement* _statementElse) :
		exp(_exp), statementIf(_statementIf), statementElse(_statementElse) {};
	virtual void accept(IVisitor* v){
		v->visit(this);
	};
};

class CStatementWHILE : public IStatement
{
public:
	CExp* exp;
	IStatement* statementWhile;
	CStatementWHILE(CExp* _exp, IStatement* _statementWhile) :
		exp(_exp), statementWhile(_statementWhile) {};
	virtual void accept(IVisitor* v) {
		v->visit(this);
	};
};

class CStatementPRINTLN : public IStatement
{
public:
	CExp* exp;
	CStatementPRINTLN(CExp* _exp): exp(_exp) {};
	virtual void accept(IVisitor* v){
		v->visit(this);
	};
};

class CStatementASIGNMENT : public IStatement
{
public:
	string id;
	CExp* exp;
	CStatementASIGNMENT(string _id, CExp* _exp):
	id(_id), exp(_exp){};
	virtual void accept(IVisitor* v){
		v->visit(this);
	};
};

class CStatementSQUEREASIGNMENT: public IStatement
{
public:
	string id;
	CExp* expInSquareBrackets;
	CExp* expAssigned;
	CStatementSQUEREASIGNMENT(string _id, CExp* _expInSquareBrackets, CExp* _expAssigned) :
		id(_id), expInSquareBrackets(_expInSquareBrackets), expAssigned(_expAssigned) {};
	virtual void accept(IVisitor* v) {
		v->visit(this);
	};
};

class CStatementBRACKETS : public IStatement
{
public:
	CStatements* statements;
	CStatementBRACKETS(CStatements* _statements) : statements(_statements){};
	virtual void accept(IVisitor* v){
		v->visit(this);
	};
};


class CExp : public IRoot
{ 
public:
	CExp() {};
};

class CExpList : public IRoot {
public:
	CExp* exp;
	CExpRests* expRests;
	CExpList(CExp* _exp = 0, CExpRests* _expRests = 0) :
		exp(_exp) {
		if (_expRests == 0)
			expRests = new CExpRests();
		else
			expRests = _expRests;
	};
	virtual void accept(IVisitor* v) {
		v->visit(this);
	};
};

class CExpBinary : public CExp
{
public:
	char op;
	CExp* exp1, *exp2;

	CExpBinary(CExp* _exp1, char _op, CExp* _exp2):
		exp1(_exp1), exp2(_exp2),op(_op)
	{}

	virtual void accept(IVisitor* v){
		v->visit(this);
	};
};

class CExpUnaryMinus : public CExp
{
public:
	CExp* exp;

	CExpUnaryMinus(CExp* _exp) :
		exp(_exp)
	{}

	virtual void accept(IVisitor* v) {
		v->visit(this);
	};
};

class CExpInSquareBrackets : public CExp {
public:
	CExp* exp1, *exp2;

	CExpInSquareBrackets(CExp* _exp1, CExp* _exp2) :
		exp1(_exp1), exp2(_exp2)
	{}
	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};


class CExpPointLENGTH : public CExp {
public:
	CExp* exp;
	CExpPointLENGTH(CExp* _exp) : exp(_exp) {};

	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};


class CExpPointID : public CExp {
public:
	CExpList* expList;
	string id;
	CExp* exp;
	CExpPointID(CExp* _exp, string _id, CExpList* _expList) :
		exp(_exp), id(_id)
	{
		if (_expList)
			expList = _expList;
		else
			expList = new CExpList(0,0);
	};

	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};


class CExpINTEGER_LITERAL : public CExp {
public:
	int integer_literal;
	CExpINTEGER_LITERAL(int i) : integer_literal(i)
	{};

	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};


class CExpSingleOp : public CExp {
public:
	bool val;
	CExpSingleOp( bool a ) {
		val = a;
	}

	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};


class CExpID : public CExp {
public:
	string id;
	CExpID( const string _id ):id(_id) {
	}

	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};


class CExpTHIS : public CExp {
public:
	CExpTHIS() {
	}

	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};


class CExpNEWINT : public CExp {
public:
	CExp* exp;
	CExpNEWINT(CExp* _exp) : exp(_exp) {};

	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};


class CExpNEWID : public CExp {
public:
	string id;
	CExpNEWID(string _id ):id(_id) {
	}

	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};


class CExpExclamationMark : public CExp {
public:
	CExp* exp;
	CExpExclamationMark(CExp* _exp) : exp(_exp) {};

	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};


class CExpCircleBrackets : public CExp {
public:
	CExp* exp;
	CExpCircleBrackets(CExp* _exp) : exp(_exp){
	};

	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};

class CExpRest :public IRoot{
public:
	CExp* exp;
	CExpRest(CExp* _exp) : exp(_exp) {};
	virtual void accept(IVisitor* v){
		v->visit(this);
	};
};





