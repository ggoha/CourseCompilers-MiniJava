#include "IRCanonisation.h"
#include "IRStm.h"
#include "IRExp.h"

void IRCanonizer::visit(const IRExpList* n){
	vector<const IRExp*> expList;
	for (int i = 0; i < n->expslist.size(); ++i)
	{
		auto node = dynamic_cast<const IRExpList*>(n->expslist[i]);
		if (node != nullptr)
		{
			node->accept(this);
		}
		else
		{
			expList.push_back(n->expslist[i]);
		}
	}
};

v_iterator find_label_pos(v_iterator lo, const CLabel* label)
{
	while (1)
	{
		++lo;
		auto curr = dynamic_cast<const IRStmLABEL*>(*lo);
		if (curr != nullptr)
		{
			if (curr->lable == label)
			{
				return lo;
			}
		}
	}
};

void cononize_cjump(v_iterator lo, v_iterator hi, vector<const IRStm*>& result)
{
	vector<const IRStm*> head;
	vector<const IRStm*> tail;
	while (lo != hi)
	{
		++lo;
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
				cononize_cjump(p_true, p_false, result);
				lo = p_end;
			}
		}
		result.push_back(*lo);
	}
}

IRStmLIST* canonize(const IRNode* root)
{
	IRCanonizer listCanonizer;
	listCanonizer.visit(dynamic_cast<const IRStmLIST*>( root));
	auto result = new IRStmLIST();
	cononize_cjump(listCanonizer.stmList->stms.begin(), listCanonizer.stmList->stms.end(), result->stms);
	return result;
};