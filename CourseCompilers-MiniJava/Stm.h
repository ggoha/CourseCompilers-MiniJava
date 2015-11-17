#pragma once
#include "Visitor.h"
class CLable;
class CTemp;
class IExp;

class IStm
{
public:
	virtual const void accept(const IVisitor* visitor) = 0;
};

class CStmMOVE : public IStm
{
public:
	const IExp* dst;
	const IExp* src;
	CStmMOVE(const IExp* _dst, const IExp* _src) :dst(_dst), src(_src) {};
	const void accept(const IVisitor* visitor) {
		visitor->visit(this);
	};
};

class CStmEXP : public IStm
{
public:
	const IExp* exp;
	CStmEXP(const IExp* _exp) : exp(_exp) {};
	const void accept(const IVisitor* visitor) {
		visitor->visit(this);
	};
};

class CStmCJUMP : public IStm
{
public:
	const IExp* left;
	const IExp* right;
	const CLable* iftrue;
	const CLable* iffalse;
	const int relop;
	CStmCJUMP(int _relop, const IExp* _exp, const IExp* _left, const IExp* _right, const CLable* _iftrue, const CLable* _iffalse) :
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

class CStmSEQ : public IStm
{
public:
	const IStm* left;
	const IStm* right;
	CStmSEQ(const IStm* _left, const IStm* _right) :
		left(_left),
		right(_right)
	{};
	const void accept(const IVisitor* visitor) {
		visitor->visit(this);
	};
};

class CStmLABEL : public IStm
{
public:
	const CLable* lable;
	CStmLABEL(const CLable* _lable) :
		lable(_lable)
	{}
	const void accept(const IVisitor* visitor) {
		visitor->visit(this);
	};
};