#include <cstdio>
#include <iostream>

int func1() { return 10; }
int& func2() { 
    static int a = 10;
    return a; 
}
const int& func3() {
    static int a = 9;
    return a;
}


class c1 {

private:
    mutable int i;
    int j;
public:
    c1() : i(1), j(2) {};
    int GetI() const { return i++; }; //cant not compile unless change i to mutable
    int GetJ() { return j++; };

};

template<int num>
void bar()
{
    static int baz;
    printf("bar<%i>::baz = %i\n", num, baz++);
}

int main() {

    // func1() = 10; //error
    func2() = 11;
    std::cout << func2() << std::endl;
    // func3() = 1; error since return val is const int&
    c1 c;
    // error. since in stream function will be call in different order in different compiler
    std::cout << "i=" << c.GetI() << ", after getI i = " << c.GetI() << std::endl;

    std::cout << "j=" << c.GetJ();
    std::cout  << ", after getJ j = " << c.GetJ() << std::endl;

    bar<1>(); // Output will be 0
    bar<2>(); // Output will be 0
    bar<3>(); // Output will be 0
    bar<1>(); // Output will be 1
    bar<2>(); // Output will be 1
    bar<3>(); // Output will be 1
    bar<1>(); // Output will be 2
    bar<2>(); // Output will be 2
    bar<3>(); // Output will be 2

    return 0;

}
