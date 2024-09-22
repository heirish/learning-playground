#ifndef __FUNCTION_TEMPALTE__
#define __FUNCTION_TEMPALTE__
#include <iostream>
namespace FUNCTION_TEMPLATE {

//function overloading
int max(int a, int b)
{
    std::cout << "max(int,int)\n";
    return a>b?a:b;
}
float max(float a, float b) {
    std::cout << "max(float,float)\n";
    return a>b?a:b;
}

template<typename T>
T max(T a, T b) {
    std::cout << "max(T,T)\n";
    return (a>b)?a:b;
}

class Dog {
public:
    explicit Dog(const char* name, int age = 1):_name(name), _age(age) {}
private:
    int _age{1};
    std::string _name{""};
    friend bool operator > (const Dog& lhs, const Dog& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Dog& dog);
};
bool operator > (const Dog& lhs, const Dog& rhs) {
    return lhs._age > rhs._age;
}
std::ostream& operator<<(std::ostream& os, const Dog& dog) {
    os << "name:" << dog._name << ",age:" << dog._age << std::endl;
    return os;
}

//或者用全特化实现Dog的max函数
class DogI {
public:
    explicit DogI(const char* name, int age = 1):_name(name), _age(age) {}
    int getAge() const {return _age;}
private:
    int _age{1};
    std::string _name{""};
    friend std::ostream& operator<<(std::ostream& os, const DogI& dog);
};
std::ostream& operator<<(std::ostream& os, const DogI& dog) {
    os << "name:" << dog._name << ",age:" << dog._age << std::endl;
    return os;
}

template<>
DogI max<DogI>(DogI lhs, DogI rhs) {
    return lhs.getAge() > rhs.getAge()? lhs : rhs;
}

void do_test() {
    std::cout << "max(3,4)=" << max(3,4) << std::endl;  //using max(int,int)
    std::cout << "max(1.2,4.9)=" << max(1.2f,4.9f) << std::endl;  //using max(float,float)

    std::cout << "max('a', 'w')=" << max('a', 'w') << std::endl; //using max(T,T)
    Dog d1{"Seven", 3};
    Dog d2{"Yellow", 1};
    std::cout << "max(d1, d2):" << max(d1, d2) << std::endl; //using max(T,T)

    //全特化测试
    DogI di1{"Seven", 3};
    DogI di2{"Yellow", 1};
    std::cout << max(di1, di2) << std::endl;
}

class A {
public:
    template <typename T>
    A (T t) {
        std::cout << "function template works for constructor" << std::endl;
    }

    //compile error
    /*
    template<typename T>
    ~A(){std::cout << "~A()" << std::endl;}    
    */

    //comiler error
    /*
    template <typename T>
    virtual void print(T msg){} 
    */

    template <typename T>
    void print(T msg){} 
};

};
#endif //__FUNCTION_TEMPALTE__
