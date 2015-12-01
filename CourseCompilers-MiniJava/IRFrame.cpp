#include "IRExp.h"
#include "IRTemp.h"
#include "map"
// ���������� ������
class IAccess {
public:
	virtual const IRExp* GetExp(const CTemp* framePtr) const = 0;
	virtual ~IAccess() {}
};

//���������� �� �����
class InFrame : IAccess{
	const IRExp* GetExp(const CTemp k) { IRExpMEM(IRExpBINOP()); }
};

//���������� �� ���������
class InReg : IAccess{
	const IRExp* GetExp(const CTemp k) {}
};

// �����-��������� � ���������-��������� ����������� � �������
class CFrame {
public:
	CFrame(const string name, int formalsCount);
	// ������ � ���������� ����������
	int FormalsCount() const { return formals.size(); }
	//		const IAccess* Formal(size_t index) const {formals[]};
	const CTemp* GetTemp(string name) { return formals.find(name)->second; };
	void setTemp(string name, CTemp* temp) { formals.insert(std::pair<string, CTemp*>(name, temp)); }

private:
	std::map<string, CTemp*> formals;
};

