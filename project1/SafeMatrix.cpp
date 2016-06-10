#include "SafeMatrix.h"
#include <cstdlib>
#include <time.h>

SafeMaxtrix<int> buildRandomIntMatrix(int rows, int cols)  {

    SafeMaxtrix<int> m(rows, cols);
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            m[i][j] = rand() % 10;
    return m;
}

SafeMaxtrix<double> buildRandomDoubleMatrix(int rows, int cols)  {

    SafeMaxtrix<double> m(rows, cols);
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            m[i][j] = (rand()%10) + (0.1*(rand()%10));
    return m;
}

int main() {

    srand(time(NULL));

    cout << "Building Int Matrices..." << endl;

    SafeMaxtrix<int> m1 = buildRandomIntMatrix(4, 3);
    SafeMaxtrix<int> m2 = buildRandomIntMatrix(3, 4);
    SafeMaxtrix<int> m3;
    SafeMaxtrix<int> m4 = buildRandomIntMatrix(5, 4);

    cout << "Int M1="    << endl <<  m1
         << "Int M2="    << endl <<  m2
         << "Int M1*M2=" << endl << (m1 * m2);
    cout << "Int M3="    << endl <<  m3;
    cout << "Int M3=M1=" << endl << (m3=m1)
         << "Int M4="    << endl <<  m4;

    try {
        cout << "Multiplying M1 and M4..." << endl;
        cout << "M1*M4=" << endl << m1 * m4 << endl;
    } catch(char const* msg) {
        cout << msg << endl;
    }

    cout << "==========" << endl;

    cout << "Building Double Matrices..." << endl;

    SafeMaxtrix<double> fm1 = buildRandomDoubleMatrix(3, 4);
    SafeMaxtrix<double> fm2 = buildRandomDoubleMatrix(4, 2);
    cout << "Double M1="    << endl << fm1
         << "Double M2="    << endl << fm2
         << "Double M1*M2=" << endl <<(fm1 * fm2);

    return 0;
}
