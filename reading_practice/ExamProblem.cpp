
#include <iostream>

int main() {

    int g = 9;
    int h = 3;
    int* px = &h;

    g = g/ *px;
    
    std::cout << g << std::endl;


    return 0;
}
