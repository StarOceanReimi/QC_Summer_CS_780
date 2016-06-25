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
    const char* GetData() { return data; }
private:
    char* data;
};

String::String(const String& rhs) : String(rhs.data) {}

String::String(const char* value) {
    int len = strlen(value);
    data = new char[len+1];
    strcpy(data, value);
}

String::~String() { delete [] data; }

String& String::operator=(const String& rhs) {
    if(this != &rhs) {
        String temp(rhs);
        std::swap(this->data, temp.data);
    }
    return *this;
}

int main() {
    String a,b,c;
    a = b = c = "Hello";
    std::cout << "a=" << a.GetData() << ", b=" << b.GetData() << ", c=" << c.GetData() << std::endl;
    b = "hello2";
    std::cout << "a=" << a.GetData() << ", b=" << b.GetData() << ", c=" << c.GetData() << std::endl;

    return 0;
}
