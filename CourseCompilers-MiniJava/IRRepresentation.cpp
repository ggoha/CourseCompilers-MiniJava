#include "IRRepresentation.h"

#include <ostream>
#include <fstream>

IRRepresentation::IRRepresentation(std::string _fileName)
: fileName(_fileName), data("digraph {\n"), isFlushed(false)
{
	tab = "";
}

IRRepresentation::~IRRepresentation()
{
	if (!isFlushed) {
		Flush();
	}
}

void IRRepresentation::AddEdge(std::string from, std::string to)
{
	decorateName(from);
	decorateName(to);
	data += tab + from + " -> " + to + " ; \n";
}

void IRRepresentation::AddEdge(std::string from, std::string to, std::string edgeName)
{
	decorateName(from);
	decorateName(to);
	decorateName(edgeName);
	data += /*tab +*/ from + " -> " + to + " [ label=\"" + edgeName + "\"] ; \n";
}

void IRRepresentation::Flush()
{
	data += "\n}";
	std::ofstream out(fileName);
	out << data;
	out.close();
	isFlushed = true;
}

void IRRepresentation::SetNodeLabel(std::string nodeName, std::string nodeLabel)
{
	decorateName(nodeName);
	decorateName(nodeLabel);
	data += nodeName + " [ label=\"" + nodeLabel + "\" ]; \n";
}


void IRRepresentation::decorateName(std::string& stringToDecorate)
{
	for (int i = 0; i < stringToDecorate.size(); i++) {
		if (stringToDecorate[i] == '.' || stringToDecorate[i] == ':' || stringToDecorate[i] == '=') {
			stringToDecorate[i] = '_';
		}
	}
}

void IRRepresentation::PlusTab(){
	tab.append("  ");
}

void IRRepresentation::MinusTab(){
	tab.pop_back();
}

void IRRepresentation::Devide(){
	//data += "/n/n";
}