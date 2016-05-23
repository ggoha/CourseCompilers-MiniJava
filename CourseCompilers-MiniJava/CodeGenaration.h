#pragma once                                                   
#include "iostream"
#include "IRStm.h"
#include "IRExp.h"
class templateBuilder{
public:
	void visit{
}
};



/*class Operation{
public:
	virtual void accept();
}

class Add :Operation{
public:	
	void accept()
};

*/

void munchMove(IRExpMEM* dst, IRExp* src) {
	// MOVE(MEM(BINOP(PLUS, e1, CONST(i ))), e2)
	if (dynamic_cast<IRExpBINOP*>(dst->exp) != 0 && ((IRExpBINOP*)dst->exp)->binop == '+'
		&& (dynamic_cast<IRExpCONST*>( ((IRExpBINOP*)dst)->right ) != 0 )
	{
		munchExp(((BINOP)dst.exp).left); munchExp(src); emit("STORE");
	}
	// MOVE(MEM(BINOP(PLUS, CONST(i ), e1)), e2)
	else if (dst.exp instanceof BINOP && ((BINOP)dst.exp).oper == BINOP.PLUS
		&& ((BINOP)dst.exp).left instanceof CONST)
	{
		munchExp(((BINOP)dst.exp).right); munchExp(src); emit("STORE");
	}
	// MOVE(MEM(e1), MEM(e2))
	else if (src instanceof MEM)
	{
		munchExp(dst.exp); munchExp(((MEM)src).exp); emit("MOVEM");
	}
	// MOVE(MEM(e1), e2)
	else
	{
		munchExp(dst.exp); munchExp(src); emit("STORE");
	}
}
void munchMove(TEMP dst, Exp src) {
	// MOVE(TEMP(t1), e)
	munchExp(src); emit("ADD");
}
void munchMove(Exp dst, Exp src) {
	// MOVE(d, e)
	if (dst instanceof MEM) munchMove((MEM)dst, src);
	else if (dst instanceof TEMP) munchMove((TEMP)dst, src);
}
void munchStm(Stm s) {
	if (s instanceof MOVE) munchMove(((MOVE)s).dst, ((MOVE)s).src);
	...
		// CALL, JUMP, CJUMP unimplemented here
}

/**
void munchMove(MEM dst, Exp src) {
	// MOVE(MEM(BINOP(PLUS, e1, CONST(i ))), e2)
	if (dst.exp instanceof BINOP && ((BINOP)dst.exp).oper == BINOP.PLUS
		&& ((BINOP)dst.exp).right instanceof CONST)
	{
		munchExp(((BINOP)dst.exp).left); munchExp(src); emit("STORE");
	}
	// MOVE(MEM(BINOP(PLUS, CONST(i ), e1)), e2)
	else if (dst.exp instanceof BINOP && ((BINOP)dst.exp).oper == BINOP.PLUS
		&& ((BINOP)dst.exp).left instanceof CONST)
	{
		munchExp(((BINOP)dst.exp).right); munchExp(src); emit("STORE");
	}
	// MOVE(MEM(e1), MEM(e2))
	else if (src instanceof MEM)
	{
		munchExp(dst.exp); munchExp(((MEM)src).exp); emit("MOVEM");
	}
	// MOVE(MEM(e1), e2)
	else
	{
		munchExp(dst.exp); munchExp(src); emit("STORE");
	}
}
void munchMove(TEMP dst, Exp src) {
	// MOVE(TEMP(t1), e)
	munchExp(src); emit("ADD");
}
void munchMove(Exp dst, Exp src) {
	// MOVE(d, e)
	if (dst instanceof MEM) munchMove((MEM)dst, src);
	else if (dst instanceof TEMP) munchMove((TEMP)dst, src);
}
void munchStm(Stm s) {
	if (s instanceof MOVE) munchMove(((MOVE)s).dst, ((MOVE)s).src);
	...
		// CALL, JUMP, CJUMP unimplemented here
}
void munchExp(Exp)
MEM(BINOP(PLUS, e1, CONST(i))) ⇒ munchExp(e1); emit("LOAD");
MEM(BINOP(PLUS, CONST(i), e1)) ⇒ munchExp(e1); emit("LOAD");
MEM(CONST(i)) ⇒ emit("LOAD");
MEM(e1) ⇒ munchExp(e1); emit("LOAD");
BINOP(PLUS, e1, CONST(i)) ⇒ munchExp(e1); emit("ADDI");
BINOP(PLUS, CONST(i), e1) ⇒ munchExp(e1); emit("ADDI");
CONST(i) ⇒ munchExp(e1); emit("ADDI");
BINOP(PLUS, e1, CONST(i)) ⇒ munchExp(e1); emit("ADD");
TEMP(t) ⇒{}
*/