#include "SparseTable.h"
#include <iostream>

template <typename T>
inline SparseTable<T>::SparseTable(const std::vector<T> &arr) : arrSize(arr.size())
{
    log.resize(arrSize + 1);
    log[0] = INT32_MIN;
    log[1] = 0;
    for (int i = 2; i <= arrSize; i++)
        log[i] = log[i / 2] + 1;

    sTable.resize(log[arrSize] + 1);
    sTable[0].resize(arrSize);
    for (int i = 0; i < arrSize; i++)
        sTable[0][i] = arr[i];

    for (int i = 1; i <= log[arrSize]; i++)
    {
        sTable[i].resize(arrSize - (1 << i) + 1);
        for (int j = 0; j + (1 << i) <= arrSize; j++)
        {
            sTable[i][j] = std::max(sTable[i - 1][j], sTable[i - 1][j + (1 << (i - 1))]);
        }
    }
}

template <typename T>
T SparseTable<T>::query(int qs, int qe)
{
    const size_t l = qe - qs + 1;
    int index = log[l];
    return std::max(sTable[index][qs], sTable[index][qe - (1 << index) + 1]);
}

int main()
{
    std::vector<int> arr{1, 2, 3, 4, 5};
    SparseTable<int> s(arr);

    for (int i = 1; i <= 5; i++)
    {
        for (int j = 0; j + i - 1 < 5; j++)
        {
            std::cout << j << " " << j + i - 1 << " " << s.query(j, j + i - 1) << "\n";
        }
    }
    return 0;
}