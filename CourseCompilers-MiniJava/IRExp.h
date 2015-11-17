#pragma once
#include "CTypes.h"
#include "Frame.h"

class IRStm;

class IRExp : public  IRNode 
{

};

class IRExpList : public IRExp
{
};

class IRExpCONST: public IRExp{
		int value;
	public:
		IRExpCONST(int _value) : value(_value) {};
};

class IRExpNAME: public IRExp
{
public:
	const CLabel* label;
	IRExpNAME( const CLabel* _label ): label(_label) {
	}
};

class IRExpTEMP: public  IRExp
{
public:
	const CTemp* temp;
	IRExpTEMP( const CTemp* _temp ):temp(_temp) {
	};
};

class IRExpBINOP: public IRExp
{
public:
	char binop;
	const IRExp* left;
	const IRExp* right;
	IRExpBINOP(char b, const IRExp* l, const IRExp* r) : binop(b), left(l), right(r) {};
};

class IRExpMEM: public IRExp {
public:
	const IRExp* exp;
	IRExpMEM(const IRExp* _exp) :exp(_exp) {};
};

class IRExpCALL: public IRExp
{
public:
	const IRExpList* arguments;
	const IRExp* function;
	IRExpCALL(const IRExp* func, const IRExpList* args) : function(func), arguments(args) {};
};
	
class IRExpESEQ: public IRExp
{
public:
	const IRStm* stms;
	const IRExp* exp;
	IRExpESEQ(const IRStm* s, const IRExp* e) : stms(s), exp(e) {};
};
