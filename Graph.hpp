#ifndef GRAPH_H
#define GRAPH_H

#include "GraphBase.hpp"
using namespace std;

class Graph: public GraphBase {
    //the node represents a vertex of the graph
    //the node represents a linked list node with
    //a pointer to the next node
    class vNode {
        private:
            string label; //label of vertex
            vNode *next; //pointer to next node
            int weight; //distance of vertex
        public:
            //constructor used to create nodes for verteces
            vNode(string l) {
                label = l;
                next = nullptr;
            }
            //constructor used to create nodes for edges
            vNode(string l, int w) {
                label = l;
                weight = w;
                next = nullptr;
            }
        friend class Graph; //granting the class Graph access to the node
    };
   
    //vector to store the graph in adjacency list form
    vector<vNode*> adjList;
    //utility vecotor to store edges of two verteces
    vector<vNode> edgeList;

    public:
        void addVertex(std::string label);
        void removeVertex(std::string label);
        void addEdge(std::string label1, std::string label2, unsigned long weight);
        void removeEdge(std::string label1, std::string label2);
        unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);
    public:
        //utility method
        void printAdjList();

};


#endif 