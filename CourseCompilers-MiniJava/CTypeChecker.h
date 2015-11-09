#pragma once
#ifndef CTYPECHECKER_H_INCLUDED
#define CTYPECHECKER_H_INCLUDED
#include <iostream>
#include "Visitor.h"
#include "CTypes.h"
#include "CSymbolTable.h"
#include <vector>
#include <string>
using std::vector;
using std::cout;
using std::endl;
using namespace std;


class CTypeChecker : public IVisitor {
public:
	CTable table;
	std::string lastTypeValue;
	int classPos = 0;
	int methodPos = -1;

	bool inMethod;

	bool checkClassExistence( std::string name ) {
		bool flag = false;
		int i = 0;
		while( !flag && (i < table.classInfo.size()) ) {
			flag = flag || (table.classInfo[i].name == name);
			i++;
		}

		if( !flag )
			return false;
		else
			return true;

	}

	bool assignType( std::string name, std::string& type ) {
		bool flagDec = false;
		for( int i = 0; i < table.classInfo[this->classPos].methods[this->methodPos].vars.size(); i++ ) {
			flagDec = flagDec || (name == table.classInfo[this->classPos].methods[this->methodPos].vars[i].name);
			if( flagDec ) {
				type = table.classInfo[this->classPos].methods[this->methodPos].vars[i].type;
				return true;
			}
		}

		if( !flagDec ) {
			for( int i = 0; i < table.classInfo[this->classPos].methods[this->methodPos].params.size(); i++ ) {
				flagDec = flagDec || (name == table.classInfo[this->classPos].methods[this->methodPos].params[i].name);
				if( flagDec ) {
					type = table.classInfo[this->classPos].methods[this->methodPos].params[i].type;
					return true;
				}
			}
		}

		if( !flagDec ) {
			for( int i = 0; i < table.classInfo[this->classPos].vars.size(); i++ ) {
				flagDec = flagDec || (name == table.classInfo[this->classPos].vars[i].name);
				if( flagDec ) {
					type = table.classInfo[this->classPos].vars[i].type;
					return true;
				}
			}
		}
	}

	std::string checkAssignment( std::string name ) {
		std::string type;
		bool declared = assignType( name, type );


		if( !declared ) {
			cout << "Variable not declared " << name << endl;
			return "";
		}

		if( type != lastTypeValue )
			cout << "Cannot assign " << lastTypeValue << " to " << type << endl;

		return type;
	}

	void visit( const CProgram* node ) {
		if( node->mainClass != NULL )
			node->mainClass->accept( this );

		if( node->classDecls != NULL )
			node->classDecls->accept( this );
	}
	void visit( const CMainClass* node ) {
		if( node->statement != NULL )
			node->statement->accept( this );
	}
	void visit( const CClassDecls* node ) {
		for( int i = 0; i < node->a.size(); i++ ) {
			node->a[i]->accept( this );
		}
	}

	void visit( const CClassDecl* node ) {
		this->classPos++;

		if( node->varDecls != NULL )
			node->varDecls->accept( this );

		if( node->methodDecls != NULL )
			node->methodDecls->accept( this );
	}

	void visit( const CClassDeclInheritance* node ) {
		this->classPos++;
		
		std::string parent = node->id;
		do {
			int i = 0;
			while( (table.classInfo[i].name != parent) && (i < table.classInfo.size()) )
				i++;

			if( i == table.classInfo.size() )
				parent = "";
			else
				parent = table.classInfo[i].parent;
		}
		while( (parent != "") || (parent != node->id2) );

		if( parent != "" )
			cout << "Cyclic inheritance with " << node->id << endl;
		
		if( node->varDecls != NULL )
			node->varDecls->accept( this );

		if( node->methodDecls != NULL )
			node->methodDecls->accept( this );
	}

	void visit( const CVarDecls* node ) {
		for( int i = 0; i < node->a.size(); i++ ) {
			node->a[i]->accept( this );
		}
	}

	void visit( const CMethodDecls* node ) {
		for( int i = 0; i < node->a.size(); i++ ) {
			node->a[i]->accept( this );
		}
	}

	void visit( const CVarDecl* node ) {
		CType* tmp = (node->type);
		if( (tmp->inputType != 0) && (tmp->inputType != 1) && (tmp->inputType != 2) )
			if( !checkClassExistence( tmp->id ) )
				cout << "No such type: " << tmp->id << endl;


		delete tmp;
	}

	void visit( const CMethodDecl* node ) {
		this->methodPos++;
		CType* tmp = (node->type);
		if( (tmp->inputType != 0) && (tmp->inputType != 1) && (tmp->inputType != 2) ) {
			bool flag = false;
			for( int i = 0; i < table.classInfo.size(); i++ ) {
				flag = flag || (table.classInfo[i].name == tmp->id);
			}

			if( !flag )
				cout << "No such type: " << tmp->id << endl;
		}
		if( node->formalList != NULL )
			node->formalList->accept( this );
		if( node->varDecls != NULL )
			node->varDecls->accept( this );
		if( node->statements != NULL )
			node->statements->accept( this );
		if( node->exp != NULL )
			node->exp->accept( this );

		delete tmp;
	}


	void visit( const CStatements* node ) {
		for( int i = 0; i < node->a.size(); i++ ) {
			node->a[i]->accept( this );
		}
	}

	void visit( const CFormalList* node ) {
		CType* tmp = (node->type);
		if( (tmp->inputType != 0) && (tmp->inputType != 1) && (tmp->inputType != 2) ) {
			bool flag = false;
			for( int i = 0; i < table.classInfo.size(); i++ ) {
				flag = flag || (table.classInfo[i].name == tmp->id);
			}

			if( !flag )
				cout << "No such type: " << tmp->id << endl;
		}
		if( node->formalRests != 0 ) {
			node->formalRests->accept( this );
		}
	}

