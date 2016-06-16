#ifndef VNT_VERSION_1_0
#define VNT_VERSION_1_0

#include <climits>
#include <cmath>
#include "SafeMatrix.h"

class VNT {

private:
    SafeMatrix<int> sm;
    int  step;
    int  rows, cols;
    int  compare(int, int);
    int  get(int, int);
    void checkDownRight(int, int);
    void checkUpLeft(int, int);
public:
    bool IsEmpty();
    bool IsFull();
    VNT& Add(int);
    int  GetMin();
    int  Step() { return step; };
    bool Find(int);
    void Sort(int*&, int);
    VNT(int, int);
    friend std::ostream& operator<< (std::ostream&, VNT);
};

#endif


