#include "IRExp.h"
#include "map"
using namespace std;

class IRFrame;
class InFrame;
class InReg; 

// Переменная фрейма
class IAccess {
public:
	virtual const IRExp* GetExp(const CTemp* framePtr) const = 0;
	virtual ~IAccess() {}
};


// Класс-контейнер с платформо-зависимой информацией о функции
class IRFrame {
public:

	static map<std::string, const CTemp*> allRegisters;
	static const int WORD_SIZE = 4;
	IRFrame(const string name, int formalsCount) : frameName(name) {
		thisPtr = new CTemp("this");
		returnPtr = new CTemp("return");
	}
	int FormalsCount() const { return formals.size(); }
	int LocalsCount() const { return locals.size(); }
	int TempraryCount() const { return temprary.size(); }
	// Доступ к формальным параметрам
	const CTemp* GetTemp(string name) {
		if (formals.find(name) != formals.end() )
			return formals.find(name)->second;
		if (locals.find(name) != locals.end())
			return locals.find(name)->second;
		if (temprary.find(name) != temprary.end())
			return temprary.find(name)->second;
		throw invalid_argument(string("no such temp ") + name);
	};
	CTemp* getThis()const {
	//заглушка
		return thisPtr;
	}
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
	const string frameName;

	static const CTemp* CallerSaveRegister() {
		return allRegisters["ecx"];
	}

	static CTempList* PreColoredRegisters() {
		return new CTempList(allRegisters["ecx"], new CTempList(allRegisters["ebp"],
			new CTempList(allRegisters["esp"], nullptr)));
	}
private:

	static std::map<std::string, const CTemp*> registersInit();
	IRStm* root;
	std::map<string, CTemp*> formals;
	std::map<string, CTemp*> locals;
	std::map<string, CTemp*> temprary;
	//Указатель на фрейм
	CTemp* framePtr;
	//Указатель на то откуа вывали
	CTemp* thisPtr;
	//Указатель на возврааемое значение
	CTemp* returnPtr;
};

//Реализация на стеке
class InFrame : IAccess {
	InFrame(int _offset) : offset(_offset) {};
	IRExp* GetExp(const CTemp framePtr) {
		int machineOffset = offset * IRFrame::WORD_SIZE;
		return (IRExp*)new IRExpMEM( (IRExp*)new IRExpBINOP('+', (IRExp*)new IRExpTEMP(&framePtr), (IRExp*)new IRExpCONST(machineOffset)));
	}
	int offset;
};

//Реализация на регистрах
class InReg : IAccess {
	InReg() { temp = &CTemp(); };
	IRExp* GetExp(const CTemp temp) {
		return (IRExp*)(new IRExpTEMP(&temp));
	}
	CTemp* temp;
};
