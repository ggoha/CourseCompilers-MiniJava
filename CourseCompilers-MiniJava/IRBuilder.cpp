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
		lastType = "boolean";
		return;
	};

	/*
	IRStmSEQ:
		cjump(exp1,ifFalseLabel, iftrue)
		IRStmSEQ
			label iftrue
			cjump(exp2,ifFalseLabel, ifTrueLabel)
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
		lastType = "boolean";
		return;
	};
	if (n->op == '+')
	{
		n->exp1->accept(this);
		IRExp* left = LastNodeAsIRExp();
		n->exp2->accept(this);
		IRExp* right = LastNodeAsIRExp();
		lastNode = new IRExpBINOP('+', left, right);
		lastType = "int";
		return;
	};
	if (n->op == '*')
	{
		n->exp1->accept(this);
		IRExp* left = LastNodeAsIRExp();
		n->exp2->accept(this);
		IRExp* right = LastNodeAsIRExp();
		lastNode = new IRExpBINOP('*', left, right);
		lastType = "int";
		return;
	};
	if (n->op == '-')
	{
		n->exp1->accept(this);
		IRExp* left = LastNodeAsIRExp();
		n->exp2->accept(this);
		IRExp* right = LastNodeAsIRExp();
		lastNode = new IRExpBINOP('-', left, right);
		lastType = "int";
		return;
	};
}

void CIRBuilder::visit(CStatementWHILE* n)
{
	LabelsSaver oldLabels(this);
	/*
	SEQ
		label startLabel
		CJump
			SEQLIST
				label iftrue
				stm
				Jump -> startLabel
			label iffalse

	*/
	CLabel* startLabel = new CLabel();
	ifTrueLabel = new CLabel();
	breakLabel = ifFalseLabel = new CLabel();
	n->statementWhile->accept(this);
	IRStm* CJump = LastNodeAsIRStm();
	n->exp->accept(this);
	IRStm* stm = LastNodeAsIRStm();
	IRStmLIST* StmLIST2 = new IRStmLIST();
	StmLIST2->add(new IRStmLABEL(ifTrueLabel));
	StmLIST2->add(stm);
	StmLIST2->add(new IRStmLABEL(startLabel));
	IRStmSEQ* StmSEQ = new IRStmSEQ(new IRStmLABEL(startLabel), CJump);
}

void CIRBuilder::visit( CExpInSquareBrackets *n ){
	LabelsSaver( this );
	n->exp1->accept( this );
	string arrType = lastType.substr(0, lastType.length() - 2);
	IRExp* mas = LastNodeAsIRExp();
	n->exp2->accept( this );
	IRExp* id = LastNodeAsIRExp();
	IRExp* offset = new IRExpBINOP( '+', mas, id );
	IRExp* oneExp = new IRExpCONST(1);
	lastNode = new IRExpMEM(new IRExpBINOP('+', offset, oneExp));
	lastType = arrType;
};

void CIRBuilder::visit( CExpPointLENGTH *n ){
	LabelsSaver( this );
	n->exp->accept( this );
	lastNode = new IRExpMEM(LastNodeAsIRExp());
	lastType = "int";
};
	 
void CIRBuilder::visit( CExpPointID *n ){
	LabelsSaver oldLabels(this);
	n->exp->accept(this);
	if (n->expList != 0)
	{
		pair<string,string> method = GetMethodType(n->id, className);
		n->expList->accept(this);
		lastNode = new IRExpCALL(new IRExpNAME(new CLabel(method.first)), dynamic_cast<IRExpList*>(LastNodeAsIRExp()));
		lastType = method.second;
	}
	else
	{
		pair<int, string> field = GetFieldType(n->id, className);
		lastNode = new IRExpMEM(new IRExpBINOP('+', LastNodeAsIRExp(), new IRExpCONST(field.first)));
		lastType = field.second;
	}
};
	 
void CIRBuilder::visit( CExpINTEGER_LITERAL *n ){
	LabelsSaver oldLabels(this);
	lastNode = new IRExpCONST( n->integer_literal );
	lastType = "int";
};
	 
