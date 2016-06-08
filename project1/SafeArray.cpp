#include <iostream>
#include <cstdlib>
#include <cassert>
#include "SafeArray.h"
using namespace std;

int main(){
    SA<int> a(10);
    int i;
    for( i=0;i<10;i++)
        a[i]=i;
    cout<<"printing using []"<<endl;
    for( i=0;i<10;i++)
        cout<<a[i]<<endl;
    cout<<"and now with overloaded <<"<<endl;
    cout<<a<<endl;

    SA<SA<int> > a2(3);
    for(i=0; i<3; i++) {
        a2[i] = SA<int>(10);
        for(int j=0; j<10; j++) {
            a2[i][j] = j+2;
        }
    }

    cout << a2[0][1] << endl;

    return 0;
}

