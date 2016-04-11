#pragma once
class CProgram;
class CMainClass;
class CClassDecl;
class CClassDeclInheritance;
class CVarDecls;
class CMethodDecls;
class CVarDecl;
class CMethodDecl;
class CStatements;
class CFormalList;
class CFormalRests;
class CFormalRest;
class CType;
class CExpList;
class CExpRests;
class CExpRest;

class CStatementIF;
class CStatementBRACKETS;
class CStatementSQUAREASSIGNMENT;
class CStatementASSIGNMENT;
class CStatementPRINTLN;
class CStatementWHILE;

class CExpBinary;
class CExpInSquareBrackets;
class CExpPointLENGTH;
class CExpPointID;
class CExpINTEGER_LITERAL;
class CExpSingleOp;
class CExpID;
class CExpTHIS;
class CExpNEWINT;
class CExpNEWID;
class CExpExclamationMark;
class CExpCircleBrackets;
class CExpUnaryMinus;
class CClassDecls;

class IRExpCALL;
class IRExpList;
class IRExpESEQ;
class IRExpMEM;
class IRExpBINOP;
class IRExpTEMP;
class IRExpNAME;
class IRExpCONST;

class IRStmMOVE;
class IRStmEXP;
class IRStmCJUMP;
class IRStmSEQ;
class IRStmLABEL;
class IRStmLIST;
class IRStmJUMP;

class IVisitor
{
public:
	
	virtual void visit(CStatementIF* n) = 0;
	virtual void visit(CStatementBRACKETS* n) = 0;

	virtual void visit(CStatementSQUAREASSIGNMENT* n) = 0;

	virtual void visit(CStatementASSIGNMENT* n) = 0;

	virtual void visit(CStatementPRINTLN* n) = 0;

	virtual void visit(CStatementWHILE* n) = 0;

	virtual void visit(CExpBinary* n) = 0;

	virtual void visit(CExpInSquareBrackets *n) = 0;

	virtual void visit(CExpPointLENGTH *n) = 0;

	virtual void visit(CExpPointID *n) = 0;

	virtual void visit(CExpINTEGER_LITERAL *n) = 0;

	virtual void visit(CExpSingleOp *n) = 0;
	virtual void visit(CExpID *n) = 0;
	virtual void visit(CExpTHIS *n) = 0;
	virtual void visit(CExpNEWINT *n) = 0;
	virtual void visit(CExpNEWID *n) = 0;
	virtual void visit(CExpExclamationMark *n) = 0;
	virtual void visit(CExpCircleBrackets *n) = 0;
	virtual void visit( CProgram *n ) = 0;
	virtual void visit( CMainClass *n ) = 0;
	virtual void visit( CClassDecl *n ) = 0;
	virtual void visit(CClassDecls *n) = 0;
	virtual void visit( CClassDeclInheritance *n ) = 0;
	virtual void visit( CVarDecls *n ) = 0;
	virtual void visit( CMethodDecls *n ) = 0;
	virtual void visit( CVarDecl *n ) = 0;
	virtual void visit( CMethodDecl *n ) = 0;
	virtual void visit( CStatements *n ) = 0;
	virtual void visit( CFormalList *n ) = 0;
	virtual void visit( CFormalRests *n ) = 0;
	virtual void visit( CFormalRest *n ) = 0;
	virtual void visit( CExpList *n ) = 0;
	virtual void visit( CType *n ) = 0;
	virtual void visit( CExpRest *n ) = 0;
	virtual void visit( CExpRests *n ) = 0;
	virtual void visit( CExpUnaryMinus *n) = 0;
	/*
	virtual void visit(IRExpCALL *n) = 0;
	virtual void visit(IRExpList *n) = 0;
	virtual void visit(IRExpESEQ *n) = 0;
	virtual void visit(IRExpMEM *n) = 0;
	virtual void visit(IRExpBINOP *n) = 0;
	virtual void visit(IRExpTEMP *n) = 0;
	virtual void visit(IRExpNAME *n) = 0;
	virtual void visit(IRExpCONST *n) = 0;

	virtual void visit(IRStmMOVE *n) = 0;
	virtual void visit(IRStmEXP *n) = 0;
	virtual void visit(IRStmCJUMP *n) = 0;
	virtual void visit(IRStmSEQ *n) = 0;
	virtual void visit(IRStmLABEL *n) = 0;
	virtual void visit(IRStmLIST *n) = 0;
	virtual void visit(IRStmJUMP *n) = 0;
	*/
}; 