#ifndef __FENWICK_TREE__
#define __FENWICK_TREE__

#include <vector>
#include <cstddef>
template <typename T>
class FenwickTree
{
private:
    std::vector<T> fTree;
    const size_t arrSize;

public:
    FenwickTree(const std::vector<T> &arr);
    T query(int index);
    T query(int qs,int qe);
    void increase(int index, T inc);
};

#endif