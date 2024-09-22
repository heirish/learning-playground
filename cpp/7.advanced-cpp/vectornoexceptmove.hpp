#ifndef __NOEXCEPT_MOVE__
#define __NOEXCEPT_MOVE__
#include <iostream>
#include <vector>

namespace NO_EXCEPT_MOVE {
class Dog{
public:
    Dog(){std::cout << "Dog()\n";}
    Dog(const Dog&){std::cout << "Dog(const Dog&)\n";} 
    Dog(const Dog&&){std::cout << "Dog(const Dog&&)\n";} 
};
class DogN{
public:
    DogN(){std::cout << "DogN()\n";}
    DogN(const DogN&){std::cout << "DogN(const Dog&)\n";} 
    DogN(const DogN&&) noexcept {std::cout << "DogN(const Dog&&)\n";} 
};
void do_test() {
    std::vector<Dog> v1;
    v1.reserve(2);
    v1.emplace_back(); //constructor
    v1.emplace_back(); //constructor
    std::cout << "memory will expand automatically and copy items\n";
    v1.emplace_back(); //动态扩容, 
    v1.push_back(Dog()); //constructor + move constructor

    std::vector<DogN> v2;
    v2.reserve(2);
    v2.emplace_back();
    v2.emplace_back();
    std::cout << "memory will expand automatically and move items\n";
    v2.emplace_back(); //动态扩容
    v2.push_back(DogN());
}
}
#endif //__NOEXCEPT_MOVE__