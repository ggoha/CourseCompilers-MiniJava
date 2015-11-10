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
	std::vector<CVarDecl*> a;
	CVarDecls() {
	};
	CVarDecls( CVarDecl * x1 ) {
		a.push_back( x1 );
	}
	void addNext( CVarDecl * x1 ) {
		a.push_back( x1 );
	};
	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};

class CClassDecls :public IRoot {
public:
	std::vector<CClassDecl*> a;
	CClassDecls() {
	};
	CClassDecls( CClassDecl * x1 ) {
		a.push_back( x1 );
	}
	void addNext( CClassDecl * x1 ) {
		a.push_back( x1 );
	};
	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};

class CMethodDecls :public IRoot {
public:
	std::vector<CMethodDecl*> a;
	CMethodDecls() {
	};
	CMethodDecls( CMethodDecl * x1 ) {
		a.push_back( x1 );
	}
	void addNext( CMethodDecl * x1 ) {
		a.push_back( x1 );
	};
	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};


class CStatements :public IRoot {
public:
	std::vector<IStatement*> a;
	CStatements() {
	};
	CStatements( IStatement * x1 ) {
		a.push_back( x1 );
	}
	void addNext( IStatement * x1 ) {
		a.push_back( x1 );
	};
	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};

};


class CFormalRests :public IRoot {
public:
	std::vector<CFormalRest*> a;
	CFormalRests() {
	};
	CFormalRests( CFormalRest * x1 ) {
		a.push_back( x1 );
	}
	void addNext( CFormalRest * x1 ) {
		a.push_back( x1 );
	};
	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};

class CExpRests :public IRoot {
public:
	std::vector<CExpRest*> a;
	CExpRests(){
	};
	CExpRests( CExpRest * x1 ) {
		a.push_back( x1 );
	}
	void addNext( CExpRest * x1 ) {
		a.push_back( x1 );
	};
	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};

class CProgram : public IRoot {
public:
	CMainClass *mainClass;
	CClassDecls *classDecls;
	CProgram( CMainClass* x1, CClassDecls * x2 ) {
		mainClass = x1;
		classDecls = x2;
	}
	CProgram( CMainClass * x1 ) {
		mainClass = x1;
		classDecls = new CClassDecls();
	}
	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};
class CMainClass :public IRoot {
public:
	string id1;
	string id2;
	CStatements * statements;
	CMainClass( string _id1, string _id2, CStatements* _statements ) {
		id1 = _id1;
		id2 = _id2;
		statements = _statements;
	};
	virtual void accept(IVisitor* v) {
		v->visit(this);
	};
};
class CClassDecl :public IRoot{
public:
	string id;
	string id2;
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
	string id2, id1;
	CClassDeclInheritance(string _id1, string _id2, CVarDecls* _varDecls, CMethodDecls* _methodDecls) :
		CClassDecl(_id1, _varDecls, _methodDecls) , id2(_id2),id1(_id1)
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
	CType(int _type, string ID = "") : inputType(_type), id(ID) {};

	virtual void accept(IVisitor* v){
		v->visit(this);
	};
};

class CStatementIF : public IStatement
{
public:
	CExp* exp;
	IStatement* statement1;
	IStatement* statement2;
	CStatementIF(CExp* _exp, IStatement* _statement1, IStatement* _statement2) :
		exp(_exp), statement1(_statement1), statement2(_statement2) {};
	virtual void accept(IVisitor* v){
		v->visit(this);
	};
};

class CStatementWHILE : public IStatement
{
public:
	CExp* exp;
	IStatement* statement;
	CStatementWHILE(CExp* _exp, IStatement* _statement) :
		exp(_exp), statement(_statement) {};
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
	CExp* exp1;
	CExp* exp2;
	CStatementSQUEREASIGNMENT(string _id, CExp* _exp1, CExp* _exp2) :
		id(_id), exp1(_exp1), exp2(_exp2) {};
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





