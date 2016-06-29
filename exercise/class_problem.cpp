#include <iostream>

class base1 { int i; int j; public: virtual void test() = 0; };

class base2 { int k; int l; };

class derived : public base1, public base2 {
    int m;
    public:
    void test() { std::cout << "print test." << std::endl; }
};

int main() {

    derived *d = new derived;
    base1* b1 = d;
    base2* b2 = d;
    std::cout << "d=" << d << ", b1=" << b2 << std::endl;
    base1* e = static_cast<base1*>(d);
    base1* f = new derived;
    std::cout << "e=" << e << std::endl;

    std::cout << "f=" << f << std::endl;
    std::cout << "f=" << dynamic_cast<derived*>(f) << std::endl;
    if(b2 == d) std::cout << "equal" << std::endl;

    return 0;
}
