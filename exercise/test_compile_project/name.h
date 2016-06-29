#include <iostream>
struct Name {
    char* first_name;
    char* last_name;
    Name(const char*, const char*);
    operator const char*();
    friend std::ostream& operator<<(std::ostream&, Name);
};