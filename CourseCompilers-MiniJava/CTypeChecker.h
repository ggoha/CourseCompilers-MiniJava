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

};