#include <vector>

class KnowledgeGraph
{
private:
    std::vector<int> parent, rank, cost;
    int n;

    std::pair<int, int> getParent(int u);

public:
    KnowledgeGraph(int n);
    ~KnowledgeGraph();
    void addEdge(int u, int v, int w);
    int getCost(int u, int v);
};
