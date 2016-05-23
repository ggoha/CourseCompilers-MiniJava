#pragma once                                                   
#include "iostream"
#include "IRStm.h"
#include "IRExp.h"
#include "Assembler.h"

class CCodegen {
public:


	CCodegen();


	void MunchStm(IRStm* s);

	void MunchStm(IRStmSEQ* s);


	void MunchMove(IRExp* dst, IRExp* src);
	void MunchMove(IRExpMEM* dst, IRExp* src);
	void MunchMove(IRExpTEMP* dst, IRExp* src);
	void MunchStm(IRStmLABEL* label);
	void MunchExpCall(IRExpCALL* call);
	CTempList* MunchArgs(shared_ptr<ExpList>);

	const CTemp*  MunchExp(IRExp* exp);
	const CTemp* MunchBinop(IRExpCONST* cst, IRExp* exp, IRExpBINOP binop);
	const CTemp* MunchBinop(IRExp* src, IRExp* exp, IRExpBINOP binop);

	CInstrList* Codegen(IRStm* s);
private:
	CInstrList* instrList;
	CInstrList* last;
	static std::vector<std::string> opNames;
	static std::vector<std::string> opSymbols;
	static std::vector<std::string> initOpNames();
	static std::vector<std::string> initOpSymbols();
	void emit(CInstr* instr);
};
