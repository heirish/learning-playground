#ifndef NULLPTR_DEMO
#define NULLPTR_DEMO
#include <iostream>

namespace NULLPTR_DEMO {
void foo(int i) {std::cout << "foo_int" << std::endl;}
void foo(char* p) {std::cout << "foo_char*" << std::endl;}

void do_test() {
    foo(NULL);   //ambiguity
    foo(nullptr);
}
}
#endif //NULLPTR_DEMO