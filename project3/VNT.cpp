#include "VNT.h"

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
    return sm[0][0];
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
    int row=0, col=0;
    while(true) {
        if(is_row_full(row)) { row++; continue; }
        if(compare(elem, sm[row][col]) < 0) {
            shift_right(row, col);
            sm[row][col] = elem;
            for(int i=col; i<cols; i++) {
                int shift_down_row = -1;
                for(int j=row-1; j>=0; j--) {
                    if(compare(sm[row][i], sm[j][i]) < 0) {
                        shift_down_row = j;
                    }
                }
                if(shift_down_row != -1) {
                    int temp = sm[row][i];
                    sm[row][i] = INT_MAX;
                    shift_down(shift_down_row, i);
                    sm[shift_down_row][i] = temp;
                }
            }
            break;
        }
        col++;
        if(col == cols) col=0, row++;
        if(row == rows) break;
    }
    return *this;
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
    int testInts[] = {14, 17, 11, 1, 2, 3, 8, 7, 9};
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
    std::cout << vnt.GetMin() << std::endl;
    std::cout << vnt.Find(10) << std::endl;
}
