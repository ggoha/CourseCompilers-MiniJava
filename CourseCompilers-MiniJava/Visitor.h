#pragma once
#include "CTypes.h"


class visitor
{
public:
	void visit(CStatementIF* n)
	{
		cout << "if ( ";
		n->c1->accept(this);
		cout << ") ";
		n->c2->accept(this);
		cout << " else ";
		n->c3->accept(this);
	};

	void visit(CStatementBRACKETS* n)
	{
		cout << "{ ";
		n->c1->accept(this);
		cout << " }";
	};

	void visit(CStatementSQUEREASIGNMENT* n)
	{
		n->c1->accept(this);
		cout << "[ ";
		n->c2->accept(this);
		cout << " ] = ";
		n->c3->accept(this);
		cout << ";";
	};

	void visit(CStatementASIGNMENT* n)
	{
		n->c1->accept(this);
		cout << " = ";
		n->c2->accept(this);
		cout << ";";
	};

	void visit(CStatementPRINTLN* n)
	{
		cout << "( ";
		n->c1->accept(this);
		cout << ")";
	};

	void visit(CStatementWHILE* n)
	{
		cout << "while ( ";
		n->c1->accept(this);
		cout << "0 ";
		n->c2->accept(this);
	};


	template< class T>
	void visit(TStar<T>* n)
	{
		cout << " ";
		for (auto i in n->v)
		{
			i->accept(this);
			cout << " ";
		};
	}
	void visit(CExpBinary* n)
	{
		n->c1->accept(this);
		cout << n->c;
		n->c2->accept(this);
	}

};