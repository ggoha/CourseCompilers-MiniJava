#pragma once
#include <iostream>
#include "Visitor.h"
#include "CTypes.h"
#include "CSymbolTable.h"
using std::vector;
using std::cout;
using std::endl;
using std::string;


class CTypeChecker : public IVisitor {
public:
	CTable table;
	string lastTypeValue;
	int classPos = 0;
	int methodPos = -1;

	bool inMethod;

	bool checkClassExistence(string name) {
		bool flag = false;
		int i = 0;
		while (!flag && (i < table.classInfo.size())) {
			flag = flag || (table.classInfo[i].name == name);
			i++;
		}

		if (!flag)
			return false;
		else
			return true;

	}

	bool assignType(string name, string& type) {
		bool flagDec = false;
		for (int i = 0; i < table.classInfo[this->classPos].methods[this->methodPos].vars.size(); i++) {
			flagDec = flagDec || (name == table.classInfo[this->classPos].methods[this->methodPos].vars[i].name);
			if (flagDec)
			{
				type = table.classInfo[this->classPos].methods[this->methodPos].vars[i].type;
				return true;
			}
		}

		if (!flagDec) {
			for (int i = 0; i < table.classInfo[this->classPos].methods[this->methodPos].params.size(); i++) {
				flagDec = flagDec || (name == table.classInfo[this->classPos].methods[this->methodPos].params[i].name);
				if (flagDec) {
					type = table.classInfo[this->classPos].methods[this->methodPos].params[i].type;
					return true;
				}
			}
		}

		if (!flagDec) {
			for (int i = 0; i < table.classInfo[this->classPos].vars.size(); i++) {
				flagDec = flagDec || (name == table.classInfo[this->classPos].vars[i].name);
				if (flagDec) {
					type = table.classInfo[this->classPos].vars[i].type;
					return true;
				}
			}
		}
	}

	string checkAssignment(string name) {
		string type;
		bool declared = assignType(name, type);


		if (!declared) {
			cout << "Variable not declared " << name << endl;
			return "";
		}

		if (type != lastTypeValue)
			cout << "Cannot assign " << lastTypeValue << " to " << type << endl;

		return type;
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
			if (lastTypeValue != "boolean")
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
			cout << "exception in array assigment:" << lastTypeValue << " is not array" << '\n';
		return ;
		string t = lastTypeValue.substr(0, lastTypeValue.length() - 2);
		n->exp2->accept(this);
		if (t != lastTypeValue)
			cout << "exception in array assigment: " << t << "=" << lastTypeValue << '\n';
	}

	void visit(CExpPointLENGTH *n)
	{
		n->exp->accept(this);
		if (lastTypeValue != "String")
			cout << "esception length is not attribute of " << lastTypeValue<<'\n';
		lastTypeValue = "int";
	}
	void visit(CExpPointID *n)
	{
		n->exp->accept(this);
		n->expList->accept(this);

		for (int i = 0; i < table.classInfo[this->classPos].methods.size(); i++)
			if (table.classInfo[this->classPos].methods[i].name == n->id) {
				lastTypeValue = table.classInfo[this->classPos].methods[i].returnType;
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