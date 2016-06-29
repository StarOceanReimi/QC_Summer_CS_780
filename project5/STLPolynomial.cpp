#include "STLPolynomial.h"
#include <stdexcept>

PolynomialParser::PolynomialParser(std::string file_name) {
    source = new std::ifstream(file_name.c_str());
}

PolynomialParser::PolynomialParser(std::vector<std::string> lines) {
    source = new std::stringstream;
    for(auto it=lines.begin(); it!=lines.end(); ++it)
        *static_cast<std::stringstream*>(source) << *it << std::endl;
}

PolynomialParser::~PolynomialParser() {
    delete source;
}

std::vector<Polynomial> PolynomialParser::Parse() {
    std::vector<Polynomial> polys;
    for(std::string line; getline(*source, line); ) {
        std::vector<std::string> temp = string_split(line, " ");
        if(temp.size()%2!=0) throw "Invalid expression! Numbers of your input should be even.";
        TERMS terms;
        for(auto it=temp.begin(); it!=temp.end(); ++it) {
            int coeffient = std::stoi(*it++);
            int power = std::stoi(*it);
            if(terms.count(power) > 0)
                terms[power] += coeffient;
            else
                terms[power] = coeffient;
        }
        polys.push_back(Polynomial(terms));
    }
    return polys;
}

Polynomial::Polynomial() {  } 
Polynomial::Polynomial(const Polynomial& p) : terms(p.terms) { }
Polynomial::Polynomial(TERMS terms) : terms(terms) { }

Polynomial Polynomial::operator+(const Polynomial& p) const {
    return term_plus(terms, p.terms, false);
}

Polynomial Polynomial::operator-(const Polynomial& p) const {
    return term_plus(terms, p.terms, true);
}

Polynomial Polynomial::operator*(const Polynomial& p) const {
    return term_product(terms, p.terms);
}

Polynomial& Polynomial::operator=(const Polynomial& p) {
    if(this == &p) return *this;
    terms = p.terms;
    return *this;
}

std::ostream& operator<<(std::ostream &os, Polynomial p) {
    os << p.to_string();
    return os;
}

std::string Polynomial::to_string() {
    std::stringstream ss;
    bool first = true;
    for(auto &elem : terms) {
        int p = elem.first, c = elem.second;
        if(c == 0) continue;
        if(!first && c > 0) ss << '+';
        if(p == 0) ss << c;
        else {
            if(c == 1) ss << 'x';
            else if(c == -1) ss << "-x";
            else ss << c << 'x';
            if(p != 1) ss << '^' << p;
        }
        first = false;
    }
    std::string retval = ss.str();
    if(retval.size() == 0) return "0";
    return retval;
}

int main() {

    PolynomialParser p("input.txt");
    std::vector<Polynomial> polys;
    try {
        polys = p.Parse();
    } catch(const char* msg) {
        std::cout << msg << std::endl;
        exit(1);
    } catch(std::invalid_argument e) {
        std::cout << "invalid input. Please check your input" << std::endl;
        exit(1);
    }

    Polynomial sum;
    Polynomial diff;
    Polynomial prod;

    bool first = true;
    int line = 0;
    for(auto it=polys.begin(); it!=polys.end(); ++it) {
        std::cout << "Polynomial in line " << ++line << " is: " << *it << std::endl;
        if(first) sum = diff = prod = *it; 
        else {
            sum = sum+*it;
            prod = prod**it;
            diff = diff-*it;
        }
        first = false;
    }
    std::cout << std::endl;
    std::cout << "Their Sum: "<< sum << std::endl;
    std::cout << "Their Difference:" << diff << std::endl;
    std::cout << "Their Product: " << prod << std::endl;

    return 0;
}
