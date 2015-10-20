#pragma once

class CStatementIF;
class CStatementBRACKETS;
class CStatementSQUEREASIGNMENT;
class CStatementASIGNMENT;
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
class CExpBool;

class IVisitor
{
public:
	virtual void visit(CStatementIF* n) = 0;
	virtual void visit(CStatementBRACKETS* n) = 0;

	virtual void visit(CStatementSQUEREASIGNMENT* n) = 0;

	virtual void visit(CStatementASIGNMENT* n) = 0;

	virtual void visit(CStatementPRINTLN* n) = 0;

	virtual void visit(CStatementWHILE* n) = 0;

	virtual void visit(TStar<T>* n) = 0;

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
	virtual void visit(CExpBool *n) = 0;


};