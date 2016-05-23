#include <string>
#include "IRTemp.h"
#include "TempMap.h"

class CTargets {
public:
	CTargets(CLabelList* _labels);
	CLabelList* labels;

};

class CInstr {
public:
	CInstr(const std::string& a);
	std::string assemCmd;

	virtual CTempList* use() = 0;
	virtual CTempList* def() = 0;
	virtual CTargets* jumps() = 0;

	const CTemp* getTemp(CTempList* l, int tempNumber);
	const CLabel* getLabel(CLabelList* l, int tempNumber);
	std::string format(CTempMap* m);
};

class CInstrList {
public:
	CInstrList(CInstr* _head, CInstrList* _tail);
	CInstr* head;
	CInstrList* tail;
};

class ALABEL : public CInstr {
public:
	ALABEL(const std::string& a, const CLabel* l);
	const CLabel* label;

	CTempList* use();
	CTempList* def();
	CTargets* jumps();
};

class AMOVE : public CInstr {
public:
	const CTemp* dst;
	const CTemp* src;
	AMOVE(const std::string& a, const CTemp* d, const CTemp* s);

	CTempList* use();
	CTempList* def();
	CTargets* jumps();
};

class AOPER : public CInstr {
public:
	CTempList* dst;
	CTempList* src;
	CTargets* jump;

	AOPER(const std::string& a, CTempList* d, CTempList* s, CLabelList* j);
	AOPER(const std::string& a, CTempList* d, CTempList* s);

	CTempList* use();
	CTempList* def();
	CTargets* jumps();
};