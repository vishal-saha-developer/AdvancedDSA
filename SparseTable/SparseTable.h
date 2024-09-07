#ifndef __SPARSE_TABLE__
#define __SPARSE_TABLE__
#include <vector>
#include <cstddef>

template <typename T>
class SparseTable
{
private:
    const size_t arrSize;
    std::vector<int> log;
    std::vector<std::vector<T>> sTable;

public:
    SparseTable(const std::vector<T> &arr);
    T query(int qs, int qe);
};

#endif
