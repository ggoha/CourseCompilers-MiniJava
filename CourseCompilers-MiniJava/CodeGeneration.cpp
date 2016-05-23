#include "CodeGeneration.h"
#include <iostream>

CCodegen::CCodegen() : instrList(0), last(0) {}

void CCodegen::MunchStm(IRStm* s) {
	IRStmSEQ* seq = dynamic_cast<IRStmSEQ*>(s);
	if (seq != 0) {
		MunchStm(seq);
	}
	else {
		IRStmMOVE* move = dynamic_cast<IRStmMOVE*>(s);
		if (move != 0) {
			MunchMove(move->dst, move->src);
		}
		else {
			IRStmLABEL* label = dynamic_cast<IRStmLABEL*>(s);
			if (label != 0) {
				MunchStm(label);
			}
			else {
				IRExp* exp = dynamic_cast<IRExp*>(s);
				if (exp != 0) {
					IRExpCALL* call = dynamic_cast<IRExpCALL*>(exp->exp);
					if (call != 0) {
						MunchExpCall(call);
					}
				}
				else {
					IRStmJUMP* jmp = dynamic_cast<IRStmJUMP*>(s);
					if (jmp != 0) {
						emit(new AOPER("jmp `j0\n",
							nullptr,
							nullptr,

							new CLabelList(jmp->target, nullptr))
							);
					}
					IRStmCJUMP* cjump = dynamic_cast<IRStmCJUMP*>(s);
					if (cjump != 0) {
						emit(new AOPER("cmp `s0, `s1\n", nullptr,
							new CTempList(
							MunchExp(cjump->left),
							new CTempList(MunchExp(cjump->right), nullptr)
							)
							)
							);
						std::string jumpCmdName;
						if (cjump->relop == EQ) {
							jumpCmdName = "je";
						}
						else if (cjump->relop == LT) {
							jumpCmdName = "jl";
						}
						emit(new AOPER(jumpCmdName + "   `j0\n", nullptr, nullptr,
							new CLabelList(cjump->iftrue, new CLabelList(cjump->iffalse, nullptr))));
					}

				}
			}
		}
	}
}

void CCodegen::MunchExpCall(IRExpCALL* call) {
	IRExpNAME* name = dynamic_cast<IRExpNAME*>(call->func);
	if (name != 0) {
		CTempList* l = MunchArgs(call->args);
		emit(new AOPER("CALL " + name->label->Name() + "\n", CFrame::PreColoredRegisters(), l));
	}
	else {
		const CTemp* r = MunchExp(call->func);
		CTempList* l = MunchArgs(call->args);
		emit(new AOPER("CALL `s0\n", CFrame::PreColoredRegisters(), new CTempList(r, l)));
	}
}

CTempList* CCodegen::MunchArgs(IRExpList* args) {
	CTempList* l = nullptr;
	for( int j = 0; j < args->expslist.size(); j++ ){
		if (l != nullptr) {
			l->tail = new CTempList(std::make_shared<CTemp>(), nullptr);
			l = l->tail;
		}
		else {
			l = new CTempList(std::make_shared<CTemp>(), nullptr);
		}
		emit(new AOPER("push `s0\n", nullptr, new CTempList(MunchExp(args->expslist[i]), nullptr)
			)
			);
	}
}


/*munchStm(EXP(CALL(e,args)))
{Temp r = munchExp(e); TempList l = munchArgs(0,args);
emit(new OPER("CALL 's0\n",calldefs,L(r,l)));}*/

void CCodegen::MunchMove(IExp* dst, IExp* src) {
	IRExpMEM* mem = dynamic_cast<IRExpMEM*>(dst);
	if (mem != 0) {
		MunchMove(mem, src);
	}
	else {
		IRExpTEMP* temp = dynamic_cast<IRExpTEMP*>(dst);
		if (temp != 0)  {
			//MOVE(IRExpTEMP(i), e2)
			MunchMove(temp, src);
		}
	}
}

