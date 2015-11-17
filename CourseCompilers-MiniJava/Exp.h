#pragma once
#include "CTypes.h"
#include "Frame.h"
class IRExp : IRNode {
	IExp() {}
}

class IRExpCONST:IRExp{
	
	class IRExpCONST {
		int value;
	public:
		IRExpCONST( int _value ): value(_value) {}
	}

	class IRExpNAME:IRExp {
	public:
		const CLabel* label;
		IRExpNAME( const CLabel* _label ): label(_label) {
		}
	}
	class IRExpTEMP:IRExp {
	public:
		const CTemp* temp
		IRExpTEMP( const CTemp* _temp ):temp(_temp) {
		}
	}
	class IRExpBINOP:IRExp{
	public:
		char binop;
		const IRExp* left;
		const IRExp* right;
		IRExpBINOP( char b, const IRExp* l, const IRExp* r ): binop(b), left(l), right(r) {}
	}
	class IRExpMEM:IRExp {
	public:
		const IRExp* exp;
		IRExpMEM( const IRExp* _exp ):exp(_exp) {}
	}
	class IRExpCALL:IRExp {
	public:
		const IRExpList* arguments;
		const IRExp* function;
		IRExpCALL( const IRExp* func, const IRExpList* args ): function(func), arguments(args) {}
	}
	
	class IRExpESEQ:IRExp {
	public:
		const IRStatements* stms;
		const IRExp* exp;
		IRExpESEQ( const IRStatemens* s, const IRExp* e ): stms(s), exp(e) {}
	}
