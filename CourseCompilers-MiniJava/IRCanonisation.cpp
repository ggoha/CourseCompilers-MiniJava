#include "IRCanonisation.h"
#include "IRStm.h"
#include "IRExp.h"

void IRCanonizer::visit(const IRStmLIST* n){

	for (int i = 0; i < n->stms.size(); ++i)
	{
		auto node = dynamic_cast<const IRStmLIST*>(n->stms[i]);
		if (node != nullptr)
		{
			node->accept(this);
		}
		else
		{
			n->stms[i]->accept(this);
			stmList->stms.push_back(LastNodeAsIRStm());			
		}
	}
};

void IRCanonizer::visit(const IRExpMEM *n){
	n->exp->accept(this);
	lastNode = new IRExpMEM(LastNodeAsIRExp());
};

void IRCanonizer::visit(const IRExpBINOP* n){
	n->left->accept(this);
	auto left = LastNodeAsIRExp();
	n->right->accept(this);
	auto right = LastNodeAsIRExp();
	lastNode = new IRExpBINOP(n->binop, left, right);
};

void IRCanonizer::visit(const IRExpNAME* n){
	lastNode = new IRExpNAME(n->label);
	
};

void IRCanonizer::visit(const IRExpTEMP* n){
	lastNode = new IRExpTEMP(n->temp);
	
};

void IRCanonizer::visit(const IRExpCONST *n){
	lastNode = new IRExpCONST(n->Value());
	
};

void IRCanonizer::visit(const IRStmMOVE *n){
	n->dst->accept(this);
	isInsideExp = false;
	auto dst = LastNodeAsIRExp();
	n->src->accept(this);
	isInsideExp = false;
	auto src = LastNodeAsIRExp();
	lastNode = new IRStmMOVE(dst, src);
	isInsideExp = true;
};

void IRCanonizer::visit(const IRStmEXP *n){
	n->exp->accept(this);
	lastNode = new IRStmEXP(LastNodeAsIRExp());
};

void IRCanonizer::visit(const IRStmCJUMP *n){
	n->left->accept(this);
	auto left = LastNodeAsIRExp();
	n->right->accept(this);
	auto right = LastNodeAsIRExp();
	lastNode = new IRStmCJUMP(n->relop, left, right, n->iftrue, n->iffalse);
};


void IRCanonizer::visit(const IRStmLABEL *n){
	lastNode = new IRStmLABEL(n->lable);
};

void IRCanonizer::visit(const IRExpList *n){
	IRExpList* el = new IRExpList();
	for (int i = 0; i < n->expslist.size(); i++){
		n->expslist[i]->accept(this);
		el->expslist.push_back(LastNodeAsIRExp());
	}
	lastNode = el;

};

void IRCanonizer::visit(const IRExpCALL* n){
	n->function->accept(this);
	const IRExp* function = LastNodeAsIRExp();
	n->arguments->accept(this);
	const IRExpList* arguments = (IRExpList*)LastNodeAsIRExp();
	IRExpCALL* expcall = new IRExpCALL(function, arguments);
	lastNode = expcall;
}


void IRCanonizer::visit(const IRStmJUMP* n){
	lastNode = new IRStmJUMP(n->lable);
}

const IRExp* IRCanonizer::LastNodeAsIRExp() {
	const IRExp* res = dynamic_cast<const IRExp*>(getLastNode());
	if (res == NULL)
		 throw invalid_argument("can't cast lastNode to IRExp");
	return res;
}

const IRStm* IRCanonizer::LastNodeAsIRStm() {
	const IRStm* res = dynamic_cast<const IRStm*>(getLastNode());
	if (res == NULL)
		 throw invalid_argument("can't cast lastNode to IRStm");
	return res;
}




const IRNode* IRCanonizer::getLastNode()
{
	if (isInsideExp)
	{
		if (dynamic_cast<const IRExpCALL*>(lastNode))
		{
			auto temp = new CTemp();
			stmList->stms.push_back(new IRStmMOVE(new IRExpTEMP(temp), dynamic_cast<const IRExpCALL*>(lastNode)));
			lastNode = new IRExpTEMP(temp);
			return lastNode;
		}
	}
	return lastNode;
}

v_iterator find_label_pos(v_iterator lo, const CLabel* label)
{
	while (1)
	{
		auto curr = dynamic_cast<const IRStmLABEL*>(*lo);
		if (curr != nullptr)
		{
			if (curr->lable == label)
			{
				return lo;
			}
		}

		++lo;
	}
};

void cononize_cjump(v_iterator lo, v_iterator hi, vector<const IRStm*>& result)
{
	while (lo != hi)
	{
		auto cjump = dynamic_cast<const IRStmCJUMP*>(*lo);
		if (cjump)
		{
			result.push_back(cjump);
			++lo;
			v_iterator p_true = find_label_pos(lo, cjump->iftrue);
			v_iterator p_false = find_label_pos(lo, cjump->iffalse);
			v_iterator p_end;
			if (p_true < p_false)
			{
				p_end = p_false;
				lo = p_true;
				while (lo < p_false)
				{
					++lo;
					auto jump = dynamic_cast<const IRStmJUMP*>(*lo);
					if (jump != nullptr)
					{
						auto p_label = find_label_pos(lo, jump->lable);
						if (p_label > p_false)
						{
							if (p_label > p_end)
							{
								p_end = p_label;
							}
						}
					}
				}
				cononize_cjump(p_false, p_end, result);
				result.push_back(new IRStmJUMP(((IRStmLABEL*)(*p_end))->lable));
				cononize_cjump(p_true, p_false, result);
				result.pop_back();
				lo = p_end;
			}
		}
		result.push_back(*lo);
		++lo;
	}
}

IRStmLIST* canonize(const IRNode* root)
{
	IRCanonizer listCanonizer;
	listCanonizer.visit(dynamic_cast<const IRStmLIST*>( root));
	auto result = new IRStmLIST();
	cononize_cjump(listCanonizer.stmList->stms.begin(), listCanonizer.stmList->stms.end(), result->stms);
	//return listCanonizer.stmList;
	return result;
};

