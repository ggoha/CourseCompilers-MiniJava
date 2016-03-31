#include "IRCononisation.h"
#include "IRStm.h"
#include "IRExp.h"


void IRCanonizer::visit(const IRExpCALL* n){};
void IRCanonizer::visit(const IRExpList* n){};
void IRCanonizer::visit(const IRExpESEQ* n){};
void IRCanonizer::visit(const IRExpMEM *n){};
void IRCanonizer::visit(const IRExpBINOP* n){};
void IRCanonizer::visit(const IRExpNAME* n){};
void IRCanonizer::visit(const IRExpTEMP* n){};
void IRCanonizer::visit(const IRExpCONST *n){};

void IRCanonizer::visit(const IRStmMOVE *n){};
void IRCanonizer::visit(const IRStmEXP *n){};
void IRCanonizer::visit(const IRStmCJUMP *n){};
void IRCanonizer::visit(const IRStmSEQ *n){
	n->left->accept(this);
	n->right->accept(this);
};
void IRCanonizer::visit(const IRStmLABEL *n){
	stmList->add(n);
};
void IRCanonizer::visit(const IRStmLIST *n){
	for (int i = 0; i < n->stms.size(); ++i)
	{
		stmList->add(n->stms[i]);
	}
};
void IRCanonizer::visit(const IRStmJUMP *n){
}

