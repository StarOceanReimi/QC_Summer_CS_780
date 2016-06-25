#include <iostream>
#include <cstring>

class RCObj {

public:
    RCObj() : counter(0), sharable(true) {};
    RCObj(const RCObj& obj) : counter(obj.counter), sharable(obj.sharable) {};
    void add_reference() {
        if(sharable) ++counter;
    };
    void remoev_reference() {
        --counter;
    };

private:
    int counter;
    bool sharable;
};

class String {

public:
    String(const char* value = "");
    String(const String&);
    String& operator=(const String&);
   ~String();
    friend std::ostream& operator<<(std::ostream&, String);
private:
    struct StringValue {
        int refCnt;
        char* value;
        StringValue(const char*);
       ~StringValue();
    };
    StringValue *value;
};

std::ostream& operator<<(std::ostream &os, String s) {
    os << s.value->value;
    return os;
}

String::StringValue::StringValue(const char* initValue) : refCnt(1) {
    int len = strlen(initValue);
    value = new char[len+1];
    strcpy(value, initValue);
}

String::StringValue::~StringValue() {
    delete [] value;
}
String::String(const String& rhs) : value(rhs.value) {
    ++value->refCnt;
}

String::String(const char* value) : value(new StringValue(value)) { }

String::~String() { if(--value->refCnt == 0) delete value; }

String& String::operator=(const String& rhs) {
    if(this == &rhs) return *this;
    if(--value->refCnt == 0) delete value;
    value = rhs.value;
    ++value->refCnt;
    return *this;
}

int main() {
    String a,b,c;
    a = b = c = "Hello";
    std::cout << "a=" << a << ", b=" << b << ", c=" << c << std::endl;
    a = "Hello1";
    std::cout << "a=" << a << ", b=" << b << ", c=" << c << std::endl;

    return 0;
}
