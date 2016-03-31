#pragma once
#include "IRVisitor.h"
#include "IRStm.h"
#include "IRExp.h"
using namespace std;



void IRVisitor::visit(const IRStmMOVE* node)
{
	treeRepresentation.PlusTab();
	node->dst->accept(this);
	treeRepresentation.MinusTab();
	string destString = lastNodeName;

	treeRepresentation.PlusTab();
	node->src->accept(this);
	treeRepresentation.MinusTab();
	string srcString = lastNodeName;

	nextNameWithId("move");

	treeRepresentation.AddEdge(lastNodeName, destString, "dest");
	treeRepresentation.AddEdge(lastNodeName, srcString, "src");
}

void IRVisitor::visit(const IRStmEXP* node)
{
	treeRepresentation.PlusTab();
	node->exp->accept(this);
	treeRepresentation.MinusTab();
	string prevString = lastNodeName;

	nextNameWithId("exp");
	treeRepresentation.AddEdge(lastNodeName, prevString);
}

void IRVisitor::visit(const IRStmJUMP* node)
{
	nextNameWithId("jump");
	treeRepresentation.AddEdge(lastNodeName, node->lable->Name(), "to_label");
}

void IRVisitor::visit(const IRStmCJUMP* node)
{
	treeRepresentation.PlusTab();
	node->right->accept(this);
	treeRepresentation.MinusTab();
	string rightString = lastNodeName;
	treeRepresentation.PlusTab();
	node->left->accept(this);
	treeRepresentation.MinusTab();
	string leftString = lastNodeName;
	string sign;
	switch( node->relop ){
	case 1:
		sign = "==";
		break;
	case 2:
		sign = "!=";
		break;
	case 3:
		sign = "<";
		break;
	case 4:
		sign = ">";
		break;
	case 5:
		sign = "<=";
		break;
	case 6:
		sign = "unary <";
		break;
	case 7:
		sign = "unary <=";
		break;
	case 8:
		sign = "unary >";
		break;
	case 9:
		sign = "unary >=";
		break;
	}
	nextNameWithId("Cjump"); //+ sign);

	treeRepresentation.AddEdge(lastNodeName, rightString, "right");
	treeRepresentation.AddEdge(lastNodeName, leftString, "left");
	treeRepresentation.AddEdge(lastNodeName, node->iftrue->Name(), "iftrue");
	treeRepresentation.AddEdge(lastNodeName, node->iffalse->Name(), "iffalse");
}

void IRVisitor::visit(const IRStmSEQ* node)
{
	if (node->left != nullptr) {
		treeRepresentation.PlusTab();
		node->left->accept(this);
		treeRepresentation.MinusTab();
		string leftString = lastNodeName;
		if (node->right != nullptr) {
			treeRepresentation.PlusTab();
			node->right->accept(this);
			treeRepresentation.MinusTab();
			string rightString = lastNodeName;
			nextNameWithId("seq");
			treeRepresentation.AddEdge(lastNodeName, leftString, "left");
			treeRepresentation.AddEdge(lastNodeName, rightString, "right");
		}
		else {
			nextNameWithId("seq");
			treeRepresentation.AddEdge(lastNodeName, leftString, "left");
		}
	}
	else {
		nextNameWithId("seq");
	}
}

void IRVisitor::visit(const IRExpCONST* node)
{
	nextNameWithId(string("const_") + to_string(node->Value()));
}

void IRVisitor::visit(const IRExpNAME* node)
{
	nextNameWithId(string("name_") + node->label->Name());
}

void IRVisitor::visit(const IRExpTEMP* node)
{
	nextNameWithId(string("temp_") + node->temp->Name());
}

void IRVisitor::visit(const IRExpBINOP* node)
{
	treeRepresentation.PlusTab();
	node->left->accept(this);
	treeRepresentation.MinusTab();
	string leftString = lastNodeName;
	treeRepresentation.PlusTab();
	node->right->accept(this);
	treeRepresentation.MinusTab();
	string rightString = lastNodeName;
	//graphviz отказывается работать с символами типа + *
	switch (node->binop) {
		
	case '*':
		nextNameWithId("binop__Mul");
		break;
	case '+':
		nextNameWithId("binop__Plus");
		break;
	case '/':
		nextNameWithId("binop__Division");
		break;
	case '-':
		nextNameWithId("binop__Minus");
		break;
	case '^': // добавить
		nextNameWithId("binop__Xor");
		break;
	case '<':
		nextNameWithId("binop__Less");
		break;
	case '>':
		nextNameWithId("binop__Greater");
		break;
	case '&':
		nextNameWithId("binop__And");
		break;
	default:
		//assert(false);
		break;
	}
	treeRepresentation.AddEdge(lastNodeName, rightString, "right");
	treeRepresentation.AddEdge(lastNodeName, leftString, "left");
}

void IRVisitor::visit(const IRExpMEM* node)
{
	treeRepresentation.PlusTab();
	node->exp->accept(this);
	treeRepresentation.MinusTab();
	string prevString = lastNodeName;
	nextNameWithId("mem");
	treeRepresentation.AddEdge(lastNodeName, prevString);
}

void IRVisitor::visit(const IRExpCALL* node)
{
	
	if (node->function != nullptr){
		treeRepresentation.PlusTab();
		node->function->accept(this);
		treeRepresentation.MinusTab();
	}
	string funcString = lastNodeName;
	if (node->arguments != nullptr){
		treeRepresentation.PlusTab();
		node->arguments->accept(this);
		treeRepresentation.MinusTab();
	}
	string argsString = lastNodeName;
	nextNameWithId("call");
	treeRepresentation.AddEdge(lastNodeName, funcString, "func");
	treeRepresentation.AddEdge(lastNodeName, argsString, "args");
}

