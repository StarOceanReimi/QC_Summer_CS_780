#include "Polynomial.h"

int main() {

    NormalPolynomialFileParser parser("input.txt");
    Polynomial** polys;
    int len = parser.Parse(polys);


    std::cout << polys[0]->ToString() << std::endl;
    polys[0]->Canonicalize();
    std::cout << polys[0]->ToString() << std::endl;
    return 0;
}
