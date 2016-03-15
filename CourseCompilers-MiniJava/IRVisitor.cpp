#include "IRVisitor.h"
#include "IRBuilder.h"
#include "IRStm.h"
#include "IRExp.h"

using namespace std;



void IRVisitor::visit( IRStmMOVE* node)
{
	node->dst->accept(this);
	string destString = lastNodeName;

	node->src->accept(this);
	string srcString = lastNodeName;

	nextNameWithId("move");

	treeRepresentation.AddEdge(lastNodeName, destString, "dest");
	treeRepresentation.AddEdge(lastNodeName, srcString, "src");
}

void IRVisitor::visit(const IRStmEXP* node)
{
	node->exp->accept(this);
	string prevString = lastNodeName;

	nextNameWithId("exp");
	treeRepresentation.AddEdge(lastNodeName, prevString);
}

void IRVisitor::visit(const IRStmJUMP* node)
{
	nextNameWithId("jump");
	treeRepresentation.AddEdge(lastNodeName, node->label->Name(), "to_label");
}

void IRVisitor::visit(const IRStmCJUMP* node)
{
	node->right->accept(this);
	string rightString = lastNodeName;
	node->left->accept(this);
	string leftString = lastNodeName;

	nextNameWithId("Cjump");

	treeRepresentation.AddEdge(lastNodeName, rightString, "right");
	treeRepresentation.AddEdge(lastNodeName, leftString, "left");
	treeRepresentation.AddEdge(lastNodeName, node->iftrue->Name(), "iftrue");
	treeRepresentation.AddEdge(lastNodeName, node->iffalse->Name(), "iffalse");
}

void IRVisitor::visit(const IRStmSEQ* node)
{
	if (node->left != nullptr) {
		node->left->accept(this);
		string leftString = lastNodeName;
		if (node->right != nullptr) {
			node->right->accept(this);
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

void IRVisitor::visit(IRExpCONST* node)
{
	nextNameWithId(string("const_") + to_string(node->Value()));
}

void IRVisitor::visit(IRExpNAME* node)
{
	nextNameWithId(string("name_") + node->label->Name());
}

void IRVisitor::visit(IRExpTEMP* node)
{
	nextNameWithId(string("temp_") + node->temp->Name());
}

void IRVisitor::visit( IRExpBINOP* node)
{
	node->left->accept(this);
	string leftString = lastNodeName;
	node->right->accept(this);
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
	case 'xor': // добавить
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
		assert(false);
		break;
	}
	treeRepresentation.AddEdge(lastNodeName, rightString, "right");
	treeRepresentation.AddEdge(lastNodeName, leftString, "left");
}

void IRVisitor::visit(const IRExpMEM* node)
{
	node->exp->accept(this);
	string prevString = lastNodeName;
	nextNameWithId("mem");
	treeRepresentation.AddEdge(lastNodeName, prevString);
}

void IRVisitor::visit(const IRExpCALL* node)
{
	node->function->accept(this);
	string funcString = lastNodeName;
	node->arguments.accept(this);
	string argsString = lastNodeName;
	nextNameWithId("call");
	treeRepresentation.AddEdge(lastNodeName, funcString, "func");
	treeRepresentation.AddEdge(lastNodeName, argsString, "args");
}

void IRVisitor::visit(IRExpESEQ* node)
{
	node->stms->accept(this);
	string stmString = lastNodeName;
	node->exp->accept(this);
	string expString = lastNodeName;
	nextNameWithId("eseq");
	treeRepresentation.AddEdge(lastNodeName, expString, "exp");
	treeRepresentation.AddEdge(lastNodeName, stmString, "stm");
}

void IRVisitor::visit(IRExpList* node)
{
	
	if (node->expslist.size() != 0) {
		node->head->accept(this);
		string headString = lastNodeName;
		if (node->tail != nullptr) {
			node->tail->accept(this);
			string tailString = lastNodeName;
			nextNameWithId("expList");
			treeRepresentation.AddEdge(lastNodeName, headString, "head");
			treeRepresentation.AddEdge(lastNodeName, tailString, "tail");
		}
		else {
			nextNameWithId("expList");
			treeRepresentation.AddEdge(lastNodeName, headString, "head");
		}
	}
	else {
		nextNameWithId("expList");
	}

}

void IRVisitor::visit(CLabel* node)
{
	if (node->Name() == "tempLabel1") {
		int a = 1;
	}
	nextNameWithId(string("label:") + node->Name());
}

void IRVisitor::nextNameWithId(std::string label)
{
	lastNodeName = label + string("__id_") + to_string(minId++);
	treeRepresentation.SetNodeLabel(lastNodeName, label);
}

void IRVisitor::LinkedVisit(IRStm* node)
{
	string fromName = lastNodeName;
	node->accept(this);
	string toName = lastNodeName;
	if (!fromName.empty()) {
		treeRepresentation.AddEdge(fromName, toName, "next");
	}
}

void IRVisitor::LinkedVisit(IRExp* node)
{
	string fromName = lastNodeName;
	node->accept(this);
	string toName = lastNodeName;
	if (!fromName.empty()) {
		treeRepresentation.AddEdge(fromName, toName, "next");
	}
}

