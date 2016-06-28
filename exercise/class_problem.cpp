#include <iostream>

class base1 { int i; int j; };

class base2 { int k; int l; };

class derived : public base1, public base2 {
    int m;
};

int main() {

    derived *d = new derived;
    base1* b1 = d;
    base2* b2 = d;
    std::cout << "d=" << d << ", b1=" << b2 << std::endl;

    if(b2 == d) std::cout << "equal" << std::endl;

    return 0;
}