#pragma once
#include "Visitor.h"
class IRVisitor : public IVisitor{
public:
	virtual void visit(IRExpCALL* n) const {};
	virtual void visit(IRExpList* n) const {};
	virtual void visit(IRExpESEQ* n) const {};
	virtual void visit(IRExpMEM *n) const {};
	virtual void visit(IRExpBINOP* n) const {};
	virtual void visit(IRExpNAME* n) const {};
	virtual void visit(IRExpTEMP* n) const {};
	virtual void visit(IRExpCONST *n) const {};

	virtual void visit(IRStmMOVE *n) const {};
	virtual void visit(IRStmEXP *n) const {};
	virtual void visit(IRStmCJUMP *n) const {};
	virtual void visit(IRStmSEQ *n) const {};
	virtual void visit(IRStmLABEL *n) const {};
	virtual void visit(IRStmLIST *n) const {};
	virtual void visit(IRStmJUMP *n) const {};
};