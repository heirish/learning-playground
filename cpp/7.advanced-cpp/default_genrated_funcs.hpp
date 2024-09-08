#ifndef __default_gen__
#define __default_gen__
#include <string>
#include <iostream>
namespace DEFAULT_GEN {
class Dog {
public:
    Dog(std::string name = "Bob"):_name(name) {
        std::cout << _name << " is born." << std::endl;
    } 
    ~Dog() { std::cout << _name << " is destoryed" << std::endl;}

private:
    std::string& _name;
};

class collar {
public:
    collar(std::string color) {std::cout << "collar is born with color:" << color << std::endl;}
};
class Cat {
    collar _collar;
};
void generated_func_test() {
    /* Dog
    1. default constructor - no
    2. copy constructor - no, not used
    3. assignment operator - no when std::string& _name, because reference is not copyable, _name is a reference
    3. assignment operator - yes when std::string _name,
    4. destructor - no
    */
    Dog d1("Herry");
    Dog d2;
    //d2 = d1; //compile error  when std::string& _name
            //ok when std::string _name;
    
    //如果_name被声明成了&, Dog类也不能被用于containers, 因为STL containers要求copy assignable and copy constructable.

    //Cat cat; //will not compile, because default constructor can not be generated for Cat due to no default constructor for collar
}
}
#endif //__default_gen__