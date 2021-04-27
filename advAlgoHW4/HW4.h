#pragma once
#include <vector>
#include "Node.h"
#include "Graph.h"
#include <iostream>
#include <cstring>
#include <stack>
#include <deque>
class HW4
{


public:
	static std::vector<Node> ChristofidesMIS(Graph* g);

	static bool hasNeighbors(Node* currentNode, std::deque<Node>* qminus, Graph* g2);
    
};


