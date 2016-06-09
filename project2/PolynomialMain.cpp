#include "Polynomial.h"

int main() {

    NormalPolynomialFileParser parser("input.txt");
    Polynomial** polys;
    int len = parser.Parse(polys);

    for(int i=0; i<len; i++) {
        std::cout << polys[i]->ToString() << std::endl;
        polys[i]->Canonicalize();
        std::cout << polys[i]->ToString() << std::endl;
    }
    return 0;
}
