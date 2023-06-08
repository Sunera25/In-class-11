#include <iostream>
#include <climits>
using namespace std;
#define V 6

// Find the vertex with the minimum key value from the set of vertices not yet included in MST
int findMinKey(int key[], bool mstSet[])
{
    int minKey = INT_MAX, minIndex;


    for(int i=0; i<V; i++)
    {
        if (mstSet[i] == false && key[i] < minKey)
        {
            minKey = key[i];
            minIndex = i;
        }
    }

    return minIndex;
}

// Print the Minimum Spanning Tree
void printMST(int parent[], int graph[V][V])
{
    cout << " Edge    Weight"<<endl;

    for(int i=1; i<V; i++)
    {
        if (parent[i] < i)
           cout << parent[i] << " - " << i << "     " << graph[i][parent[i]] << endl;
        else
            cout << i << " - " << parent[i] << "     " << graph[i][parent[i]] <<endl;
    }
}

// Function to construct and print MST using Prim's algorithm
void primMST(int graph[V][V])
{
    int parent[V];
    int key[V];
    bool mstSet[V];

    for(int i=0; i<V; i++)
    {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[3] = 0;      // Start with the first vertex
    parent[3] = -1;  // First node is always the root of MST


    for(int i=0; i<V-1; i++)
    {
        int selectedVertex = findMinKey(key, mstSet); // Select the vertex with the minimum key value
        mstSet[selectedVertex] = true;                // Include the selected vertex in MST

        for(int adjacentVertex=0;adjacentVertex<V; adjacentVertex++)
        {
            if (graph[selectedVertex][adjacentVertex] && mstSet[adjacentVertex] == false && graph[selectedVertex][adjacentVertex] < key[adjacentVertex])
            {
                parent[adjacentVertex] = selectedVertex; // Update parent of the adjacent vertex
                key[adjacentVertex] = graph[selectedVertex][adjacentVertex]; // Update the key value of the adjacent vertex
            }
        }
    }

    printMST(parent, graph);
}

int main()
{
    int graph[V][V] = {{0, 3, 0, 0, 0, 1},
                       {3, 0, 2, 1, 10, 0},
                       {0, 2, 0, 3, 0, 5},
                       {0, 1, 3, 0, 5, 0},
                       {0, 10, 0, 5, 0, 4},
                       {1, 0, 5, 0, 4, 0}};

    primMST(graph);

    return 0;
}