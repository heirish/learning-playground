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
    foo(vec);
    vec.print();  //copy constructor, vec can still be used

    foo(createMyVector()); //optimized by compiler, construct directly, no copy or move
    foo(std::move(vec));
    //resusable destoryed here.
    vec.print();
    
}


}