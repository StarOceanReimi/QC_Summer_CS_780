#include "hello.h"
#include <iostream>

void Hello::say_hello(const char* name) const {
    std::cout << "Hello, " << name << std::endl;
}