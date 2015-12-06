#include "IRExp.h"
#include "map"
using namespace std;



// Переменная фрейма
class IAccess {
public:
	virtual const IRExp* GetExp(const CTemp* framePtr) const = 0;
	virtual ~IAccess() {}
};

//Реализация на стеке
class InFrame : IAccess{
	const IRExp* GetExp(const CTemp k) { IRExpMEM(IRExpBINOP()); }
};

//Реализация на регистрах
class InReg : IAccess{
	const IRExp* GetExp(const CTemp k) {}
};

// Класс-контейнер с платформо-зависимой информацией о функции
class IRFrame {
public:
	IRFrame(const string name, int formalsCount);
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
	};
	CTemp* getThis(){
	//заглушка
		if (!formals.empty())
			return formals.begin()->second;
		if (!locals.empty())
			return locals.begin()->second;
		if (!temprary.empty())
			return locals.begin()->second;
		return nullptr;
	}
	void setFormalsTemp(string name, CTemp* temp) { formals.insert(std::pair<string, CTemp*>(name, temp)); }
	void setLocalsTemp(string name, CTemp* temp) { locals.insert(std::pair<string, CTemp*>(name, temp)); }
	void setTempraryTemp(string name, CTemp* temp) { temprary.insert(std::pair<string, CTemp*>(name, temp)); }

private:
	std::map<string, CTemp*> formals;
	std::map<string, CTemp*> locals;
	std::map<string, CTemp*> temprary;
};
