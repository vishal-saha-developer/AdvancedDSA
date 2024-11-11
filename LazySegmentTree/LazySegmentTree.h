#include <vector>

class LazySegmentTree
{
private:
    std::vector<int> tree, lazy;
    const int n;
    void construct(int i, int start, int end, std::vector<int> &arr);
    void update(int i, int start, int end, int l, int r, int val);
    int query(int i, int start, int end, int l, int r);

public:
    LazySegmentTree(std::vector<int> &arr);
    ~LazySegmentTree();
    void update(int l, int r, int val);
    int query(int l, int r);
};

