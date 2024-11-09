#include "TwoDFenwickTree.h"
#include <iostream>

template <typename T>
TwoDFenwickTree<T>::TwoDFenwickTree(std::vector<std::vector<T>> &matrix) : sizeX(matrix.size()), sizeY(matrix[0].size())
{
    tree.resize(sizeX + 1, std::vector<T>(sizeY + 1, 0));
    for (int i = 1; i <= sizeX; i++)
    {
        for (int j = 1; j <= sizeY; j++)
        {
            tree[i][j] += matrix[i - 1][j - 1];
            int nextIndexj = j + (j & (-j));
            if (nextIndexj <= sizeY)
                tree[i][nextIndexj] += matrix[i - 1][j - 1];

            int nextIndex = i + (i & (-i));
            if (nextIndex <= sizeX)
            {
                tree[nextIndex][j] += matrix[i - 1][j - 1];
                if (nextIndexj <= sizeY)
                    tree[nextIndex][nextIndexj] += matrix[i - 1][j - 1];
            }
        }
    }
}

template <typename T>
TwoDFenwickTree<T>::~TwoDFenwickTree()
{
}

template <typename T>
T TwoDFenwickTree<T>::query(int x, int y)
{
    x++, y++;
    T result = 0;
    while (x > 0)
    {
        int tempY = y;
        while (tempY > 0)
        {
            result += tree[x][tempY];
            tempY -= tempY & (-tempY);
        }
        x -= x & (-x);
    }
    return result;
}

template <typename T>
T TwoDFenwickTree<T>::query(int x1, int y1, int x2, int y2)
{
    if (x1 < 0 || y1 < 0 || x2 >= sizeX || y2 >= sizeY)
        return 0;

    if (x2 < x1 || y2 < y1)
        return 0;

    return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
}

template <typename T>
void TwoDFenwickTree<T>::update(int x, int y, T inc)
{
    x++, y++;
    while (x <= sizeX)
    {
        int tempY = y;
        while (tempY <= sizeY)
        {
            tree[x][tempY] += inc;
            tempY += tempY & (-tempY);
        }
        x += x & (-x);
    }
}

int main(int argc, char const *argv[])
{
    std::vector<std::vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    TwoDFenwickTree<int> twoDFenwickTree(matrix);

    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[0].size(); j++)
        {
            for (int i2 = 0; i2 < matrix.size(); i2++)
            {
                for (int j2 = 0; j2 < matrix[0].size(); j2++)
                {
                    std::cout << twoDFenwickTree.query(i, j, i2, j2) << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    twoDFenwickTree.update(1, 1, 10);
    std::cout << twoDFenwickTree.query(0, 0, 2, 2) << std::endl;

    return 0;
}