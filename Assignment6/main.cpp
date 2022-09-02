#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct Node{
    char vertex;
    int cost;
    Node *next;
};

struct GraphNode{
    char vertex;
    Node *listPointer;
};

void addNodeToFront(Node *&listPointer, char newVertex, int newCost) {
    Node *temp;
    temp = new Node;
    temp->vertex = newVertex;
    temp->cost = newCost;
    temp->next = listPointer;
    listPointer = temp;
}

class Graph{
private:
    vector<GraphNode> adjacencyList;
public:
    Graph() {};
    ~Graph() {};
    void AddNewGraphNode(char newGraphNode);
    void AddNewEdgeBetweenGraphNodes(char A, char B, int distance);
    void SortByVertex(char sourceNode);
    void Dijkstra(char startNode);
    bool AllStateTrue(bool state[]);
    int FindIndexOfMin(int cost[], bool state[]);
    void printDijkistra(char startNode, int sourceNode, int cost[], int inf);
    int getIndexOfVertex(char vertex);
};

void Graph::AddNewGraphNode(char newGraphNode) {
    GraphNode temp;
    temp.vertex = newGraphNode;
    temp.listPointer = nullptr;
    adjacencyList.push_back(temp);
}

void Graph::AddNewEdgeBetweenGraphNodes(char A, char B, int distance) {
    int a;
    for(a = 0; !adjacencyList.empty(); a++) {
        if(A == adjacencyList[a].vertex) break;
    }
    addNodeToFront(adjacencyList[a].listPointer, B, distance);
}

//Sorts adjacencyList by vertex into alphabetical order
void Graph::SortByVertex(char sourceNode) {
    for(int i = 0; i < adjacencyList.size(); i++) {  // To make sure source node is always at index 0
        if(adjacencyList[i].vertex == sourceNode) {
            GraphNode temp = adjacencyList[0];
            adjacencyList[0] = adjacencyList[i];
            adjacencyList[i] = temp;
            break;
        }
    }

    for(int i = 1; i < adjacencyList.size(); i++) { // Sorts the rest of the adjacencyList into alphabetical order
        for(int j = i + 1; j < adjacencyList.size(); j++) {
            if(adjacencyList[i].vertex > adjacencyList[j].vertex) {
                GraphNode temp = adjacencyList[i];
                adjacencyList[i] = adjacencyList[j];
                adjacencyList[j] = temp;
            }
        }
    }
}

//Determines if the state of all nodes is true
bool Graph::AllStateTrue(bool state[]) {
    for(int a = 0; a < adjacencyList.size(); a++) {
        if(!state[a]) {
            return false;
        }
    }
    return true;
}

//Returns index of the minimum value as long as it's state is false
int Graph::FindIndexOfMin(int cost[], bool state[]) {
    int i;
    for(i = 0; i < adjacencyList.size(); i++) {
        if(!state[i]) {
            break;
        }
    }

    int temp = cost[i];
    int trackIndex;
    for(int a = i; a < adjacencyList.size(); a++) {
        if(temp >= cost[a]) {
            if(!state[a]) {
                temp = cost[a];
                trackIndex = a;
            }
        }
    }
    return trackIndex;
}

// returns index of vertex
int Graph::getIndexOfVertex(char vertex) {
    for(int i = 0; i < adjacencyList.size(); i++) {
        if(adjacencyList[i].vertex == vertex) {
            return i;
        }
    }
}

//Simulates Dijkstra's Algorithm
void Graph::Dijkstra(char startNode) {
    SortByVertex(startNode);
    int sourceNode = getIndexOfVertex(startNode);
    int cost[adjacencyList.size()];
    bool state[adjacencyList.size()]; //false if state is temporary and true if permanent

    cost[sourceNode] = 0;
    state[sourceNode] = true;
    int current = sourceNode;
    int inf = 9999999;

    for(int v = 0; v < adjacencyList.size(); v++) {
        if(v != sourceNode) {
            cost[v] = inf;
            state[v] = false;
        }
    }
    Node *currentNode;
    int toVertex;
    char vertex;
    while(!AllStateTrue(state)) {
        currentNode = adjacencyList[current].listPointer;
        if(currentNode == nullptr) {
            current = FindIndexOfMin(cost, state);
            state[current] = true;
        } else {
            while(true) {
                if(currentNode->vertex != 0) {
                    vertex = currentNode->vertex;
                    toVertex = getIndexOfVertex(vertex);
                    cost[toVertex] = min(cost[toVertex], cost[current] + currentNode->cost);
                    if(currentNode->next == nullptr) {break;}
                    currentNode = currentNode->next;
                } else {
                    break;
                }
            }
        }
        current = FindIndexOfMin(cost, state);
        state[current] = true;
    }
    printDijkistra(startNode, sourceNode, cost, inf);
}


void Graph::printDijkistra(char startNode, int sourceNode, int cost[], int inf) {
    for(int i = sourceNode + 1; i < adjacencyList.size(); i++) {
        if(cost[i] != inf) {
            cout << "From " << startNode << " to " << adjacencyList[i].vertex << ":" << cost[i] << endl;
        }
    }
}


Graph graph;

int main(int argc, char **argv) {
    string expression;
    ifstream input_file;
    if(argc != 2) {
        cout << "Type a file name. " << endl << argv[1] << endl;
        exit(0);
    }
    input_file.open(argv[1]);
    if(!input_file.is_open()) {
        cout << "Could not read file: " << endl << argv[1] << endl;
        exit(0);
    }
    string token;
    while(!input_file.eof()) {
        getline(input_file, expression);
        stringstream line(expression);
        if(input_file.eof()) break;
        if(expression[0] == '#') continue;
        char node_name;
        if(expression[0] == 'N' && expression[1] == 'o') {
            getline(line, token, ' ');
            getline(line, token, ' ');
            node_name = (token.c_str())[0];
            graph.AddNewGraphNode(node_name);

        } else {
            char nodeFrom;
            getline(line, token, ' ');
            nodeFrom = (token.c_str())[0];
            char nodeTo;
            getline(line, token, ' ');
            nodeTo = (token.c_str())[0];
            int cost;
            getline(line, token, ' ');
            cost = atoi(token.c_str());//use this one if your compiler is not C++11
            graph.AddNewEdgeBetweenGraphNodes(nodeFrom, nodeTo, cost);
        }
    }
    graph.Dijkstra('A');
}