#pragma once
#include "IRVisitor.h"
#include "IRBuilder.h"

class IRCanonizer : public IRVisitor
{
public:
	IRStmLIST* stmList;
	IRCanonizer(std::string treeFileName) : IRVisitor(treeFileName) { stmList = new IRStmLIST(); };
	virtual void visit(const IRExpCALL* n){};
	virtual void visit(const IRExpList* n);
	virtual void visit(const IRExpESEQ* n){};
	virtual void visit(const IRExpMEM *n){};
	virtual void visit(const IRExpBINOP* n){};
	virtual void visit(const IRExpNAME* n){};
	virtual void visit(const IRExpTEMP* n){};
	virtual void visit(const IRExpCONST *n){};

	virtual void visit(const IRStmMOVE *n){};
	virtual void visit(const IRStmEXP *n){};
	virtual void visit(const IRStmCJUMP *n){};
	virtual void visit(const IRStmSEQ *n){};
	virtual void visit(const IRStmLABEL *n){};
	virtual void visit(const IRStmLIST *n){};
	virtual void visit(const IRStmJUMP *n){};

};

void cononize_cjump(v_iterator lo, v_iterator hi, vector<const IRStm*>& result);
IRStmLIST* canonize(const IRNode* root)
{
	IRCanonizer listCanonizer;
	root->accept(*listCanonizer);
	auto result = new IRStmLIST()
	cononize_cjump(listCanonizer.stmList->stms.begin(),listCanonizer.stmList->stms.end(),result->stms);
	return result;
};