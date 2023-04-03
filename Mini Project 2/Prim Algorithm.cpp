/**
 * @file Prim Algorithm.cpp
 * @author Abel Lagonell (alagonell1730@floridapoly.edu)
 * @brief The implementation of Prim's Algorithm
 * @version 0.1
 * @date 2023-04-02
*/

#include <iostream>
#include <list>
#include <queue>

using namespace std;

class Graph
{
private: 
    int Vertices;
    
    // Adjacency list representation Pair of a neighbor vertex and a weight for every edge
    list< pair<int, int> > *adj;

public:
    
    Graph(int V){
        this->Vertices = V;
        adj = new list< pair<int, int> >[V];
    }
    
    // Function to add an edge to graph
    void addEdge(int u, int v, int w){}
    
    // Print MST using Prim's algorithm
    void primMST(){

    }
};