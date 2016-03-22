#pragma once

#include <string>

class Graph {
public:

	Graph(std::string _fileName);
	~Graph();

	void SetNodeLabel(std::string nodeName, std::string nodeLabel);

	void AddEdge(std::string from, std::string to);
	void AddEdge(std::string from, std::string to, std::string edgeName);
	void PlusTab();
	void MinusTab();
	void Flush();

private:

	bool isFlushed;
	std::string tab;
	std::string fileName;
	std::string data;

	void decorateName(std::string& stringToDecorate);

};