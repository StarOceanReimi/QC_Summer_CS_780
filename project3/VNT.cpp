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
    if(compare(cur, left)>=0 && compare(cur, up)>=0)
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
    step = 1;
    if(IsEmpty()) return false;
    if(elem < sm[0][0]) return false;
    if(elem > sm[rows-1][cols-1]) return false;
    int r=rows-1,c=0;
    while(r>=0&&c<cols) {
        int cur = sm[r][c];
        if(elem > cur) c++;
        else if(elem < cur) r--;
        else return true;
        step++;
    }
    step--;
    return false;
}

bool VNT::IsEmpty() {
    return sm[0][0] == INT_MAX;
}

bool VNT::IsFull() {
    return sm[rows-1][cols-1] < INT_MAX;
}

int VNT::compare(int i, int j) {
    return i > j ? 1 : i==j ? 0 : -1;
}

void initRandomArray(int*& arr, int size) {
    delete [] arr;
    arr = new int[size];
    for(int i=0; i<size; i++)
        arr[i] = rand() % 100;
}

void printArray(int* arr, int size) {
    for(int i=0; i<size; i++) {
        if(i != 0)
            std::cout << ",";
        std::cout << arr[i];
    }
    std::cout << std::endl;
}

int main() {
    srand(time(NULL));
    VNT vnt(3,3);
    int testInts[] = {5,4,6,2,3,1,8,9,7};
    int len = sizeof(testInts) / sizeof(int);
    for(int i=0; i<len; i++) {
        try {
            std::cout << "Inserting " << testInts[i]  << std::endl;
            vnt.Add(testInts[i]);
            std::cout << vnt  << std::endl;
        } catch(const char* msg) {
            std::cout << msg << std::endl;
            exit(1);
        }
    }

    std::cout << "extracting minium value: " << vnt.GetMin() <<  std::endl;
    std::cout << vnt  << std::endl;
    std::cout << "extracting minium value: " << vnt.GetMin() <<  std::endl;
    std::cout << vnt  << std::endl;

    std::cout << "Please enter a number to find: ";
    int target;
    std::cin >> target;

    std::cout << "Finding element "<< target <<  " in testInts" << std::endl;
    bool found = vnt.Find(target);
    std::cout << (found ? "Found target " : "Not Found ") << "in " <<  vnt.Step() << " steps." << std::endl;
    std::cout << std::endl;

    std::cout << "Initializing Random Array..." << std::endl;
    int* toBeSortedArray = 0;
    int  size = 20;
    initRandomArray(toBeSortedArray, size);
    std::cout << "Before Sorting:" << std::endl;
    printArray(toBeSortedArray, size);
    vnt.Sort(toBeSortedArray, size);
    std::cout << "After Sorting:" << std::endl;
    printArray(toBeSortedArray, size);

    delete[] toBeSortedArray;

}
