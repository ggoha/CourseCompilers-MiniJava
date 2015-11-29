#include "IRBuilder.h"
#include "CTypes.h"

IRExp* CIRBuilder::LastNodeAsIRExp() {
	IRExp* res = dynamic_cast<IRExp*>(lastNode);
	if (res == NULL)
		throw invalid_argument("can't cast lastNode to IRExp");
	return res;
}
IRStm* CIRBuilder::LastNodeAsIRStm() {
	IRStm* res = dynamic_cast<IRStm*>(lastNode);
	if (res == NULL)
		throw invalid_argument("can't cast lastNode to IRStm");
	return res;
}

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
	IRStm* stmIf = LastNodeAsIRStm();
	ASTnode->statementElse->accept(this);
	IRStm* stmElse = LastNodeAsIRStm();
	ASTnode->exp->accept(this);
	IRStmCJUMP* cjump = dynamic_cast<IRStmCJUMP*>(lastNode);
	IRStmSEQ* SEQ4 = new IRStmSEQ(new IRStmLABEL(ifFalseLabel), stmElse);
	IRStmSEQ* SEQ3 = new IRStmSEQ(new IRStmLABEL(ifTrueLabel), stmIf);
	IRStmSEQ* SEQ2 = new IRStmSEQ(SEQ3, SEQ4);
	IRStmSEQ* SEQ1 = new IRStmSEQ(cjump, SEQ2);
	lastNode = SEQ1;
	return;
}


void CIRBuilder::visit(CExpBinary* n)
{
	LabelsSaver oldLabels(this);
	int relop;
	if (n->op == '<')
	{
		n->exp1->accept(this);
		IRExp* expLeft = LastNodeAsIRExp();
		n->exp2->accept(this);
		IRExp* expRigth = LastNodeAsIRExp();
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
		IRStmSEQ* stmSEQ = new IRStmSEQ(new IRStmLABEL(ifExp1True),LastNodeAsIRStm());//label goes before exp2
		const CLabel* iftrue = ifTrueLabel;
		ifTrueLabel = ifExp1True;
		n->exp1->accept(this);
		lastNode = new IRStmSEQ(LastNodeAsIRStm(), stmSEQ);///first goes exp1(with falseCIRBuilder::val
		ifTrueLabel = iftrue;
		return;
	};
	if (n->op == '+')
	{
		n->exp1->accept(this);
		IRExp* left = LastNodeAsIRExp();
		n->exp2->accept(this);
		IRExp* right = LastNodeAsIRExp();
		lastNode = new IRExpBINOP('+', left, right);
		return;
	};
	if (n->op == '*')
	{
		n->exp1->accept(this);
		IRExp* left = LastNodeAsIRExp();
		n->exp2->accept(this);
		IRExp* right = LastNodeAsIRExp();
		lastNode = new IRExpBINOP('*', left, right);
		return;
	};
	if (n->op == '-')
	{
		n->exp1->accept(this);
		IRExp* left = LastNodeAsIRExp();
		n->exp2->accept(this);
		IRExp* right = LastNodeAsIRExp();
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
			label labelBack
			CJump
			SEQ3
				label iftrue
				stm
				Jump -> labelBack
		label iffalse

	*/
	startLabel = new CLabel();
	n->statementWhile->accept(this);
	ifTrueLabel = new CLabel();
	breakLabel = ifFalseLabel = new CLabel();
	IRStmSEQ* SEQ3 = new IRStmSEQ(new IRStmLABEL(ifTrueLabel), LastNodeAsIRStm());
	n->exp->accept(this);
	IRStmSEQ* SEQ2 = new IRStmSEQ(LastNodeAsIRStm(), SEQ3);
	IRStmSEQ* SEQ1 = new IRStmSEQ(SEQ3, new IRStmLABEL(ifFalseLabel));
}

void CIRBuilder::visit( CExpInSquareBrackets *n ){
	LabelsSaver( this );
	n->exp1->accept( this );
	//CTemp * mas = frame.getTemp( lastNode );
	IRExp* mas = LastNodeAsIRExp();
	n->exp2->accept( this );
	IRExp* id = LastNodeAsIRExp();
	lastNode = new IRExpBINOP( '+', mas, id );
};
	 

 // ��������
void CIRBuilder::visit( CExpPointLENGTH *n ){
	LabelsSaver( this );
	n->exp->accept( this );
};
	 
void CIRBuilder::visit( CExpPointID *n ){
	n->exp->accept(this);
	if( n->expList != 0 )
		n->expList->accept(this);
};
	 
void CIRBuilder::visit( CExpINTEGER_LITERAL *n ){	
	lastNode = new IRExpTEMP( new CTemp( n->integer_literal ) );
};
	 
void CIRBuilder::visit( CExpSingleOp *n ){
	lastNode = new IRExpTEMP( new CTemp( n->val ) );
};
void CIRBuilder::visit( CExpID *n ){
	lastNode = new IRExpTEMP( new CTemp( n->id ) );
};
void CIRBuilder::visit( CExpTHIS *n ){};
void CIRBuilder::visit( CExpNEWINT *n ){};
void CIRBuilder::visit( CExpNEWID *n ){};
void CIRBuilder::visit( CExpExclamationMark *n ){};
void CIRBuilder::visit( CExpCircleBrackets *n ){};
void CIRBuilder::visit( CProgram *n ){};
void CIRBuilder::visit( CMainClass *n ){};
void CIRBuilder::visit( CClassDecl *n ){};
void CIRBuilder::visit( CClassDecls *n ){};
void CIRBuilder::visit( CClassDeclInheritance *n ){};
void CIRBuilder::visit( CVarDecls *n ){};
void CIRBuilder::visit( CMethodDecls *n ){};
void CIRBuilder::visit( CVarDecl *n ){};
void CIRBuilder::visit( CMethodDecl *n ){};
void CIRBuilder::visit( CStatements *n ){};
void CIRBuilder::visit( CFormalList *n ){};
void CIRBuilder::visit( CFormalRests *n ){};
void CIRBuilder::visit( CFormalRest *n ){};
void CIRBuilder::visit( CExpList *n ){};
void CIRBuilder::visit( CType *n ){};
void CIRBuilder::visit( CExpRest *n ){};
void CIRBuilder::visit( CExpRests *n ){};
void CIRBuilder::visit( CExpUnaryMinus *n ){};

