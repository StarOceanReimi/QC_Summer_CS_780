#include "name.h"
#include <cstring>
Name::Name(const char* first, const char* last) {
    first_name = new char[strlen(first)+1];
    strcpy(first_name, first);
    last_name = new char[strlen(last)+1];
    strcpy(last_name, last);
}

Name::operator const char*() {
    return strcat(strcat(first_name, " "), last_name);
}

std::ostream& operator<<(std::ostream& os, Name name) {
    os << name.first_name << " " << name.last_name;
    return os;
}