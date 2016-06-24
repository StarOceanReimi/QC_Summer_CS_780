#include <cstring>
#include <cstdlib>
#include <iostream>

class String {

private:
    static String *newlist;
    union {
        String *freepointer;
        char   *rep;
    };
    int len;
public:
    String() { rep = new char[1]; rep[0] = '\0'; }
    String(const char *cs) {
        rep = new char[::strlen(cs)+1];
        ::strcpy(rep, cs);
    }
   ~String() { delete [] rep; }
    void* operator new(size_t);
    void  operator delete(void*);
};

String* String::newlist = 0;

void* String::operator new(size_t size) {

    std::cout << "string new! size=" << size << std::endl;

    if(size != sizeof(String)) {
        return malloc(size);
    } else if(!newlist) {
        newlist = (String*)new char[100*sizeof(String)];
        for(int i=0; i<99; i++)
            newlist[i].freepointer = &(newlist[i+1]);
        newlist[99].freepointer = 0;
    }
    String *savenew = newlist;
    newlist = newlist->freepointer;
    return savenew;
}

void String::operator delete(void *p) {
    std::cout << "string delete!" << std::endl;
    String *s = (String*)p;
    s->freepointer = newlist;
    newlist = s;
}


int main() {

    std::cout << "Size of String is:"<< sizeof(String) << std::endl;
    String *p = new String;
    delete p;

    return 0;
}
