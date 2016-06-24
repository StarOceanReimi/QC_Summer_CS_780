#ifndef STLPOLYNOMIAL_VERSION_1_0
#define STLPOLYNOMIAL_VERSION_1_0

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

struct greater {
    bool operator() (const int& a, const int& b) const { return a > b; }
};

typedef std::map<int, int, greater> TERMS;

TERMS term_plus(TERMS terms1, TERMS terms2, bool negative) {
    for(auto &el: terms2) {
        int p = el.first, c = el.second;
        if(terms1.count(p) > 0) {
            terms1[p] = negative ? terms1[p] - c
                                 : terms1[p] + c;
        } else {
            terms1[p] = c;
        }
    }
    return terms1;
}

TERMS term_product(TERMS terms1, TERMS terms2) {
    TERMS new_terms;
    for(auto &t2: terms2) {
        for(auto &t1: terms1) {
            int new_power = t1.first+t2.first;
            if(new_terms.count(new_power) > 0)
                new_terms[new_power] += t1.second * t2.second;
            else
                new_terms[new_power] = t1.second * t2.second;
        }
    }
    return new_terms;
}

std::vector<std::string> string_split(const std::string& str, std::string delim) {
    int start = 0, end = -1;
    std::vector<std::string> result;
    while((end=str.find(delim, start)) != std::string::npos) {
        std::string temp = str.substr(start, end-start);
        result.push_back(temp);
        start = end + delim.size();
    }
    result.push_back(str.substr(start));
    return result;
}

class Polynomial {

public:
    Polynomial();
    Polynomial(const Polynomial&);
    Polynomial(TERMS);
    Polynomial  operator+(Polynomial&);
    Polynomial  operator-(Polynomial&);
    Polynomial  operator*(Polynomial&);
    Polynomial& operator=(Polynomial&);
    std::string to_string();
    friend std::ostream& operator<<(std::ostream&, Polynomial);
private:
    TERMS terms;
};

class PolynomialParser {

public:
    PolynomialParser(std::string);
    PolynomialParser(std::vector<std::string>);
   ~PolynomialParser();
    std::vector<Polynomial> Parse();
private:
    std::istream *source;
};

#endif
