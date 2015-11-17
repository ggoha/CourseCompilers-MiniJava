#pragma once
#include "Visitor.h"
#include "Frame.h"
class IExp;

class IRStm : public IRNode
{
public:
	virtual const void accept(const IVisitor* visitor) = 0;
};

class IRStmMOVE : public IRStm
{
public:
	const IExp* dst;
	const IExp* src;
	IRStmMOVE(const IExp* _dst, const IExp* _src) :dst(_dst), src(_src) {};
	const void accept(const IVisitor* visitor) {
		visitor->visit(this);
	};
};

class IRStmEXP : public IRStm
{
public:
	const IExp* exp;
	IRStmEXP(const IExp* _exp) : exp(_exp) {};
	const void accept(const IVisitor* visitor) {
		visitor->visit(this);
	};
};

class IRStmCJUMP : public IRStm
{
public:
	const IExp* left;
	const IExp* right;
	const CLabel* iftrue;
	const CLabel* iffalse;
	const int relop;
	IRStmCJUMP(int _relop, const IExp* _exp, const IExp* _left, const IExp* _right, const CLabel* _iftrue, const CLabel* _iffalse) :
		relop(_relop),
		left(_left),
		right(_right),
		iftrue(_iftrue),
		iffalse(_iffalse)
	{};
	const void accept(const IVisitor* visitor) {
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
	const void accept(const IVisitor* visitor) {
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
	const void accept(const IVisitor* visitor) {
		visitor->visit(this);
	};
};