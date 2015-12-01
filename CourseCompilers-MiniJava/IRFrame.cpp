#include "IRExp.h"
#include "IRTemp.h"
#include "map"
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
class CFrame {
public:
	CFrame(const string name, int formalsCount);
	// Доступ к формальным параметрам
	int FormalsCount() const { return formals.size(); }
	//		const IAccess* Formal(size_t index) const {formals[]};
	const CTemp* GetTemp(string name) { return formals.find(name)->second; };
	void setTemp(string name, CTemp* temp) { formals.insert(std::pair<string, CTemp*>(name, temp)); }

private:
	std::map<string, CTemp*> formals;
};

