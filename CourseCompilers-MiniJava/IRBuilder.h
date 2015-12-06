#pragma once
#include "vector"
#include "Visitor.h"
#include "IRStm.h"
#include "IRExp.h"
#include "CSymbolTable.h"
#include "IRFrame.h"
class CIRBuilder : public IVisitor
{
	string lastType;
	IRNode* lastNode;
	const CLabel* ifFalseLabel;
	const CLabel* ifTrueLabel;
	const CLabel* breakLabel;
	IRFrame* frame;
	//keeper current labels , create it in every visit in the first string
	class LabelsSaver;
	//save cast lastNode
	IRExp* LastNodeAsIRExp();
	IRStm* LastNodeAsIRStm();
	IRFrame* currentFrame;
	CTable* SymbolTable;//глобальная таблица символов
	string className;//имя  класса метода который описывается билдером
	string methodName;//имя метода который описывается билдером
	pair<string, string> GetMethodType(const string&) const;
	pair<int, string> GetFieldType(const string&)const;
	string GetVarType(const string&)const;
	std::vector<CExp*> lastList;
public:
	CIRBuilder() {};
	virtual void visit(CStatementIF* n);//done
	virtual void visit(CStatementBRACKETS* n);//done

	virtual void visit(CStatementSQUEREASIGNMENT* n);//done

	virtual void visit(CStatementASIGNMENT* n);//done

	virtual void visit(CStatementPRINTLN* n);//done

	virtual void visit(CStatementWHILE* n);//done

	virtual void visit(CExpBinary* n);//done

	virtual void visit(CExpInSquareBrackets *n);//done

	virtual void visit(CExpPointLENGTH *n);//done

	virtual void visit(CExpPointID *n);//done

	virtual void visit(CExpINTEGER_LITERAL *n);//done

	virtual void visit(CExpSingleOp *n);//done
	virtual void visit(CExpID *n);//done
	virtual void visit(CExpTHIS *n);//done
	virtual void visit(CExpNEWINT *n);//done
	virtual void visit(CExpNEWID *n);//done
	virtual void visit(CExpExclamationMark *n);
	virtual void visit(CExpCircleBrackets *n);//done
	virtual void visit(CProgram *n) {};
	virtual void visit(CMainClass *n) {};
	virtual void visit(CClassDecl *n) {};
	virtual void visit(CClassDecls *n) {};
	virtual void visit(CClassDeclInheritance *n) {};
	virtual void visit(CVarDecls *n);//done
	virtual void visit(CMethodDecls *n);
	virtual void visit(CVarDecl *n);//done
	virtual void visit(CMethodDecl *n) {};
	virtual void visit(CStatements *n);//done
	virtual void visit(CFormalList *n);//done
	virtual void visit(CFormalRests *n);//done
	virtual void visit(CFormalRest *n);//done
	virtual void visit(CExpList *n);
	virtual void visit(CType *n) {};
	virtual void visit(CExpRest *n);
	virtual void visit(CExpRests *n);
	virtual void visit(CExpUnaryMinus *n);
};

class CIRBuilder::LabelsSaver
{
	const CLabel* ifFalseLabel;
	const CLabel* ifTrueLabel;
	const CLabel* breakLabel;
	CIRBuilder* irBuilder;
public:
	LabelsSaver(CIRBuilder* _irBuilder) : irBuilder(_irBuilder) {
		ifFalseLabel = irBuilder->ifFalseLabel;
		ifTrueLabel = irBuilder->ifTrueLabel;
		breakLabel = irBuilder->breakLabel;
	};
	~LabelsSaver() {
		irBuilder->ifFalseLabel = ifFalseLabel;
		irBuilder->ifTrueLabel = ifTrueLabel;
		irBuilder->breakLabel = breakLabel;
	}
};