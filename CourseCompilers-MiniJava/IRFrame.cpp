#include "IRExp.h"
#include "IRTemp.h"
namespace Frame {
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
		CFrame(const Symbol::CSymbol* name, int formalsCount);
		// ������ � ���������� ����������
		int FormalsCount() const { return formals.size(); }
		const IAccess* Formal(size_t index) const;

	private:
		// ...
	};
}

