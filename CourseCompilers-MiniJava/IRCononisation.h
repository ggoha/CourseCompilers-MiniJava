#pragma once
#include "IRVisitor.h"

class IRCanonizer : public IRVisitor
{
	IRNode *lastNode;

	//save cast lastNode
	IRExp* LastNodeAsIRExp();
	IRStm* LastNodeAsIRStm();
public:
	IRStmLIST* stmList;

	virtual void visit(const IRExpCALL* n);
	virtual void visit(const IRExpList* n);
	virtual void visit(const IRExpESEQ* n);
	virtual void visit(const IRExpMEM *n);
	virtual void visit(const IRExpBINOP* n);
	virtual void visit(const IRExpNAME* n);
	virtual void visit(const IRExpTEMP* n);
	virtual void visit(const IRExpCONST *n);

	virtual void visit(const IRStmMOVE *n);
	virtual void visit(const IRStmEXP *n);
	virtual void visit(const IRStmCJUMP *n);
	virtual void visit(const IRStmSEQ *n);
	virtual void visit(const IRStmLABEL *n);
	virtual void visit(const IRStmLIST *n);
	virtual void visit(const IRStmJUMP *n);

};

IRExp* IRCanonizer::LastNodeAsIRExp() {
	IRExp* res = dynamic_cast<IRExp*>(lastNode);
	if (res == NULL)
		throw invalid_argument("can't cast lastNode to IRExp");
	return res;
}

IRStm* IRCanonizer::LastNodeAsIRStm() {
	IRStm* res = dynamic_cast<IRStm*>(lastNode);
	if (res == NULL)
		throw invalid_argument("can't cast lastNode to IRStm");
	return res;
}