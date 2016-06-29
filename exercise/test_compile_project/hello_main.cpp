#include "hello.h"
#include "name.h"

int main() {

    Hello h;
    h.say_hello(Name("Li", "Qiu"));

    return 0;
}