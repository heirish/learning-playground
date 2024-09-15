#ifndef __DUALITY__
#define __DUALITY__
#include <iostream>

namespace DUALITY {
class Dog {
public:
    virtual void bark() = 0;
    void run() {std::cout << "I am running.\n";}
    virtual void eat() {std::cout << "I am eating.\n";}
protected:
    void sleep() { std::cout << "I am sleeping.\n";}
};
class YellowDog:public Dog {
public:
    virtual void bark() {std::cout << "I am a yellow dog.\n";}
    void iSleep() {sleep();}
};
}
#endif //__DUALITY__