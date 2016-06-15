#include "VNT.h"
#include <time.h>

std::ostream& operator<< (std::ostream& os, VNT vnt) {
    for(int i=0; i<vnt.rows; i++) {
        os << "[";
        for(int j=0; j<vnt.cols; j++) {
            int v = vnt.sm[i][j];
            if(j != 0)
                os << ",";
            if(v == INT_MAX)
                os << "M";
            else
                os << v;

        }
        os << "]" << std::endl;
    }
    return os;
}

VNT::VNT(int row, int col) {
    rows = row;
    cols = col;
    SafeMatrix<int> temp(row, col);
    for(int i=0; i<row; i++) {
        for(int j=0; j<col; j++) {
            temp[i][j] = INT_MAX;
        }
    }
    sm = temp;
}

int VNT::GetMin() { 
    if(IsEmpty()) throw "VNT is empty.";
    int min = sm[0][0];
    sm[0][0] = INT_MAX;
    checkDownRight(0, 0);
    return min;
}

int VNT::get(int row, int col) {
    if(row >= rows || col >= cols)
        return INT_MAX;
    if(row < 0 || col < 0)
        return INT_MIN;
    return sm[row][col];
}

void VNT::checkUpLeft(int row, int col) {
    int up = get(row-1, col);
    int left = get(row, col-1);
    int cur = get(row, col);
    if(cur >= left && cur >= up)
        return;
    if(up > left) {
        sm[row][col] = up;
        sm[row-1][col] = cur;
        checkUpLeft(row-1, col);
    } else {
        sm[row][col] = left;
        sm[row][col-1] = cur;
        checkUpLeft(row, col-1);
    }
}

void VNT::checkDownRight(int row, int col) {
    int down = get(row+1, col);
    int right = get(row, col+1);
    if(down == INT_MAX && right == INT_MAX)
        return;
    if(compare(down, right) < 0) {
        sm[row][col] = down;
        sm[row+1][col] = INT_MAX;
        checkDownRight(row+1, col);
    } else {
        sm[row][col] = right;
        sm[row][col+1] = INT_MAX;
        checkDownRight(row, col+1);
    }
}

void VNT::shift_right(int row, int col) {
    for(int i=cols-1; i>col; i--) {
        sm[row][i] = sm[row][i-1];
    }
}

void VNT::shift_down(int row, int col) {
    for(int i=rows-1; i>row; i--)
        sm[i][col] = sm[i-1][col];
}

VNT& VNT::Add(int elem) {
    if(IsFull()) throw "VNT is full, can not add elements.";
    sm[rows-1][cols-1] = elem;
    checkUpLeft(rows-1, cols-1);
    return *this;
}

void VNT::Sort(int*& k, int size) {
    int n = (int)ceil(sqrt(size));
    VNT vnt(n, n);
    for(int i=0; i<size; i++) {
        vnt.Add(k[i]);
    }
    int cnt=0;
    while(!vnt.IsEmpty()) {
        try {
            k[cnt++] = vnt.GetMin();
        } catch(const char* msg) {
            std::cout << msg << std::endl;
            exit(1);
        }
    }
}

bool VNT::Find(int elem) {
    if(IsEmpty()) return false;
    if(elem < GetMin()) return false;
    int row=0, col=0, rl=rows, cl=cols;
    int cnt = 0;
    while(true) {
        int cur = sm[row][col];
        if(elem == cur) return true;
        if(elem < cur) cl = col;
        else col++;
        if(col == cl) { col=0; row++; }
        if(row == rl) break;
        cnt++;
    }
    return false;
}

bool VNT::is_row_full(int row) {
    return sm[row][cols-1] < INT_MAX;
}

bool VNT::IsEmpty() {
    return sm[0][0] == INT_MAX;
}

bool VNT::IsFull() {
    return sm[rows-1][cols-1] < INT_MAX;
}

int VNT::compare(int i, int j) {
    return i-j;
}

int main() {
    VNT vnt(3,3);
    int testInts[] = {14, 2, 1, 11, 3, 17, 8, 7, 9};
    int len = sizeof(testInts) / sizeof(int);
    for(int i=0; i<len; i++) {
        try {
            vnt.Add(testInts[i]);
            std::cout << vnt  << std::endl;
        } catch(const char* msg) {
            std::cout << msg << std::endl;
            exit(1);
        }
    }
    srand(time(NULL));
    int* k = new int[10];
    for(int i=0; i<10; i++)
        k[i] = rand()%100;
    for(int i=0; i<10; i++)
        std::cout << k[i] << " ";
    std::cout << std::endl;
    vnt.Sort(k, 10);
    for(int i=0; i<10; i++)
        std::cout << k[i] << " ";
    std::cout << std::endl;
}
