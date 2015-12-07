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
	virtual void visit(IRExpCONST *n) {};
};