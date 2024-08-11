#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
#include "initializer_list_demo.h"
#include "nullptr_demo.h"
#include "enum_class_demo.h"
#include "Rvalue_Refernce_demo.h"

void initializer_list_test() {
    int arra[4] = {1,2,3,4};
    std::vector<std::string> strs = {"now", "you", "can", "init", "vector", "using", "initializer_list"};
    InitDemo::MyVec vec1{0,1,2,3,4,5};
    InitDemo::MyVec vec2 = {0,1,2,3,4,5};
}

void auto_test() {
    auto a = 6;
    auto b = 9.6;
    auto str = "this is a string";

    std::cout << "type of a :" << typeid(a).name() << std::endl;
    std::cout << "type of b:" << typeid(b).name() << std::endl;
    std::cout << "type of str:" << typeid(str).name() << std::endl;

    std::vector<int> vec{1,2,3,4};
    auto it = vec.begin();
    std::cout << "type of it:" << typeid(it).name() << std::endl;
}

void forloop_test() {
    std::vector<int> vec{1,2,3,4,5};
    //before c++11.
    for(std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    //in c++11
    for(auto const& i:vec) {
        std::cout << i << " ";
    }

}

constexpr int func() {return 3;}
int constexpr_test() {
    int arr[6];
    int arr1[func() + 3]; //compile error if no constexpr for function func()
}
int main(int argc, char const *argv[])
{
    //initializer_list_test();
    //auto_test();
    //forloop_test();
    //NULLPTR_DEMO::do_test();
    //ENUM_CLASS_DEMO::do_enum_demo_test();
    //constexpr_test();
    
    //RVALUE
    //RVALUE_DEMO::do_move_semantic_test();
    RVALUE_DEMO::do_perfect_forwarding_test();
    return 0;
}
