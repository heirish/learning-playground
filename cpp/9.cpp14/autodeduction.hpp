#ifndef __RETURNTYPE_D__
#define __RETURNTYPE_D__
#include <iostream>
#include <vector>
#include <string>
namespace AUTO_DEDUCTION {

void autovartype_test() {
   //cv-qualifiers
	const int x = 1;
  	auto x1 = x;  //auto will lose the cv-qualifiers., int x1
  	auto const x2 = x; //need to add const manually to deduced to const int, const int x2
  	decltype(x) x3 = x; //const int x3
  	//decltype(auto) x4 = x; //const int x4, c++14
  
  	//references
  	int y = 2;
  	int& ry = y;
  	auto y1 = ry; //int y1, lose the references
  	auto& y2 = ry; //int& y2, need to add & manually
    auto const y3 = ry; //const int y3
  	auto const& y4 = ry; //const int& y4
  	decltype(ry) y5 = ry; //int& y5
  	//decltype(auto) y6 = ry; //int& y6, c++14
  	//decltype(auto) y7 = y4; //const int& y7, c++14
  
  	//references
  	int&& z = 0;
  	auto z1 = std::move(z); //int z1
  	auto&& z2 = std::move(z);//typename std::remove_reference<int &>::type && z2
  	decltype(std::move(z)) z3 = std::move(z); //int&& z3;
  	decltype(auto) z4 = std::move(z); //int&& z4
}

//c++11, need decltype
auto f1(int i) -> decltype(i) { //return  int
    return i;
}
auto f1r(int& i) ->decltype(i) { //return int&
    return i;
}

//c++14
auto f2(int i) {
    return i;
}
auto& f2r(int& i)  {
    return i;
}

template <typename T>
auto& returnref(T& t) {
    return t;
}

template <typename T>
struct SomeContainerWrapper {
    std::vector<const T*> vec;    

    typename std::vector<const T*>::iterator beginCPP03() const {
        return std::begin(vec);
    }
    auto beginCPP11() const -> decltype(std::begin(vec)) {
        return std::begin(vec);
    }
    auto beginCPP14() const {
        return std::begin(vec);
    }
};
template <typename T1, typename T2, typename T3>
auto complicatedFuncCpp11(T1 x, T2 y, T3 z) -> decltype((x*y)-(y*z)) {
    return (x*y) - (y*z);
}
template <typename T1, typename T2, typename T3>
auto complicatedFuncCpp14(T1 x, T2 y, T3 z) {
    return (x*y) - (y*z);
}
void autoreturntype_test() {
    std::cout << "Return Type Deduction" << std::endl;
    //c++11
    std::cout << "need decltype: " << f1(10) << std::endl;
    int x1 = 10;
    f1r(x1) = 20;
    std::cout << "x1=" << x1 << std::endl;
    //check return type
    static_assert(std::is_same<decltype(f1(10)), int>());
    static_assert(std::is_same<decltype(f1r(x1)), int&>());

    //c++14
    std::cout << "c++14: return type auto deduction." << std::endl;
    std::cout << f2(10) << std::endl;
    f2r(x1) = 30;
    std::cout << "x1=" << x1 << std::endl;
    static_assert(std::is_same<decltype(f2(10)), int>());
    static_assert(std::is_same<decltype(f2r(x1)), int&>());

    //return a reference to a deduced type
    //auto f = [](auto& x)->auto& {return returnref(x);};
    //int x = 10;
    //int& y = f(x);
    //直接返回引用
    auto f = [](auto& x) ->auto& {return x;};
    int x = 10;
    f(x) = 20;
    std::cout << x << std::endl;
    std::string s = "hello";
    f(s) = "world";
    std::cout << s << std::endl;
    static_assert(std::is_same<decltype(f(x)), int&>());
    static_assert(std::is_same<decltype(f(s)), std::string&>());
    std::cout << "also works in lambda." << std::endl;
}


/*
- `auto` will always deduce a non-reference type.
- `auto&&` will always deduce a reference type.
- `decltype(auto)` deduces a non-reference or reference type depending upon the value category and the nature of a particular expression
*/

auto func3() { //actually return type is std::string, not std::string&
    static std::string test{"byte"};
    auto& result{test};
    return result;
}
decltype(auto) func4() { //actually return type is std::string&
    static std::string test{"byte again"};
    auto& result{test};
    return result;
}
decltype(auto) func5() { //actually return type is std::string&&
    std::string test{"byte one more time"};
    return std::move(test);
    //demo code, do not use it in your project
    //by the way, do not `std::move`  things out of a function
    //this actually returns a reference to a local object
    //which is not right!
    //Rely on the compiler's RVO.(return value optimization) instead
}
void autoreturntype_test1() {
    static_assert(std::is_same<decltype(func3()), std::string>());
    static_assert(std::is_same<decltype(func4()), std::string&>());
    static_assert(std::is_same<decltype(func5()), std::string&&>());
}
}
#endif //__RETURNTYPE_D__