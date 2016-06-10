#ifndef POLYNOMIAL_VERSION_1_0
#define POLYNOMIAL_VERSION_1_0
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctype.h>
#include <cstdlib>


template<class T>
void array_resize(T*& arr, int old_size, int new_size);

class Term {

private:
    int coeffient;
    std::string alphbet;
    int power;

public:
    Term&   FilpCoeffient();
    Term    operator+(Term);
    Term    operator*(Term);
    std::string  ToString();

    int Coeffient() { return coeffient; };
    std::string Alphbet() { return alphbet; }
    int Power() { return power; }

    Term() : coeffient(1), alphbet("x"), power(0) {};
    Term(int coeffient, int power) : coeffient(coeffient), alphbet("x"), power(power) {};
    Term(int coeffient, std::string alphbet, int power);

    friend std::ostream& operator<<(std::ostream& os, Term t);
};

std::ostream& operator<<(std::ostream& os, Term t) {
    os << t.ToString();
    return os;
}

Term::Term(int c, std::string a, int p) {
    this->coeffient = c;
    this->alphbet = a;
    this->power = p;
}

Term& Term::FilpCoeffient() {
    this->coeffient = 0 - this->coeffient;
    return *this;
}

Term  Term::operator+(Term t) {
    if(alphbet != t.alphbet && alphbet != "" && t.alphbet != "") {
        throw "Can not add since alpha is differnet.";
    }
    if(power != t.power) {
        throw "Can not add since power is differnet.";
    }
    return Term(coeffient+t.coeffient, alphbet, power);
}

Term Term::operator*(Term t) {
    if(alphbet != t.alphbet && alphbet != "" && t.alphbet != "") {
        throw "Not support to multiply with differnt alphabet.";
    }
    std::string a;
    if(alphbet.size() == 0 && t.alphbet.size() == 0) {
        a = "";
    } else {
        if(alphbet.size() == 0) a = t.alphbet;
        else a = alphbet;
    }
    return Term(coeffient*t.coeffient, a, power+t.power);
}

std::string Term::ToString() {
    std::stringstream ss;
    if(coeffient == 0) return "";

    if(coeffient == 1 && power == 0) {
        return "1";
    }

    if(coeffient == -1 && power == 0) {
        return "-1";
    }

    if(coeffient != 1) {
        if(coeffient == -1) {
            ss << "-";
        } else
            ss << coeffient;
    }

    if(power != 0) {
        if(alphbet.size() != 0) {
            ss << alphbet;
        }
        if(power != 1) {
            ss << "^" << power;
        }
    }

    return ss.str();
}

class Polynomial {

private:
    Term**   terms;
    int      terms_length;
    void     order_terms_by_power();
    void     destroy();
public:
    Polynomial&   Canonicalize();

    Polynomial&   operator=(Polynomial&);
    Polynomial    operator+(Polynomial);
    Polynomial    operator*(Polynomial);
    Polynomial    operator-(Polynomial);
    std::string   ToString();

    Polynomial(const Polynomial&);
    Polynomial(Term**&, int);
   ~Polynomial();

    friend std::ostream& operator<<(std::ostream&, Polynomial);
};

std::ostream& operator<<(std::ostream& os, Polynomial p) {
    os << p.ToString();
    return os;
}

Polynomial::Polynomial(const Polynomial& p) {
    this->terms_length = p.terms_length;
    this->terms = new Term*[this->terms_length];
    for(int i=0; i<this->terms_length; i++) {
        this->terms[i] = p.terms[i];
    }
}

Polynomial::Polynomial(Term**& terms, int len) {
    this->terms_length = len;
    this->terms = new Term*[len];
    for(int i=0; i<len; i++) {
        this->terms[i] = terms[i];
    }
}

void Polynomial::destroy() {
    delete [] terms;
}

std::string Polynomial::ToString() {
    std::stringstream ss;
    for(int i=0; i<terms_length; i++) {
        if(i != 0 && terms[i]->Coeffient() > 0) {
            ss << '+';
        }
        ss << *terms[i];
    }

    return ss.str();
}

Polynomial::~Polynomial() {
    destroy();
}

void Polynomial::order_terms_by_power() {
    for(int i=0; i<terms_length; i++) {
        for(int j=i; j<terms_length; j++) {
            if(terms[j]->Power() > terms[i]->Power()) {
                Term* temp = terms[j];
                terms[j] = terms[i];
                terms[i] = temp;
            }
        }
    }
}

Polynomial& Polynomial::Canonicalize() {
    order_terms_by_power();
    Term** new_terms;
    int counter = 0;
    Term* prev = terms[0];
    for(int i=1; i<terms_length; i++) {
        if(prev->Power() == terms[i]->Power()) {
            *prev = (*prev + *terms[i]);
        } else {
            array_resize(new_terms, counter++, counter);
            new_terms[counter-1] = prev;
            prev = terms[i];
        }
    }
    array_resize(new_terms, counter++, counter);
    new_terms[counter-1] = prev;

    delete [] terms;

    this->terms_length = counter;
    this->terms = new Term*[terms_length];
    for(int i=0; i<counter; i++)
        terms[i] = new_terms[i];

    delete[] new_terms;

    return *this;
}

