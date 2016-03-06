#pragma once
#include <vector>
#include "IRVisitor.h"
#include "IRTemp.h"

class IRStm;

class IRExp : public  IRNode 
{
public:
	virtual const void accept(const IRVisitor* visitor) = 0;
};

class IRExpList : public IRExp
{

public:
	std::vector<const IRExp*> expslist;
	IRExpList( std::vector<const IRExp*> & exps ) : expslist( exps ) {};
	IRExpList(const IRExp* exps) : expslist(1,exps) {};
	const void accept(const IRVisitor* irb ) {
		irb->visit(this);
	}
};

class IRExpCONST: public IRExp{
		int value;
	public:
		IRExpCONST(int _value) : value(_value) {};
		const void accept(const IRVisitor* irb ) {
			irb->visit(this);
		}
		int Value(){
			return value;
		}
};

class IRExpNAME: public IRExp
{
public:
	const CLabel* label;
	IRExpNAME( const CLabel* _label ): label(_label) {
	}
	const void accept(const IRVisitor* irb ) {
		irb->visit(this);
	}
};

class IRExpTEMP: public  IRExp
{
public:
	const CTemp* temp;
	IRExpTEMP( const CTemp* _temp ):temp(_temp) {
	};
	const void accept(const IRVisitor* irb ) {
		irb->visit(this);
	}
};

class IRExpBINOP: public IRExp
{
public:
	char binop;
	const IRExp* left;
	const IRExp* right;
	IRExpBINOP(char b, const IRExp* l, const IRExp* r) : binop(b), left(l), right(r) {};
	const void accept(const IRVisitor* irb ) {
		irb->visit(this);
	}
};

class IRExpMEM: public IRExp {
public:
	const IRExp* exp;
	IRExpMEM(const IRExp* _exp) :exp(_exp) {};
	const void accept(const IRVisitor* irb ) {
		irb->visit(this);
	}
};

class IRExpCALL: public IRExp
{
public:
	const IRExpList* arguments;
	const IRExp* function;
	IRExpCALL(const IRExp* func, const IRExpList* args) : function(func), arguments(args) {};
	const void accept(const IRVisitor* irb ) {
		irb->visit( this );
	}
};
	
class IRExpESEQ: public IRExp
{
public:
	const IRStm* stms;
	const IRExp* exp;
	IRExpESEQ(const IRStm* s, const IRExp* e) : stms(s), exp(e) {};
	const void accept(const IRVisitor* irb ) {
		irb->visit(this);
	}
};
