#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge
{
    int u, v, weight;
};

// Compare edges by weight
bool cmp(Edge a, Edge b)
{
    return a.weight < b.weight;
}

// Disjoint Set (Union-Find)
class DSU
{
    vector<int> parent;

public:
    DSU(int n)
    {
        parent.resize(n);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y)
    {
        parent[find(x)] = find(y);
    }
};

void kruskal(int V, vector<Edge> &edges)
{

    sort(edges.begin(), edges.end(), cmp);

    DSU dsu(V);

    cout << "Minimum Spanning Tree:\n";
    int total = 0;

    for (auto e : edges)
    {
        if (dsu.find(e.u) != dsu.find(e.v))
        {
            cout << e.u << " - " << e.v
                 << " : " << e.weight << endl;

            total += e.weight;
            dsu.unite(e.u, e.v);
        }
    }

    cout << "Total Distance: " << total << endl;
}

int main()
{

    int V = 5;

    vector<Edge> edges = {
        {0, 1, 4},
        {0, 3, 6},
        {0, 4, 3},
        {1, 2, 5},
        {1, 4, 2},
        {2, 3, 7},
        {2, 4, 4},
        {3, 4, 3}};

    kruskal(V, edges);

    return 0;
}