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


	void CPrettyPrinter::visit( CProgram *node ) {
		node->mainClass->accept( this );
		cout << "\node";
		node->classDecls->accept( this );
	};
	
	void CPrettyPrinter::visit( CClassDecls *node ) {
		for( int i = 0; i < node->a.size(); i++ ) {
			node->a[i]->accept( this );
			cout << "\node";
		}
	
	}
	void CPrettyPrinter::visit( CMainClass *node ) {
		cout << "class" << " " << node->id1 << " " << "{\node" << "public static void main ( String[] ";
		cout << node->id2 << " ";
		cout << ")" << " " << "{\node" << " ";
		node->statements->accept( this );
		cout << "\node}" << " " << "\node}";
	}
	
	void CPrettyPrinter::visit( CClassDecl * node ) {
		cout << "public class" << " " << node->id << " ";
		cout << " {\node ";
		node->varDecls->accept( this );
		cout << " ";
		node->methodDecls->accept( this );
		cout << "\node}\node ";
	}

	void CPrettyPrinter::visit( CClassDeclInheritance *node ) {
		cout << "class " << node->id1 << " extends " << node->id2 << " ";
		cout << " {\node";
		node->varDecls->accept( this );
		cout << " ";
		node->methodDecls->accept( this );
		cout << "\node}\node";
	}


	void CPrettyPrinter::visit( CVarDecls *node ) {
		for( int i = 0; i < node->a.size(); i++ ) {
			node->a[i]->accept( this );
			cout << " ";
		}
	}

	

	void CPrettyPrinter::visit( CMethodDecls *node ) {
		for( int i = 0; i < node->a.size(); i++ ) {
			node->a[i]->accept( this );
			cout << " ";
		}
	}
	
	void CPrettyPrinter::visit( CVarDecl *node ) {
		cout << " ";
		node->type->accept(this);
		cout << " " << node->id << ";\node";
	}
	void CPrettyPrinter::visit( CMethodDecl *node ) {
		cout << " ";
		node->type->accept( this );
		cout << " ";
		cout << node->id;
		cout << " (";
		if(node->formalList)
			node->formalList->accept(this);
		cout<< " )  {\node";
		node->varDecls->accept( this );
		cout << " ";
		node->statements->accept( this );
		cout << ";\node return ";
		node->exp->accept( this );
		cout << ";\node}\node";
	}
	void CPrettyPrinter::visit( CStatements *node ) {
		for( int i = 0; i < node->a.size(); i++ ) {
			node->a[i]->accept( this );
			cout << "\node";
		}
	}

	void CPrettyPrinter::visit(CStatementIF* node)
	{
		cout << "if ( ";
		node->exp->accept(this);
		cout << ")\node ";
		node->statement1->accept(this);
		cout << "\nelse\node";
		node->statement2->accept(this);
	};

	void CPrettyPrinter::visit(CStatementBRACKETS* node)
	{
		cout << "{\node";
		node->statements->accept(this);
		cout << "\node}\node";
	};

	void CPrettyPrinter::visit(CStatementSQUEREASIGNMENT* node)
	{
		cout << node->id;
		cout << "[ ";
		node->exp1->accept(this);
		cout << " ] = ";
		node->exp2->accept(this);
		cout << ";\node";
	};

	void CPrettyPrinter::visit(CStatementASIGNMENT* node)
	{
		cout << node->id;
		cout << " = ";
		node->exp->accept(this);
		cout << ";\node";
	};

	void CPrettyPrinter::visit(CStatementPRINTLN* node)
	{
		cout << "System.out.println( ";
		node->exp->accept(this);
		cout << ");\node";
	};

	void CPrettyPrinter::visit(CStatementWHILE* node)
	{
		cout << " ";
		cout << "while ( ";
		node->exp->accept(this);
		cout << ") \node";
		node->statement->accept(this);
		cout << " ";
	};

	void CPrettyPrinter::visit(CExpBinary* node)
	{
		node->exp1->accept(this);
		cout << node->op;
		node->exp2->accept(this);
	}
	void CPrettyPrinter::visit(CExpInSquareBrackets *node) {
		node->exp1->accept(this);
		cout << '[';
		node->exp2->accept(this);
		cout << ']';
	}
	void CPrettyPrinter::visit(CExpPointLENGTH *node) {
		node->exp->accept(this);
		cout << '.';
		cout << "length()";
	}
	void CPrettyPrinter::visit(CExpPointID *node) {
		node->exp->accept(this);
		cout << '.';
		cout<<node->id;
		cout << '(';
		node->expList->accept(this);
		cout << ')';
	}
	void CPrettyPrinter::visit(CExpINTEGER_LITERAL *node) {
		cout << node->integer_literal;
	}
	void CPrettyPrinter::visit(CExpSingleOp *node) {
		cout << node->val;
	}
	void CPrettyPrinter::visit(CExpID *node) {
		cout <<  node->id;
	}
	void CPrettyPrinter::visit(CExpTHIS *node) {
		cout << "this" ;
	}
	void CPrettyPrinter::visit(CExpNEWINT *node) {
		cout << "new int";
		cout << '[';
		node->exp->accept(this);
		cout << ']';
	}
	void CPrettyPrinter::visit(CExpNEWID *node) {
		cout <<"new "<< node->id;
		cout << '(' << ')';
	}
	void CPrettyPrinter::visit(CExpExclamationMark *node) {
		cout << '!';
		node->exp->accept( this );
	}
	void CPrettyPrinter::visit( CExpCircleBrackets *node ) {
		cout << '(';
		node->exp->accept(this);
		cout << ')';
	}
	
	
	void CPrettyPrinter::visit( CFormalList *node ) {
		cout << " ";
		node->type->accept( this );
		cout << " " << node->id << " " ;
		node->formalRests->accept( this );
		cout << " ";
		
	}
	void CPrettyPrinter::visit( CFormalRest *node ) {
		cout << " ,";
		node->type->accept( this );
		cout << node->id << " ";
	}
	void CPrettyPrinter::visit( CFormalRests *node ) {
		for( int i = 0; i < node->a.size(); i++ ) {
			node->a[i]->accept( this );
			cout << " ";
		}
	}
	void CPrettyPrinter::visit( CType *node ) {
		if( node->inputType == CType:: _mas ) {
			cout << "int [] ";
		}
		if( node->inputType == CType::_bool ) {
			cout << " bool ";
		}
		if( node->inputType == CType::_int ) {
			cout << " int ";
		}
		if( node->inputType == CType::_id ) {
			cout << node->id;
		}
	}
	void CPrettyPrinter::visit( CExpList *node ) {
		cout << " ";
		if(node->exp)
			node->exp->accept( this );
		cout << " ";
		node->expRests->accept( this );
	}
	void CPrettyPrinter::visit( CExpRests *node ) {
		for( int i = 0; i < node->a.size(); i++ ) {
			node->a[i]->accept( this );
			cout << " ";
		}
	}
	void CPrettyPrinter::visit( CExpRest *node ) {
		cout << " ,";
		node->exp->accept( this );
		cout << " ";

	}
	void CPrettyPrinter::visit( CExpUnaryMinus *node ) {
		cout << " - ";
		node->exp->accept( this );
		cout << " ";
	}




