#include "Polynomial.h"

int main() {

    NormalPolynomialFileParser parser("input.txt");

    Polynomial** polys;

    int len = parser.Parse(polys);

    for(int i=0; i<len; i++) {
        std::cout << "Before Canonicalizing: " << *polys[i] << std::endl;
        polys[i]->Canonicalize();
        std::cout << "After Canonicalizing: " << *polys[i] << std::endl;
    }

    std::cout << "(" << *polys[1] << ") + (" << *polys[0] << ") = " << (*polys[1]+*polys[0]) << std::endl;
    std::cout << "(" << *polys[1] << ") - (" << *polys[0] << ") = " << (*polys[1]-*polys[0]) << std::endl;
    std::cout << "(" << *polys[2] << ") * (" << *polys[2] << ") = " << (*polys[2])*(*polys[2]) << std::endl;
    std::cout << "(" << *polys[1] << ") * (" << *polys[2] << ") = " << (*polys[1])*(*polys[2]) << std::endl;

    delete [] polys;

    return 0;
}
