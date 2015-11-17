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
		CExp* left;
		CExp* right;
		IRExpBINOP( char b, const CExp* l, const CExp* r ) {
			binop = b; left = l; right = r;
		}
	}
	class IRExpMEM:IRExp {
		IRExpMEM( CExp* exp ) {

		}
	}
	class IRExpCALL:IRExp {
		IRExpCALL( const CExp* func, CExpList* args ) {

		}
	}
	
	class IRExpESEQ:IRExp {
		IRExpESEQ( CStatement stm, CExp exp ) {

		}
	}
