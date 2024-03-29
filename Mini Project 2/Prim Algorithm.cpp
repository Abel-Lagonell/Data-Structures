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
#define INF 10000 //A constant to represent infinity

using namespace std;
typedef pair<int, int> pii; //Type alias that creates a pii pair

class Graph
{
private:
    int Vertices; //Total number of vertices in the graph

    // Adjacency list representation Pair of a neighbor vertex and a weight for every edge
    list<pii> *adj; // the adj is the vertex and the pair are the weight and the vertex of the next node |pointer to an array linked lists of pairs of integers

public:

    Graph(int V)
    {
        this->Vertices = V+1; // The number of vertices | assigns the value of V to the Vertices, iterating through the array
        adj = new list<pii>[V+1]; // The adjacency list | allocates memory for the array of linked lists
    }

    // Function to add an edge to graph
    void addEdge(int u, int v, int w)
    // u is the vertex, v is the vertex, w is the weight
    {
        //Add a pair to the Vertex u
        adj[u].push_back(make_pair(v, w));
        //push_back is a function that adds a new element at the end of the vector, after its current last element.
        //make_pair is a function that creates a pair with two elements
        //Add a pair to the Vertex v
        adj[v].push_back(make_pair(u, w));
        //Undirected egde so we add the pair to both vertices
    }

    // Print MST using Prim's algorithm
    void primMST()
    {
        priority_queue< pii, vector <pii> , greater<pii> > pq; // Holds the order of which the vertices will be visited (weight, vertex)
        int src =0; // The source vertex (the first vertex)
        vector <bool> inMST(Vertices+1, false); //Keeps track of which vertices were used in the MST
        vector <int> value(Vertices, INF); //Keeps track of the minimum weighted edge for every vertex
        vector <int> parent(Vertices, -1); //Keeps track of the parent of every vertex

        pq.push(make_pair(0, src)); // Push the source vertex with a weight of 0
        value[src] = 0;
        //The source vertex is just the starting point so it can be removed from the queue
        while (!pq.empty())
        {
            int u = pq.top().second; // Get the second Vertex
            pq.pop();

            if (inMST[u] == true) continue; // If the vertex was already used in the MST, skip it (this is to avoid cycles)
            inMST[u] = true; // Mark the vertex as used in the MST

            //For every neighbor of the vertex find the minimum weighted edge, excluding edges with vertices already used in the MST
            //auto is a keyword that tells the compiler to automatically determine the type of the variable based on its initialization
            for (auto x: adj[u])
            {
                //x represents the pair of the vertex and the weight
                int v = x.first;
                int weight = x.second;

                if (inMST[v] == false && value[v] > weight)
                {
                    value[v] = weight;
                    pq.push(make_pair(value[v], v));
                    parent[v] = u;
                }
            }
        }

        for (int i = 1; i < Vertices; i++)
        {
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
