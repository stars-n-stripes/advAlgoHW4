// advAlgoHW4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once
#include <iostream>
#include <fstream>
#include "Graph.h"
#include "GraphParser.h"
//#include "HW4.h"
#include "Node.h"
#include <deque>


Node * hasNeighbors(Node* currentNode, std::deque<Node>* qminus, Graph* g2)
{
	auto connections = currentNode->getConnections(); //get list of neighbors
	Node* nodeHolder;

	if (connections.size() > 0) //if has neighbors
	{
		for (int i = 0; i < connections.size(); i++) //iterate through neighbor list
		{
			nodeHolder = g2->getNode(connections[i]);
			//std::cout << "foobarbaz\n";

			if (nodeHolder == nullptr) continue;

			auto check = std::find(qminus->begin(), qminus->end(), *nodeHolder);
			
			if (check == qminus->end()) //found a neighbor that is in the graph and avoid circular movement
			{
				std::cout << "Current node is " << currentNode->id << "\n";
				//currentNode = nodeHolder; //set currentNode

				std::cout << "Setting currentNode to " << nodeHolder->id << "\n";
				// qminus->push_back(*nodeHolder); //push vertice onto the stack
				return nodeHolder;
			}
		}
	}
	return nullptr; //return false, no change to currentNode
}


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

	//qplus = g->nodeList; //populate qplus with list of vectors

	Node* currentNode = &g2->nodeList.front();
	qminus.push_back(g2->nodeList.front()); //push first node onto the stack

	if (g2->nodeList.size() == 1) //if only one node
		return g2->nodeList;

	while (!g2->nodeList.empty()) //main while loop, while g2 nodeList has nodes
	{
		//bool neighbors = true;

		while (currentNode != nullptr) //initial depth first search
		{
			currentNode = hasNeighbors(currentNode, &qminus, g2);
			if (currentNode == nullptr) break;
			qminus.push_back(*currentNode); //push vertice onto the stack
		}

		//neighbors = true;
		std::vector<Node> holder;

		for (int i = 0; i < qminus.size(); i++)
		{
			holder.push_back(qminus[i]);
		}
		mislist.push_back(holder);

		currentNode = &qminus.back();
		//auto old_currentNode = currentNode;
		

		do  //backtracking, continue if no neighbors
		{
			std::cout << "Entering this loop thingy\n";
			int currentId = currentNode->id;
			currentNode = hasNeighbors(currentNode, &qminus, g2);

			if (currentNode == nullptr) {//if neighbors are found
				std::cout << "Breaking due to currentNode being a nullptr.\n";
				g2->removeNode(currentId); //remove from g2
				qminus.pop_back();
				break;
			}
			
			qminus.push_back(*currentNode); //push vertice onto the stack
			//currentNode = &qminus.back();
			// qminus.pop_back(); //pop from stack
		} while (currentNode != nullptr);
	}


	int mislist_largest = 1; //MIS determiner
	int mislist_largestindex = 0;
	std::cout << "MIS Lists:\n";
	for (int i = 0; i < mislist.size(); i++)
	{
		std::cout << "List " << i << ": ";
		for (int j = 0; j < mislist[i].size(); j++) {
			std::cout << mislist[i][j].id << ",";
		}
		std::cout << "\n";
		
		if (mislist[i].size() > mislist_largest)
		{
			mislist_largest = mislist[i].size();
			mislist_largestindex = i;
		}
	}

	return mislist[mislist_largestindex];
}









int main(int argc, char* argv[]) {

	// Check if the file path provided is proper
	std::ifstream test(argv[1]);
	if (!test.good()) {
		std::cout << "Failed to open the given input file.\n";
		return -1;
	}

	// Create the graph from our given input file
	std::vector<std::string> file_lines;
	GraphParser::readFile(std::string(argv[1]), file_lines);
	Graph* inputGraph = GraphParser::parseFile(file_lines);

	// DEBUG: Print the graph
	std::cout << "Super Duper MIS-inator 9001 (c) 2021 I. WannaPass and P. Lshelpme\n";
	std::cout << "Loaded Graph Successfully:\n";
	inputGraph->print();
	std::cout << "Executing MIS algorithm. If this works, James Lynch wrote it. If it doesn't, Andrew Park did.\n";
	std::cout << "Preparing Graph...\nPraying to Jesus...\nPraying to Satan...\nTriangulating recursion matrices...\nDone.\n";
	auto output = ChristofidesMIS(inputGraph);

	std::cout << "Finished MIS calculations...\nMIS nodes are:\n";
	for (Node n : output) {
		std::cout << "\tNode " << n.id << "\n";
	}

	std::cout << "So long, and thanks for all the fish!\n";



}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
