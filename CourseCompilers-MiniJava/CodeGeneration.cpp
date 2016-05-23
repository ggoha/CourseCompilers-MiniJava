#include "CodeGeneration.h"

CCodegen::CCodegen() : instrList(0), last(0) {}

void CCodegen::MunchStm(const IRStm* s) {
	const IRStmSEQ* seq = dynamic_cast<const IRStmSEQ*>(s);
	if (seq != 0) {
		MunchStmSEQ(seq);
	}
	else {
		const IRStmMOVE* move = dynamic_cast<const IRStmMOVE*>(s);
		if (move != 0) {
			MunchMove(move->dst, move->src);
		}
		else {
			const IRStmLABEL* label = dynamic_cast<const IRStmLABEL*>(s);
			if (label != 0) {
				MunchStm(label);
			}
			else {
				const IRExp* exp = dynamic_cast<const IRExp*>(s);
				if (exp != 0) {
					const IRExpCALL* call = dynamic_cast<const IRExpCALL*>(exp);
					if (call != 0) {
						MunchExpCall(call);
					}
				}
				else {
					const IRStmJUMP* jmp = dynamic_cast<const IRStmJUMP*>(s);
					if (jmp != 0) {
						emit(new AOPER("jmp `j0\n",
							nullptr,
							nullptr,

							new CLabelList(jmp->lable, nullptr))
							);
					}
					const IRStmCJUMP* cjump = dynamic_cast<const IRStmCJUMP*>(s);
					if (cjump != 0) {
						emit(new AOPER("cmp `s0, `s1\n", nullptr,
							new CTempList(
							MunchExp(cjump->left),
							new CTempList(MunchExp(cjump->right), nullptr)
							)
							)
							);
						std::string jumpCmdName;
						if (cjump->relop == IRStmCJUMP::EQ) {
							jumpCmdName = "je";
						}
						else if (cjump->relop == IRStmCJUMP::LT) {
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

void CCodegen::MunchExpCall(const IRExpCALL* call) {
	const IRExpNAME* name = dynamic_cast<const IRExpNAME*>(call->function);
	if (name != 0) {
		CTempList* l = MunchArgs(call->arguments);
		emit(new AOPER("CALL " + name->label->Name() + "\n", IRFrame::PreColoredRegisters(), l));
	}
	else {
		const CTemp* r = MunchExp(call->function);
		CTempList* l = MunchArgs(call->arguments);
		emit(new AOPER("CALL `s0\n", IRFrame::PreColoredRegisters(), new CTempList(r, l)));
	}
}

CTempList* CCodegen::MunchArgs(const IRExpList* args) {
	CTempList* l = nullptr;
	for( int j = 0; j < args->expslist.size(); j++ ){
		if (l != nullptr) {
			l->tail = new CTempList(new CTemp(), nullptr);
			l = l->tail;
		}
		else {
			l = new CTempList(new CTemp(), nullptr);
		}
		emit(new AOPER("push `s0\n", nullptr, new CTempList(MunchExp(args->expslist[j]), nullptr)
			)
			);
	}
}


/*munchStm(EXP(CALL(e,args)))
{Temp r = munchExp(e); TempList l = munchArgs(0,args);
emit(new OPER("CALL 's0\n",calldefs,L(r,l)));}*/

void CCodegen::MunchMove(const IRExp* dst, const IRExp* src) {
	const IRExpMEM* mem = dynamic_cast<const IRExpMEM*>(dst);
	if (mem != 0) {
		MunchMove(mem, src);
	}
	else {
		const IRExpTEMP* temp = dynamic_cast<const IRExpTEMP*>(dst);
		if (temp != 0)  {
			//MOVE(IRExpTEMP(i), e2)
			MunchMove(temp, src);
		}
	}
}

void CCodegen::MunchMove(const IRExpMEM* dst, const IRExp* src) {

	const IRExpBINOP* binop = dynamic_cast<const IRExpBINOP*>(dst->exp);
	if (binop != 0) {

		const IRExpCONST* cst = dynamic_cast<const IRExpCONST*>(binop->right);
		if (cst != 0) {
			//MOVE(IRExpMEM(IRExpBINOP(PLUS,e1,IRExpCONST(i))),e2)

			emit(new AOPER("mov [`s0 " + CCodegen::opSymbols[binop->binop] + std::to_string(cst->Value()) + "],	`s1\n",
				nullptr, new CTempList(MunchExp(binop->left),
				new CTempList(MunchExp(src), nullptr)
				)
				)
				);
			return;
		}

		cst = dynamic_cast<const IRExpCONST*>(binop->left);
		if (cst != 0) {
			//MOVE(IRExpMEM(IRExpBINOP(PLUS,IRExpCONST(i),e1)),e2)
			emit(new AOPER("mov [`s0 " + CCodegen::opSymbols[binop->binop] + std::to_string(cst->Value()) + "],	`s1\n",
				nullptr, new CTempList(MunchExp(binop->right),
				new CTempList(MunchExp(src), nullptr)
				)
				)
				);
			return;
		}


	}

	//???
	const IRExpMEM* mem = dynamic_cast<const IRExpMEM*>(src);
	if (mem != 0) {
		emit(new AMOVE("mov `d0, `s0\n", MunchExp(dst->exp), MunchExp(mem->exp)
			)
			);
		return;
	}
	const IRExpCONST* cst = dynamic_cast<const IRExpCONST*>(dst->exp);
	if (cst != 0) {
		emit(new AOPER("mov [" + std::to_string(cst->Value()) + "], `s0\n", nullptr,
			new CTempList(MunchExp(src), nullptr)));
		return;
	}

	emit(new AMOVE("mov `d0, `s0\n", MunchExp(dst->exp), MunchExp(src)
		)
		);

}


void CCodegen::MunchMove(const IRExpTEMP* dst, const IRExp* src) {
	//MOVE(IRExpTEMP(i), e2)
	//???
	emit(new AOPER("mov 	`d0, `s0\n", new CTempList(dst->temp, nullptr),
		new CTempList(MunchExp(src), nullptr)));
}

void CCodegen::MunchStmSEQ(const IRStmSEQ* s) {
	MunchStm(s->left);
	MunchStm(s->right);
}


void CCodegen::MunchStm(const IRStmLABEL* label) {
	emit(new ALABEL(label->lable->Name() + ":\n", label->lable));
}

const CTemp*  CCodegen::MunchExp(const IRExp* exp) {
	const IRExpMEM* mem = dynamic_cast<const IRExpMEM*>(exp);
	if (mem != 0) {
		const IRExpBINOP* binop = dynamic_cast<const IRExpBINOP*>(mem->exp);
		if (binop != 0) {
			const IRExpCONST* cst = dynamic_cast<const IRExpCONST*>(binop->right);
			if (cst != 0) {
				//IRExpMEM(IRExpBINOP(PLUS,e1,IRExpCONST(i)))
				const CTemp* r = new const CTemp();
				emit(new AOPER("mov `d0, [`s0 " + CCodegen::opSymbols[binop->binop] + std::to_string(cst->Value()) + "]\n",
					new CTempList(r, nullptr), new CTempList(MunchExp(binop->left), nullptr)
					)
					);
				return r;
			}
			cst = dynamic_cast<const IRExpCONST*>(binop->left);
			if (cst != 0) {
				//IRExpMEM(IRExpBINOP(PLUS,IRExpCONST(i),e1))
				const CTemp* r = new const CTemp();
				emit(new AOPER("mov `d0, [`s0 " + CCodegen::opSymbols[binop->binop] + std::to_string(cst->Value()) + "]\n",
					new CTempList(r, nullptr), new CTempList(MunchExp(binop->right), nullptr)
					)
					);
				return r;
			}
		}
		const IRExpCONST* cst = dynamic_cast<const IRExpCONST*>(mem->exp);
		if (cst != 0) {
			//IRExpMEM(IRExpCONST(i))
			const CTemp* r = new CTemp();
			emit(new AOPER("mov `d0, [" + std::to_string(cst->Value()) + "]\n",
				new CTempList(r, nullptr), nullptr));
			return r;
		}
		const CTemp*r = new const CTemp();
		//IRExpMEM(e1)
		//?????
		emit(new AMOVE("mov `d0, `s0\n", r, MunchExp(mem->exp)
			)
			);
		return r;
	}

	const IRExpBINOP* binop = dynamic_cast<const IRExpBINOP*>(exp);
	if ((binop != 0)) {
		return MunchBinop(binop->left, binop->right, binop->binop);
	}
	const IRExpCONST* cst = dynamic_cast<const IRExpCONST*>(exp);
	if (cst != 0) {
		//IRExpCONST(i)
		const CTemp* r =   new CTemp();
		emit(new AOPER("mov `d0, " + std::to_string(cst->Value()) + "\n", new CTempList(r, nullptr), nullptr)
			);
		return r;
	}
	const IRExpTEMP* t = dynamic_cast<const IRExpTEMP*>(exp);
	if (t != 0) {
		return t->temp;
	}
	const IRExpCALL* call = dynamic_cast<const IRExpCALL*>(exp);
	if (call != 0) {
		MunchExpCall(call);
		return IRFrame::CallerSaveRegister();
	}




}

const CTemp* CCodegen::MunchBinop(const IRExpCONST* cst, const IRExp* exp, ArithmeticOpType binop)
{

	const CTemp* r = new const CTemp();
	emit(new AMOVE("move `d0, `s0\n", r, MunchExp(exp)
		)
		);
	emit(new AOPER(CCodegen::opNames[binop] + " `d0, " + std::to_string(cst->Value()) + "\n", new CTempList(r, nullptr),
		new CTempList(r, nullptr)
		)
		);
	return r;
}

const CTemp*:: CCodegen::MunchBinop( const IRExp* src, const IRExp* exp, ArithmeticOpType binop)
{
	const IRExpCONST* cst = dynamic_cast<const IRExpCONST*>(src);
	if (cst != 0) {
		return MunchBinop(cst, exp, binop);
	}
	cst = dynamic_cast<const IRExpCONST*>(exp);
	if (cst != 0){
		return MunchBinop(cst, src, binop);
	}
	//IRExpBINOP(PLUS,e1,e2)
    const CTemp* r = new const CTemp();
	emit(new AMOVE("mov `d0, `s0\n", r, MunchExp(src)
		)
		);
	emit(new AOPER(CCodegen::opNames[binop] + " `d0, `s1\n", new CTempList(r, nullptr),
		new CTempList(r, new CTempList(MunchExp(exp), nullptr))
		)
		);
	return r;
}

CInstrList* CCodegen::Codegen(const IRStm* s) {
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
		Temp::CDefaultMap* defMap = new Temp::CDefaultMap();
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
			blockInstructions.push_back(new CInstrList(*instructs));
		}
	}
}