#include "Polynomial.h"

void OutputResult(std::ostream& os, PolynomialParser& parser) {

    Polynomial** polys = 0;
    int len = 0;
    try {
        len = parser.Parse(polys);
    } catch(const char* msg) {
        std::cout << msg << std::endl;
        exit(1);
    }
    
    if(len < 1) {   
        std::cout<<"parsing error please check your input."<<std::endl; 
        exit(1);
    }

    Polynomial sum  = *polys[0];
    Polynomial diff = *polys[0];
    Polynomial prod = *polys[0];

    for(int i=0; i<len; i++) {
        os << "Polynomial in line " << i+1 << ": " << *polys[i] << std::endl;
        polys[i]->Canonicalize();
        os << "Its canonical form is: " << *polys[i] << std::endl;
        os << std::endl;
        if(i > 0) {
            try {
                sum =  sum  + (*polys[i]);
                diff = diff - (*polys[i]);
                prod = prod * (*polys[i]);
            } catch(const char* msg) {
                os << msg << std::endl;
                exit(1);
            }
        }
    }

    os << std::endl;
    os << "Their Sum is: " << sum.Canonicalize() << std::endl;
    os << "Their Difference is: " << diff.Canonicalize() << std::endl;
    os << "Their Product is: " << prod.Canonicalize() << std::endl;

    for(int i=0; i<len; i++)
        delete polys[i];
    delete[] polys;

}

int main() {
    
    SimplePolynomialParser parser("input.txt");
    std::ofstream output("output.txt");
    OutputResult(output,    parser);
    OutputResult(std::cout, parser);
    return 0;
}
