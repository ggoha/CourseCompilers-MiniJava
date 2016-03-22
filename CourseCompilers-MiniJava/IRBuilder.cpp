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

void CIRBuilder::visit(CStatementIF* ASTnode) {
	LabelsSaver oldLabels(this);
	/*
	SEQList
		cjump
		label iftrue
		stmiftrue?
		jump -> end
		label iffalse
		stmelse
		label_end

	*/
	auto stmList = new IRStmLIST();
	ifTrueLabel = new CLabel();
	ifFalseLabel = new CLabel();
	auto end = new CLabel();
	ASTnode->exp->accept(this);
	stmList->add(LastNodeAsIRStm());
	stmList->add(new IRStmLABEL(ifTrueLabel));
	if (((CStatements*)ASTnode->statementIf)->statements.size() != 0)
	{
		ASTnode->statementIf->accept(this);
		stmList->add(LastNodeAsIRStm());
	}
	stmList->add(new IRStmJUMP(end));
	stmList->add(new IRStmLABEL(ifFalseLabel));
	if (((CStatements*)ASTnode->statementElse)->statements.size() != 0)
	{
		ASTnode->statementElse->accept(this);
		stmList->add(LastNodeAsIRStm());
	}
	stmList->add(new IRStmLABEL(end));
	return;
}

