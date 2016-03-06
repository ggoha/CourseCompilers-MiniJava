#include "Graph.h"

class IRVisitor : public IVisitor {
public:
	IRVisitor(std::string treeFileName) : treeRepresentation(treeFileName), minId(0) {}

	// ћетоды позвол€ют строить линейно св€занные деревь€
	void LinkedVisit(IRStm* node);
	void LinkedVisit(IRExp* node);

	virtual void visit( IRExpCALL* n);
	virtual void visit( IRExpList* n);
	virtual void visit( IRExpESEQ* n);
	virtual void visit( IRExpMEM *n);
	virtual void visit( IRExpBINOP* n);
	virtual void visit( IRExpNAME* n);
	virtual void visit( IRExpTEMP* n);
	virtual void visit( IRExpCONST *n);

	virtual void visit( IRStmMOVE *n);
	virtual void visit( IRStmEXP *n);
	virtual void visit( IRStmCJUMP *n);
	virtual void visit( IRStmSEQ *n);
	virtual void visit( IRStmLABEL *n);
	virtual void visit( IRStmLIST *n);
	virtual void visit( IRStmJUMP *n);

	void Flush() { treeRepresentation.Flush(); }

private:

	int minId;

	std::string lastNodeName;

	Graph treeRepresentation;

	void nextNameWithId(std::string label);
};

