#include <iostream>

using namespace std;

int main() {
    
    int n = 100;

    for(int i=1; i<n; i++) {
        //when i == 7 (i&(i-1)) eques 6 which is not a number of power of 2
        cout << (i&(i-1)) << endl;
    }

    return 0;
}
