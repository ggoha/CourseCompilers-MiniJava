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
	void visit( CExpInSquareBrackets *n ) {
		n->c1->accept( this );
		cout << '[';
		n->c2->accept( this );
		cout << ']';
	}
	void visit( CExpPointLENGTH *n ) {
		n->c1->accept( this );
		cout << '.';
		n->c2->accept( this );
	}
	void visit( CExpPointID *n ) {
		n->c1->accept( this );
		cout << '.';
		n->c2->accept( this );
		cout << '(';
		n->c3->accept( this );
		cout << ')';
	}
	void visit( CExpINTEGER_LITERAL *n ) {
		n->c1->accept( this );
	}
	void visit( CExpSingleOp *n ) {
		n->c1->accept( this );
	}
	void visit( CExpID *n ) {
		n->c1->accept( this );
	}
	void visit( CExpTHIS *n ) {
		n->c1->accept( this );
	}
	void visit( CExpNEWINT *n ) {
		n->c1->accept( this );
		n->c2->accept( this );
		cout << '[';
		n->c3->accept( this );
		cout << ']';
	}
	void visit( CExpNEWID *n ) {
		n->c1->accept( this );
		n->c2->accept( this );
		cout << '(' <<  ')';
	}
	void visit( CExpExclamationMark *n ) {
		cout << '!'
	}
	void visit( CExpCircleBrackets *n ) {
		cout << '(';
		n->c1->accept( this );
		cout << ')';
	}

};


