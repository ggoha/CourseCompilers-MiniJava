#include "Graph.h"

#include <ostream>
#include <fstream>

Graph::Graph(std::string _fileName)
: fileName(_fileName), data("digraph {\n"), isFlushed(false)
{

}

Graph::~Graph()
{
	if (!isFlushed) {
		Flush();
	}
}

void Graph::AddEdge(std::string from, std::string to)
{
	decorateName(from);
	decorateName(to);
	data += from + " -> " + to + " ; \n";
}

void Graph::AddEdge(std::string from, std::string to, std::string edgeName)
{
	decorateName(from);
	decorateName(to);
	decorateName(edgeName);
	data += from + " -> " + to + " [ label=\"" + edgeName + "\"] ; \n";
}

void Graph::Flush()
{
	data += "\n}";
	std::ofstream out(fileName);
	out << data;
	out.close();
	isFlushed = true;
}

void Graph::SetNodeLabel(std::string nodeName, std::string nodeLabel)
{
	decorateName(nodeName);
	decorateName(nodeLabel);
	data += nodeName + " [ label=\"" + nodeLabel + "\" ]; \n";
}


void Graph::decorateName(std::string& stringToDecorate)
{
	for (int i = 0; i < stringToDecorate.size(); i++) {
		if (stringToDecorate[i] == '.' || stringToDecorate[i] == ':' || stringToDecorate[i] == '=') {
			stringToDecorate[i] = '_';
		}
	}
}