	void visit( const CStatementBRACKETS* node ) {
		if( node->statement != NULL )
			node->statement->accept( this );
	}

	void visit( const CStatementIF* node ) {
		node->exp->accept( this );
		if( lastTypeValue != "bool" )
			cout << "Error in if/else statement expression" << endl;
		node->statement1->accept( this );
		node->statement2->accept( this );
	}

	void visit( const CStatementWHILE* node ) {
		node->exp->accept( this );
		if( lastTypeValue != "bool" )
			cout << "Error in while statement expression" << endl;
		node->statement->accept( this );
	}

	void visit( const CStatementPRINTLN* node ) {
		node->exp->accept( this );
		if( lastTypeValue != "int" )
			cout << "Error in print expression" << endl;
	}

	void visit( const CStatementASIGNMENT* node ) {
		if( node->exp != NULL )
			node->exp->accept( this );

		checkAssignment( node->id );
	}

	void visit( const CStatementSQUEREASIGNMENT* node ) {
		if( node->exp1 != NULL )
			node->exp1->accept( this );

		if( lastTypeValue != "int" )
			cout << "Array index is not int in " << node->id << endl;

		if( node->exp2 != NULL )
			node->exp2->accept( this );

		std::string type;
		assignType( node->id, type );
		if( !((type == "int[]") && (lastTypeValue == "int")) )
			cout << "Cannot assign " << lastTypeValue << " to " << type << endl;

	}

	void visit( const CInvokeExpressionNode* node ) {
		if( node->firstExp != NULL )
			node->firstExp->accept( this );

		if( lastTypeValue != "int[]" )
			cout << "Trying to access non-existent array" << endl;

		if( node->secondExp != NULL )
			node->secondExp->accept( this );

		if( lastTypeValue != "int" )
			cout << "Array index is not int" << endl;

		lastTypeValue = "int";
	}

	void visit( const CLengthExpressionNode* node ) {

		if( node->expr != NULL )
			node->expr->accept( this );
		lastTypeValue = "int";
	}

	void visit( const CArithmeticExpressionNode* node ) {
		node->firstExp->accept( this );
		if( (lastTypeValue != "int") && (lastTypeValue != "bool") )
			cout << "Error in arithmetic expression" << endl;

		node->secondExp->accept( this );
		if( (lastTypeValue != "int") && (lastTypeValue != "bool") )
			cout << "Error in arithmetic expression" << endl;

		lastTypeValue = "int";
	}

	void visit( const CUnaryExpressionNode* node ) {
		node->expr->accept( this );

		if( lastTypeValue != "int" )
			cout << "Error in unary expression" << endl;

		lastTypeValue = "int";
	}

	void visit( const CCompareExpressionNode* node ) {
		node->firstExp->accept( this );
		if( (lastTypeValue != "int") && (lastTypeValue != "bool") )
			cout << "Error in compare expression" << endl;

		node->secondExp->accept( this );
		if( (lastTypeValue != "int") && (lastTypeValue != "bool") )
			cout << "Error in compare expression" << endl;

		lastTypeValue = "bool";
	}

	void visit( const CNotExpressionNode* node ) {
		node->expr->accept( this );

		if( lastTypeValue != "int" )
			cout << "Error in NOT expression";

		lastTypeValue = "bool";
	}

	void visit( const CNewArrayExpressionNode* node ) {
		if( node->expr != NULL )
			node->expr->accept( this );

		if( lastTypeValue != "int" )
			cout << "Array index is not int in new array" << lastTypeValue << endl;
		lastTypeValue = "int[]";
	}

	void visit( const CNewObjectExpressionNode* node ) {
		if( (node->objType != "int") && (node->objType != "bool") )
			if( !checkClassExistence( node->objType ) )
				cout << "No such type: " << node->objType << endl;
	}

	void visit( const CIntExpressionNode* node ) {
		lastTypeValue = "int";

	}
	void visit( const CBooleanExpressionNode* node ) {
		lastTypeValue = "bool";
	}

	void visit( const CIdentExpressionNode* node ) {
		std::string tmp;
		assignType( node->name, tmp );
		if( tmp != "" )
			lastTypeValue = tmp;
	}

	void visit( const CThisExpressionNode* node ) {
	}

	void visit( const CParenExpressionNode* node ) {
		if( node->expr != NULL )
			node->expr->accept( this );

		if( (lastTypeValue != "int") && (lastTypeValue != "bool") )
			cout << "Expression in brackets is not valid" << endl;
	}
	void visit( const CInvokeMethodExpressionNode* node ) {
		if( node->args != NULL )
			node->args->accept( this );
		if( node->expr != NULL )
			node->expr->accept( this );

		for( int i = 0; i < table.classInfo[this->classPos].methods.size(); i++ )
			if( table.classInfo[this->classPos].methods[i].name == node->name ) {
				lastTypeValue = table.classInfo[this->classPos].methods[i].returnType;
			}
	}
	void visit( const CFewArgsExpressionNode* node ) {
		if( node->expr != NULL )
			node->expr->accept( this );
	}

	void visit( const CListExpressionNode* node ) {
		if( node->prevExps != NULL )
			node->prevExps->accept( this );
		if( node->nextExp != NULL )
			node->nextExp->accept( this );
	}
	void visit( const CLastListExpressionNode* node ) {
		if( node->expr != NULL )
			node->expr->accept( this );
	}
};
#endif