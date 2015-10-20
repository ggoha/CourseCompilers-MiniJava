#pragma once

#include <iostream>
#include "Visitor.h"

using namespace std;

class CPrettyPrinter : public IVisitor
{
public:
	void visit(CStatementIF* n);

	void visit(CStatementBRACKETS* n);

	void visit(CStatementSQUEREASIGNMENT* n);

	void visit(CStatementASIGNMENT* n);

	void visit(CStatementPRINTLN* n);

	void visit(CStatementWHILE* n);

	template< class T>
	void visit(TStar<T>* n);
	void visit(CExpBinary* n);
	void visit(CExpInSquareBrackets *n);
	void visit(CExpPointLENGTH *n);
	void visit(CExpPointID *n);
	void visit(CExpINTEGER_LITERAL *n);
	void visit(CExpSingleOp *n);
	void visit(CExpID *n);
	void visit(CExpTHIS *n);
	void visit(CExpNEWINT *n);
	void visit(CExpNEWID *n);
	void visit(CExpExclamationMark *n);
	void visit(CExpCircleBrackets *n);
	void visit(CExpBool *n);
};


