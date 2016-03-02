#include "IRExp.h"
#include "map"
using namespace std;


// ���������� ������
class IAccess {
public:
	virtual const IRExp* GetExp(const CTemp* framePtr) const = 0;
	virtual ~IAccess() {}
};

//���������� �� �����
class InFrame : IAccess{
	InFrame(int _offset) : offset( _offset) {};
	const IRExp* GetExp(const CTemp framePtr) { 
		int machineOffset = offset * IRFrame::WORD_SIZE;
		return new IRExpMEM(new IRExpBINOP('+', new IRExpTEMP(&framePtr), new IRExpCONST(machineOffset)));
	}
	int offset;
};

//���������� �� ���������
class InReg : IAccess{
	InReg() { temp = &CTemp(); };
	const IRExp* GetExp(const CTemp temp) {
		return new IRExpTEMP(&temp );
	}
	CTemp* temp;
};

// �����-��������� � ���������-��������� ����������� � �������
class IRFrame {
public:
	static const int WORD_SIZE = 4;
	IRFrame(const string name, int formalsCount) : frameName(name) {

	}
	int FormalsCount() const { return formals.size(); }
	int LocalsCount() const { return locals.size(); }
	int TempraryCount() const { return temprary.size(); }
	// ������ � ���������� ����������
	const CTemp* GetTemp(string name) {
		if (formals.find(name) != formals.end() )
			return formals.find(name)->second;
		if (locals.find(name) != locals.end())
			return locals.find(name)->second;
		if (temprary.find(name) != temprary.end())
			return temprary.find(name)->second;
	};
	/*
	CTemp* getThis(){
	//��������
		if (!formals.empty())
			return formals.begin()->second;
		if (!locals.empty())
			return locals.begin()->second;
		if (!temprary.empty())
			return locals.begin()->second;
		return nullptr;
	}
	*/
	void setFormalsTemp(string name, CTemp* temp) { formals.insert(std::pair<string, CTemp*>(name, temp)); }
	void setLocalsTemp(string name, CTemp* temp) { locals.insert(std::pair<string, CTemp*>(name, temp)); }
	void setTempraryTemp(string name, CTemp* temp) { temprary.insert(std::pair<string, CTemp*>(name, temp)); }
	void setStatements(IRStm* statements)
	{
		root = statements;
	}

	CTemp* GetFramePtr() const
	{
		return framePtr;
	}
	CTemp* GetThisPtr() const
	{
		return thisPtr;
	}
	CTemp* GetReturnPtr() const
	{
		return returnPtr;
	}
	IRStm* GetRootStm() const
	{
		return root;
	}
private:
	const string frameName;
	IRStm* root;
	std::map<string, CTemp*> formals;
	std::map<string, CTemp*> locals;
	std::map<string, CTemp*> temprary;
	//��������� �� �����
	CTemp* framePtr;
	//��������� �� �� ����� ������
	CTemp* thisPtr;
	//��������� �� ����������� ��������
	CTemp* returnPtr;
};
