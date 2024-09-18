#ifndef __LAMBDA__
#define __LAMBDA__
#include <iostream>
#include <string>
#include <memory>

namespace LAMBDA {
class Pointer {
friend std::ostream& operator<<(std::ostream& os, const Pointer& p); 
friend Pointer operator+(const Pointer& p1, const Pointer& p2); 
public:
    explicit Pointer(int x, int y):_x(x), _y(y) {}
    Pointer() = default;
private:
    int _x{0};
    int _y{0};
};

std::ostream& operator<<(std::ostream& os, const Pointer& p) {
    os << "Pointer(" << p._x << ", " << p._y << ")";
    return os;
}
Pointer operator+(const Pointer& p1, const Pointer& p2) {
    return Pointer(p1._x + p2._x, p1._y + p2._y);
}

void generic_lambda_test() {
    //before c++14
    auto lambdai = [](int x, int y){return x+y;};
    std::cout << "3+4=" << lambdai(3,4) << std::endl;
    auto lambdaf = [](float x, float y){return x+y;};
    std::cout << "3.1+4.2=" << lambdaf(3.1,4.2) << std::endl;
    //std::cout << "3.1+4.2=" << lambdai(3.1,4.2) << std::endl; //data cutted
    auto lambdas = [](const std::string& s1, const std::string& s2){return s1+s2;};
    //std::cout << "3.1+4.2=" << lambdas(3.1,4.2) << std::endl; //compile error

    //c++14, define one, used for all
    auto lambdag = [](auto x, auto y){return x+y;};
    //gets converted to something like this during compilation
    /*
    struct CompilerGeneratedlambdag {
        template<typename T1, typename T2>
        auto operator()(T1 x, T2 y) const {
            return x+y;
        }
    };
    */
    std::cout << "3+4=" << lambdag(3,4) << std::endl;
    std::cout << "3.1 + 4.2  = " << lambdag(3.1, 4.2) << std::endl;
    std::cout <<  "hello + world = " << lambdag(std::string("hello"), std::string("world")) << std::endl;
    Pointer p1(1,2), p2(3,4);
    std::cout <<  p1 << "+" << p2 << "=" << lambdag(p1, p2) << std::endl;
    static_assert(std::is_same<decltype(lambdag(3,4)), int>());
    static_assert(std::is_same<decltype(lambdag(3.1f,4.2f)), float>());
    static_assert(std::is_same<decltype(lambdag(p1,p2)), Pointer>());

    //labmdas can also variadic parameter packs.
    auto l1 = [](auto... xs) {return sizeof...(xs);};
}



int factory(int i) {return 10*i;}
//lambda init-capture
void lambda_init_capture_test() {
    //c++11, can only capture variable in enclosed scope
    int x = 2;
    std::string  text{"CO"};
    auto f = [x, &text] {
        text.append(std::to_string(x));
    };
    f();
    std::cout << text << std::endl;

    //c++14, can capture variable in enclosed scope and init-capture(init a new variable in lambda capture)
    auto f1 = [y = factory(2)] {return y;}; //y is a new variable, declared and initialized in lambda capture
    std::cout << f1() << std::endl; 
    auto generator = [v=0] () mutable{
        //this would not compile without 'mutable' as we are modifying on each call
        return ++v; 
    };
    //std::cout << v << std::endl; //v is not accessible outside lambda, compile error
    std::cout << generator() << std::endl; //1
    std::cout << generator() << std::endl; //2
    std::cout << generator() << std::endl; //3

    auto p = std::make_unique<int>(1);
    //auto task1 = [=] {*p = 5;}; //Error:std::unique_ptr cannot be copied
    auto task2 = [p = std::move(p)] { *p = 5;}; //OK, p is moved constructed
    //the original p is empty after task2 is CREATED
    //std::cout << *p << std::endl; //coredump event task2 is not called yet.

    //lambda中新引入的变量a=a*10，可以在lambda中修改，但是不会影响外部变量
    //要修改外部变量，需要使用引用捕获&r
    int a = 1;
    auto fa = [&r = a, a = a*10] (){
        ++r;
        std::cout << "r=" << r << ", a=" << a << std::endl;
        return r+a;
    };
    std::cout << fa() << "," << a << std::endl;
}
}
#endif //__LAMBDA__