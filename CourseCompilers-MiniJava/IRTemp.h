#pragma once
#include <string>
#include <set>
#include "IRVisitor.h"

using namespace std;

class IRNode
{
	virtual void accept(IRVisitor* visitor) const = 0;
};

// ����� - ����� �������� � ����
class CLabel {
public:
	// ������� ����� � ���������� ������
	CLabel() {
		name = to_string(nextUniqueId);
		++nextUniqueId;
	}
	CLabel(const string& _name) {
		name = _name;
	}
	const std::string& Name() const { return name; }
private:
	// ������� ��� �������� ���������� ���������������
	static int nextUniqueId;
	std::string name;
};

// ��������� ����������
class CTemp {
public:
	// ����� ���������� � ���������� ������
	CTemp() {
		name = to_string(nextUniqueId);
		++nextUniqueId;
	}
	// ����� ���������� � �������� ������
	CTemp(const string& _name) {
		name = _name;
	}
	const std::string& Name() const { return name; }
private:
	// ������� ��� �������� ���������� ���
	static int nextUniqueId;
	std::string name;
};

class CTempList {
public:
	CTempList(const CTemp* _head, CTempList* _tail);
	CTempList* Reverse();

	const CTemp* head;
	CTempList* tail;

	set<const CTemp*> GetSet() {
		CTempList* cur = this;
		set<const CTemp*> res;
		while (cur != 0) {
			assert(cur->head != 0);
			res.insert(cur->head.get());
			cur = cur->tail;
		}
		return res;
	}
};

class CLabelList {
public:
	CLabelList(const CLabel* _head, CLabelList* _tail);

	const CLabel* head;
	CLabelList* tail;
};
}
