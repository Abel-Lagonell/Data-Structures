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
#include <vector>
#define INF 10000

using namespace std;
typedef pair<int, int> pii;

class Graph
{
private: 
    int Vertices;
    
    // Adjacency list representation Pair of a neighbor vertex and a weight for every edge
    list<pii> *adj; // the adj is the vertex and the pair is the weight and the vertex of the next node

public:
    
    Graph(int V){
        this->Vertices = V;
        adj = new list<pii>[V];
    }
    
    // Function to add an edge to graph
    void addEdge(int u, int v, int w){
        //Add a pair to the Vertex u
        adj[u].push_back(make_pair(v, w));
        //Add a pair to the Vertex v
        adj[v].push_back(make_pair(u, w));
    }
    
    // Print MST using Prim's algorithm
    void primMST(){
        priority_queue< pii, vector <pii> , greater<pii> > pq; // Holds the order of which the vertices will be visited (weight, vertex)
        int src =0;
        vector <bool> inMST(Vertices, false); //Keeps track of which vertices were used in the MST
        vector <int> value(Vertices, INF);
        vector <int> parent(Vertices, -1);

        pq.push(make_pair(0, src));
        value[src] = 0;

        while (!pq.empty()){
            int u = pq.top().second;
            pq.pop();
            if (inMST[u] == true) continue; // If the vertex was already used in the MST, skip it (this is to avoid cycles)
            inMST[u] = true;
            
            list <pii>::iterator i;
            for (i = adj[u].begin(); i != adj[u].end(); ++i){
                int v = (*i).first;
                int weight = (*i).second;
                
                if (inMST[v] == false && value[v] > weight){
                    value[v] = weight;
                    pq.push(make_pair(value[v], v));
                    parent[v] = u;
                }
            }
        }

        for (int i = 1; i < Vertices; i++){
            cout << parent[i] << " - " << i << endl;
        }
    }
};

int main(){
    int V = 8;
    Graph g(V);
    
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 9);
    g.addEdge(1, 4, 9);
    g.addEdge(1, 2, 12);
    g.addEdge(4, 7, 8);
    g.addEdge(2, 3, 8);
    g.addEdge(2, 5, 2);
    g.addEdge(3, 4, 3);
    g.addEdge(3, 5, 7);
    g.addEdge(4, 7, 8);
    g.addEdge(4, 6, 5);
    g.addEdge(5, 6, 3);
    g.addEdge(6, 7, 15);
    g.addEdge(6, 8, 11);
    g.addEdge(7, 8, 10);
    
    g.primMST();
    
    return 0;
}