void CIRBuilder::visit( CExpSingleOp *n ){
	LabelsSaver oldLabels(this);
	lastNode = new IRExpCONST( (n->val) ? 1 : 0 );
	lastType = "int";
};

void CIRBuilder::visit( CExpID *n ){
	LabelsSaver oldLabels(this);
	const CTemp* temp = frame->GetTemp(n->id);
	if (temp)
	{
		lastNode = new IRExpTEMP(frame->GetTemp(n->id));
	}
	else
	{
		int offset = GetFieldType(n->id, className).first;

	}
	lastType = GetVarType(n->id);
};

void CIRBuilder::visit( CExpTHIS *n )
{
	LabelsSaver oldLabels(this);
	lastNode = new IRExpTEMP(frame->getThis());
	lastType = className;
};

void CIRBuilder::visit(CVarDecl *n) {
	frame->setLocalsTemp(n->id, new CTemp(n->id));
}

void CIRBuilder::visit(CVarDecls *n)
{
	for (size_t i = 0; i < n->vars.size(); ++i)
	{
		n->vars[i]->accept(this);
	}
}

void CIRBuilder::visit(CFormalList *n)
{
	frame->setFormalsTemp(n->id, new CTemp(n->id));
	n->formalRests->accept(this);
}

void CIRBuilder::visit(CFormalRests *n){
	for (size_t i = 0; i < n->parametrs.size(); ++i)
		n->parametrs[i]->accept(this);
}

void CIRBuilder::visit(CFormalRest *n) {
	frame->setFormalsTemp(n->id, new CTemp(n->id));
}

void CIRBuilder::visit(CExpNEWINT *n) {
	LabelsSaver oldLabels(this);
	n->exp->accept(this);
	lastNode = new IRExpCALL(new IRExpNAME(new CLabel("malloc")), new IRExpList(LastNodeAsIRExp()));

	lastType = "int";
}

void CIRBuilder::visit(CExpNEWID *n) {
	LabelsSaver oldLabels(this);
	lastNode = new IRExpCALL(
							 new IRExpNAME(new CLabel("malloc")), 
							 new IRExpList(new IRExpCONST(SymbolTable->classInfo[SymbolTable->getClassIndex(n->id)].vars.size())));
	lastType = n->id;
}

void CIRBuilder::visit(CStatementPRINTLN* n) {
	LabelsSaver oldLabels(this);
	n->exp->accept(this);
	lastNode = new IRStmEXP(new IRExpCALL(new IRExpNAME(new CLabel("printLn")), new IRExpList(LastNodeAsIRExp())));
}


void CIRBuilder::visit(CStatementSQUEREASIGNMENT* n) {
	LabelsSaver oldLabels(this);
	n->expAssigned->accept(this);
	IRExp* Val = LastNodeAsIRExp();
	n->expInSquareBrackets->accept(this);
	lastNode = new IRStmMOVE(new IRExpMEM(new IRExpBINOP('+',new IRExpTEMP(frame->GetTemp(n->id)), LastNodeAsIRExp())), Val);
}

void CIRBuilder::visit(CStatementASIGNMENT* n) {
	LabelsSaver oldLabels(this);
	n->exp->accept(this);
	lastNode = new IRStmMOVE(new IRExpTEMP(frame->GetTemp(n->id)), LastNodeAsIRExp());
}


void CIRBuilder::visit(CStatementBRACKETS* n) {
	LabelsSaver oldLabels(this);
	n->statements->accept(this);
}


void CIRBuilder::visit(CStatements *n) {
	auto stms = new IRStmLIST();
	for (size_t i = 0; i < n->statements.size(); ++i)
	{
		n->statements[i]->accept(this);
		stms->add(LastNodeAsIRStm());
	}
}


void CIRBuilder::visit(CExpCircleBrackets *n) {
	n->exp->accept(this);
}

pair<string, string> CIRBuilder::GetMethodType(const string& name, const string& _className) const
{
	int classIndex = SymbolTable->getClassIndex(lastType);
	int methodIndex = SymbolTable->classInfo[classIndex].getMethodIndex(name);
	while (methodIndex < 0)
	{
		classIndex = SymbolTable->getClassIndex(SymbolTable->classInfo[classIndex].parent);
		methodIndex = SymbolTable->classInfo[classIndex].getMethodIndex(name);
	}
	return pair<string, string>(lastType+"."+name,SymbolTable->classInfo[classIndex].methods[methodIndex].returnType);
}

