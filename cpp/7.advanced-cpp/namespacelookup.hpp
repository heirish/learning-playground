#ifndef __LOOKUP__
#define __LOOKUP__
#include <iostream>
namespace A{
    struct X{};
    void g(struct X) {std::cout << "calling A::g()\n";}
}
namespace LOOKUP {
void do_test() {
    struct A::X x;
    g(x); //Koenig lookup ok. can work without qualifier or using declaration. 
}
}
#endif //__LOOKUP__