void IRVisitor::visit(const IRExpESEQ* node)
{
	treeRepresentation.PlusTab();
	node->stms->accept(this);
	treeRepresentation.MinusTab();
	string stmString = lastNodeName;
	treeRepresentation.PlusTab();
	node->exp->accept(this);
	treeRepresentation.MinusTab();
	string expString = lastNodeName;
	nextNameWithId("eseq");
	treeRepresentation.AddEdge(lastNodeName, expString, "exp");
	treeRepresentation.AddEdge(lastNodeName, stmString, "stm");
}

void IRVisitor::visit(const IRExpList* node)
{
	//if (node->expslist.size() != 0) {
		/*
		treeRepresentation.PlusTab();
		node->expslist[0]->accept(this);
		treeRepresentation.MinusTab();
		string headString = lastNodeName;
		treeRepresentation.AddEdge(lastNodeName, headString, "head");
		if (node->expslist.size() > 1){
			for (unsigned i = 1; i < node->expslist.size(); ++i){
				treeRepresentation.PlusTab();
				node->expslist[i]->accept(this);
				treeRepresentation.MinusTab();
				treeRepresentation.AddEdge(lastNodeName, headString, "head");
			}
			string tailString = lastNodeName;
			nextNameWithId("expList");
			treeRepresentation.AddEdge(lastNodeName, tailString, "tail");
		}
		else{
			nextNameWithId("expList");
			treeRepresentation.AddEdge(lastNodeName, headString, "head");
		}
	}
	else { 
		nextNameWithId("expList");
	}*/
		//for (unsigned i = 1; i < node->expslist.size(); ++i){
			//node->expslist[i]->accept(this);
			//treeRepresentation.AddEdge(lastNodeName, headString, "head");
	RecursiveVisitExp(node, 0);
}

void IRVisitor::visit(const IRStmLABEL* node)
{
	nextNameWithId(string("label:") + node->lable->Name());
}

void IRVisitor::nextNameWithId(std::string label)
{
	lastNodeName = label + string("__id_") + to_string(minId++);
	treeRepresentation.SetNodeLabel(lastNodeName, label);
}

void IRVisitor::LinkedVisit(const IRStm* node)
{
	string fromName = lastNodeName;
	treeRepresentation.PlusTab();
	node->accept(this);
	treeRepresentation.MinusTab();
	string toName = lastNodeName;
	if (!fromName.empty()) {
		treeRepresentation.AddEdge(fromName, toName, "next");
	}
}

void IRVisitor::LinkedVisit(const IRExp* node)
{
	string fromName = lastNodeName;
	treeRepresentation.PlusTab();
	node->accept(this);
	treeRepresentation.MinusTab();
	string toName = lastNodeName;
	if (!fromName.empty()) {
		treeRepresentation.AddEdge(fromName, toName, "next");
	}
}

	/*
	if (node->stms.size() != 0) {
		treeRepresentation.PlusTab();
		node->stms[0]->accept(this);
		treeRepresentation.MinusTab();
		string headString = lastNodeName;
		treeRepresentation.AddEdge(lastNodeName, headString, "head");
		if (node->stms.size() > 1){
			for (unsigned i = 1; i < node->stms.size(); ++i){
				treeRepresentation.PlusTab();
				node->stms[i]->accept(this);
				treeRepresentation.MinusTab();
			    treeRepresentation.AddEdge(lastNodeName, headString, "head");
			}
			string tailString = lastNodeName;
			nextNameWithId("stmList");
			treeRepresentation.AddEdge(lastNodeName, tailString, "tail");
		}
		else{
			nextNameWithId("stmList");
			treeRepresentation.AddEdge(lastNodeName, headString, "head");
		}
	}
	else {
		nextNameWithId("stmList");
	} */
void IRVisitor::RecursiveVisit(const IRStmLIST *node, int i)
{
	string name = "";
	if (i == 0){
		name = "StmList";
	}
	else{
		name = "Step_" + to_string(i);
	}
    if (node->stms.size() > i) {
		node->stms[i]->accept(this);
		string headString = lastNodeName;
		if (node->stms.size() > i) {

			RecursiveVisit(node, i + 1);
			string tailString = lastNodeName;
			nextNameWithId(name);
			treeRepresentation.AddEdge(lastNodeName, headString, "head");
			treeRepresentation.AddEdge(lastNodeName, tailString, "tail");
		}
		else {
			nextNameWithId(name);
			treeRepresentation.AddEdge(lastNodeName, headString, "head");
		}
	}
	else {
		nextNameWithId(name);
	}
}

void IRVisitor::RecursiveVisitExp(const IRExpList *node, int i)
{
	string name = "";
	if (i == 0){
		name = "ExpList";
	}
	else{
		name = "Step_" + to_string(i);
	}
	if (node->expslist.size() > i) {
		node->expslist[i]->accept(this);
		string headString = lastNodeName;
		if (node->expslist.size() > i) {
			RecursiveVisitExp(node, i + 1);
			string tailString = lastNodeName;
			nextNameWithId(name);
			treeRepresentation.AddEdge(lastNodeName, headString, "head");
			treeRepresentation.AddEdge(lastNodeName, tailString, "tail");
		}
		else {
			nextNameWithId(name);
			treeRepresentation.AddEdge(lastNodeName, headString, "head");
		}
	}
	else {
		nextNameWithId(name);
	}
}
void IRVisitor::visit(const IRStmLIST *node)
{
		RecursiveVisit(node, 0);
}

void IRVisitor::Devide(){
	treeRepresentation.Devide();
}
