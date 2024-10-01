#ifndef __META_HELLO__
#define __META_HELLO__
#include <iostream>
#include <type_traits>
#include <string>

namespace meta_hello {

//type traits:to query type properties
template <typename T>
struct is_pointer {
    static constexpr bool value = false;
};
template <typename T>
struct is_pointer<T*> {
    static constexpr bool value = true;
};


//metafunction:manipulate type
template <typename T>
struct strip_pointer{
    using type = T;
};
template <typename T>
struct strip_pointer<T*>{
    using type = T;
};

template <typename T>
void print(T t) {
    using T_without_pointer = strip_pointer<T>::type; //c++20
    if constexpr(std::is_pointer<T>::value) {
    //if constexpr(is_pointer<T>::value) { //self defined type traits
        if constexpr (std::is_floating_point<T_without_pointer>::value) {
            std::cout << 'F';
        }
        std::cout << *t;
    } else {
        std::cout << t;
    }
}
template<typename A, typename B, typename C>
void print3(A a, B b, C c) {
    print(a);
    std::cout << ",";
    print(b);
    std::cout << ",";
    print(c);
    std::cout << std::endl;
}
void do_test() {
    print3(1,2,3); //1,2,3
    std::string hello = "Hello";
    print3(hello, 2, hello); //Hello, 2 Hello
    print3(&hello, 2, hello); //Hello, 2 Hello
    float f = 2.1;
    double db = 3.1;
    print3(1,&f, &db); //1, F2.1, F3.1
}
}
#endif //__META_HELLO__