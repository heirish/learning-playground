#include "Rvalue_Refernce_demo.h"
namespace RVALUE_DEMO {
void printInt(int& i) {std::cout << "lvalue reference:" << i << std::endl;}
void printInt(int&& i) {std::cout << "rvalue reference:" << i << std::endl;}
void foo(MyVector v) {
    v.print();
}
MyVector createMyVector() {
    return MyVector(5,1.2);
}
void do_move_semantic_test() {
    int a = 5; //a is lvalue
    printInt(a);  //call printInt(int&)
    printInt(6);  //call printInt(int&&)
    int& b  = a;  //b is lvalue reference
    printInt(b);

    MyVector vec = createMyVector();
    foo(vec); //copy constructor
    vec.print();  //vec can still be used

    foo(createMyVector()); //optimized by compiler, construct directly, no copy or move
    std::cout << "before std::move" << std::endl;
    foo(std::move(vec));
    //resusable destoryed here.
    std::cout << "after std::move" << std::endl;
    vec.print();
    
}

//not perfect forwarding
template <typename T>
void relay(T arg) {
    foo(arg);  //argument forwarding: forward arg to foo
}

template <typename T>
void perfect_relay(T&& arg) {
    foo(std::forward<T>(arg));
}

void do_perfect_forwarding_test() {
//1. no costly and unneccessary copy constuction of MyVector is made;
//2.rvalue is forwarded as rvalue, and lvalue is forwardded as lvalue;
    std::cout << "lvalue is forwarded as lvalue." << std::endl;
    MyVector reusable = createMyVector();
    //relay(reusable); //lvalue is forwarded as lvalue
    perfect_relay(reusable);

    std::cout << "rvalue is forwarded as rvalue." << std::endl;
    //relay(createMyVector()); //rvalue still called copy constrctor
    perfect_relay(createMyVector());
}

void bar(int&& i) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}
void test_move_forward() {
    bar(3); //ok
    int a = 4;
    //bar(a); //compile error, not matching function call to bar. because it requires rvalue.
    bar(std::move(a)); //ok, std::move convert lvalue to rvalue;
    bar(std::forward<int>(a)); //ok, 如果是非template,直接变成rvalue.
    bar(std::forward<int>(1)); //ok, 如果是非template,直接变成rvalue.

    //move用在非template上, forward用在template上(T&&)
}
}