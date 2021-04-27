#include "HW4.h"
#include "GraphParser.h"
#include <fstream>

std::vector<Node> ChristofidesMIS(Graph* g) {

	// How does Christofides play into this? https://en.wikipedia.org/wiki/Christofides_algorithm
	// Take created graph
	// Create a spanning tree of said graph
	// Then apply MIS to it https://en.wikipedia.org/wiki/Maximal_independent_set

	// https://stackoverflow.com/questions/23901977/walk-through-all-vertices-in-a-non-hamiltonian-unweighted-undirected-graph

	// http://www.martinbroadhurst.com/greedy-max-independent-set-in-c.html


	std::deque<Node> qminus; //initially empty
	std::vector<Node> qplus;

	std::vector<int> connections;

	std::vector<std::vector<Node> > mislist; //ending list for MIS

	Graph* g2 = Graph::New(g->nodeList);

	qplus = g->nodeList; //populate qplus with list of vectors

	Node* currentNode = &qplus.front();
	qminus.push_back(qplus.front()); //push first node onto the stack

	if (qplus.size() == 1) //if only one node
		return qplus;

	while (!g2->nodeList.empty()) //main while loop, while g2 nodeList has nodes
	{
		bool neighbors = true;

		while(neighbors) //initial depth first search
		{
			neighbors = HW4::hasNeighbors(currentNode, &qminus, g2);
		}

		neighbors = true;
		std::vector<Node> holder;

		for (int i = 0; i < qminus.size(); i ++)
		{
			holder.push_back(qminus[i]);
		}
		mislist.push_back(holder);
		
		currentNode = &qminus.back();
		qminus.pop_back();

		while(!neighbors) //backtracking, continue if no neighbors
		{
			neighbors = HW4::hasNeighbors(currentNode, &qminus, g2);
			
			if(neighbors) //if neighbors are found
				break;
			
			g2->removeNode(currentNode->id); //remove from g2
			currentNode = &qminus.back();
			qminus.pop_back(); //pop from stack
		}	
	}

	int mislist_largest = 1; //MIS determiner
	int mislist_largestindex = 0;
	for (int i = 0; i < mislist.size(); i++)
	{
		if (mislist[i].size() > mislist_largest)
		{
			mislist_largest = mislist[i].size();
			mislist_largestindex = i;
		}
	}

	return mislist[mislist_largestindex];
}

bool hasNeighbors(Node* currentNode, std::deque<Node>* qminus, Graph *g2)
{
	auto connections = currentNode->getConnections(); //get list of neighbors

		if (connections.size() > 0) //if has neighbors
		{
			for ( int i = 0; i < connections.size(); i ++) //iterate through neighbor list
			{
				auto nodeHolder = g2->getNode(connections[i]);

				if (currentNode != nullptr) //found a neighbor that is in the graph
				{
					currentNode = nodeHolder; //set currentNode
					qminus->push_back(*currentNode); //push vertice onto the stack
					return true;
				}
			}
		}
	return false; //return false, no change to currentNode
}


