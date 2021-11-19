#include "Graph.hpp"
using namespace std;


void Graph::addVertex(string label) {
    //we loop through the adjacency list
    //if a vertex already exists, the method simply returns
    for (unsigned int i = 0; i < adjList.size(); i++) {
        if (adjList[i]->label == label) {
            return;
        }
    }
    //if the vertex is not found in the list,
    //a new vertex is inserted
    vNode *v = new vNode(label);
    adjList.push_back(v);
}


void Graph::removeVertex(std::string label) {
    //we loop through the adjacency list, and when we find
    //the vertex, we use the erase function of vectors to get rid 
    //of the vertex
    for (unsigned int i = 0; i < adjList.size(); i++) {
        if (adjList[i]->label == label) {
            adjList.erase(adjList.begin() + i);
            break;
        }
    }
}


void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) {
    //two vertex nodes to add as edges to the respective verteces 
    vNode *edge1 = new vNode(label1, weight);
    vNode *edge2 = new vNode(label2, weight);

    //first we add a node with label 1 to a node with label 2
    for (unsigned int i = 0; i < adjList.size(); i++) {
        if (adjList[i]->label == label1) {
            //if the node with label 1 points to NULL, then it does not have any edges yet
            if(adjList[i]->next == nullptr) {
                adjList[i]->next = edge2;
            } else {
                //otherwise, if there already edges, we loop through all the edges of the node with label 1
                //and then simply add another node with label 2 to the end of the list of edges
                vNode *temp;
                for (temp = adjList[i]; temp->next != nullptr; temp = temp->next) {
                    ;
                }
                temp->next = edge2;
            }
        }
    }

    for (unsigned int i = 0; i < adjList.size(); i++) {
        if (adjList[i]->label == label2) {
            //if the node with label 2 points to NULL, then it does not have any edges yet
            if (adjList[i]->next == nullptr) {
                adjList[i]->next = edge1;
            } else {
                //otherwise, if there already edges, we loop through all the edges of the node with label 2
                //and then simply add another node with label 1 to the end of the list of edges
                vNode *temp = adjList[i];
                for (temp = adjList[i]; temp->next != nullptr; temp = temp->next) {
                    ;
                }
                temp->next = edge1;
            }
        }
    }
}


//utlity method to print the graph in adjacency list form
void Graph::printAdjList() {
    for (unsigned int i = 0; i < adjList.size(); i++) {
        cout<<adjList[i]->label<<": -> ";
        vNode *temp;
        for (temp = adjList[i]->next; temp != nullptr; temp = temp->next) {
            cout<<" "<<temp->label<<"("<<temp->weight<<")";
        }
        cout<<"\n";
    }
}


void Graph::removeEdge(std::string label1, std::string label2) {
    //first, we loop through the adjacency list to find an edge node with label 2
    //from a vertex with label 1
    for (unsigned int i = 0; i < adjList.size(); i++) {
        //first, we find the vertex with label 1
        if (adjList[i]->label == label1) {
            vNode *cur = adjList[i];
            //now we look for an edge node with label 2
            while(cur->next->label != label2) {
                cur = cur->next;
            }
            vNode *n_del = cur->next;
            vNode *next_n = n_del->next;
            cur->next = next_n;
            delete n_del;
            break;
        }
    }
    
    //now we loop though the adjacency list again to find an edge node with label 1
    //from a vertex with label 2
    for (unsigned int i = 0; i < adjList.size(); i++) {
        //first, we find the vertex with label 2
        if (adjList[i]->label == label2) {
            vNode *cur = adjList[i];
            //now we look for an edge node with label 1
            while(cur->next->label != label1) {
                cur = cur->next;
            }
            vNode *n_del = cur->next;
            vNode *next_n = n_del->next;
            cur->next = next_n;
            delete n_del;
            break;
        }
    }
}


unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) {

    //the distance from a vertex with start label to the vertex with end label
    unsigned long shortestPathSize;

    //a vector of labels of nodes already visted
    vector<string> visited; 

    //a table that stores verteces as rows and distances from the 
    //node with start label to all the other nodes as columns
    map<string, int>  shortestDistStartL;  

    //a table that stores verteces as rows and the labels of the nodes visited 
    //prior to each verteces in the shortest path
    map<string, string> prevVerteces;

    //an entree that will help in iterating through the two tables above
    //it will hold the node with shortest dinstance from the node with start label
    pair<string, int> shortest_of_unvisted;

    //a stack of map entrees to store the nodes of adjacent nodes of a node 
    //precessed inside the loop below
    vector<pair<string, int> > stackNeighbors;

    //value of infinity for the purposes of the algorithm
    int const INFINITY = 1000000;
    
    unsigned int size = adjList.size();

    //initializing the shortest distance from starting label to all others
    //except for the node with start label, whose distance in the table will be set to 0,
    //all the nodes' distances will be set to infinity
    for (unsigned int i = 0; i < adjList.size(); i++) {
       if (adjList[i]->label == startLabel) {
            shortestDistStartL[startLabel] = 0;
        } else {
            shortestDistStartL[adjList[i]->label] = INFINITY; 
        }
    } 

    while(size != 0) {
        //first we find the label with shortest distance from the start label in unvistited list
        //the bool variable will help in identifying nodes that are already visited
        bool already_considered = false;
        for (map<string, int>::iterator itr = shortestDistStartL.begin(); itr != shortestDistStartL.end(); itr++) {
            for (unsigned int i = 0; i < visited.size(); i++) {
                if (itr->first == visited[i]) {
                    already_considered = true;
                    break;
                }
            }
            if (already_considered) {
                already_considered = false;
                continue;
            } else {
                shortest_of_unvisted.first = itr->first;
                shortest_of_unvisted.second = itr->second;
                break;
            }
        }

        //we loop through the visited stack to set the map entree first to
        //a node not yet visited in the table
        map<string, int>::iterator itr = shortestDistStartL.begin();
        for (unsigned int i = 0; i < visited.size(); i++) {
            if (visited[i] == shortest_of_unvisted.first) {
                itr++;
                shortest_of_unvisted.first = itr->first;
                shortest_of_unvisted.second = itr->second;
            }
        }

        //now we loop through the shortest distances table to set the iterator map entree to
        //a node with smallest distance
        for (map<string, int>::iterator itr = shortestDistStartL.begin(); itr != shortestDistStartL.end(); itr++) {
            if (itr->second < shortest_of_unvisted.second) {
                //we check if the vertex is already visited,
                //if so, we take the next vertex with smallest weight
                for (unsigned int i = 0; i < visited.size(); i++) {
                    if (itr->first == visited[i]) {
                        already_considered = true;
                    }
                }
                if (already_considered) {
                    already_considered = false;
                    continue;
                }
                shortest_of_unvisted.first = itr->first;
                shortest_of_unvisted.second = itr->second;
            } 
            
        }

        //now we collect all the neighbors of this label to the stack
        for (unsigned int i = 0; i < adjList.size(); i++) {
            if (shortest_of_unvisted.first == adjList[i]->label) {
                for (vNode *temp = adjList[i]->next; temp != nullptr; temp=temp->next) {
                    //we also check if we already considered a node before
                    //if so, we do not consider them in the next calculations
                    for (unsigned int j = 0; j < visited.size(); j++) {
                        if (temp->label == visited[j]) {
                            already_considered = true;
                        }
                    }
                    if (already_considered) {
                        already_considered = false;
                        continue;
                    }
                    stackNeighbors.push_back(pair<string, int>(temp->label, temp->weight));
                }
            }
        }
  
        //now we update shortest distance table
        //if the distance in the shortest distance table is greater than the distance of the label we got,
        //we update the distance value in the table
        //we also update the prevVertices table to keep track of shortest path
        int shortest_weight;
        while(stackNeighbors.size() != 0) {
            for (unsigned int i = 0; i < stackNeighbors.size(); i++) {
                //we also need to get the shortest weight from the start label to the current vertex
                //we check the prevVertices table to get the last vertex and get the shortest weight
                //to that vertex in the shortestDistStartL table
                shortest_weight =  shortestDistStartL[shortest_of_unvisted.first];
                if (shortestDistStartL[stackNeighbors[i].first] > stackNeighbors[i].second + shortest_weight) {
                    shortestDistStartL[stackNeighbors[i].first] = stackNeighbors[i].second + shortest_weight;
                    prevVerteces[stackNeighbors[i].first] = shortest_of_unvisted.first;
                }
                stackNeighbors.erase(stackNeighbors.begin() + i);
            }
        }
        //now we add the current vertex to the visted list and remove from unvisited list
        visited.push_back(shortest_of_unvisted.first);

        //we now decrement the size of unvisted list of verteces
        size--;
    }
    
    //now we construct the shortest path from the pervVertices table
    //we access the value of the end label from the table and push it to the path
    //if the value is the start label, we push it and break the loop
    //otherwise we keep watching for the value of it in the table again 
    //until the value is the start label
    string temp = prevVerteces[endLabel];
    path.insert(path.begin(), endLabel);
    if (temp == startLabel) {
        path.insert(path.begin(),startLabel);
    } else {
        while (temp != startLabel) {
            path.insert(path.begin(), temp);
            temp = prevVerteces[temp];
            if (temp == startLabel) {
                path.insert(path.begin(), temp);
            }
        }
    }

    //we get the size of the shortest path from the start label to the end label
    shortestPathSize = shortestDistStartL[endLabel];

    return shortestPathSize;
}

