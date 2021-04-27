#include "GraphParser.h"
#include <fstream>
#include <iostream>
#include <string>

void GraphParser::readFile(std::string filepath, std::vector<std::string>& vecOfStrs)
{
    std::ifstream in(filepath.c_str());

    std::string str;
    // Read the next line from File untill it reaches the end.
    while (std::getline(in, str))
    {
        // Line contains string of length > 0 then save it in vector
        if (str.size() > 0)
            vecOfStrs.push_back(str);
    }
    //Close The File
    in.close();

}

Graph* GraphParser::parseFile(std::vector<std::string>& vecOfStrs)
{
    std::cout << "DEBUG\n";
    for (std::string s : vecOfStrs) {
        std::cout << s << "\n";
    }
    std::cout << "Length of file read: " << vecOfStrs.size() << "\n";
    std::vector<Node> parsedNodes;
    // First two lines should be "N"s; this is more of a gut-check than anything
    if (vecOfStrs[0] != "N" || vecOfStrs[1] != "N") {
        std::cout << "ERROR: File not parsed properly (first two lines read were not 'N's.\n";
        return nullptr;
    }


    // Then, we loop through the same pattern:
    // 1. pick up the degree
    // 2. read [degree] many lines after and remember the connections
    // 3. build the node
    // Until we're out of lines.

    //for (std::string line : vecOfStrs) { //TODO: change to iter w/ i (bc of degree-node subloop)
    //    if (line == vecOfStrs[0] || line == vecOfStrs[1]) {
    //        // skip the first two lines
    //        continue;
    //    }
    //    // Pull the degree 
    int degree = 0;
    int currentId = 0;
    for (int i=0; i < vecOfStrs.size(); i += 0) {
        if (i == 0 || i == 1) {
            // skip the first two lines
            i++;
            continue;
        }
        else if (i == 2) {
            // Print out how many vertices there will be
            std::cout << "Graph has " << vecOfStrs[i] << " vertices.\n";
            i++;
            continue;
        }

        // Start a loop for each degree
        degree = std::stoi(vecOfStrs[i++]);
        std::cout << "Detected degree of " << degree << " for node " << parsedNodes.size() << "\n";
        Node newNode;
        for (int j = 0; j < degree; j++) {
            // Add the node to the connection vector
            //std::cout << "DEBUG - Current Line: " << vecOfStrs[i] << "\n";
            currentId = std::stoi(vecOfStrs[i++]);
            newNode.addConnection(currentId);
            std::cout << "\tAdding connection " << j + 1 << " of " << degree <<" to " << currentId << ". Line number is " << i << "\n";

        }
        //i++; //idfk
        // Add the new node to our list of nodes
        parsedNodes.push_back(newNode);
        
    }

    // Finally, construct the graph itself
    std::cout << "Final count of parsed nodes: \n";
    for (Node n : parsedNodes) {
        std::cout << "Node ID: " << n.id << " / Neighbors: ";
        for (int neighbor : n.getConnections()) {
            std::cout << neighbor << ",";
        }
        std::cout << "\n";
    }
    return Graph::New(parsedNodes);
}