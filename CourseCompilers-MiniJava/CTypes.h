#pragma once
#include <iostream>
#include <vector>
#include "Visitor.h"
using namespace std;


class IRoot
{
public:
	virtual void accept(IVisitor* v);
};

class IStatement : public IRoot
{
public:
	IRoot *c1, *c2, *c3;
	IStatement() {};
};


class CStatementIF : public IStatement
{
public:
	CStatementIF(IRoot* x1, IRoot* x2, IRoot* x3) {
		c1 = x1;
		c2 = x2;
		c3 = x3;
	};
	virtual void accept(IVisitor* v){
		v->visit(this);
	};
};

class CStatementWHILE : public IStatement
{
public:
	CStatementWHILE(IRoot* x1, IRoot* x2) {
		c1 = x1;
		c2 = x2;
	};
	virtual void accept(IVisitor* v){
		v->visit(this);
	};
};

class CStatementPRINTLN : public IStatement
{
public:
	CStatementPRINTLN(IRoot* x1) {
		c1 = x1;
	};
	virtual void accept(IVisitor* v){
		v->visit(this);
	};
};

class CStatementASIGNMENT : public IStatement
{
public:
	CStatementASIGNMENT(IRoot* x1,IRoot* x2) {
		c1 = x1;
		c2 = x2;
	};
	virtual void accept(IVisitor* v){
		v->visit(this);
	};
};

class CStatementSQUEREASIGNMENT: public IStatement
{
public:
	CStatementSQUEREASIGNMENT(IRoot* x1, IRoot* x2, IRoot* x3) {
		c1 = x1;
		c2 = x2;
		c3 = x3;
	};
	virtual void accept(IVisitor* v){
		v->visit(this);
	};
};

class CStatementBRACKETS : public IStatement
{
public:
	CStatementBRACKETS(IRoot* x1) {
		c1 = x1;
	};
	virtual void accept(IVisitor* v){
		v->visit(this);
	};
};

//it's * : Statments, ExpRests , ect.
template< class T>
class TStar : public IRoot
{
public:
	vector<T*> v;
	TStar(){};
	void add(T* x)
	{
		v.push_back(x);
	}
	virtual void accept(IVisitor* v){
		v->visit(this);
	};
};

class CExp : public IRoot
{ 
public:
	IRoot *c1, *c2, *c3;
	CExp() {};
};

class CExpBinary : public CExp
{
public:
	char c;
	CExpBinary(CExp* x1, char _C, CExp* x2)
	{
		c = _C;
		c1 = x1;
		c2 = x2;
	}

	virtual void accept(IVisitor* v){
		v->visit(this);
	};
};


class CExpInSquareBrackets : public CExp {
public:
	CExpInSquareBrackets( CExp* x1, CExp* x2 ) {
		c1 = x1;
		c2 = x2;
	}

	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};


class CExpPointLENGTH : public CExp {
public:
	CExpPointLENGTH( CExp* x1, CExp* x2 ) {
		c1 = x1;
		c2 = x2;
	}

	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};


class CExpPointID : public CExp {
public:
	CExpPointID( CExp* x1, CExp* x2, CExp* x3 ) {
		c1 = x1;
		c2 = x2;
		c3 = x3;
	}

	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};


class CExpINTEGER_LITERAL : public CExp {
public:
	CExpINTEGER_LITERAL( CExp* x1 ) {
		c1 = x1;
	}

	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};


class CExpBool : public CExp {
public:
	CExpBool(CExp* x1) {
		c1 = x1;
	}

	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};


class CExpID : public CExp {
public:
	CExpID( CExp* x1 ) {
		c1 = x1;
	}

	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};


class CExpTHIS : public CExp {
public:
	CExpTHIS( CExp* x1 ) {
		c1 = x1;
	}

	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};


class CExpNEWINT : public CExp {
public:
	CExpNEWINT( CExp* x1, CExp* x2, CExp* x3 ) {
		c1 = x1;
		c2 = x2;
		c3 = x3;
	}

	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};


class CExpNEWID : public CExp {
public:
	CExpNEWID( CExp* x1, CExp* x2 ) {
		c1 = x1;
		c2 = x2;
	}

	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};


class CExpExclamationMark : public CExp {
public:
	CExpExclamationMark( CExp* x1 ) {
		c1 = x1;
	}

	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};


class CExpCircleBrackets : public CExp {
public:
	CExpCircleBrackets( CExp* x1 ) {
		c1 = x1;
	}

	virtual void accept( IVisitor* v ) {
		v->visit( this );
	};
};
