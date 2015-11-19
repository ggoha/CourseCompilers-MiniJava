#include "IRBuilder.h"
#include "CTypes.h"

void CIRBuilder::visit(CStatementIF* ASTnode)
{
	LabelsSaver oldLabels(this);
	/*
	SEQ1
		cjump
		SEQ2
			SEQ3
				label iftrue
				stmif
			SEQ4
				label iffalse
				stmelse

	*/
	ifTrueLabel  = new CLabel();
	ifFalseLabel = new CLabel();
	ASTnode->statementIf->accept(this);
	IRStm* stmIf = (IRStm*)lastNode;
	ASTnode->statementElse->accept(this);
	IRStm* stmElse = (IRStm*)lastNode;
	ASTnode->exp->accept(this);
	IRStmCJUMP* cjump = (IRStmCJUMP*)lastNode;
	IRStmSEQ* SEQ4 = new IRStmSEQ(new IRStmLABEL(ifFalseLabel), stmElse);
	IRStmSEQ* SEQ3 = new IRStmSEQ(new IRStmLABEL(ifTrueLabel), stmIf);
	IRStmSEQ* SEQ2 = new IRStmSEQ(SEQ3, SEQ4);
	IRStmSEQ* SEQ2 = new IRStmSEQ(cjump, SEQ2);
}


void CIRBuilder::visit(CExpBinary* n)
{
	LabelsSaver oldLabels(this);
	int relop;
	if (n->op == '<')
	{
		n->exp1->accept(this);
		IRExp* expLeft = (IRExp*)lastNode;
		n->exp2->accept(this);
		IRExp* expRigth = (IRExp*)lastNode;
		relop = IRStmCJUMP::LE;
		lastNode = new IRStmCJUMP(relop, expLeft, expRigth, ifTrueLabel, ifFalseLabel);
		return;
	};

	/*
	IRStmSEQ:
		cjump(exp1,ifFalseLabel, iftrue)
		IRStmSEQ
			label iftrue
			cjump(exp1,ifFalseLabel, ifTrueLabel)
	*/
	if (n->op == '&')
	{
		const CLabel* ifExp1True = new CLabel();//this label is iftrue for exp1
		n->exp2->accept(this);
		IRStmSEQ* stmSEQ = new IRStmSEQ(new IRStmLABEL(ifExp1True),(IRStm*)lastNode);//label goes before exp2
		const CLabel* iftrue = ifTrueLabel;
		ifTrueLabel = ifExp1True;
		n->exp1->accept(this);
		lastNode = new IRStmSEQ((IRStm*)lastNode, stmSEQ);///first goes exp1(with false val
		ifTrueLabel = iftrue;
		return;
	};
	if (n->op == '+')
	{
		n->exp1->accept(this);
		IRExp* left = (IRExp*)lastNode;
		n->exp2->accept(this);
		IRExp* right = (IRExp*)lastNode;
		lastNode = new IRExpBINOP('+', left, right);
		return;
	};
	if (n->op == '*')
	{
		n->exp1->accept(this);
		IRExp* left = (IRExp*)lastNode;
		n->exp2->accept(this);
		IRExp* right = (IRExp*)lastNode;
		lastNode = new IRExpBINOP('*', left, right);
		return;
	};
	if (n->op == '-')
	{
		n->exp1->accept(this);
		IRExp* left = (IRExp*)lastNode;
		n->exp2->accept(this);
		IRExp* right = (IRExp*)lastNode;
		lastNode = new IRExpBINOP('-', left, right);
		return;
	};
}

void CIRBuilder::visit(CStatementWHILE* n)
{
	LabelsSaver oldLabels(this);
	/*
	SEQ1
		SEQ2
			CJump
			SEQ3
				label iftrue
				stm
		label iffalse

	*/
	n->statementWhile->accept(this);
	ifTrueLabel = new CLabel();
	breakLabel = ifFalseLabel = new CLabel();
	IRStmSEQ* SEQ3 = new IRStmSEQ(new IRStmLABEL(ifTrueLabel), (IRStm*)lastNode);
	n->exp->accept(this);
	IRStmSEQ* SEQ2 = new IRStmSEQ((IRStm*)lastNode, SEQ3);
	IRStmSEQ* SEQ2 = new IRStmSEQ(SEQ3, new IRStmLABEL(ifFalseLabel));
}

