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
		CVarInfo(const string& _name, const string& _type) :
			name(_name), type(_type){}
	};

	struct CMethodInfo{
		string name;
		vector<CVarInfo> vars;
		vector<CVarInfo> params;
		string returnType;
		CMethodInfo(const string& _name, const string& _returnType) :
			name(_name), returnType(_returnType), vars(), params(){}
	};

	struct CClassInfo{
		string name;
		string parent;
		vector<CVarInfo> vars;
		vector<CMethodInfo> methods;
		CClassInfo(const string& _name) :
			name(_name), vars(), methods(){}
	};

	struct CTable{
		vector<CClassInfo> classInfo;
		CTable() : classInfo(){}
	};

	class CSymbolTableBuilder : public IVisitor{
	public:
		CTable table;
		bool inMethod;
		string lastTypeValue;
		CSymbolTableBuilder() : inMethod(0) {}



		void visit(const CProgram* node){
			node->mainClass->accept(this);
			if (node->classDecls != 0) {
				node->classDecls->accept(this);
			}
		}
		void visit(const CMainClass* node){
			inMethod = 0;
			table.classInfo.push_back(CClassInfo(node->id1));
			CMethodInfo mainMthd("main", "void");
			mainMthd.params.push_back(CVarInfo(node->id2, "String[]"));
			table.classInfo.back().methods.push_back(mainMthd);
			if (node->statement != 0) {
				node->statement->accept(this);
			}
		}
		void visit(const CClassDecls* node){
			for (int i = 0; i < node->a.size(); i++) {
				node->a[i]->accept(this);
			}
		}
		void visit(const CClassDecl* node){
			inMethod = 0;
			table.classInfo.push_back(CClassInfo(node->id));
			if (node->methodDecls != 0) {
				node->methodDecls->accept(this);
			}
			if (node->varDecls != 0) {
				node->varDecls->accept(this);
			}
		}

		void visit(const CVarDecls* node){
			for (int i = 0; i < node->a.size(); i++) {
				node->a[i]->accept(this);
			}
		}

		void visit(const CMethodDecls* node){
			for (int i = 0; i < node->a.size(); i++) {
				node->a[i]->accept(this);
			}
		}
		void visit(const CVarDecl* node){
			node->type->accept(this);
			if (inMethod) {
				table.classInfo.back().methods.back().vars.push_back(CVarInfo(node->id, lastTypeValue));
			}
			else {
				table.classInfo.back().vars.push_back(CVarInfo(node->id, lastTypeValue));
			}
		}
		void visit(const CMethodDecl* node){
			node->type->accept(this);
			table.classInfo.back().methods.push_back(CMethodInfo(node->id, lastTypeValue));
			if (node->formalList != 0) {
				node->formalList->accept(this);
			}
			if (node->exp != 0) {
				inMethod = 1;
				node->exp->accept(this);
				inMethod = 0;
			}
		}

		void visit(const CStatements* node){}

		void visit(const CFormalList* node){
			if (node->formalRests != 0) {
				node->formalRests->accept(this);
			}
		}
		void visit(const CFormalRests* node){
			for (int i = 0; i < node->a.size(); i++) {
				node->a[i]->accept(this);
			}
		}
		void visit(const CFormalRest* node){
		}

		void visit(const class CExpList *node){
			if (node->expRests != 0) {
				node->expRests->accept(this);
			}
		}

		void visit(const CExpRests* node){
			for (int i = 0; i < node->a.size(); i++) {
				node->a[i]->accept(this);
			}
		}
		void visit(const CExpRest* node){
		}

		void visit(const CStatementIF* node){}
		void visit(const CStatementBRACKETS* node){}
		void visit(const CStatementSQUEREASIGNMENT* node){}
		void visit(const CStatementASIGNMENT* node){}
		void visit(const CStatementPRINTLN* node){}
		void visit(const CStatementWHILE* node){}



		void visit(const CExpBinary* node){}
		void visit(const CExpInSquareBrackets* node){}
		void visit(const CExpPointLENGTH* node){}
		void visit(const CExpUnaryMinus* node){}
		void visit(const CExpPointID* node){}
		void visit(const CExpINTEGER_LITERAL* node){}
		void visit(const CExpSingleOp* node){}
		void visit(const CExpNEWINT* node){}
		void visit(const CExpID* node){}
		void visit(const CExpNEWINT* node){}
		void visit(const CExpExclamationMark* node){}
		void visit(const CExpTHIS* node){}
		void visit(const CExpCircleBrackets* node){}
	};
