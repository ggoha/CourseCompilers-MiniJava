#pragma once
#include "IRVisitor.h"
#include "IRBuilder.h"

class IRCanonizer : public IRVisitor
{
	IRNode* lastNode;

	//save cast lastNode
	IRExp* LastNodeAsIRExp();
	IRStm* LastNodeAsIRStm();
public:
	IRStmLIST* stmList;
	IRCanonizer(std::string treeFileName) : IRVisitor(treeFileName) { stmList = new IRStmLIST(); };
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
