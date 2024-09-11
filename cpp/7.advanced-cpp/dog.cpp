#include "dog.hpp"
#include "cat.hpp"
#include "singleton.hpp"
#include <iostream>

STATIC_INIT_FIASCO::Cat c("Tom");
namespace STATIC_INIT_FIASCO{
Dog::Dog(const std::string& name) {
    _name = name;
    std::cout << "dog " << _name << " is born" << std::endl;
    //c.meow();
    Singtone::getCat().meow();

}
Dog::~Dog() {
    std::cout << "dog " << _name << " is destroyed" << std::endl;
}
void Dog::bark() {
    std::cout << "dog " << _name << " bark" << std::endl;
}
}