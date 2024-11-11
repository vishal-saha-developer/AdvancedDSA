
#include "KnowledgeGraph.h"
#include <iostream>

KnowledgeGraph::KnowledgeGraph(int n) : n(n + 1)
{
    parent.resize(n + 1);
    rank.resize(n + 1);
    cost.resize(n + 1);

    for (int i = 0; i <= n; i++)
        parent[i] = i;
}

KnowledgeGraph::~KnowledgeGraph()
{
}

std::pair<int, int> KnowledgeGraph::getParent(int u)
{
    if (u == parent[u])
        return {u, 0};
    auto pU = getParent(parent[u]);
    cost[u] += pU.second;
    parent[u] = pU.first;
    return {parent[u], cost[u]};
}

void KnowledgeGraph::addEdge(int u, int v, int w)
{
    auto pU = getParent(u);
    auto pV = getParent(v);
    int parentU = pU.first;
    int parentV = pV.first;
    int costU = pU.second;
    int costV = pV.second;

    if (parentU == parentV)
    {
        // NOTE: we may need to throw exception in case of attempt of
        // update with incosistent values.
        return;
    }
    if (rank[parentU] > rank[parentV])
    {
        parent[parentV] = parentU;
        cost[parentV] = w + costU - costV;
    }
    else if (rank[parentV] > rank[parentU])
    {
        parent[parentU] = parentV;
        cost[parentU] = costV - costU - w;
    }
    else
    {
        rank[parentU]++;
        parent[parentV] = parentU;
        cost[parentV] = w + costU - costV;
    }
}

int KnowledgeGraph::getCost(int u, int v)
{
    auto pU = getParent(u);
    auto pV = getParent(v);
    int parentU = pU.first;
    int parentV = pV.first;
    int costU = pU.second;
    int costV = pV.second;

    if (parentU != parentV)
        return -1;
    return costV - costU;
}

int main(int argc, char **argv)
{
    KnowledgeGraph kg(12);
    kg.addEdge(9, 1, 80);
    kg.addEdge(5, 4, 10);
    kg.addEdge(4, 1, 30);
    kg.addEdge(12, 8, 40);
    std::cout << kg.getCost(9, 5) << std::endl;
    std::cout << kg.getCost(1, 4) << std::endl;
    std::cout << kg.getCost(12, 1) << std::endl;
    kg.addEdge(12, 9, 30);
    std::cout << kg.getCost(12, 1) << std::endl;

    return 0;
}