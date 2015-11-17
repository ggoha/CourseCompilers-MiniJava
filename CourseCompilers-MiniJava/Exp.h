#pragma once
#include "CTypes.h"

class IRExp : IRNode {
	IExp() {}
}

class IRExpCONST:IRExp{
	
	class IRExpCONST {
		IRExpCONST( int value ) {

		}
	}

	class IRExpNAME:IRExp {
		IRExpNAME( CLabel* label ) {

		}
	}
	class IRExpTEMP:IRExp {
		IRExpTEMP( CTemp* temp ) {

		}
	}
	class IRExpBINOP:IRExp{
	public:
		char binop;
		const IRExp* left;
		const IRExp* right;
		IRExpBINOP( char b, const IRExp* l, const IRExp* r ) {
			binop = b; left = l; right = r;
		}
	}
	class IRExpMEM:IRExp {
		IRExpMEM( CExp* exp ) {
			 IRExp* func;
			 IRExpList* args;
			 IRExpCALL( IRExp* f, IRExpList* a ) { func = f; args = a; }
		}
	}
	class IRExpCALL:IRExp {
		IRExpCALL( const CExp* func, CExpList* args ) {

		}
	}
	
	class IRExpESEQ:IRExp {
		IRExpESEQ( CStatement stm, IRExpexp ) {

		}
	}
