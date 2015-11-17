#pragma once
#include "CTypes.h"

class IRExp : IRNode {
	IExp() {}
}

class CONST:IRExp{
	
	class CONST {
		CONST( int value ) {

		}
	}

	class NAME:IRExp {
		NAME( CLabel* label ) {

		}
	}
	class TEMP:IRExp {
		TEMP( CTemp* temp ) {

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
