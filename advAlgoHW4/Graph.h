#include "Node.h"
#include <unordered_map>
#include <iostream>
#pragma once
class Graph
{

	std::unordered_map<int, Node*> nodeLookupTable;
protected:
	Graph(std::vector<Node> nodes) {
		this->nodeList = nodes;
		//for (Node n : nodes) {
		//	nodeLookupTable[n.id] = &n;
		//}
		for (int i = 0; i < nodeList.size(); i++) {
			nodeLookupTable[i+1] = &nodeList[i];
		}
	}
public:

	std::vector<Node> nodeList;

	static Graph* New(std::vector<Node> nodes) {
		Graph* ng = new Graph(nodes);
		return ng;
	}

	void removeNode(int id) {
		int targetIndex = -1;
		for (int n = 0; n < nodeList.size(); n++) {
			if (nodeList[n].id == id) {
				targetIndex = n;
				break;
			}
		}
		if (targetIndex != - 1) {
			this->nodeList.erase(nodeList.begin() + targetIndex); // remove from node list
			this->nodeLookupTable.erase(id); // remove from lookup
		}
		else {
			std::cout << "Failed to remove node " << id << "\n";
		}
		
	}

	Node* getNode(int id) {
		std::unordered_map<int, Node*>::const_iterator got = nodeLookupTable.find(id);
		Node* out;
		if (got == nodeLookupTable.end()) {
			std::cout << "Failed to find node " << id << "\n";
			return nullptr;
		}
		else {
			out = nodeLookupTable[id];
			return out;
		}
	}
	void print() {
		for (Node n : nodeList) {
			std::cout << n.id << " -> (";
			for (int neighbor : n.getConnections()) {
				std::cout << neighbor << ", ";
			}
			std::cout << ")\n";
		}
	}
};

