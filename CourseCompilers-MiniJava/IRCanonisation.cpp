#include "IRCanonisation.h"
#include "IRStm.h"
#include "IRExp.h"


void IRCanonizer::visit(const IRExpCALL* n){
	n->arguments->accept(this);
	auto args = LastNodeAsIRExp();
	n->function->accept(this);
	auto func = LastNodeAsIRExp();

	lastNode = new IRExpCALL(func,(IRExpList*) args);
};
void IRCanonizer::visit(const IRExpList* n){
	vector<const IRExp*> expList;
	for (int i = 0; i < n->expslist.size(); ++i)
	{
		n->expslist[i]->accept(this);
		expList.push_back(LastNodeAsIRExp());
	}
	lastNode = new IRExpList(expList);
};
void IRCanonizer::visit(const IRExpESEQ* n){

};
void IRCanonizer::visit(const IRExpMEM *n){
	n->exp->accept(this);
	lastNode = new IRExpMEM(LastNodeAsIRExp());
};
void IRCanonizer::visit(const IRExpBINOP* n){};
void IRCanonizer::visit(const IRExpNAME* n){
	lastNode = new IRExpNAME(n->label);
};
void IRCanonizer::visit(const IRExpTEMP* n){
	lastNode = new IRExpTEMP(n->temp);
};
void IRCanonizer::visit(const IRExpCONST *n){
	lastNode = new IRExpCONST(n->Value());
};

void IRCanonizer::visit(const IRStmMOVE *n){
	n->dst->accept(this);
	auto dst = LastNodeAsIRExp();
	n->src->accept(this);
	auto src = LastNodeAsIRExp();
	lastNode = new IRStmMOVE(dst, src);
};
void IRCanonizer::visit(const IRStmEXP *n){
	n->exp->accept(this);
	lastNode = new IRStmEXP(LastNodeAsIRExp());
};
void IRCanonizer::visit(const IRStmCJUMP *n){
	n->left->accept(this);
	auto left = LastNodeAsIRExp();
	n->right->accept(this);
	auto right = LastNodeAsIRExp();
	lastNode = new IRStmCJUMP(n->relop, left, right, n->iftrue, n->iffalse);
};
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
		n->stms[i]->accept(this);
		if(LastNodeAsIRStm())
		stmList->add(n->stms[i]);
	}
};
void IRCanonizer::visit(const IRStmJUMP *n){
	lastNode = new IRStmJUMP(n->lable);
}


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