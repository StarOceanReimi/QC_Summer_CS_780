#ifndef SAFEMATRX_VERSION_0_1
#define SAFEMATRX_VERSION_0_1

#include <iostream>
#include "SafeArray.h"

template<class T>
class SafeMatrix;

template<class T>
ostream& operator<<(ostream& os, SafeMatrix<T> m);

template<class T>
class SafeMatrix {

private:
    SA<SA<T> > matrix;
    int row_low, row_high, col_low, col_high;
    void init(int, int, int, int);
    void destroy();
    SA<SA<T> > Matrix() const { return matrix; };
    void copy_matrix(const SafeMatrix<T>&);
public:

    SafeMatrix(int, int);
    SafeMatrix(int, int, int, int);
    SafeMatrix();
    SafeMatrix(const SafeMatrix<T> &);
   ~SafeMatrix();
    SA<T>&          operator[](int i);
    SafeMatrix<T>  operator*(SafeMatrix<T>);
    SafeMatrix<T>& operator=(SafeMatrix<T>&);

    friend ostream& operator<< <T>(ostream& os, SafeMatrix<T> m);
};

template<class T>
SafeMatrix<T>::SafeMatrix() {
    init(0, 0, 0, 0);
}

template<class T>
SafeMatrix<T>::SafeMatrix(int row, int col) {
    init(0, row-1, 0, col-1);
}

template<class T>
SafeMatrix<T>::SafeMatrix(const SafeMatrix<T> &m) {
    init(m.row_low, m.row_high, m.col_low, m.col_high);
    copy_matrix(m);
}

template<class T>
SA<T>&  SafeMatrix<T>::operator[](int i) {
    return matrix[i];
}

template<class T>
SafeMatrix<T>& SafeMatrix<T>::operator=(SafeMatrix<T>& m) {
    if(&m == this) return *this;
    destroy();
    init(m.row_low, m.row_high, m.col_low, m.col_high);
    copy_matrix(m);
    return *this;
}

template<class T>
SafeMatrix<T> SafeMatrix<T>::operator*(SafeMatrix<T> m) {
    int col_size = col_high-col_low+1;
    int row_size = m.row_high-m.row_low+1;
    if(col_size != row_size) {
        throw "Columns not match Rows. Can not multiply.";
    }
    int new_row_size = row_high-row_low+1;
    int new_col_size = m.col_high-m.col_low+1;
    SafeMatrix<T> new_matrix(new_row_size, new_col_size);
    for(int i=0; i<new_row_size; i++) {
        for(int j=0; j<new_col_size; j++) {
            T sum = 0;
            for(int x=0; x<col_size; x++) {
                sum += matrix[i][x] * m.matrix[x][j];
            }
            new_matrix[i][j] = sum;
        }
    }
    return new_matrix;
}

template<class T>
ostream& operator<<(ostream& os, SafeMatrix<T> m) {

    for(int i=m.row_low; i<=m.row_high; i++) {
        os << "[" << m[i] << "]" << endl;
    }

    return os;
}


template<class T>
void SafeMatrix<T>::init(int rl, int rh, int cl, int ch) {
    row_low  = rl;
    row_high = rh;
    col_low  = cl;
    col_high = ch;

    matrix = SA<SA<T> >(rl, rh);
    for(int i=rl; i<=rh; i++) {
        matrix[i] = SA<T>(cl, ch);
        for(int j=cl; j<=ch; j++)
            matrix[i][j] = 0;
    }
}

template<class T>
SafeMatrix<T>::~SafeMatrix() {
    destroy();
}

template<class T>
void SafeMatrix<T>::destroy() {
}

template<class T>
void SafeMatrix<T>::copy_matrix(const SafeMatrix<T> &m) {
    for(int i=row_low; i<=row_high; i++)
        for(int j=col_low; j<=col_high; j++)
            matrix[i][j] = m.Matrix()[i][j];
}

#endif
