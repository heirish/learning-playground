#ifndef __VAR_TEMPLATE__
#define __VAR_TEMPLATE__

#include <iostream>
#include <limits>

//A variable template defines a family of variables or static data members.
namespace VAR_TEMPLATE {
//before c++14
template <typename T>
struct is_float_old {
    static const bool value = std::is_same<T, float>::value;
};
template <typename T>
void test_old(T t) {
    if (is_float_old<T>::value) {
        std::cout << "float" << std::endl;
    } else {
        std::cout << "not float" << std::endl;
    }

}
//since c++14
template <typename T>
constexpr bool is_float = std::is_same<T, float>::value;

template <typename T>
void test(T t) {
    if (is_float<T>) {
        std::cout << "float" << std::endl;
    } else {
        std::cout << "not float" << std::endl;
    }
}

template <typename T>
T pi = T(3.1415926535897932384626433L);

//variable template can also be specialized
//全特化
template<typename T> int typeID;
template<> constexpr int typeID<int>{0};
template<> constexpr int typeID<float>{1};
template<> constexpr int typeID<double>{2};
//偏特化
template<typename T> constexpr std::size_t v = 6;
template<typename T> constexpr std::size_t v<const T> = 100;

template<std::size_t ...args>
constexpr  std::size_t w = (args+...);

void do_test() {
    test_old(1.0f);
    test_old(1);

    test(1.0f);
    test(1);

    std::cout.precision(std::numeric_limits<long double>::max_digits10);
    pi<char> = 'a'; //每个pi<T>都是不同的变量
    std::cout << pi<char> << std::endl; //a
    std::cout << pi<int> << std::endl; //3
    std::cout << pi<float> << std::endl; 
    std::cout << pi<double> << std::endl;
    std::cout << pi<long double> << std::endl;

    //variable template can also be specialized
    static_assert(typeID<int> == 0);
    static_assert(typeID<float> == 1);
    static_assert(typeID<double> == 2);
    std::cout << v<int> << std::endl; //6
    std::cout << v<double> << std::endl; //6
    std::cout << v<const double> << std::endl; //100

    std::cout << w<1,2,3,4,5> << std::endl;
}
}
#endif //__VAR_TEMPLATE__