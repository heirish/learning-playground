#ifndef __TYPE_DEDUCTION__
#define __TYPE_DEDUCTION__
#include <vector>
#include <iostream>

namespace type_deduction {
template<typename T>

//Type deduction problem: usually works as expected, but not always
class MyContainer {
public:
    //can not work for MyContainer<bool> b; b[42]=false;
    //T& operator[](int index) {return _data[index];}
    //can not work for MyContainer<int> i; i[42] = 2;
    //auto operator[](int index) {return _data[index];}
    explicit MyContainer(std::size_t size=1):_data(size){}
    decltype(auto) operator[](int index) {return _data[index];}
private:
    std::vector<T> _data;
};

template<typename T>
void func(T param) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

template<typename T>
void funcR(T& param) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

template<typename T>
void funcFR(T&& param) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void do_test() {
    MyContainer<int> a;
    //a[42] = 2;

    //////////Duduction for by value parameters/////////////////////
    //- If expr's type is a reference, ignore that
    //- If expr is **top-level** const or volatile, ignore that
    std::cout << "========Deduction for by value parameters========\n";
    int x = 42;
    const int &rcx = x;
    func(x); //func(T) [ T = int], param type = int, T = int
    func(rcx); //func(T) [T = int]. param type = int, T = int, if expr's type is reference, ignor it, if expr is const or volatile, ignor it.
    func(42); //func(T) [T = int], param type = int, T = int
    int temp = 1;
    func(std::move(temp));//func(T) [T = int], param type = int, T = int

    //if expr is top-level const or volatile, ignore that
    const int* p1 = nullptr; //ptr to const int
    const int* const p2 = nullptr; //const ptr to const int
    int* const p3 = nullptr; //const ptr to int
    func(p1); //param type = const int*
    func(p2); //param type = const int*  //top-level const is stipped
    func(p3); //param type = int*  //top-level const is stripped

    ////////////////Deduction for references and pointers///////////////
    //- If expr's type is a reference, ignore that
    //- Pattern-match expr's type against the parameter to determine T
    std::cout << "============Deduction for references and pointers=========\n";
    const int cx = 42;
    funcR(x); //param type = int&, T = int. Rule 2
    funcR(cx); //param type = const int&, T = const int. Rule 2
    funcR(rcx); //param type = const int&, T = const int, Rule 1
    int temp1 = 1;
    //funcR(std::move(temp1));//can not deduce, no matching function

    /////////////////////Deduction for forwarding references////////////////
    //- if expr is lvalue or lvalue reference of type E. T=E&, parameter is of type E& && => reference collapsing => E&
    //- if expr is rvalue(reference), ignore references and pattern-match
    std::cout << "=============Deduction for forwarding references============\n";
    funcFR(x); //param type = int&, T=int&, Rule 1
    funcFR(rcx); //param type = const int&, T = const int&, Rule 1
    funcFR(42); //param type = int&&, T = int, Rule 2
    int temp2 = 1;
    funcFR(std::move(temp2));//param type = int&&, T = int, Rule 2

    std::cout << "============auto type deduction=============\n";
    /////auto
    int ax = 1;
    int &rax = ax;
    const int cxx = 42;
    auto av1 = x;
    static_assert(std::is_same_v<decltype(av1), int>); //a1:int
    auto av2 = rax;
    static_assert(std::is_same_v<decltype(av2), int>); //a2:int
    auto av3 = std::move(ax);
    static_assert(std::is_same_v<decltype(av3), int>); //a3:int
    auto av4 = cxx;
    static_assert(std::is_same_v<decltype(av4), int>); //a3:int
    ////auto&
    int ax1 = 1;
    int &rax1 = ax1;
    auto& ar1 = ax1;
    static_assert(std::is_same_v<decltype(ar1), int&>);
    auto& ar2 = rax1;
    static_assert(std::is_same_v<decltype(ar2), int&>);
    //auto& ar3 = std::move(ax1); //compile error
    ////auto&&
    int ax2 = 1;
    int &rax2 = ax2;
    auto&& arr1 = ax2;
    static_assert(std::is_same_v<decltype(arr1), int&>);
    auto&& arr2 = rax2;
    static_assert(std::is_same_v<decltype(arr2), int&>);
    auto&& arr3 = std::move(ax2);
    static_assert(std::is_same_v<decltype(arr3), int&&>);

    /////////////////////decltype type deduction//////////////////////////
    int i = 1;
    const int&ci = i;
    static_assert(std::is_same_v<decltype(i), int>);
    static_assert(std::is_same_v<decltype(ci), const int&>);
    static_assert(std::is_same_v<decltype(42), int>);
    static_assert(std::is_same_v<decltype(std::move(i)), int&&>);

    /////////////////////lambda capture deduction//////////////////////////
    std::cout << "============lambda deduction=============\n";
    //capture deduction
    const int la = 1;
    [la](){
        //this is different with auto or template deduction by value parameter, cv is kept.
        static_assert(std::is_same_v<decltype(la), const int>);
    }();
    //compiler error
    //auto fcd = [la]()mutable {
    //    return ++la;
    //};
    auto f = [la = la]() mutable {
        //here la is init-capture deduction, 
        //it follows the same rule as auto deduction, la is deducted to int, cv is stripped
        static_assert(std::is_same_v<decltype(la), int>);
        return ++la;
    };
    std::cout << f() << "," << f() << std::endl; //2,3
}

}
#endif //__TYPE_DEDUCTION__