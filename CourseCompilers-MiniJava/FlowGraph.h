#include <set>
#include "Graph.h"
#include "IRTemp.h"
#include "Assembler.h"

class CFlowGraph : public CGraph<int, CInstr*> {
public:
	CFlowGraph() : CGraph<int, CInstr*>() {}
	void Build(const CInstrList* instructions);
	CInstr* GetInstr(int node);
	set<const CTemp*> GetDef(int node);
	set<const CTemp*> GetUse(int node);
	bool isMove(int node);
};