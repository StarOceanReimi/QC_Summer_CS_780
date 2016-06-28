#include <iostream>
#include <cstring>

class String {
public:
    String(const char* value="");
    String(const String&);
   ~String();
    String& operator=(const String&);
    friend std::ostream& operator<<(std::ostream&, String); 

private:
    struct StringValue {
        char* data;
        int refCnt;
        StringValue(const char* data);
       ~StringValue(); 
    };
    StringValue* value;
    
};

String::String(const char* value) : value(new StringValue(value)) {
    std::cout << "Convert Ctor..." << value << std::endl;
}
String::String(const String& copy) : value(copy.value) {
    value->refCnt++;
}
String::~String() { if (--value->refCnt == 0) delete value; }
String& String::operator=(const String& rhs) {
    if(this == &rhs) return *this;
    if(--value->refCnt == 0) delete value;
    value = rhs.value;
    ++value->refCnt;
    return *this;
}

String::StringValue::StringValue(const char* value) : refCnt(1) {
    int len = strlen(value);
    data = new char[len+1];
    strcpy(data, value);
}

String::StringValue::~StringValue() {
    delete [] data;
}

std::ostream& operator<<(std::ostream& os, String str) {
    os << str.value->data;
    return os;
}

int main() {

    String a, b, c;
    a = b = c = "Hello";
    std::cout << "a=" << a << ", b=" << b << ", c=" << c << std::endl;
    b = "Hello1";
    std::cout << "a=" << a << ", b=" << b << ", c=" << c << std::endl;

    return 0;
}