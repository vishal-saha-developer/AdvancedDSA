#ifndef __2D_SEGMENT_TREE__
#define __2D_SEGMENT_TREE__

#include <vector>
#include <cstddef>

template <typename T>
class TwoDSegmentTree
{
private:
    const size_t sizeX, sizeY;
    std::vector<std::vector<T>> tree;

    void constructX(int ix, int startx, int endx, const std::vector<std::vector<T>> &matrix);
    void constructY(int ix, int startx, int endx, int iy, int starty, int endy, const std::vector<std::vector<T>> &matrix);
    T queryx(int ix, int startx, int endx, int qsx, int qex, int qsy, int qey);
    T queryy(int ix, int iy, int starty, int endy, int qsy, int qey);
    void updatex(int ix, int startx, int endx, int indexx, int indexy, T val);
    void updatey(int ix, int iy, int startx, int endx, int starty, int endy, int indexy, T val);

public:
    TwoDSegmentTree(const std::vector<std::vector<T>> &matrix);
    ~TwoDSegmentTree();
    T query(int qsx, int qsy, int qex, int qey);
    void update(int indexx, int indexy, T val);
};

#endif
