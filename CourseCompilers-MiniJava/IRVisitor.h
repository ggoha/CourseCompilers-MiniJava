#pragma once
#include "Graph.h"
class IRExpCALL;
class IRExpList;
class IRExpESEQ;
class IRExpMEM;
class IRExpBINOP;
class IRExpNAME;
class IRExpNAME;
class IRExpTEMP;
class IRExpCONST;
class IRStmMOVE;
class IRStmCJUMP;
class IRStmSEQ;
class IRStmLABEL;
class IRStmLIST;
class IRStmJUMP;
class IRStmEXP;
class IRStm;
class IRExp;

class IRVisitor {
public:
	IRVisitor(std::string treeFileName) : treeRepresentation(treeFileName), minId(0) {};

	// ћетоды позвол€ют строить линейно св€занные деревь€
	void LinkedVisit(const IRStm* node);
	void LinkedVisit(const IRExp* node);

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

	void RecursiveVisit(const IRStmLIST *node, int i);
	void RecursiveVisitExp(const IRExpList *node, int i);

	void Devide();
	void Flush() { treeRepresentation.Flush(); };

private:

	int minId;

	std::string lastNodeName;

	Graph treeRepresentation;

	void nextNameWithId(std::string label);
};

