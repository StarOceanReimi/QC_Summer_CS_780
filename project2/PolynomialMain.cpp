#include "Polynomial.h"

int main() {

    NormalPolynomialFileParser parser("input.txt");

    Polynomial** polys;

    int len = parser.Parse(polys);

    polys[1] = polys[0];

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

    std::string poly_expression = "x+x^2+5x^2-4x^3+10\r\n4x+x^2+5x^2-4x^3+10";
    NormalPolynomialStringParser sparser(poly_expression);
    Polynomial** polys1;
    int length = sparser.Parse(polys1);

    std::cout << *polys1[0] + *polys1[1] << std::endl;
    std::cout << *polys1[1] << std::endl;

    delete [] polys1;

    return 0;
}
