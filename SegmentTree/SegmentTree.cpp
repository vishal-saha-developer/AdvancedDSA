#include "SegmentTree.h"
#include <iostream>
template <typename T>
void SegmentTree<T>::build(int i, int start, int end, const std::vector<T> &arr)
{
    if (start == end)
    {
        segTree[i] = arr[start];
        return;
    }

    int mid = (start + end) / 2;
    build(2 * i + 1, start, mid, arr);
    build(2 * i + 2, mid + 1, end, arr);
    segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];
}

template <typename T>
T SegmentTree<T>::query(int i, int start, int end, int qs, int qe)
{
    if (start > qe || end < qs)
        return 0;

    if (qs <= start && end <= qe)
        return segTree[i];

    int mid = (start + end) / 2;
    return query(2 * i + 1, start, mid, qs, qe) + query(2 * i + 2, mid + 1, end, qs, qe);
}

template <typename T>
void SegmentTree<T>::update(int i, int start, int end, int index, T val)
{
    if (start == end)
    {
        segTree[i] = val;
        return;
    }
    int mid = (start + end) / 2;
    if (index <= mid)
        update(2 * i + 1, start, mid, index, val);
    else
        update(2 * i + 2, mid + 1, end, index, val);
    segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];
}

template <typename T>
inline SegmentTree<T>::SegmentTree(const std::vector<T> &arr) : arrSize(arr.size())
{
    segTree.resize(arrSize << 2);
    build(0, 0, arrSize - 1, arr);
}

template <typename T>
T SegmentTree<T>::query(int qs, int qe)
{
    return query(0, 0, arrSize - 1, qs, qe);
}

template <typename T>
void SegmentTree<T>::update(int index, T val)
{
    update(0, 0, arrSize - 1, index, val);
}

int main(int argc, char **argv)
{
    std::vector<int> arr = {1, 2, 3, 4, 5};

    SegmentTree<int> s(arr);

    for (int i = 0; i < 5; i++)
    {
        for (int j = i; j < 5; j++)
            std::cout << i << " " << j << " -> " << s.query(i, j) << "\n";
    }
}
