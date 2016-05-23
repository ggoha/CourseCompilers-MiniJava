#pragma once

#include <string>

class IRRepresentation {
public:

	IRRepresentation(std::string _fileName);
	~IRRepresentation();

	void SetNodeLabel(std::string nodeName, std::string nodeLabel);

	void AddEdge(std::string from, std::string to);
	void AddEdge(std::string from, std::string to, std::string edgeName);
	void PlusTab();
	void MinusTab();
	void Devide();
	void Flush();

private:

	bool isFlushed;
	std::string tab;
	std::string fileName;
	std::string data;

	void decorateName(std::string& stringToDecorate);
	
};