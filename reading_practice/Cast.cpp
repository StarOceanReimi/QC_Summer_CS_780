#include <iostream>

class B {

public:
    explicit operator bool() { std::cout << "use this." << std::endl; return true;} 
    int operator() () { return 10; };
};

int main() {

    int i = 10;
    const int& immutable_I = i;
    // immutable_I = 4; // error since const int&
    const_cast<int&>(immutable_I) = 4; //remove const
    std::cout << "i="  << i << ", immutable_I=" << immutable_I << std::endl;
    int& mutable_I = i;
    // const_cast<const int&>(mutable_I) = 10; // add const

    int* i_ptr = &i;
    void* ptr = static_cast<void*>(i_ptr);
    std::cout << "void ptr=" << ptr << ", derefference it:"  << *static_cast<int*>(ptr) << std::endl;
    
    const int* const_i = new int;
    *const_cast<int*>(const_i) = 5;

    std::cout << "const_i = " << const_i << ", *const_i = " << *const_i << std::endl;

    B b;
    bool bl = static_cast<bool>(b);
    std::cout << b() << std::endl;
    
    return 0;
}
