#pragma once
#include "IRVisitor.h"
#include "IRBuilder.h"

class IRCanonizer : public IRVisitor
{
	const IRNode* lastNode;
	bool isInsideExp;
	const IRNode* getLastNode();
public:
	IRStmLIST* stmList;
	IRCanonizer() : IRVisitor("A") { stmList = new IRStmLIST(); };
	virtual void visit(const IRExpCALL* n);
	virtual void visit(const IRExpList* n);
	virtual void visit(const IRExpESEQ* n){};
	virtual void visit(const IRExpMEM *n);
	virtual void visit(const IRExpBINOP* n);
	virtual void visit(const IRExpNAME* n);
	virtual void visit(const IRExpTEMP* n);
	virtual void visit(const IRExpCONST *n);

	virtual void visit(const IRStmMOVE *n);
	virtual void visit(const IRStmEXP *n);
	virtual void visit(const IRStmCJUMP *n);
	virtual void visit(const IRStmSEQ *n){};
	virtual void visit(const IRStmLABEL *n);
	virtual void visit(const IRStmLIST *n);
	virtual void visit(const IRStmJUMP *n);
	const IRExp* LastNodeAsIRExp();
	const IRStm* LastNodeAsIRStm();
};

typedef  vector<const IRStm*>::const_iterator  v_iterator;
void cononize_cjump(v_iterator lo, v_iterator hi, vector<const IRStm*>& result);
IRStmLIST* canonize(const IRNode* root);