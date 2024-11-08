
#include "TwoDSegmentTree.h"
#include <iostream>

template <typename T>
TwoDSegmentTree<T>::TwoDSegmentTree(const std::vector<std::vector<T>> &matrix) : sizeX{matrix.size()}, sizeY{matrix[0].size()}
{
    tree.resize(sizeX * 4);
    for (int i = 0; i < sizeX * 4; i++)
        tree[i].resize(sizeY * 4);
    constructX(0, 0, sizeX - 1, matrix);
}

template <typename T>
TwoDSegmentTree<T>::~TwoDSegmentTree()
{
}

template <typename T>
T TwoDSegmentTree<T>::query(int qsx, int qsy, int qex, int qey)
{
    return queryx(0, 0, sizeX - 1, qsx, qex, qsy, qey);
}

template <typename T>
void TwoDSegmentTree<T>::update(int indexx, int indexy, T val)
{
    updatex(0, 0, sizeX - 1, indexx, indexy, val);
}

template <typename T>
void TwoDSegmentTree<T>::constructX(int ix, int startx, int endx, const std::vector<std::vector<T>> &matrix)
{
    if (startx == endx)
    {
        constructY(ix, startx, endx, 0, 0, sizeY - 1, matrix);
        return;
    }

    int midx = startx + (endx - startx) / 2;
    constructX(ix * 2 + 1, startx, midx, matrix);
    constructX(ix * 2 + 2, midx + 1, endx, matrix);
    constructY(ix, startx, endx, 0, 0, sizeY - 1, matrix);
}

template <typename T>
void TwoDSegmentTree<T>::constructY(int ix, int startx, int endx, int iy, int starty, int endy, const std::vector<std::vector<T>> &matrix)
{
    if (starty == endy)
    {
        if (startx == endx)
        {
            tree[ix][iy] = matrix[startx][starty];
        }
        else
        {
            tree[ix][iy] = tree[ix * 2 + 1][iy] + tree[ix * 2 + 2][iy];
        }
        return;
    }
    int midy = starty + (endy - starty) / 2;
    constructY(ix, startx, endx, iy * 2 + 1, starty, midy, matrix);
    constructY(ix, startx, endx, iy * 2 + 2, midy + 1, endy, matrix);
    tree[ix][iy] = tree[ix][iy * 2 + 1] + tree[ix][iy * 2 + 2];
}

template <typename T>
T TwoDSegmentTree<T>::queryx(int ix, int startx, int endx, int qsx, int qex, int qsy, int qey)
{
    if (endx < qsx || startx > qex)
        return 0;
    if (startx >= qsx && endx <= qex)
        return queryy(ix, 0, 0, sizeY - 1, qsy, qey);
    int midx = startx + (endx - startx) / 2;
    return queryx(ix * 2 + 1, startx, midx, qsx, qex, qsy, qey) + queryx(ix * 2 + 2, midx + 1, endx, qsx, qex, qsy, qey);
}

template <typename T>
T TwoDSegmentTree<T>::queryy(int ix, int iy, int starty, int endy, int qsy, int qey)
{
    if (starty > qey || endy < qsy)
        return 0;
    if (starty >= qsy && endy <= qey)
        return tree[ix][iy];

    int midy = starty + (endy - starty) / 2;
    return queryy(ix, iy * 2 + 1, starty, midy, qsy, qey) + queryy(ix, iy * 2 + 2, midy + 1, endy, qsy, qey);
}

template <typename T>
void TwoDSegmentTree<T>::updatex(int ix, int startx, int endx, int indexx, int indexy, T val)
{
    if (startx == endx)
    {
        updatey(ix, 0, startx, endx, 0, sizeY - 1, indexy, val);
        return;
    }
    int midx = startx + (endx - startx) / 2;

    if (indexx <= midx)
        updatex(ix * 2 + 1, startx, midx, indexx, indexy, val);
    else
        updatex(ix * 2 + 2, midx + 1, endx, indexx, indexy, val);
    updatey(ix, 0, startx, endx, 0, sizeY - 1, indexy, val);
}

template <typename T>
void TwoDSegmentTree<T>::updatey(int ix, int iy, int startx, int endx, int starty, int endy, int indexy, T val)
{
    if (starty == endy)
    {
        if (startx == endx)
            tree[ix][iy] = val;
        else
            tree[ix][iy] = tree[ix * 2 + 1][iy] + tree[ix * 2 + 2][iy];
        return;
    }
    int midy = starty + (endy - starty) / 2;
    if (indexy <= midy)
        updatey(ix, 2 * iy + 1, startx, endx, starty, midy, indexy, val);
    else
        updatey(ix, 2 * iy + 2, startx, endx, midy + 1, endy, indexy, val);
    tree[ix][iy] = tree[ix][iy * 2 + 1] + tree[ix][iy * 2 + 2];
}

int main(int argc, char const *argv[])
{
    std::vector<std::vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    TwoDSegmentTree<int> twoDSegmentTree(matrix);

    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[0].size(); j++)
        {
            for (int i2 = 0; i2 < matrix.size(); i2++)
            {
                for (int j2 = 0; j2 < matrix[0].size(); j2++)
                {
                    std::cout << twoDSegmentTree.query(i, j, i2, j2) << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    twoDSegmentTree.update(1, 1, 10);
    std::cout << twoDSegmentTree.query(0, 0, 2, 2) << std::endl;
    return 0;
}
