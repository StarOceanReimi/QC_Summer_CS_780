#include <iostream>
#include <stdlib.h>
#include <algorithm> 

using namespace std;

class MyMatrix {
    private:
        int rows_low, rows_high, column_low, column_high;
        int rows_size, column_size;
        int **p;
        void init(int rl, int rh, int cl, int ch);
        void destroy();

    public:
        MyMatrix(int rh, int ch) {
            init(0, rh, 0, ch);
        };
        MyMatrix(int rl, int rh, int cl, int ch) {
            init(rl, rh, cl, ch);
        };
        MyMatrix(const MyMatrix &m) {
            rows_low = m.rows_low;
            rows_high = m.rows_high;
            column_low = m.column_low;
            column_high = m.column_high;
            rows_size = m.rows_size;
            column_size = m.column_size;
            for(int i=0; i<rows_size; i++) {
                p = new int*[rows_size];
                for(int j=0; j<column_size; j++) {
                    p[i] = new int[column_size];
                    p[i][j] = m.p[i][j];
                }
            }
        };
        ~MyMatrix() {
            destroy();
        }

        int Rows() { return rows_size; }
        int Columns() { return column_size; }

        int* operator[](int i) {
            if(i < rows_low || i > rows_high) {
                cout << "index " << i << " out of range" << endl;
                exit(1);
            }
            return p[i-rows_low];
        }

        MyMatrix operator*(const MyMatrix &m) {

            if(column_size != m.rows_size) {
                cout << "Columns not match Rows. Can not multiply." << endl;
                exit(1);
            }
            MyMatrix newMatrix(rows_size, m.column_size);
            for(int i=0; i<rows_size; i++) {
                for(int j=0; j<m.column_size; j++) {
                    int sum = 0; 
                    for(int x=0; x<column_size; x++) {
                        sum += p[i][x] * m.p[x][j];
                    }
                    newMatrix[i][j] = sum;
                }
            }
            return newMatrix;
        }

        MyMatrix& operator=(const MyMatrix &m) {
            if(this == &m) return *this;
            destroy();
            rows_low = m.rows_low;
            rows_high = m.rows_high;
            column_low = m.column_low;
            column_high = m.column_high;
            rows_size = m.rows_size;
            column_size = m.column_size;
            for(int i=0; i<rows_size; i++) {
                p = new int*[rows_size];
                for(int j=0; j<column_size; j++) {
                    p[i] = new int[column_size];
                    p[i][j] = m.p[i][j];
                }
            }
            return *this;
        }

        friend ostream& operator<<(ostream& os, MyMatrix& m);
};

void MyMatrix::init(int rl, int rh, int cl, int ch) {
    rows_size = rh - rl;
    column_size = ch - cl;

    if(rows_size <= 0 || column_size <= 0) {
        cout << "construct error in bounds definition." << endl;
        exit(1);
    }
    rows_low = rl;
    rows_high = rh;
    column_low = cl;
    column_high = ch;
    p = new int*[rows_size];
    for(int i=0; i<rows_size; i++)
        p[i] = new int[column_size];
}

void MyMatrix::destroy() {
    for(int i=0; i<rows_size; i++)  
        delete [] p[i];
    delete [] p;
}

ostream& operator<<(ostream& os, MyMatrix& m) {
    for(int i=0; i<m.rows_size; i++) {
        cout << "[";
        for(int j=0; j<m.column_size; j++) {
            if(j == 0) {
                cout << m.p[i][j];
            } else
                cout << "," << m.p[i][j];
        }
        cout << "]" << endl;
    }
    return os;
}
