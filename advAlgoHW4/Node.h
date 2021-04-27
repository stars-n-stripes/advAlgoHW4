#pragma once
#include <vector>
class Node
{
	
	std::vector<int> connections;
	
public:
	static int num_nodes;
	
	bool operator==(const Node other) { return this->id == other.id; }


	int id = 0;
	int degree = 0;
	~Node() = default;
	Node() { this->id = ++Node::num_nodes; };
	Node(std::vector<int> neighbors) {
		this->id = ++Node::num_nodes;
		for (int n: neighbors)
		{
			this->connections.push_back(n);
		}
		this->degree = this->connections.size();
	}

	std::vector<int> getConnections() {
		return this->connections;
	}
	void addConnection(int conn_id) {
		this->connections.push_back(conn_id);
	}

};

