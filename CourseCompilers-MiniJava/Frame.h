#pragma once
#include <string>

using namespace std;


class IRNode
{};

// Метка - точка перехода в коде
class CLabel {
public:
	// Создать метку с уникальным именем
	CLabel() {
		name = to_string(nextUniqueId);
		++nextUniqueId;
	}
	const std::string& Name() const { return name; }
private:
	// Счётчик для создания уникальных идентификаторов
	static int nextUniqueId;
	std::string name;
};

// Временная переменная
class CTemp {
public:
	// Новая переменная с уникальным именем
	CTemp() {
		name = to_string(nextUniqueId);
		++nextUniqueId;
	}
	// Новая переменная с заданным именем
	CTemp(const string& _name) {
		name = _name;
	}
	const std::string& Name() const { return name; }
private:
	// Счётчик для создания уникальных имён
	static int nextUniqueId;
	std::string name;
};
