#include <vector>

template <typename T>
class TwoDFenwickTree
{
private:
    std::vector<std::vector<T>> tree;
    const int sizeX, sizeY;

    void constructY(int x, std::vector<T> &arr);
    T query(int x, int y);

public:
    TwoDFenwickTree(std::vector<std::vector<T>> &matrix);
    ~TwoDFenwickTree();

    T query(int x1, int y1, int x2, int y2);
    void update(int x, int y, T inc);
};
