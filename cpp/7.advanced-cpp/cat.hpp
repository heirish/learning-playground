#ifndef __cat__
#define __cat__
#include <string>
namespace STATIC_INIT_FIASCO {
class Cat {
public:
    //explicit Cat(const std::string& name);
    explicit Cat(const char* name);
    ~Cat();
    void meow();

private:
    //std::string _name;
    char* _name;
};
}
#endif //__cat__