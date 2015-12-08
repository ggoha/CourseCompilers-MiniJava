#pragma once
#include <string>

using namespace std;


class IRNode
{
	virtual const void accept(const IRVisitor* visitor) = 0;
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
