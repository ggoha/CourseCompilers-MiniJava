#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Visitor.h"
#include "CTypes.h"
using std::vector;
using std::cout;
using std::endl;
using std::string;

	struct CVarInfo{
		string name;
		string type;
		CVarInfo(  string _name,   string _type) :
			name(_name), type(_type){}
		void Print() const{
			std::cout << "Var" << type << " " << name << std::endl;
		}
	};

	struct CMethodInfo{
		string name;
		vector<CVarInfo> vars;
		vector<CVarInfo> params;
		string returnType;
		CMethodInfo(  string _name,   string _returnType) :
			name(_name), returnType(_returnType), vars(), params(){}
		void Print() const{
			std::cout << "Method" << name << std::endl;
			std::cout << "Params ";
			for (size_t i = 0; i < params.size(); ++i)
				params[i].Print();
			std::cout << "Vars ";
			for (size_t i = 0; i < vars.size(); ++i)
				vars[i].Print();
		}
	};

	struct CClassInfo{
		string name;
		string parent;
		vector<CVarInfo> vars;
		vector<CMethodInfo> methods;
		int getMethodIndex(const string& name) const {
			for (size_t i = 0; i < methods.size(); ++i)
				if (methods[i].name == name)
					return i;
			return -1;
		}

		int getVarIndex(const string& name) const {
			for (size_t i = 0; i < methods.size(); ++i)
				if (vars[i].name == name)
					return i;
			return -1;
		}

		CClassInfo(  string _name) :
			name(_name), vars(), methods(){}
		void Print() const{
			std::cout << "Class" << name << ":" << parent << std::endl;
			std::cout << "Methods ";
			for (size_t i = 0; i < methods.size(); ++i)
				methods[i].Print();
			std::cout << "Vars ";
			for (size_t i = 0; i < vars.size(); ++i)
				vars[i].Print();
		}
	};

	struct CTable{
		vector<CClassInfo> classInfo;
		vector<std::string> baseType;
		int getClassIndex(const string& name) const {
			for (size_t i = 0; i < classInfo.size(); ++i)
				if (classInfo[i].name == name)
					return i;
			return -1;
		}
		CTable() : classInfo(){
			baseType.push_back("int");
			baseType.push_back("int[]");
			baseType.push_back("boolean");
		}
	};

	class CSymbolTableBuilder : public IVisitor{
	public:
		CTable table;
		bool inMethod;
		string lastTypeValue;
		CSymbolTableBuilder() : inMethod(0) {}

		template <typename T>
		void checkItemAlreadyExists(const std::vector<T>& items, const string& itemName) {
			typename std::vector<T>::const_iterator it = items.cbegin();
			typename std::vector<T>::const_iterator itEnd = items.cend();
			for (; it != itEnd; ++it) {
				if (it->name == itemName) {
					std::cerr << "redefinition: " << itemName << std::endl;
				}
			}
		}

		void Print(){
			for (size_t i = 0; i < table.classInfo.size(); ++i)
			{
				table.classInfo[i].Print();
			}
		}

		void visit(  CProgram* node){
			node->mainClass->accept(this);
			if (node->classDecls != 0) {
				node->classDecls->accept(this);
			}
		}
		void visit(  CMainClass* node){
			inMethod = 0;
			table.classInfo.push_back(CClassInfo(node->id));
			CMethodInfo mainMthd("main", "void");
			mainMthd.params.push_back(CVarInfo(node->idParams, "String[]"));
			table.classInfo.back().methods.push_back(mainMthd);
			if (node->statements != 0) {
				node->statements->accept(this);
			}
		}
		void visit(  CClassDecls* node){
			for (size_t i = 0; i < node->classes.size(); i++) {
				node->classes[i]->accept(this);
			}
		}
		void visit(  CClassDecl* node){
			inMethod = 0;
			table.classInfo.push_back(CClassInfo(node->id));
			if (node->methodDecls != 0) {
				node->methodDecls->accept(this);
			}
			if (node->varDecls != 0) {
				node->varDecls->accept(this);
			}
		}

		void visit(  CVarDecls* node){
			for (size_t i = 0; i < node->vars.size(); i++) {
				node->vars[i]->accept(this);
			}
		}

		void visit(  CMethodDecls* node){
			for (size_t i = 0; i < node->methods.size(); i++) {
				node->methods[i]->accept(this);
			}
		}
		void visit(  CVarDecl* node){
			node->type->accept(this);
			if (inMethod) {
				table.classInfo.back().methods.back().vars.push_back(CVarInfo(node->id, lastTypeValue));
			}
			else {
				table.classInfo.back().vars.push_back(CVarInfo(node->id, lastTypeValue));
			}
		}
		void visit(  CMethodDecl* node){
			inMethod = true;
			node->type->accept(this);
			table.classInfo.back().methods.push_back(CMethodInfo(node->id, lastTypeValue));

			if (node->formalList != 0) {
				node->formalList->accept(this);
			}
			if (node->varDecls)
				node->varDecls->accept(this);
			if (node->exp != 0)
				node->exp->accept(this);
			inMethod = false;
		}

		void visit(  CFormalList* node){
			node->type->accept(this);
			checkItemAlreadyExists<CVarInfo>(table.classInfo.back().methods.back().params, node->id);
			table.classInfo.back().methods.back().params.push_back(CVarInfo(node->id, lastTypeValue));
			if (node->formalRests != 0) {
				node->formalRests->accept(this);
			}
		}
		void visit(  CFormalRests* node){
			for (size_t i = 0; i < node->parametrs.size(); i++) {
				node->parametrs[i]->accept(this);
			}
		}
		void visit(  CFormalRest* node) {
			node->type->accept(this);
			checkItemAlreadyExists<CVarInfo>(table.classInfo.back().methods.back().params, node->id);
			table.classInfo.back().methods.back().params.push_back(CVarInfo(node->id, lastTypeValue));
		}

		void visit(  class CExpList *node){
			if (node->expRests != 0) {
				node->expRests->accept(this);
			}
		}

		void visit(  CExpRests* node){
			for (size_t i = 0; i < node->expressions.size(); i++) {
				node->expressions[i]->accept(this);
			}
		}
		void visit(  CExpRest* node){
		}	

		  void visit(CStatementIF* n) { }
		  void visit(CStatementBRACKETS* n) { }

		  void visit(CStatementSQUEREASIGNMENT* n) { }

		  void visit(CStatementASIGNMENT* n) { }

		  void visit(CStatementPRINTLN* n) { }

		  void visit(CStatementWHILE* n) { }

		  void visit(CExpBinary* n) { }

		  void visit(CExpInSquareBrackets *n) { }

		  void visit(CExpPointLENGTH *n) { }

		  void visit(CExpPointID *n) { }

		  void visit(CExpINTEGER_LITERAL *n) { }

		  void visit(CExpSingleOp *n) { }
		  void visit(CExpID *n) { }
		  void visit(CExpTHIS *n) { }
		  void visit(CExpNEWINT *n) { }
		  void visit(CExpNEWID *n) { }
		  void visit(CExpExclamationMark *n) { }
		  void visit(CExpCircleBrackets *n) { }
		  void visit(CClassDeclInheritance *node) {
			  inMethod = 0;
			  table.classInfo.push_back(CClassInfo(node->id));
			  table.classInfo.back().parent = node->idParent;
			  if (node->methodDecls != 0) {
				  node->methodDecls->accept(this);
			  }
			  if (node->varDecls != 0) {
				  node->varDecls->accept(this);
			  }
		  }
		  void visit(CStatements *n) { }
		  void visit(CType *n) { 
			  lastTypeValue = n->id;
		  }
		  void visit(CExpUnaryMinus *n) { }
	};
