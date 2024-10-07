#ifndef __INTEGER_SEQUENCE__
#define __INTEGER_SEQUENCE__
#include <cxxabi.h>
#include <iostream>
#include <string>
#include <typeinfo>
#include <utility>

namespace integer_seq_demo {
// to get the deduced type info,
// better solution is to use boost,
// type_id_with_cvr<decltype<T>>().pretty_name()
// or check it using compiler error: declare an template struct, no
// implementation.template<typename T> struct showtype;
template <typename T> std::string type_name() {
    typedef typename std::remove_reference<T>::type TR;
    std::string r = typeid(TR).name();

    int status = 0;
    char *demangled = abi::__cxa_demangle(r.c_str(), NULL, NULL, &status);
    if (0 == status) {
        r = std::string(demangled);
        free(demangled);
    }

    if (std::is_const<TR>::value)
        r += " const";
    if (std::is_volatile<TR>::value)
        r += " volatile";
    if (std::is_lvalue_reference<T>::value)
        r += "&";
    else if (std::is_rvalue_reference<T>::value)
        r += "&&";
    return r;
}

void print() { std::cout << std::endl; }
template <typename T> void print(T t) { std::cout << t << std::endl; }
template <typename Int, typename... Ints> void print(Int t, Ints... args) {
    std::cout << t << ",";
    print(args...);
}
template <typename T, T... Ints> void printsequence(std::integer_sequence<T, Ints...> seq) {
    std::cout << "sequence of type:" << type_name<T>() << ",size:" << seq.size() << std::endl;
    //((std::cout << Ints << ","),...); // 这个是c++17中的写法, pack fold expression
    // std::cout << std::endl;
    print(Ints...); // 这个是c++17以前的写法
}
void do_test() {
    printsequence(std::integer_sequence<int, 9, 6, 7, 1, 2, 4, 0>{});       // int, 9,6,7,1,2,4,0
    printsequence(std::integer_sequence<char, 'a', 'f', 'd', 'e', 'a'>{});  // char, a,f,d,e,a
    printsequence(std::integer_sequence<bool, true, false, false, true>{}); // bool, 1,0,0,1

    // make sequence自动生成从0~N-1的sequence
    printsequence(std::make_integer_sequence<int, 10>{}); // int, 0,1,2,3,4,5,6,7,8,9
    printsequence(std::make_index_sequence<5>{});         // unsigned long long, 0,1,2,3,4
}
} // namespace integer_seq_demo
#endif //__INTEGER_SEQUENCE__
