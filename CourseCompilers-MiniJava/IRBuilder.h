#pragma once
#include "Visitor.h"
#include "IRStm.h"

class CIRBuilder : public IVisitor
{
	IRNode* lastNode;
public:
	CIRBuilder() {};
	virtual void visit(CStatementIF* n);
	virtual void visit(CStatementBRACKETS* n);

	virtual void visit(CStatementSQUEREASIGNMENT* n);

	virtual void visit(CStatementASIGNMENT* n);

	virtual void visit(CStatementPRINTLN* n);

	virtual void visit(CStatementWHILE* n);

	virtual void visit(CExpBinary* n);

	virtual void visit(CExpInSquareBrackets *n);

	virtual void visit(CExpPointLENGTH *n);

	virtual void visit(CExpPointID *n);

	virtual void visit(CExpINTEGER_LITERAL *n);

	virtual void visit(CExpSingleOp *n);
	virtual void visit(CExpID *n);
	virtual void visit(CExpTHIS *n);
	virtual void visit(CExpNEWINT *n);
	virtual void visit(CExpNEWID *n);
	virtual void visit(CExpExclamationMark *n);
	virtual void visit(CExpCircleBrackets *n);
	virtual void visit(CProgram *n);
	virtual void visit(CMainClass *n);
	virtual void visit(CClassDecl *n);
	virtual void visit(CClassDecls *n);
	virtual void visit(CClassDeclInheritance *n);
	virtual void visit(CVarDecls *n);
	virtual void visit(CMethodDecls *n);
	virtual void visit(CVarDecl *n);
	virtual void visit(CMethodDecl *n);
	virtual void visit(CStatements *n);
	virtual void visit(CFormalList *n);
	virtual void visit(CFormalRests *n);
	virtual void visit(CFormalRest *n);
	virtual void visit(CExpList *n);
	virtual void visit(CType *n);
	virtual void visit(CExpRest *n);
	virtual void visit(CExpRests *n);
	virtual void visit(CExpUnaryMinus *n);

};

