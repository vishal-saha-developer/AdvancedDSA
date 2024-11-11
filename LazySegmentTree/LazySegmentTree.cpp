#include "LazySegmentTree.h"
#include <iostream>

LazySegmentTree::LazySegmentTree(std::vector<int> &arr) : n(arr.size())
{
    tree.resize(4 * n);
    lazy.resize(4 * n);

    construct(0, 0, n - 1, arr);
}

LazySegmentTree::~LazySegmentTree()
{
}

void LazySegmentTree::update(int l, int r, int val)
{
    update(0, 0, n - 1, l, r, val);
}

int LazySegmentTree::query(int l, int r)
{
    return query(0, 0, n - 1, l, r);
}

void LazySegmentTree::construct(int i, int start, int end, std::vector<int> &arr)
{
    if (start == end)
    {
        tree[i] = arr[start];
        return;
    }
    int mid = start + (end - start) / 2;
    construct(2 * i + 1, start, mid, arr);
    construct(2 * i + 2, mid + 1, end, arr);
    tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
}

void LazySegmentTree::update(int i, int start, int end, int l, int r, int val)
{
    if (lazy[i] != 0)
    {
        if (start != end)
        {
            lazy[2 * i + 1] += lazy[i];
            lazy[2 * i + 2] += lazy[i];
        }
        tree[i] += lazy[i] * (end - start + 1);
        lazy[i] = 0;
    }
    if (end < l || start > r)
        return;
    if (start >= l && end <= r)
    {
        tree[i] += (end - start + 1) * val;
        if (start != end)
        {
            lazy[2 * i + 1] += val;
            lazy[2 * i + 2] += val;
        }
        return;
    }
    int mid = start + (end - start) / 2;
    update(2 * i + 1, start, mid, l, r, val);
    update(2 * i + 2, mid + 1, end, l, r, val);
    tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
}

int LazySegmentTree::query(int i, int start, int end, int l, int r)
{
    if (lazy[i] != 0)
    {
        if (start != end)
        {
            lazy[2 * i + 1] += lazy[i];
            lazy[2 * i + 2] += lazy[i];
        }
        tree[i] += lazy[i] * (end - start + 1);
        lazy[i] = 0;
    }
    if (end < l || start > r)
        return 0;
    if (l <= start && end <= r)
        return tree[i];
    int mid = start + (end - start) / 2;
    return query(2 * i + 1, start, mid, l, r) + query(2 * i + 2, mid + 1, end, l, r);
}

int main(int argc, char **argv)
{
    std::vector<int> arr = {1, 2, 3, 4, 5};

    LazySegmentTree lz(arr);
    for (int sz = 1; sz <= arr.size(); sz++)
    {
        for (int i = 0; i < arr.size() - sz + 1; i++)
        {
            std::cout << i + 1 << " " << i + sz << " " << lz.query(i, i + sz - 1) << "\n";
        }
    }

    for (int sz = 1; sz <= arr.size(); sz++)
    {
        for (int i = 0; i < arr.size() - sz + 1; i++)
        {
            lz.update(i, i + sz - 1, 1);
            std::cout << i + 1 << " " << i + sz << " " << lz.query(i, i + sz - 1) << "\n";
            lz.update(i, i + sz - 1, -1);
        }
    }
    return 0;
}
