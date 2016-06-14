#ifndef VNT_VERSION_1_0
#define VNT_VERSION_1_0
#include <climits>
#include "SafeMatrix.h"

class VNT {

private:
    SafeMatrix<int> sm;
    int  rows, cols;
    int  compare(int, int);
    bool is_row_full(int);
    void shift_right(int, int);
    void shift_down(int, int);
public:
    bool IsEmpty();
    bool IsFull();
    VNT& Add(int);
    int  GetMin();
    bool Find(int);
    void Sort(int*, int);
    VNT(int, int);
    friend std::ostream& operator<< (std::ostream&, VNT);
};
#endif


