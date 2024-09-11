#include "cat.hpp"
#include "dog.hpp"
#include <iostream>
#include <cstring>

namespace STATIC_INIT_FIASCO {
//Cat::Cat(const std::string& name) {
Cat::Cat(const char* name):_name(nullptr) {
    int len = strlen(name);
    _name = (char*)malloc(len+1);
    if (len > 0) {
        strncpy(_name, name, len);
    }
    _name[len] = '\0';
    std::cout << "cat " << _name << " is born" << std::endl;
}
Cat::~Cat() {
    std::cout << "cat " << _name << " destroyed" << std::endl;
    if (_name !=nullptr) {
        free(_name);
        _name = nullptr;
    }
}
void Cat::meow() {
    std::cout << "cat " << _name << " meow" << std::endl;
}
}