#include <iostream>
#include <cstring>

class RCObj {

private:
    int refCnt;
    bool sharable;

public:
    RCObj();
    virtual ~RCObj() = 0;
    void add_reference();
    void remove_reference();
    bool is_sharable();
    bool is_shared();
    void mark_unsharable();
};

RCObj::RCObj() : refCnt(0), sharable(true) { }
RCObj::~RCObj() {}
void RCObj::add_reference() { refCnt++; }
void RCObj::remove_reference() { if (--refCnt == 0) delete this; }
bool RCObj::is_sharable() { return sharable; }
bool RCObj::is_shared() { return refCnt > 1; }
void RCObj::mark_unsharable() { sharable = false; }

template<class T>
class RCPtr {
public:
    RCPtr(T* realPtr = 0);
    RCPtr(const RCPtr& ptr);
    ~RCPtr();
    T* operator->() const { return pointee; }
    T& operator*() const { return *pointee; }
    RCPtr& operator=(const RCPtr&);
private:
    T* pointee;
    void init();
};

template<class T>
RCPtr<T>::RCPtr(T* realPtr) : pointee(realPtr) { init(); }

template<class T>
RCPtr<T>::RCPtr(const RCPtr& ptr) : pointee(ptr.pointee) { init(); }

template<class T>
RCPtr<T>::~RCPtr() { if (pointee) pointee->remove_reference(); }

template<class T>
void RCPtr<T>::init() {
    if (pointee == 0) return;
    if (!pointee->is_sharable()) {
        pointee = new T(*pointee);
    }
    pointee->add_reference();
}

template<class T>
RCPtr<T>& RCPtr<T>::operator=(const RCPtr<T>& new_ptr) {
    if (this != &new_ptr) {
        if (pointee) pointee->remove_reference();
        pointee = new_ptr.pointee;
        init();
    }
    return *this;
}

class String {
public:
    String(const char* value = "");
    friend std::ostream& operator<<(std::ostream&, String);

private:
    struct StringValue : public RCObj {
        char* data;
        StringValue(const char*);
        StringValue(const StringValue&);
        ~StringValue();
        void init(const char* initData);
    };
    RCPtr<StringValue> str_value;

};

String::String(const char* value) : str_value(new StringValue(value)) { }

String::StringValue::StringValue(const StringValue& copy) {
    init(copy.data);
}

String::StringValue::StringValue(const char* value) {
    init(value);
}

void String::StringValue::init(const char* initData) {
    int len = strlen(initData);
    data = new char[len + 1];
    strcpy(data, initData);
    data[len] = '\0';
}

String::StringValue::~StringValue() {
    delete[] data;
}

std::ostream& operator<<(std::ostream& os, String str) {
    os << str.str_value->data;
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