#include "Polynomial.h"
#include <stdexcept>

void OutputResult(std::ostream& os) {

    NormalPolynomialFileParser parser("input.txt");
    Polynomial** polys = 0;
    int len = parser.Parse(polys);

    if(len < 1) {   
        os<<"parsing error please check your input."<<std::endl; 
        exit(1);
    }

    Polynomial sum  = *polys[0];
    Polynomial diff = *polys[0];
    Polynomial prod = *polys[0];

    for(int i=0; i<len; i++) {
        os << "Polynomial that you input: " << *polys[i] << std::endl;
        polys[i]->Canonicalize();
        os << "After Canonicalizing: " << *polys[i] << std::endl;
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
    os << "Their Sum is: " << sum << std::endl;
    os << "Their Difference is: " << diff << std::endl;
    os << "Their Production is: " << prod << std::endl;

    for(int i=0; i<len; i++)
        delete polys[i];
    delete[] polys;

}

int main() {

    OutputResult(std::cout);
    std::ofstream output("output.txt");
    OutputResult(output);
    
    return 0;
}