pair<int, string> CIRBuilder::GetFieldType(const string& name, const string& _className) const
{
	int classIndex = SymbolTable->getClassIndex(_className);
	int varIndex = SymbolTable->classInfo[classIndex].getVarIndex(name);
	while (varIndex < 0)
	{
		classIndex = SymbolTable->getClassIndex(SymbolTable->classInfo[classIndex].parent);
#ifdef _DEBUG
		if(classIndex < 0)
			throw invalid_argument("error in GetFieldType: can't find field " + name + "in " + lastType);
#endif
		varIndex = SymbolTable->classInfo[classIndex].getVarIndex(name);
	}
	string type = SymbolTable->classInfo[classIndex].vars[varIndex].type;
	int offset = 0;
	while (SymbolTable->classInfo[classIndex].parent != "")
	{
		classIndex = SymbolTable->getClassIndex(SymbolTable->classInfo[classIndex].parent);
		offset += SymbolTable->classInfo[classIndex].vars.size();
	}
	return pair<int, string>(varIndex + offset, type);
}

string CIRBuilder::GetVarType(const string& name)const
{
	int classIndex = SymbolTable->getClassIndex(lastType);
	int methodIndex = SymbolTable->classInfo[classIndex].getMethodIndex(methodName);
	for (auto i = SymbolTable->classInfo[classIndex].methods[methodIndex].params.begin(); i != SymbolTable->classInfo[classIndex].methods[methodIndex].params.end(); ++i)
	{
		if (i->name == name)
		{
			return i->type;
		}
	}
	for (auto i = SymbolTable->classInfo[classIndex].methods[methodIndex].vars.begin(); i != SymbolTable->classInfo[classIndex].methods[methodIndex].vars.end(); ++i)
	{
		if (i->name == name)
		{
			return i->type;
		}
	}
	return GetFieldType(name, className).second;
}

void CIRBuilder::visit( CExpList *n ) {
	LabelsSaver oldLabels( this );
	n->exp->accept( this );
	n->expRests->accept( this );
	lastNode = new IRExpList( lastList );
}
void CIRBuilder::visit( CExpRest *n ) {
	LabelsSaver oldLabels( this );
	n->exp->accept( this );
	lastList.push_back( (IRExp*)lastNode );

}
void CIRBuilder::visit( CExpRests *n ) {
	LabelsSaver oldLabels( this );
	for( size_t i = 0; i < n->expressions.size(); i++ ) {
		n->expressions[i]->accept( this );
	}
}


void CIRBuilder::visit( CExpUnaryMinus *n ) {

	LabelsSaver oldLabels( this );
	IRExpCONST * constNull = new IRExpCONST( 0 );
	n->exp->accept( this );
	lastNode = dynamic_cast<IRNode*>(new IRExpBINOP( '-', (IRExp*)constNull, (IRExp*)lastNode ));
	
}


//not done!!!!!!!!!!!
//initialization of IFrame required!!!
void CIRBuilder::visit(CMethodDecl *n) 
{
	auto root = new IRStmLIST();
	for (size_t i = 0; i < n->statements->statements.size(); ++i)
	{
		n->statements->statements[i]->accept(this);
		root->add(LastNodeAsIRStm());
	}
}


//not done!!!!!!!!!!!
//initialization of IFrame required!!!
void CIRBuilder::visit(CMainClass *n)
{
	auto root = new IRStmLIST();
	for (size_t i = 0; i < n->statements->statements.size(); ++i)
	{
		n->statements->statements[i]->accept(this);
		root->add(LastNodeAsIRStm());
	}

}

void CIRBuilder::visit(CExpExclamationMark *n)
{
	LabelsSaver oldLabels(this);
	n->exp->accept(this);
	lastNode = new IRExpBINOP('^', LastNodeAsIRExp(), new IRExpCONST(1));

}
