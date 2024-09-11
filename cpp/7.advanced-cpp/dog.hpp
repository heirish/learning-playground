#ifndef __dog__
#define __dog__
#include <iostream>
namespace STATIC_INIT_FIASCO {
class Dog {
public:
    explicit Dog(const std::string& name);
    ~Dog();
    void bark();
private:
    std::string _name;
};
}
#endif //__dog__