#include "FenwickTree.h"
#include <iostream>
template <typename T>
FenwickTree<T>::FenwickTree(const std::vector<T> &arr) : arrSize(arr.size())
{
    fTree.resize(arrSize + 1);
    for (int i = 1; i <= arrSize; i++)
    {
        fTree[i] += arr[i - 1];
        int nextIndex = i + (i & (-i));
        if (nextIndex <= arrSize)
            fTree[nextIndex] += fTree[i];
    }
}

template <typename T>
T FenwickTree<T>::query(int index)
{
    index++;
    T result = 0;

    while (index > 0)
    {
        result += fTree[index];
        index -= index & (-index);
    }
    return result;
}

template <typename T>
T FenwickTree<T>::query(int qs, int qe)
{
    return query(qe) - query(qs - 1);
}

template <typename T>
void FenwickTree<T>::increase(int index, T inc)
{
    index++;
    while (index <= arrSize)
    {
        fTree[index] += inc;
        index += index & (-index);
    }
}

int main(int argc, char const *argv[])
{
    std::vector<int> arr(5);
    for (int i = 0; i < 5; i++)
        arr[i] = i + 1;
    FenwickTree<int> f(arr);

    for (int i = 0; i < 5; i++)
    {
        for (int j = i; j < 5; j++)
            std::cout << i << " " << j << "->" << f.query(i, j) << "\n";
    }
    return 0;
}
