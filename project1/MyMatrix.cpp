#include "MyMatrix.h"
#include <cstdlib>
#include <time.h>

const MyMatrix buildRandomMatrix(int rows, int cols)  {

    MyMatrix m(rows, cols);
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++) 
            m[i][j] = rand() % 10;
    return m;    
}

int main() {

    srand(time(NULL));

    MyMatrix m1 = buildRandomMatrix(4,3);
    MyMatrix m2 = buildRandomMatrix(3,4);

    cout << "M1=" << endl << m1 << endl;
    cout << "M2=" << endl << m2 << endl;

    MyMatrix m3 = m1 * m2;

    cout << "M3=M1*M2=" << endl << m3 << endl;

    return 0;

}
