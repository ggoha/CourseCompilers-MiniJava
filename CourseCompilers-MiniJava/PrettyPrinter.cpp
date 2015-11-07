#pragma once

#include <iostream>
#include "Visitor.h"
#include "CTypes.h"

using namespace std;

class CPrettyPrinter : public IVisitor
{
public:
	void visit( CProgram *n ) {
		n->mainClass->accept( this );
		cout << " ";
		n->classDecls->accept( this );
	}
	
	void visit( CClassDecls *n ) {
		for( int i = 0; i < n->a.size(); i++ ) {
			n->a[i]->accept( this );
			cout << " ";
		}
	
	}
	void visit( CMainClass *n ) {
		cout << "class" << " " << n->id << " " << "{" << "public static void main ( string[] ";
		cout << n->id << " ";
		cout << ")" << " " << "{" << " ";
		n->statement->accept( this );
		cout << "}" << " " << "}";
	}
	
	void visit( CClassDecl * n ) {
		cout << "class" << " " << n->id << " ";
		cout << " { ";
		n->varDecls->accept( this );
		cout << " ";
		n->methodDecls->accept( this );
		cout << " } ";
	}

	void visit( CClassDeclInheritance *n ) {
		cout << "class " << n->id1 << " extends " << n->id2 << " ";
		cout << " { ";
		n->varDecls->accept( this );
		cout << " ";
		n->methodDecls->accept( this );
		cout << " } ";
	}


	void visit( CVarDecls *n ) {
		for( int i = 0; i < n->a.size(); i++ ) {
			n->a[i]->accept( this );
			cout << " ";
		}
	}

	

	void visit( CMethodDecls *n ) {
		for( int i = 0; i < n->a.size(); i++ ) {
			n->a[i]->accept( this );
			cout << " ";
		}
	}
	
	void visit( CVarDecl *n ) {
		cout << " ";
		n->type->accept(this);
		cout << " " << n->id << " ";
	}
	void visit( CMethodDecl *n ) {
		cout << " ";
		n->type->accept( this );
		cout << " " << n->id << " ( " << " { ";
		n->varDecls->accept( this );
		cout << " ";
		n->statements->accept( this );
		cout << " return ";
		n->exp->accept( this );
	}
	void visit( CStatements *n ) {
		for( int i = 0; i < n->a.size(); i++ ) {
			n->a[i]->accept( this );
			cout << " ";
		}
	}

	void visit(CStatementIF* n)
	{
		cout << "if ( ";
		n->exp1->accept(this);
		cout << ") ";
		n->statement1->accept(this);
		cout << " else ";
		n->statement2->accept(this);
	};

	void visit(CStatementBRACKETS* n)
	{
		cout << "{ ";
		n->statement->accept(this);
		cout << " }";
	};

	void visit(CStatementSQUEREASIGNMENT* n)
	{
		cout << id;
		cout << "[ ";
		n->exp1->accept(this);
		cout << " ] = ";
		n->exp2->accept(this);
		cout << ";";
	};

	void visit(CStatementASIGNMENT* n)
	{
		cout << id;
		cout << " = ";
		n->exp->accept(this);
		cout << ";";
	};

	void visit(CStatementPRINTLN* n)
	{
		cout << "( ";
		n->exp->accept(this);
		cout << ")";
	};

	void visit(CStatementWHILE* n)
	{
		cout << " ";
		cout << "while ( ";
		n->exp->accept(this);
		cout << ") ";
		n->statement->accept(this);
		cout << " ";
	};

	void visit(CExpBinary* n)
	{
		n->exp1->accept(this);
		cout << n->c;
		n->exp2->accept(this);
	}
	void visit(CExpInSquareBrackets *n) {
		n->exp1->accept(this);
		cout << '[';
		n->exp2->accept(this);
		cout << ']';
	}
	void visit(CExpPointLENGTH *n) {
		n->exp1->accept(this);
		cout << '.';
		cout << "length()"
	}
	void visit(CExpPointID *n) {
		n->exp1->accept(this);
		cout << '.';
		n->id;
		cout << '(';
		n->exp2->accept(this);
		cout << ')';
	}
	void visit(CExpINTEGER_LITERAL *n) {
		cout << n->integer_literal;
	}
	void visit(CExpSingleOp *n) {
		cout n->val;
	}
	void visit(CExpID *n) {
		cout <<  n->exp;
	}
	void visit(CExpTHIS *n) {
		cout << "this" ;
	}
	void visit(CExpNEWINT *n) {
		cout << "new int"
		cout << '[';
		n->exp->accept(this);
		cout << ']';
	}
	void visit(CExpNEWID *n) {
		cout n->id;
		cout << '(' << ')';
	}
	void visit(CExpExclamationMark *n) {
		cout << '!';
		n->exp->accept( this );
	}
	void visit( CExpCircleBrackets *n ) {
		cout << '(';
		n->exp->accept(this);
		cout << ')';
	}
	
	
	void visit( CFormalList *n ) {
		cout << " ";
		n->type->accept( this );
		cout << " " -> n->id << " " ;
		n->formalRests->accept( this );
		cout << " ";
		
	}
	void visit( CFormalRest *n ) {
		cout << " ,";
		n->type->accept( this );
		cout << n->id << " ";
	}
	void visit( CFormalRests *n ) {
		for( int i = 0; i < n->a.size(); i++ ) {
			n->a[i]->accept( this );
			cout << " ";
		}
	}
	void visit( CType *n ) {
		if( inputType == CType:: _mas ) {
			cout << "int [] ";
		}
		if( inputType == CType::_bool ) {
			cout << " bool ";
		}
		if( inputType == CType::_int ) {
			cout << " int ";
		}
		if( inputType == CType::_id ) {
			cout << n->id;
		}
	}
	void visit( CExpList *n ) {
		cout << " ";
		n->exp->accept( this );
		cout << " ";
		n->expRests->accept( this );
	}
	void visit( CExpRests *n ) {
		for( int i = 0; i < n->a.size(); i++ ) {
			n->a[i]->accept( this );
			cout << " ";
		}
	}
	void visit( CExpRest *n ) {
		cout << " ,";
		n->exp->accept( this );
		cout << " ";

	}
	void visit( CExpUnaryMinus *n ) {
		cout << " - ";
		n->exp->accept( this );
		cout << " ";
	}

};