Polynomial Polynomial::operator+(Polynomial p) {

    int len = terms_length + p.terms_length;
    Term** temp_terms = new Term*[len];

    for(int i=0; i<terms_length; i++)
        temp_terms[i] = new Term(*terms[i]);

    for(int i=terms_length; i<len; i++)
        temp_terms[i] = new Term(*p.terms[i-terms_length]);

    Polynomial new_p(temp_terms, len);
    new_p.Canonicalize();

    return new_p;
}

Polynomial Polynomial::operator-(Polynomial p) {
    int len = terms_length + p.terms_length;
    Term** temp_terms = new Term*[len];

    for(int i=0; i<terms_length; i++)
        temp_terms[i] = new Term(*terms[i]);

    for(int i=terms_length; i<len; i++) {
        temp_terms[i] = new Term(*p.terms[i-terms_length]);
        temp_terms[i]->FilpCoeffient();
    }

    Polynomial new_p(temp_terms, len);
    new_p.Canonicalize();

    return new_p;
}

Polynomial Polynomial::operator*(Polynomial p) {
    int len = terms_length * p.terms_length;
    Term** temp_terms = new Term*[len];
    for(int i=0; i<terms_length; i++) {
        for(int j=0; j<p.terms_length; j++) {
            temp_terms[i*p.terms_length+j] = new Term((*terms[i]) * (*p.terms[j]));
        }
    }

    Polynomial new_p(temp_terms, len);
    new_p.Canonicalize();
    return new_p;
}


class PolynomialFileParser {

private:
    std::string input_path;

protected:
    virtual Term ParseTerm(std::string) = 0;
    virtual int  SplitPattern(std::string, std::string*&) = 0;
public:
    int Parse(Polynomial**& polynomials);
    PolynomialFileParser(std::string);
};

class NormalPolynomialFileParser : public PolynomialFileParser {

protected:
    virtual Term ParseTerm(std::string);
    virtual int  SplitPattern(std::string, std::string*&);

public:
    NormalPolynomialFileParser(std::string input) : PolynomialFileParser(input) {};
};

PolynomialFileParser::PolynomialFileParser(std::string input) {
    this->input_path = input;
}

template<class T>
void array_resize(T*& arr, int old_size, int new_size) {
    T* new_arr = new T[new_size];
    int copy_size = std::min(old_size, new_size);
    for(int i=0; i<copy_size; i++)
        new_arr[i] = arr[i];
    std::swap(arr, new_arr);
}

int PolynomialFileParser::Parse(Polynomial**& polynomials) {

    std::ifstream input(this->input_path.c_str());

    int counter = 0;
    for(std::string line; std::getline(input, line);) {
        std::string* patterns;
        int patterns_len = this->SplitPattern(line, patterns);
        Term** terms = new Term*[patterns_len];
        for(int i=0; i<patterns_len; i++) {
            terms[i] = new Term(this->ParseTerm(patterns[i]));
        }
        array_resize(polynomials, counter++, counter);
        polynomials[counter-1] = new Polynomial(terms, patterns_len);

        delete [] patterns;
    }
    return counter;
}

Term NormalPolynomialFileParser::ParseTerm(std::string term_pattern) {
    const char* tp = term_pattern.c_str();
    std::string coeffient_str = "";
    std::string alpha_str = "";
    std::string power_str = "";
    bool coeffient_part = true;
    for(int i=0; i<term_pattern.size(); i++) {
        char cur = tp[i];
        if(cur == '+' || cur == '^') continue;
        if(coeffient_part) {
            if(isalpha(cur)) {
                coeffient_part = false;
                alpha_str.append(1, cur);
                continue;
            }
            coeffient_str.append(1, cur);
            continue;
        }
        power_str.append(1, cur);
    }
    int c = -1, p = -1;
    if(coeffient_str.size() == 0) c = 1;
    if(alpha_str.size() == 0) { p = 0; }
    else if(power_str.size() == 0) { p = 1; }

    if(c == -1) c = atoi(coeffient_str.c_str());
    if(p == -1) p = atoi(power_str.c_str());

    return Term (c, alpha_str, p);
}

int NormalPolynomialFileParser::SplitPattern(std::string polynomial_line, std::string*& term_patterns) {

    std::string temp_term;
    const char* line = polynomial_line.c_str();
    int pattern_counter = 0;
    for(int i=0; i<polynomial_line.size(); i++) {
        char cur = line[i];
        switch(cur) {
            case '+':
            case '-':
                if(temp_term.size() != 0) {
                    array_resize(term_patterns, pattern_counter++, pattern_counter);
                    term_patterns[pattern_counter-1] = temp_term;
                    temp_term = "";
                }
                break;
        }
        temp_term.append(1, cur);
    }
    if(temp_term.size() != 0) {
        array_resize(term_patterns, pattern_counter++, pattern_counter);
        term_patterns[pattern_counter-1] = temp_term;
    }
    return pattern_counter;
}


#endif // POLYNOMIAL_VERSION_1_0

























