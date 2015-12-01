#pragma once
#include "CTypes.h"
#include "Frame.h"

class IRStm;

class IRExp : public  IRNode 
{

};

class IRExpList : public IRExp
{
public:

};

class IRExpCONST: public IRExp{
		int value;
	public:
		IRExpCONST(int _value) : value(_value) {};
		void accept( CIRBuilder* irb ) {
		}
};

class IRExpNAME: public IRExp
{
public:
	const CLabel* label;
	IRExpNAME( const CLabel* _label ): label(_label) {
	}
	void accept( CIRBuilder* irb ) {
	}
};

class IRExpTEMP: public  IRExp
{
public:
	const CTemp* temp;
	IRExpTEMP( const CTemp* _temp ):temp(_temp) {
	};
	void accept( CIRBuilder* irb ) {
	}
};

class IRExpBINOP: public IRExp
{
public:
	char binop;
	const IRExp* left;
	const IRExp* right;
	IRExpBINOP(char b, const IRExp* l, const IRExp* r) : binop(b), left(l), right(r) {};
	void accept( CIRBuilder* irb ) {
	}
};

class IRExpMEM: public IRExp {
public:
	const IRExp* exp;
	IRExpMEM(const IRExp* _exp) :exp(_exp) {};
	void accept( CIRBuilder* irb ) {
	}
};

class IRExpCALL: public IRExp
{
public:
	const IRExpList* arguments;
	const IRExp* function;
	IRExpCALL(const IRExp* func, const IRExpList* args) : function(func), arguments(args) {};
	void accept( CIRBuilder* irb ) {
	}
};
	
class IRExpESEQ: public IRExp
{
public:
	const IRStm* stms;
	const IRExp* exp;
	IRExpESEQ(const IRStm* s, const IRExp* e) : stms(s), exp(e) {};
	void accept( CIRBuilder* irb ) {
	}
};
