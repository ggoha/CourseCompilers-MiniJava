#pragma once

#include <iostream>
#include "Visitor.h"
#include "CTypes.h"
#include "PrettyPrinter.h"

using namespace std;

ostream& operator<<( ostream& o, const string& s ) {
	o << s.c_str();
	return o;
}


	void CPrettyPrinter::visit( CProgram *n ) {
		n->mainClass->accept( this );
		cout << " ";
		n->classDecls->accept( this );
	};
	
	void CPrettyPrinter::visit( CClassDecls *n ) {
		for( int i = 0; i < n->a.size(); i++ ) {
			n->a[i]->accept( this );
			cout << " ";
		}
	
	}
	void CPrettyPrinter::visit( CMainClass *n ) {
		cout << "class" << " " << n->id1 << " " << "{\n" << "public static void main ( String[] ";
		cout << n->id2 << " ";
		cout << ")" << " " << "{\n" << " ";
		n->statements->accept( this );
		cout << "\n}" << " " << "\n}";
	}
	
	void CPrettyPrinter::visit( CClassDecl * n ) {
		cout << "public class" << " " << n->id << " ";
		cout << " { ";
		n->varDecls->accept( this );
		cout << " ";
		n->methodDecls->accept( this );
		cout << " } ";
	}

	void CPrettyPrinter::visit( CClassDeclInheritance *n ) {
		cout << "class " << n->id1 << " extends " << n->id2 << " ";
		cout << " { ";
		n->varDecls->accept( this );
		cout << " ";
		n->methodDecls->accept( this );
		cout << " } ";
	}


	void CPrettyPrinter::visit( CVarDecls *n ) {
		for( int i = 0; i < n->a.size(); i++ ) {
			n->a[i]->accept( this );
			cout << " ";
		}
	}

	

	void CPrettyPrinter::visit( CMethodDecls *n ) {
		for( int i = 0; i < n->a.size(); i++ ) {
			n->a[i]->accept( this );
			cout << " ";
		}
	}
	
	void CPrettyPrinter::visit( CVarDecl *n ) {
		cout << " ";
		n->type->accept(this);
		cout << " " << n->id << "; ";
	}
	void CPrettyPrinter::visit( CMethodDecl *n ) {
		cout << " ";
		n->type->accept( this );
		cout << " ";
		cout << n->id;
		cout << " (";
		n->formalList->accept(this);
		cout<< " )  { ";
		n->varDecls->accept( this );
		cout << " ";
		n->statements->accept( this );
		cout << "; return ";
		n->exp->accept( this );
		cout << ';';
	}
	void CPrettyPrinter::visit( CStatements *n ) {
		for( int i = 0; i < n->a.size(); i++ ) {
			n->a[i]->accept( this );
			cout << " ";
		}
	}

	void CPrettyPrinter::visit(CStatementIF* n)
	{
		cout << "if ( ";
		n->exp->accept(this);
		cout << ") ";
		n->statement1->accept(this);
		cout << " else ";
		n->statement2->accept(this);
	};

	void CPrettyPrinter::visit(CStatementBRACKETS* n)
	{
		cout << "{ ";
		n->statements->accept(this);
		cout << " }";
	};

	void CPrettyPrinter::visit(CStatementSQUEREASIGNMENT* n)
	{
		cout << n->id;
		cout << "[ ";
		n->exp1->accept(this);
		cout << " ] = ";
		n->exp2->accept(this);
		cout << ";\n";
	};

	void CPrettyPrinter::visit(CStatementASIGNMENT* n)
	{
		cout << n->id;
		cout << " = ";
		n->exp->accept(this);
		cout << ";\n";
	};

	void CPrettyPrinter::visit(CStatementPRINTLN* n)
	{
		cout << "System.out.println( ";
		n->exp->accept(this);
		cout << ");";
	};

	void CPrettyPrinter::visit(CStatementWHILE* n)
	{
		cout << " ";
		cout << "while ( ";
		n->exp->accept(this);
		cout << ") \n";
		n->statement->accept(this);
		cout << " ";
	};

	void CPrettyPrinter::visit(CExpBinary* n)
	{
		n->exp1->accept(this);
		cout << n->op;
		n->exp2->accept(this);
	}
	void CPrettyPrinter::visit(CExpInSquareBrackets *n) {
		n->exp1->accept(this);
		cout << '[';
		n->exp2->accept(this);
		cout << ']';
	}
	void CPrettyPrinter::visit(CExpPointLENGTH *n) {
		n->exp->accept(this);
		cout << '.';
		cout << "length()";
	}
	void CPrettyPrinter::visit(CExpPointID *n) {
		n->exp->accept(this);
		cout << '.';
		cout<<n->id;
		cout << '(';
		n->expList->accept(this);
		cout << ')';
	}
	void CPrettyPrinter::visit(CExpINTEGER_LITERAL *n) {
		cout << n->integer_literal;
	}
	void CPrettyPrinter::visit(CExpSingleOp *n) {
		cout << n->val;
	}
	void CPrettyPrinter::visit(CExpID *n) {
		cout <<  n->id;
	}
	void CPrettyPrinter::visit(CExpTHIS *n) {
		cout << "this" ;
	}
	void CPrettyPrinter::visit(CExpNEWINT *n) {
		cout << "new int";
		cout << '[';
		n->exp->accept(this);
		cout << ']';
	}
	void CPrettyPrinter::visit(CExpNEWID *n) {
		cout <<"new "<< n->id;
		cout << '(' << ')';
	}
	void CPrettyPrinter::visit(CExpExclamationMark *n) {
		cout << '!';
		n->exp->accept( this );
	}
	void CPrettyPrinter::visit( CExpCircleBrackets *n ) {
		cout << '(';
		n->exp->accept(this);
		cout << ')';
	}
	
	
	void CPrettyPrinter::visit( CFormalList *n ) {
		cout << " ";
		n->type->accept( this );
		cout << " " << n->id << " " ;
		n->formalRests->accept( this );
		cout << " ";
		
	}
	void CPrettyPrinter::visit( CFormalRest *n ) {
		cout << " ,";
		n->type->accept( this );
		cout << n->id << " ";
	}
	void CPrettyPrinter::visit( CFormalRests *n ) {
		for( int i = 0; i < n->a.size(); i++ ) {
			n->a[i]->accept( this );
			cout << " ";
		}
	}
	void CPrettyPrinter::visit( CType *n ) {
		if( n->inputType == CType:: _mas ) {
			cout << "int [] ";
		}
		if( n->inputType == CType::_bool ) {
			cout << " bool ";
		}
		if( n->inputType == CType::_int ) {
			cout << " int ";
		}
		if( n->inputType == CType::_id ) {
			cout << n->id;
		}
	}
	void CPrettyPrinter::visit( CExpList *n ) {
		cout << " ";
		if(n->exp)
			n->exp->accept( this );
		cout << " ";
		n->expRests->accept( this );
	}
	void CPrettyPrinter::visit( CExpRests *n ) {
		for( int i = 0; i < n->a.size(); i++ ) {
			n->a[i]->accept( this );
			cout << " ";
		}
	}
	void CPrettyPrinter::visit( CExpRest *n ) {
		cout << " ,";
		n->exp->accept( this );
		cout << " ";

	}
	void CPrettyPrinter::visit( CExpUnaryMinus *n ) {
		cout << " - ";
		n->exp->accept( this );
		cout << " ";
	}




