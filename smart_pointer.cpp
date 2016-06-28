#include <iostream>
#include <cstring>

template<class T>
class SPtr {

public:
    SPtr(T* real_ptr=0) : pointee(real_ptr) {}
    T& operator*() const { return *pointee; }
    T* operator->() const { return pointee; }
   ~SPtr() { delete pointee; }
private:
    T* pointee;
};

class String{
public:
    static int cnt; 
    String(const char* init) {
        data = new char[strlen(init)+1];
        strcpy(data, init);
    }

    String(const String& rhs) : String(rhs.data) {
        std::cout << "Copy Ctor called " << ++cnt << " times." << std::endl;
    }

    void print() { std::cout << data << std::endl; }

private:
   
    char* data;
};
int String::cnt = 0;

String test(String sval) { //parameter second copy ctor
    sval.print();
    return sval; //thrid copy ctor
}

int main() {

    SPtr<String> s = new String("hello");
    String testS = *s; //first copy ctor
    test(testS);
    return 0;
}