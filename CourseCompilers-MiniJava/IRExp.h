#pragma once
#include <vector>
#include "IRTemp.h"

class IRExp : public  IRNode 
{
public:
	virtual void accept(IRVisitor* visitor)const = 0;
};

class IRExpList : public IRExp
{

public:
	std::vector<const IRExp*> expslist;
	IRExpList( std::vector<const IRExp*> & exps ) : expslist( exps ) {};
	IRExpList(const IRExp* exps) : expslist(1,exps) {};
	void accept(IRVisitor* irb ) const {
		irb->visit(this);
	}
};

class IRExpCONST: public IRExp{
		int value;
	public:
		IRExpCONST(int _value) : value(_value) {};
		void accept(IRVisitor* irb ) const {
			irb->visit(this);
		}
		int Value() const{
			return value;
		}
};

class IRExpNAME: public IRExp
{
public:
	const CLabel* label;
	IRExpNAME( const CLabel* _label ): label(_label) {
	}
	void accept(IRVisitor* irb ) const {
		irb->visit(this);
	}
};

class IRExpTEMP: public  IRExp
{
public:
	const CTemp* temp;
	IRExpTEMP( const CTemp* _temp ):temp(_temp) {
	};
	void accept(IRVisitor* irb ) const {
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
	void accept(IRVisitor* irb ) const {
		irb->visit(this);
	}
};

class IRExpMEM: public IRExp {
public:
	const IRExp* exp;
	IRExpMEM(const IRExp* _exp) :exp(_exp) {};
	void accept(IRVisitor* irb ) const {
		irb->visit(this);
	}
};

class IRExpCALL: public IRExp
{
public:
	const IRExpList* arguments;
	const IRExp* function;
	IRExpCALL(const IRExp* func, const IRExpList* args) : function(func), arguments(args) {};
	void accept(IRVisitor* irb ) const {
		irb->visit( this );
	}
};
	
class IRExpESEQ: public IRExp
{
public:
	const IRStm* stms;
	const IRExp* exp;
	IRExpESEQ(const IRStm* s, const IRExp* e) : stms(s), exp(e) {};
	void accept(IRVisitor* irb ) const {
		irb->visit(this);
	}
};
