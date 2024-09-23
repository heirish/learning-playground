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
T max(const T& a, const T& b) { //better version for user-defined data type
//T max(T a, T b) {
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
DogI max<DogI>(const DogI& lhs, const DogI& rhs) {
    return lhs.getAge() > rhs.getAge()? lhs : rhs;
}

template<typename T, std::size_t N>
void foo(T input) {
    for(std::size_t i = 0; i<N; i++) {
        std::cout << input << std::endl;
    }
}

void do_test() {
    std::cout << "max(3,4)=" << max(3,4) << std::endl;  //using max(int,int)
    std::cout << "max(1.2,4.9)=" << max(1.2f,4.9f) << std::endl;  //using max(float,float)

    std::cout << "max('a', 'w')=" << max('a', 'w') << std::endl; //using max(T,T)
    Dog d1{"Seven", 3};
    Dog d2{"Yellow", 1};
    std::cout << "max(d1, d2):" << max(d1, d2) << std::endl; //using max(T,T)

    //full specialization全特化测试
    DogI di1{"Seven", 3};
    DogI di2{"Yellow", 1};
    std::cout << max(di1, di2) << std::endl;

    //non object-type template parameter
    foo<float, 3>(3.14f);
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

template <typename T>
T Sum(T t) {
    return t;
}
template <typename T, typename... Args>
auto Sum(T start, Args... args) {
//T Sum(T start, Args... args) {
    return start + Sum(args...);
}
void test(const int& v) {
   std::cout << v << std::endl; 
}
void vairadic_function_template() {
    std::cout << Sum(1,2,3,4) << std::endl;
    //std::cout << Sum<double>(1,2.2f,3.7,4) << std::endl;
    std::cout << Sum(1,2.2f,3.7,4) << std::endl; //c++11之后可以用auto作为返回值，让编译器自动推导类型

    int a = 1;
    test(a);
    test(2);
}



};
#endif //__FUNCTION_TEMPALTE__
