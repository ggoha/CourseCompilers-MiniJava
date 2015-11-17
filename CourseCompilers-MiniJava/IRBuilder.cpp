#include "IRBuilder.h"
#include "CTypes.h"

void CIRBuilder::visit(CStatementIF* ASTnode)
{
	ASTnode->exp->accept(this);
	IExp* exp = lastNode;



}

