#pragma once

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
		size_t i = 0;
		while( !flag && (i < table.classInfo.size()) ) {
			flag = flag || (table.classInfo[i].name == name);
			i++;
		}
		i = 0;
		while (!flag && (i < table.baseType.size())){
			flag = flag || (table.baseType[i] == name);
			i++;
		}
		if( !flag )
			return false;
		else
			return true;

	}

	bool assignType( std::string name, std::string& type ) {
		bool flagDec = false;
		for( size_t i = 0; i < table.classInfo[this->classPos].methods[this->methodPos].vars.size(); i++ ) {
			flagDec = flagDec || (name == table.classInfo[this->classPos].methods[this->methodPos].vars[i].name);
			if( flagDec ) {
				type = table.classInfo[this->classPos].methods[this->methodPos].vars[i].type;
				return true;
			}
		}

		if( !flagDec ) {
			for( size_t i = 0; i < table.classInfo[this->classPos].methods[this->methodPos].params.size(); i++ ) {
				flagDec = flagDec || (name == table.classInfo[this->classPos].methods[this->methodPos].params[i].name);
				if( flagDec ) {
					type = table.classInfo[this->classPos].methods[this->methodPos].params[i].type;
					return true;
				}
			}
		}

		if( !flagDec ) {
			for( size_t i = 0; i < table.classInfo[this->classPos].vars.size(); i++ ) {
				flagDec = flagDec || (name == table.classInfo[this->classPos].vars[i].name);
				if( flagDec ) {
					type = table.classInfo[this->classPos].vars[i].type;
					return true;
				}
			}
		}
		return false;
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

	void visit( CProgram* node ) {
		if( node->mainClass != NULL )
			node->mainClass->accept( this );

		if( node->classDecls != NULL )
			node->classDecls->accept( this );
	}
	void visit( CMainClass* node ) {
		++methodPos;
		if( node->statements != NULL )
			node->statements->accept( this );
	}
	void visit( CClassDecls* node ) {
		for( size_t i = 0; i < node->classes.size(); i++ ) {
			node->classes[i]->accept( this );
		}
	}

	void visit( CClassDecl* node ) {
		this->classPos++;
		methodPos = -1;

		if( node->varDecls != NULL )
			node->varDecls->accept( this );

		if( node->methodDecls != NULL )
			node->methodDecls->accept( this );
	}

	void visit(  CClassDeclInheritance* node ) {
		this->classPos++;
		methodPos = -1;
		std::string parent = node->id2;
		size_t _count = 0;
		do {
			if (_count > table.classInfo.size())
				break;
			++_count;
			int i = table.getClassIndex(parent);
			if (i == -1) {
				cout << "error in extends: no such class " << parent << '\n';
				break;
			};
			parent = table.classInfo[i].parent;
		}
		while( (parent != "") && (parent != node->id) );

		if( parent != "" )
			cout << "Cyclic inheritance with " << node->id << endl;
		
		if( node->varDecls != NULL )
			node->varDecls->accept( this );

		if( node->methodDecls != NULL )
			node->methodDecls->accept( this );
	}

	void visit( CVarDecls* node ) {
		for( size_t i = 0; i < node->vars.size(); i++ ) {
			node->vars[i]->accept( this );
		}
	}

	void visit( CMethodDecls* node ) {
		for( size_t i = 0; i < node->methods.size(); i++ ) {
			node->methods[i]->accept(this);
		}
	}

	void visit( CVarDecl* node ) {
		CType* tmp = (node->type);
		if( (tmp->inputType != 0) && (tmp->inputType != 1) && (tmp->inputType != 2) )
			if( !checkClassExistence( tmp->id ) )
				cout << "No such type: " << tmp->id << endl;
	}

	void visit( CMethodDecl* node ) {
		this->methodPos++;
		CType* tmp = (node->type);
		if( (tmp->inputType != 0) && (tmp->inputType != 1) && (tmp->inputType != 2) ) {
			bool flag = false;
			for( size_t i = 0; i < table.classInfo.size(); i++ ) {
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
	}


	void visit( CStatements* node ) {
		for( size_t i = 0; i < node->statements.size(); i++ ) {
			node->statements[i]->accept( this );
		}
	}

	void visit( CFormalList* node ) {
		CType* tmp = (node->type);
		if( (tmp->inputType != 0) && (tmp->inputType != 1) && (tmp->inputType != 2) ) {
			bool flag = false;
			for( size_t i = 0; i < table.classInfo.size(); i++ ) {
				flag = flag || (table.classInfo[i].name == tmp->id);
			}

			if( !flag )
				cout << "No such type: " << tmp->id << endl;
		}
		if( node->formalRests != 0 ) {
			node->formalRests->accept( this );
		}
	}

	void visit( CStatementBRACKETS* node ) {
		if( node->statements != NULL )
			node->statements->accept( this );
	}

	void visit( CStatementIF* node ) {
		node->exp->accept( this );
		if( lastTypeValue != "boolean" )
			cout << "Error in if/else statement expression" << endl;
		node->statementIf->accept( this );
		node->statementElse->accept( this );
	}

	void visit(  CStatementWHILE* node ) {
		node->exp->accept( this );
		if( lastTypeValue != "boolean" )
			cout << "Error in while statement expression" << endl;
		node->statementWhile->accept( this );
	}

	void visit( CStatementPRINTLN* node ) {
		node->exp->accept( this );
		if( lastTypeValue != "int" )
			cout << "Error in print expression" << endl;
	}

	void visit( CStatementASIGNMENT* node ) {
		if( node->exp != NULL )
			node->exp->accept( this );

		checkAssignment( node->id );
	}

	void visit( CStatementSQUEREASIGNMENT* node ) {
		if( node->expInSquareBrackets != NULL )
			node->expInSquareBrackets->accept( this );

		if( lastTypeValue != "int" )
			cout << "Array index is not int in " << node->id << endl;

		if( node->expAssigned != NULL )
			node->expAssigned->accept( this );

		std::string type;
		assignType( node->id, type );
		if( !((type == "int[]") && (lastTypeValue == "int")) )
			cout << "Cannot assign " << lastTypeValue << " to " << type << endl;

	}

	void visit(CFormalRest *n)
	{
		n->type->accept(this);
	}
	void visit(CFormalRests *n)
	{
		for (size_t i = 0; i < n->parametrs.size();++i)
			n->parametrs[i]->accept(this);
	}

	void visit(CExpBinary* n)
	{
		n->exp1->accept(this);
		string typeExp1 = lastTypeValue;
		n->exp2->accept(this);
		if (typeExp1 != lastTypeValue)
			cout << "exception in "  << n->op;
		if (n->op == '&')
		{
			if (lastTypeValue != "boolean")
				cout << "exception in "  << n->op << " arguments is not boolean" << '\n';
			lastTypeValue = "boolean";
		}
		else
		{
			if (lastTypeValue != "int")
				cout << "exception in "  << n->op  << " arguments is not int" << '\n';
			if (n->op == '<')
				lastTypeValue = "boolean";
			else
				lastTypeValue = "int";
		};
	}

	void visit(CExpInSquareBrackets *n)
	{
		n->exp1->accept(this);
		if (lastTypeValue[lastTypeValue.length() - 1] != ']' || lastTypeValue[lastTypeValue.length() - 2] != '[')
		{
			cout << "exception in array assigment:" << lastTypeValue << " is not array" << '\n';
			return;
		}
		string t = lastTypeValue.substr(0, lastTypeValue.length() - 2);
		n->exp2->accept(this);
		if (t != lastTypeValue)
			cout << "exception in array assigment: " << t << "=" << lastTypeValue << '\n';
	}

	void visit(CExpPointLENGTH *n)
	{
		n->exp->accept(this);
		if (lastTypeValue.substr(lastTypeValue.length()-2,2) != "[]")
			cout << "Error in length :" << lastTypeValue<<"is not array\n";
		lastTypeValue = "int";
	}
	void visit(CExpPointID *n)
	{
		n->exp->accept(this);
		string t = lastTypeValue;
		n->expList->accept(this);
		int clPos = table.getClassIndex(t);
		int mPos = -1;
		size_t _count = 0;
		while(clPos > 0)
		{
			if (_count > table.classInfo.size())
				break;
			++_count;
			mPos = table.classInfo[clPos].getMethodIndex(n->id);
			if (mPos >= 0)
			{
				lastTypeValue = table.classInfo[clPos].methods[mPos].returnType;
				break;
			}
			clPos = table.getClassIndex(table.classInfo[clPos].parent);
		}
		if(mPos == -1)
		{
			cout << "no method "<<n->id<<" in class "<<t<<"\n";
			return;
		}
	}

	void visit(CExpINTEGER_LITERAL *n)
	{
		lastTypeValue = "int";
	}

	void visit(CExpSingleOp *n)
	{
		lastTypeValue = "boolean";
	}
	void visit(CExpID *n)
	{
		string t = "";
		if (assignType(n->id, t))
			lastTypeValue = t;
		else
			cout << n->id << "doesn't exist\n";
	}
	void visit(CExpTHIS *n)
	{
		lastTypeValue = table.classInfo[classPos].name;
	}
	void visit(CExpNEWINT *n)
	{
		n->exp->accept(this);
		if (lastTypeValue != "int")
			cout << "array index must be int\n";
		lastTypeValue = "int[]";
	}
	void visit(CExpNEWID *n)
	{
		if ((n->id != "int") && (n->id != "boolean"))
			if (!checkClassExistence(n->id))
				cout << "No such type: " << n->id << endl;
		lastTypeValue = n->id;
	}
	void visit(CExpExclamationMark *n)
	{
		n->exp->accept(this);
		if (lastTypeValue != "boolean")
			cout << "! just for boolean but called with type " << lastTypeValue << '\n';
		lastTypeValue = "boolean";
	}
	void visit(CExpCircleBrackets *n)
	{
		n->exp->accept(this);
	}

	void visit(CExpUnaryMinus *n)
	{
		n->exp->accept(this);
		if (lastTypeValue != "int")
			cout << "unary minus must be used with int but called with " << lastTypeValue;
		lastTypeValue = "int";
	}

	void visit( CExpList * node ) {
		if( node->exp != 0 )
			node->exp->accept( this );
		if( node->expRests != 0 ) {
			node->expRests->accept( this );
		}
	}

	void visit( CExpRests * node ) {
		for( size_t i = 0; i < node->expressions.size(); i++ ) {
			node->expressions[i]->accept( this );
		}
	}

	void visit( CExpRest * node ) {
		node->exp->accept( this );
	}

	void visit(CType *n)
	{
		if (n->inputType == n->_int)
			lastTypeValue = "int";

		if (n->inputType == n->_bool)
			lastTypeValue = "boolean";

		if (n->inputType == n->_mas)
			lastTypeValue = "int[]";

		if (n->inputType == n->_id)
		{
			lastTypeValue = n->id;
			if (!checkClassExistence(lastTypeValue))
				cout << "class " << n->id << " doesn't exist in the current context\n";
		};
	}
};
