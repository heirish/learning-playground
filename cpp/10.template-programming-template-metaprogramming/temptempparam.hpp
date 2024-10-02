#ifndef __TEMP_TEMP_PARAM__
#define __TEMP_TEMP_PARAM__
#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <array>

namespace temp_temp_param{

//TTP是一个template template parameter, TTP中的typename T可以省略掉T
//T是一个template parmeter.
//template<template<typename T> typename TTP, typename T>
template<template<typename> typename TTP, typename T>
struct TEST1{
    using type = TTP<T>;
    void printtype() {
        std::cout << __PRETTY_FUNCTION__ << std::endl; //Macro available in GCC
    }
};

template<typename T, typename U>
struct TP {};
template<template<typename, typename> typename TTP, typename T, typename U>
struct TEST2{
    using type = TTP<T, U>;
    void printtype() {
        std::cout << __PRETTY_FUNCTION__ << std::endl; //Macro available in GCC
    }
};

template<template<typename...> typename VTTP, typename... Args>
struct TEST3 {
    using type = VTTP<Args...>;
    void printtype() {
        std::cout << __PRETTY_FUNCTION__ << std::endl; //Macro available in GCC
    }
};

template<typename T>
struct ST{};
template<template<typename>typename ITTP>
struct TEST4 {
    using type = ITTP<int>; 
};

template<int T>
struct SI{};
template<template<int>typename ITTP, int n>
struct TEST5 {
    using type = ITTP<n>; 
};

template<typename T, int n>
struct SVI{};
template<template<typename, int>typename ITTP>
struct TEST6 {
    void printtype() {
        std::cout << __PRETTY_FUNCTION__ << std::endl; //Macro available in GCC
    }
};

void do_test() {
    TEST1<std::vector, int>().printtype();
    static_assert(std::is_same_v<std::vector<int>, TEST1<std::vector, int>::type>);
    static_assert(std::is_same_v<std::vector<float>, TEST1<std::vector, float>::type>);
    static_assert(std::is_same_v<std::list<int>, TEST1<std::list, int>::type>);

    static_assert(std::is_same_v<std::tuple<int, float>, TEST2<std::tuple, int, float>::type>);
    static_assert(std::is_same_v<TP<double, float>, TEST2<TP, double, float>::type>);

    static_assert(std::is_same_v<std::tuple<char,char,bool,int>, TEST3<std::tuple, char,char,bool, int>::type>);

    static_assert(std::is_same_v<ST<int>, TEST4<ST>::type>);
    static_assert(std::is_same_v<std::vector<int>, TEST4<std::vector>::type>);
    static_assert(std::is_same_v<std::list<int>, TEST4<std::list>::type>);

    static_assert(std::is_same_v<SI<0>, TEST5<SI, 0>::type>);

    //这个实际有啥使用案例?
    TEST6<std::array>().printtype();
    TEST6<SVI>().printtype();
}
}
#endif //__TEMP_TEMP_PARAM__