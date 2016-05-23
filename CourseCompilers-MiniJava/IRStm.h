#pragma once
#include <vector>
#include "IRTemp.h"


class IRStm : public IRNode
{
public:
	virtual void accept(IRVisitor* visitor) const = 0;
};

class IRStmMOVE : public IRStm
{
public:
	const IRExp* dst;
	const IRExp* src;
	IRStmMOVE(const IRExp* _dst, const IRExp* _src) :dst(_dst), src(_src) {};
	virtual void accept(IRVisitor* visitor) const {
		visitor->visit(this);
	};
};

class IRStmEXP : public IRStm
{
public:
	const IRExp* exp;
	IRStmEXP(const IRExp* _exp) : exp(_exp) {};
	virtual void accept(IRVisitor* visitor)  const {
		visitor->visit(this);
	};
}; 

class IRStmCJUMP : public IRStm
{
public:

	enum CJUMP : int
	{
		EQ,
		NE,
		LT,
		GT,
		LE,
		GE,
		ULT,
		ULE,
		UGT,
		UGE
	};
	
	const IRExp* left;
	const IRExp* right;
	const CLabel* iftrue;
	const CLabel* iffalse;
	const int relop;
	IRStmCJUMP(int _relop, const IRExp* _left, const IRExp* _right, const CLabel* _iftrue, const CLabel* _iffalse) :
		relop(_relop),
		left(_left),
		right(_right),
		iftrue(_iftrue),
		iffalse(_iffalse)
	{};
	virtual void accept(IRVisitor* visitor)  const {
		visitor->visit(this);
	};
};

class IRStmSEQ : public IRStm
{
public:
	const IRStm* left;
	const IRStm* right;
	IRStmSEQ(const IRStm* _left, const IRStm* _right) :
		left(_left),
		right(_right)
	{};
	virtual void accept(IRVisitor* visitor)  const {
		visitor->visit(this);
	};
};

class IRStmLABEL : public IRStm
{
public:
	const CLabel* lable;
	IRStmLABEL(const CLabel* _lable) :
		lable(_lable)
	{}
	virtual void accept(IRVisitor* visitor)  const {
		visitor->visit(this);
	};
};

class IRStmLIST : public IRStm
{
public:
	IRStmLIST(){};
	vector<const IRStm*> stms;
	void add(const IRStm* stm)
	{
		stms.push_back(stm);
	}
	virtual void accept(IRVisitor* visitor)  const {
		visitor->visit(this);
	};
};

class IRStmJUMP : public IRStm
{
public:
	const CLabel* lable;
	IRStmJUMP(const CLabel* _lable) :
		lable(_lable)
	{}
	virtual void accept(IRVisitor* visitor)  const {
		visitor->visit(this);
	};
};