void CIRBuilder::visit(CExpBinary* n) {
	LabelsSaver oldLabels(this);
	int relop;
	if (n == nullptr)
	{
		std::cout << "in wisit CExBinary is null";
		return;
	}
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

void CIRBuilder::visit(CStatementWHILE* n) {
	if (n == nullptr)
	{
		std::cout << "in wisit CStatementWHILE is null";
		return;
	}
	LabelsSaver oldLabels(this);
	/*
		label startLabel
		CJump
		label iftrue
		stm
		Jump -> startLabel
		label iffalse

	*/
	IRStmLIST* stmList = new IRStmLIST();
	CLabel* startLabel = new CLabel();
	ifTrueLabel = new CLabel();
	breakLabel = ifFalseLabel = new CLabel();
	stmList->add(new IRStmLABEL(startLabel));

	//exp
	n->exp->accept(this);
	stmList->add(LastNodeAsIRStm());

	stmList->add(new IRStmLABEL(ifTrueLabel));
	if (((CStatements*)(n->statementWhile))->statements.size() != 0)
	{
		n->statementWhile->accept(this);
		stmList->add(LastNodeAsIRStm());
	}
	stmList->add(new IRStmJUMP(startLabel));
	stmList->add(new IRStmLABEL(ifFalseLabel));
	lastNode = stmList;
}

void CIRBuilder::visit( CExpInSquareBrackets *n ){
	if (n == nullptr)
	{
		std::cout << "in wisit CExpInSquareBrackets is null";
		return;
	}
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

void CIRBuilder::visit( CExpPointLENGTH *n ) {
	if (n == nullptr)
	{
		std::cout << "in wisit CExpPointLENGTH is null";
		return;
	}
	LabelsSaver( this );
	n->exp->accept( this );
	lastNode = new IRExpMEM(LastNodeAsIRExp());
	lastType = "int";
};

void CIRBuilder::visit( CExpPointID *n ) {
	if (n == nullptr)
	{
		std::cout << "in wisit CExpPointID is null";
		return;
	}
	n->exp->accept(this);
	auto oldList = lastList;
	lastList.clear();
	lastList.push_back(LastNodeAsIRExp());
	pair<string,string> method = GetMethodType(n->id, lastType);
	n->expList->accept(this);
	lastNode = new IRExpCALL(new IRExpNAME(new CLabel(method.first)), dynamic_cast<IRExpList*>(LastNodeAsIRExp()));
	lastType = method.second;
	lastList = oldList;
};
	 
void CIRBuilder::visit( CExpINTEGER_LITERAL *n ){
	if (n == nullptr)
	{
		std::cout << "in wisit CExpINTEGER_LITERAL is null";
		return;
	}
	LabelsSaver oldLabels(this);
	lastNode = new IRExpCONST( n->integer_literal );
	lastType = "int";
};
	 
void CIRBuilder::visit( CExpSingleOp *n ){
	if (n == nullptr)
	{
		std::cout << "in wisit CExpSingleOp is null";
		return;
	}
	LabelsSaver oldLabels(this);
	lastNode = new IRExpCONST( (n->val) ? 1 : 0 );
	lastType = "int";
};

void CIRBuilder::visit( CExpID *n ) {
	if (n == nullptr)
	{
		std::cout << "in wisit CExpID is null";
		return;
	}
	LabelsSaver oldLabels(this);
	const CTemp* temp = frame->GetTemp(n->id);
	if (temp)
	{
		lastNode = new IRExpTEMP(frame->GetTemp(n->id));
	}
	else
	{
		int offset = GetFieldType(n->id, className).first;
		lastNode = new IRExpMEM(new IRExpBINOP('+', new IRExpTEMP(frame->GetThisPtr()), new IRExpCONST(offset)));
	}
	lastType = GetVarType(n->id);
};

void CIRBuilder::visit( CExpTHIS *n ) {
	if (n == nullptr)
	{
		std::cout << "in wisit CExpTHIS is null";
		return;
	}
	LabelsSaver oldLabels(this);
	lastNode = new IRExpTEMP(frame->getThis());
	lastType = className;
};

void CIRBuilder::visit(CVarDecl *n) {
	if (n == nullptr)
	{
		std::cout << "in wisit CVarDecl is null";
		return;
	}
	frame->setLocalsTemp(n->id, new CTemp(n->id));
}

void CIRBuilder::visit(CVarDecls *n) {
	if (n == nullptr)
	{
		std::cout << "in wisit CVarDecls is null";
		return;
	}
	for (size_t i = 0; i < n->vars.size(); ++i)
	{
		n->vars[i]->accept(this);
	}
}

void CIRBuilder::visit(CFormalList *n) {
	if (n == nullptr)
	{
		std::cout << "in wisit CFormalList is null";
		return;
	}
	frame->setFormalsTemp(n->id, new CTemp(n->id));
	if (n->formalRests != nullptr)
	{
		n->formalRests->accept(this);
	}
}

void CIRBuilder::visit(CFormalRests *n) {
	if (n == nullptr)
	{
		std::cout << "in wisit CFormalRests is null";
		return;
	}
	for (size_t i = 0; i < n->parametrs.size(); ++i)
		n->parametrs[i]->accept(this);
}

void CIRBuilder::visit(CFormalRest *n) {
	if (n == nullptr)
	{
		std::cout << "in wisit CFormalRest is null";
		return;
	}
	frame->setFormalsTemp(n->id, new CTemp(n->id));
}

void CIRBuilder::visit(CExpNEWINT *n) {
	if (n == nullptr)
	{
		std::cout << "in wisit CExpNEWINT is null";
		return;
	}
	LabelsSaver oldLabels(this);
	n->exp->accept(this);
	lastNode = new IRExpCALL(new IRExpNAME(new CLabel("malloc")), new IRExpList(LastNodeAsIRExp()));

	lastType = "int";
}

void CIRBuilder::visit(CExpNEWID *n) {
	if (n == nullptr)
	{
		std::cout << "in wisit CExpNEWID is null";
		return;
	}
	LabelsSaver oldLabels(this);
	lastNode = new IRExpCALL(
							 new IRExpNAME(new CLabel("malloc")), 
							 new IRExpList(new IRExpCONST(SymbolTable->classInfo[SymbolTable->getClassIndex(n->id)].vars.size())));
	lastType = n->id;
}

void CIRBuilder::visit(CStatementPRINTLN* n) {
	if (n == nullptr)
	{
		std::cout << "in wisit CStatementPRINTLN is null";
		return;
	}
	LabelsSaver oldLabels(this);
	n->exp->accept(this);
	lastNode = new IRStmEXP(new IRExpCALL(new IRExpNAME(new CLabel("printLn")), new IRExpList(LastNodeAsIRExp())));
}


void CIRBuilder::visit(CStatementSQUEREASIGNMENT* n) {
	if (n == nullptr)
	{
		std::cout << "in wisit CStatementSQUEREASIGNMENT is null";
		return;
	}
	LabelsSaver oldLabels(this);
	n->expAssigned->accept(this);
	IRExp* Val = LastNodeAsIRExp();
	n->expInSquareBrackets->accept(this);
	lastNode = new IRStmMOVE(new IRExpMEM(new IRExpBINOP('+',new IRExpTEMP(frame->GetTemp(n->id)), LastNodeAsIRExp())), Val);
}

void CIRBuilder::visit(CStatementASIGNMENT* n) {
	if (n == nullptr)
	{
		std::cout << "in wisit CStatementASIGNMENT is null";
		return;
	}
	LabelsSaver oldLabels(this);
	n->exp->accept(this);
	lastNode = new IRStmMOVE(new IRExpTEMP(frame->GetTemp(n->id)), LastNodeAsIRExp());
}


void CIRBuilder::visit(CStatementBRACKETS* n) {
	if (n == nullptr)
	{
		std::cout << "in wisit CStatementBRACKETS is null";
		return;
	}
	LabelsSaver oldLabels(this);
	n->statements->accept(this);
}


void CIRBuilder::visit(CStatements *n) {
	if (n == nullptr)
	{
		std::cout << "in wisit CStatementBRACKETS is null";
		return;
	}
	auto stms = new IRStmLIST();
	for (size_t i = 0; i < n->statements.size(); ++i)
	{
		n->statements[i]->accept(this);
		stms->add(LastNodeAsIRStm());
	}
}


void CIRBuilder::visit(CExpCircleBrackets *n) {
	if (n == nullptr)
	{
		std::cout << "in wisit CExpCircleBrackets is null";
		return;
	}
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
	int classIndex = SymbolTable->getClassIndex(className);
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
	if (n->exp == nullptr)
	{
		lastNode = new IRExpList(lastList);
		return;
	}
	else
	{
		n->exp->accept(this);
		lastList.push_back(LastNodeAsIRExp());
		if (n->expRests != nullptr)
		{
			n->expRests->accept(this);
		}
		lastNode = new IRExpList(lastList);
	}
}
void CIRBuilder::visit( CExpRest *n ) {
	if (n == nullptr)
	{
		std::cout << "in wisit CExpList is null";
		return;
	}
	n->exp->accept( this );
	lastList.push_back( LastNodeAsIRExp() );
}
void CIRBuilder::visit( CExpRests *n ) {
	if (n == nullptr)
	{
		std::cout << "in wisit CExpRests is null";
		return;
	}
	LabelsSaver oldLabels( this );
	for( size_t i = 0; i < n->expressions.size(); i++ ) {
		n->expressions[i]->accept( this );
	}
}


void CIRBuilder::visit( CExpUnaryMinus *n ) {
	if (n == nullptr)
	{
		std::cout << "in wisit CExpUnaryMinus is null";
		return;
	}
	LabelsSaver oldLabels( this );
	IRExpCONST * constNull = new IRExpCONST( 0 );
	n->exp->accept( this );
	lastNode = dynamic_cast<IRNode*>(new IRExpBINOP( '-', (IRExp*)constNull, (IRExp*)lastNode ));
	
}

void CIRBuilder::visit(CMainClass *n) {
	if (n == nullptr)
	{
		std::cout << "in wisit CMainClass is null";
		return;
	}
	frame = new IRFrame(className + "_" + methodName, 1);
	frame->setFormalsTemp(string(n->idParams), new CTemp(n->idParams));
	root = new IRStmLIST();
	for (size_t i = 0; i < n->statements->statements.size(); ++i)
	{
		n->statements->statements[i]->accept(this);
		root->add(LastNodeAsIRStm());
	}

}

void CIRBuilder::visit(CMethodDecl *n) {
	if (n == nullptr)
	{
		std::cout << "in wisit CMethodDecl is null";
		return;
	}
	if (n->formalList != nullptr){
		if (n->formalList->formalRests == nullptr)
		{
			frame = new IRFrame(className + "_" + methodName, 1 + n->formalList->formalRests->parametrs.size());
		}
		frame = new IRFrame(className + "_" + methodName, 1);
		n->formalList->accept(this);
	}
	else
	{
		frame = new IRFrame(className + "_" + methodName, 0);
	}
	if (n->varDecls != nullptr){
		n->varDecls->accept(this);
	}
	root = new IRStmLIST();
	if (n->statements != nullptr){
		for (size_t i = 0; i < n->statements->statements.size(); ++i)
		{
			n->statements->statements[i]->accept(this);
			root->add(LastNodeAsIRStm());
		}
	}
	if (n->exp != nullptr){
		n->exp->accept(this);
		root->add(new IRStmMOVE(new IRExpTEMP(frame->GetReturnPtr()), LastNodeAsIRExp()));
	}

}

void CIRBuilder::visit(CExpExclamationMark *n) {
	if (n == nullptr)
	{
		std::cout << "in wisit CExpExclamationMark is null";
		return;
	}
	LabelsSaver oldLabels(this);
	n->exp->accept(this);
	lastNode = new IRExpBINOP('^', LastNodeAsIRExp(), new IRExpCONST(1));

}
