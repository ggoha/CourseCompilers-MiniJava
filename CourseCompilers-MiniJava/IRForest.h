#pragma once
#include "IRBuilder.h"

class CIRForest
{
	vector<IRNode* > IRForest;
	vector< IRFrame* > Frames;
public:

	void build(CProgram* program, CTable* symbolTabel)
	{
		CIRBuilder *iRBuilder = new CIRBuilder(program->mainClass->id, "main", symbolTabel);
		iRBuilder->visit(program->mainClass);
		IRForest.push_back(iRBuilder->getRoot());
		Frames.push_back(iRBuilder->getFrame());
		delete iRBuilder;
		for (int i = 0; i < program->classDecls->classes.size(); ++i)
		{
			for (int j = 0; j < program->classDecls->classes[i]->methodDecls->methods.size(); ++j)
			{
				iRBuilder = new CIRBuilder(program->classDecls->classes[i]->id, program->classDecls->classes[i]->methodDecls->methods[j]->id, symbolTabel);
				iRBuilder->visit(program->classDecls->classes[i]->methodDecls->methods[j]);
				IRForest.push_back(iRBuilder->getRoot());
				Frames.push_back(iRBuilder->getFrame());
				delete iRBuilder;
			}
		};


	}


};