void CCodegen::MunchMove(IRExpMEM* dst, IExp* src) {

	IRExpBINOP* binop = dynamic_cast<IRExpBINOP*>(dst->exp);
	if (binop != 0) {

		IRExpCONST* cst = dynamic_cast<IRExpCONST*>(binop->right);
		if (cst != 0) {
			//MOVE(IRExpMEM(IRExpBINOP(PLUS,e1,IRExpCONST(i))),e2)

			emit(new AOPER("mov [`s0 " + CCodegen::opSymbols[binop->binop] + std::to_string(cst->value) + "],	`s1\n",
				nullptr, new CTempList(MunchExp(binop->left),
				new CTempList(MunchExp(src), nullptr)
				)
				)
				);
			return;
		}

		cst = dynamic_cast<IRExpCONST*>(binop->left);
		if (cst != 0) {
			//MOVE(IRExpMEM(IRExpBINOP(PLUS,IRExpCONST(i),e1)),e2)
			emit(new AOPER("mov [`s0 " + CCodegen::opSymbols[binop->binop] + std::to_string(cst->value) + "],	`s1\n",
				nullptr, new CTempList(MunchExp(binop->right),
				new CTempList(MunchExp(src), nullptr)
				)
				)
				);
			return;
		}


	}

	//???
	IRExpMEM* mem = dynamic_cast<IRExpMEM*>(src);
	if (mem != 0) {
		emit(new AMOVE("mov `d0, `s0\n", MunchExp(dst->exp), MunchExp(mem->exp)
			)
			);
		return;
	}
	IRExpCONST* cst = dynamic_cast<IRExpCONST*>(dst->exp);
	if (cst != 0) {
		emit(new AOPER("mov [" + std::to_string(cst->value) + "], `s0\n", nullptr,
			new CTempList(MunchExp(src), nullptr)));
		return;
	}

	emit(new AMOVE("mov `d0, `s0\n", MunchExp(dst->exp), MunchExp(src)
		)
		);

}


void CCodegen::MunchMove(IRExpTEMP* dst, IExp* src) {
	//MOVE(IRExpTEMP(i), e2)
	//???
	emit(new AOPER("mov 	`d0, `s0\n", new CTempList(dst->temp, nullptr),
		new CTempList(MunchExp(src), nullptr)));
}

void CCodegen::MunchStm(SEQ* s) {
	MunchStm(s->left);
	MunchStm(s->right);
}


void CCodegen::MunchStm(LABEL* label) {
	emit(new ALABEL(label->label->Name() + ":\n", label->label));
}

const Temp::CTemp*  CCodegen::MunchExp(IExp* exp) {
	IRExpMEM* mem = dynamic_cast<IRExpMEM*>(exp);
	if (mem != 0) {
		IRExpBINOP* binop = dynamic_cast<IRExpBINOP*>(mem->exp);
		if (binop != 0) {
			IRExpCONST* cst = dynamic_cast<IRExpCONST*>(binop->right);
			if (cst != 0) {
				//IRExpMEM(IRExpBINOP(PLUS,e1,IRExpCONST(i)))
				const CTemp* r = const CTemp*;
				emit(new AOPER("mov `d0, [`s0 " + CCodegen::opSymbols[binop->binop] + std::to_string(cst->value) + "]\n",
					new CTempList(r, nullptr), new CTempList(MunchExp(binop->left), nullptr)
					)
					);
				return r;
			}
			cst = dynamic_cast<IRExpCONST*>(binop->left);
			if (cst != 0) {
				//IRExpMEM(IRExpBINOP(PLUS,IRExpCONST(i),e1))
				const CTemp* r = make_shared<const CTemp>();
				emit(new AOPER("mov `d0, [`s0 " + CCodegen::opSymbols[binop->binop] + std::to_string(cst->value) + "]\n",
					new CTempList(r, nullptr), new CTempList(MunchExp(binop->right), nullptr)
					)
					);
				return r;
			}
		}
		IRExpCONST* cst = dynamic_cast<IRExpCONST*>(mem->exp);
		if (cst != 0) {
			//IRExpMEM(IRExpCONST(i))
			const CTemp* r = new CTemp();
			emit(new AOPER("mov `d0, [" + std::to_string(cst->value) + "]\n",
				new CTempList(r, nullptr), nullptr));
			return r;
		}
		shared_ptr<const CTemp> r = make_shared<const CTemp>();
		//IRExpMEM(e1)
		//?????
		emit(new AMOVE("mov `d0, `s0\n", r, MunchExp(mem->exp)
			)
			);
		return r;
	}

	IRExpBINOP* binop = dynamic_cast<IRExpBINOP*>(exp);
	if ((binop != 0)) {
		return MunchBinop(binop->left, binop->right, binop->binop);
	}
	IRExpCONST* cst = dynamic_cast<IRExpCONST*>(exp);
	if (cst != 0) {
		//IRExpCONST(i)
		const CTemp* r =   new CTemp();
		emit(new AOPER("mov `d0, " + std::to_string(cst->value) + "\n", new CTempList(r, nullptr), nullptr)
			);
		return r;
	}
	IRExpTEMP* t = dynamic_cast<IRExpTEMP*>(exp);
	if (t != 0) {
		return t->temp;
	}
	IRExpCALL* call = dynamic_cast<IRExpCALL*>(exp);
	if (call != 0) {
		MunchExpCall(call);
		return CFrame::CallerSaveRegister();
	}




}

