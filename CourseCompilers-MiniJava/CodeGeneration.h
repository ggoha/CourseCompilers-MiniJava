#pragma once                                                   
#include "iostream"
#include "IRStm.h"
#include "IRExp.h"
#include "IRTemp.h"
#include "IRFrame.h"
#include "Assembler.h"
#include "TempMap.h"
#define ArithmeticOpType char

class CCodegen {
public:


	CCodegen();


	void MunchStm(const IRStm* s);

	void MunchStmSEQ(const IRStmSEQ* s);


	void MunchMove(const IRExp* dst, const IRExp* src);
	void MunchMove(const IRExpMEM* dst, const IRExp* src);
	void MunchMove(const IRExpTEMP* dst, const IRExp* src);
	void MunchStm(const IRStmLABEL* label);
	void MunchExpCall(const IRExpCALL* call);
	CTempList* MunchArgs(const IRExpList* explist);

	const CTemp* MunchExp(const IRExp* exp);
	const CTemp* MunchBinop(const IRExpCONST* cst, const IRExp* exp, ArithmeticOpType binop);
	const CTemp* MunchBinop(const IRExp* src, const IRExp* exp, ArithmeticOpType binop);

	CInstrList* Codegen(const IRStm* s);
private:
	CInstrList* instrList;
	CInstrList* last;
	static std::vector<std::string> opNames;
	static std::vector<std::string> opSymbols;
	static std::vector<std::string> initOpNames();
	static std::vector<std::string> initOpSymbols();
	void emit(CInstr* instr);
};
void GenerateCode(ostream &out, const vector<IRStmLIST*> &blocks,
	vector<CInstrList*> &blockInstructions);
