#include <iostream>

#ifndef POLYNOMIAL_VERSION_1_0
#define POLYNOMIAL_VERSION_1_0

class Term {

private:
    int coeffient;
    char alphbet;
    int power;

public:
    Term&   FilpCoeffient();
    Term    operator+(Term);
    Term    operator*(Term);
    std::string  ToString();

    Term(const Term&);
    Term(int coeffient=1, char alphbet='x', int power=0);
   ~Term();
};

class Polynomial {

private:
    Term*   terms;

public:
    Polynomial&   Canonicalize();
    Polynomial&   Order();
    Polynomial    operator+(Polynomial);
    Polynomial    operator*(Polynomial);
    Polynomial    operator-(Polynomial);
    std::string   ToString();
    Polynomial(const Polynomial&);
    Polynomial(const Term*&);
   ~Polynomial();
};

class PolynomialFileParser {

private:
    std::string input_path;

protected:
    virtual Term ParseTerm(std::string);
    virtual std::string* SplitPattern(std::string, int&);
public:
    Polynomial* Parse();
    PolynomialFileParser(std::string);
};

#endif // POLYNOMIAL_VERSION_1_0
