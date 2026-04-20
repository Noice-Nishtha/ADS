#include <iostream>
#include <climits>
using namespace std;

#define V 5

// Function to find vertex with minimum key value
int minKey(int key[], bool mstSet[])
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
    {
        if (mstSet[v] == false && key[v] < min)
        {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Print MST
void printMST(int parent[], int graph[V][V])
{
    cout << "Edge \tWeight\n";
    int total = 0;

    for (int i = 1; i < V; i++)
    {
        cout << parent[i] << " - " << i << "\t" << graph[i][parent[i]] << endl;
        total += graph[i][parent[i]];
    }

    cout << "Total Distance (MST): " << total << endl;
}

// Prim's Algorithm
void primMST(int graph[V][V])
{
    int parent[V];
    int key[V];
    bool mstSet[V];

    for (int i = 0; i < V; i++)
    {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++)
    {
        int u = minKey(key, mstSet);
        mstSet[u] = true;

        for (int v = 0; v < V; v++)
        {
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
            {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph);
}

int main()
{
    // Graph representing departments (example)
    int graph[V][V] = {
        {0, 2, 0, 6, 0}, // Admin
        {2, 0, 3, 8, 5}, // CSE
        {0, 3, 0, 0, 7}, // IT
        {6, 8, 0, 0, 9}, // Mechanical
        {0, 5, 7, 9, 0}  // Civil
    };

    primMST(graph);

    return 0;
}