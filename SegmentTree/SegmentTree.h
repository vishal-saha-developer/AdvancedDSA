#ifndef __SEGMENT_TREE__
#define __SEGMENT_TREE__

#include <vector>
#include <cstddef>

template <typename T>
class SegmentTree
{
private:
    std::vector<T> segTree;
    const size_t arrSize;
    void build(int i, int start, int end, const std::vector<T> &arr);
    T query(int i, int start, int end, int qs, int qe);
    void update(int i, int start, int end, int index, T val);

public:
    SegmentTree(const std::vector<T> &arr);
    T query(int qs, int qe);
    void update(int index, T val);
};

#endif