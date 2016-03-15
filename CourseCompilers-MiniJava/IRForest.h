#pragma once
#include "IRBuilder.h"

class IRForest
{
	vector<IRNode* > iRForest;
	vector< IRFrame* > Frames;
public:

	void build(CProgram* program, CTable* symbolTabel)
	{
		CIRBuilder *iRBuilder = new CIRBuilder(program->mainClass->id, "main", symbolTabel);
		iRBuilder->visit(program->mainClass);
		iRForest.push_back(iRBuilder->getRoot());
		Frames.push_back(iRBuilder->getFrame());
		delete iRBuilder;
		for (unsigned i = 0; i < program->classDecls->classes.size(); ++i)
		{
			for (unsigned j = 0; j < program->classDecls->classes[i]->methodDecls->methods.size(); ++j)
			{
				iRBuilder = new CIRBuilder(program->classDecls->classes[i]->id, program->classDecls->classes[i]->methodDecls->methods[j]->id, symbolTabel);
				iRBuilder->visit(program->classDecls->classes[i]->methodDecls->methods[j]);
				iRForest.push_back(iRBuilder->getRoot());
				Frames.push_back(iRBuilder->getFrame());
				delete iRBuilder;
			}
		};


	}


};
