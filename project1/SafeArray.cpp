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

    SA<SA<int> > a2(0,0);
    a2[0] = SA<int>(0,0);
    cout << a2[0][0] << endl;

    return 0;
}

