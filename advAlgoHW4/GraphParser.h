#pragma once
#include "Graph.h"
class GraphParser
{
public:
	static void readFile(std::string filepath, std::vector<std::string>& vecOfStrs);
	static Graph* parseFile(std::vector<std::string>& vecOfStrs);
};