shared_ptr<const Temp::CTemp> CCodegen::MunchBinop(
	IRExpCONST* cst,
	IExp* exp,
	ArithmeticOpType binop)
{

	shared_ptr<const CTemp> r = make_shared<const CTemp>();
	emit(new AMOVE("move `d0, `s0\n", r, MunchExp(exp)
		)
		);
	emit(new AOPER(CCodegen::opNames[binop] + " `d0, " + std::to_string(cst->value) + "\n", new CTempList(r, nullptr),
		new CTempList(r, nullptr)
		)
		);
	return r;
}

shared_ptr<const Temp::CTemp> CCodegen::MunchBinop(
	IRTree::IExp* src, IRTree::IExp* exp,
	ArithmeticOpType binop)
{
	IRExpCONST* cst = dynamic_cast<IRExpCONST*>(src);
	if (cst != 0) {
		return MunchBinop(cst, exp, binop);
	}
	cst = dynamic_cast<IRExpCONST*>(exp);
	if (cst != 0){
		return MunchBinop(cst, src, binop);
	}
	//IRExpBINOP(PLUS,e1,e2)
	shared_ptr<const CTemp> r = make_shared<const CTemp>();
	emit(new AMOVE("mov `d0, `s0\n", r, MunchExp(src)
		)
		);
	emit(new AOPER(CCodegen::opNames[binop] + " `d0, `s1\n", new CTempList(r, nullptr),
		new CTempList(r, new CTempList(MunchExp(exp), nullptr))
		)
		);
	return r;
}

CInstrList* CCodegen::Codegen(IStm* s) {
	CInstrList* l;
	MunchStm(s);
	l = instrList;
	last = 0;
	instrList = last;
	return l;
}

void CCodegen::emit(CInstr* instr) {
	if (last != nullptr) {
		last->tail = new CInstrList(instr, 0);
		last = last->tail;
	}
	else {
		instrList = new CInstrList(instr, 0);
		last = instrList;
	}
}


std::vector<std::string> CCodegen::initOpNames() {
	std::vector<std::string> names;
	names.push_back("add");
	names.push_back("sub");
	names.push_back("mul");
	names.push_back("div");
	return names;
}
std::vector<std::string> CCodegen::initOpSymbols() {
	std::vector<std::string> names;
	names.push_back("+");
	names.push_back("-");
	names.push_back("*");
	names.push_back("/");
	return names;
}

std::vector<std::string> CCodegen::opNames = CCodegen::initOpNames();
std::vector<std::string> CCodegen::opSymbols = CCodegen::initOpSymbols();


namespace CodeGenerator {
	void GenerateCode(ostream &out, const vector<IRStmLIST*> &blocks,
		vector<CInstrList*> &blockInstructions) {
		CCodegen generator;
		CDefaultMap* defMap = new CDefaultMap();
		for (int i = 0; i < blocks.size(); ++i) {
			CInstrList* instructs = 0;
			out << "===========================" << endl;
			IRStmLIST* curBlock = blocks[i];
			for (int j = 0; j < curBlock->stms.size(); j++){
				instructs = generator.Codegen(curBlock->stms[j]);
				while (instructs != 0) {
					if (instructs->head != 0) {
						out << instructs->head->format(defMap);
					}
					instructs = instructs->tail;
				}
			}
			blockInstructions.push_back(CInstrList*(instructs));
		}
	}
}