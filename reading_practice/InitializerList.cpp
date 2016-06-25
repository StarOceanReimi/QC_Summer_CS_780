#include <iostream>
#include <cstring>
#include <initializer_list>

class P {

private:
    char* data;
public:
    P(int i) {
        data = new char[i+1];
        for(int x=0; x<i; x++)
            data[x] = '-';
        data[i] = '\0';
    };
    P(const std::initializer_list<const char*> list) {
        data = 0;
        for(auto msg : list) {
            int len = strlen(msg);
            int data_len = data == 0 ? 0 : strlen(data);
            char* new_data = new char[len+data_len+1];
            if(data != 0) strcpy(new_data, data);
            strcat(new_data, msg);
            new_data[len+data_len] = '\0';
            delete [] data;
            data = new_data;
        }
    }
    P(const char* msg) {
        std::cout << "conversion ctor." << std::endl;
        int len = strlen(msg);
        data = new char[len+1];
        strcpy(data, msg);
        data[len] = '\0';
    };
    P(const P& p) : P(p.data) { std::cout << "copy ctor." << std::endl; };
   ~P() { std::cout << "deleting.. " << data << std::endl; delete data; }
    P& operator=(const P& p) {
        if(this != &p) {
            P temp(p);
            std::swap(temp.data, this->data);
        }
        return *this;
    }
    const char* GetMsg() const { return const_cast<const char*>(data); }
    void SetMsg(const char* msg) { 
        delete [] data;
        int len = strlen(msg);
        data = new char[len+1];
        strcpy(data, msg);
        data[len] = '\0';
    }
    void PrintMsg() const { std::cout << data << std::endl; }
};

void test(const P& p) {
    p.PrintMsg();
}

int main() {

    for(int i : {1,2,3,4}) {
        std::cout << i << std::endl;
    }
    P largeP {"this is a initializer_list ctor.", " do you think it is a good way of initialing obj?"};
    largeP.PrintMsg();

    P p1 = "test";
    p1 = "test2";
    std::cout << "before test method" << std::endl;
    test(p1);

    const char testMsg[] = {'s', 'f', 'e', 'd', 'h', 'j' ,'\0', 's'};
    std::cout << "array size=" << sizeof(testMsg)/sizeof(char) << std::endl;
    std::cout << "cstring size=" << strlen(&testMsg[0]) << std::endl;
    std::cout << "\\0 bool value is " << (int)'\0' << std::endl;
    std::cout << "size of long long " << sizeof(long long) << std::endl;
    std::cout << "size of long int " << sizeof(long int) << std::endl;
    std::cout << "size of long " << sizeof(long) << std::endl;
    std::cout << "size of int " << sizeof(int) << std::endl;
    std::cout << "size of short " << sizeof(short) << std::endl;
    std::cout << "size of short int " << sizeof(short int) << std::endl;

    return 0;
}

