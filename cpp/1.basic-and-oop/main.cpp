#include <iostream>
#include "cat.h"
#include "person.h"
#include "worker.h"
#include "engineer.h"
using namespace std;

void basic_data_type()
{
    int x{0};
    cout << sizeof(x) << endl; //4
    cout << "Integer " << sizeof(int) << endl; //4
    cout << "Char " << sizeof(char) << endl; //1
    cout << "Bool " << sizeof(bool) << endl; //1
    cout << "Float " << sizeof(float) << endl; //4
    cout << "Double " << sizeof(double) << endl; //8
    cout << "Long " << sizeof(long) << endl; //4
    cout << "Long Long " << sizeof(long long) << endl; //8
    cout << "Unsigned Long " << sizeof(unsigned long) << endl; //4
    cout << "Long Double " << sizeof(long double) << endl; //16
    

    cout << "Bool*" << sizeof(bool*) << endl; //8
    cout << "Float*" << sizeof(float*) << endl; //8
    cout << "Double*" << sizeof(double*) << endl; //8
    cout << "Long*" << sizeof(long*) << endl; //8
    
    auto value1{12};
    auto value2{2.4};
    auto value3{123ll};
    auto value4{1.3f};
    auto value5{123ul};
    auto value6{1.3l};
    cout << "Int " << sizeof(value1) << endl; //4
    cout << "Double " << sizeof(value2) << endl; //8
    cout << "Long Long " << sizeof(value3) << endl; //8
    cout << "Float " << sizeof(value4) << endl; //4
    cout << "unsiged long " << sizeof(value5) << endl; //4
    cout << "long double " << sizeof(value6) << endl; //16
}

void test_lambda() 
{
    auto func = [](){
        cout << "lambda" << endl;
    };
    func();

    int a{10};
    auto func0 = [a](){
        cout << "a = " << a << endl; 
    };
    func0();

    int b{20};
    auto func1 = [&b](){
        b=13;
    };
    func1();
    cout << "b = " << b << endl;

}

void test_heap_array() 
{
    double *pArray{new double[13]{4.2, 3.1}};
    for(size_t i{0}; i<13; i++) 
    {
        cout << "index:" << i << ",value: " << pArray[i] << endl;
    }
    double arr[13]{123,34,2};
    cout << "arr size:" << sizeof(arr)/sizeof(arr[0]) << endl; //13
    cout << size(arr) << endl;  //std::size from c++17

    delete [] pArray;
    pArray = nullptr;
}

int add(int a, int b) {
    return a+b;
}
void test_lvalue_rvalue()
{
    int a0{1};
    int a1{2};
    int a2{3};
    //都是左值, 都可以获取地址
    cout << &a0 << "," << &a1 << "," << &a2 << endl;
    int *p(&a0);
    cout << *p << endl;

    int x{0};
    x = (a1 + a2); //(a1 + a2)是右值,到x进行了一次copy
    //int *p = &(a1 + a2); //因为是右值，不能获取地址
    int &&result1 = a1 + a2;  //result1也是右值，因此到result1没有copy,效率更高
    cout << result1 << endl;
    int &&result2 = add(a1, a2);
    cout << result2 << endl;
}

void test_const_object_method() 
{
    const Cat cat1("moon", 3);
    cat1.print_object();

    const Cat *cat_point(&cat1);
    cout << cat_point->get_name() << endl;
    cout << cat_point->get_age() << endl;
    cat_point->print_object();

    const Cat &cat_ref(cat1);
    cout << cat_ref.get_name() << endl;
    cout << cat_ref.get_age() << endl;
    cat_ref.print_object();

    Cat c("cat1", 2);
    c.name() = "min";
    c.print_object();
    const Cat cc("cat1", 2);
    cc.print_object();
    //cc.name() = "min"; //error, 不可修改，因为cc是const, 调用的是带const的name()
}

void test_mutable()
{
    const Cat cc("mimi", 1);
    cc.print_object();
    cc.print_object();
    cc.print_object();
}

bool compare(const Cat& cat1, const Cat& cat2)
{
    cout << cat1.get_age() << "," << cat2.get_age() << endl;
    return cat1.get_age() > cat2.get_age();
}
void test_implicit_conversion() 
{
    Cat c1("a", 1);
    Cat c2("b", 2);
    cout << compare(c1, c2) << endl;
    std::string unknown = "unkown";
    cout << compare(c1, unknown) << endl; //要想让类不支持隐式转换，需要在构造函数前加上explicit关键字
}

void test_move_constructor()
{
    Cat c1("a", 1);
    Cat c2{std::move(c1)};
    c2.print_object();

    Cat c3("b", 2);
    c3  = std::move(c2);
    c3.print_object();
}

void test_friend()
{
    Cat c("moon", 2);
    cout << c << endl;

    Person p;
    p.cat_info(c);
}

void test_derive()
{
    Worker worker;
    worker.m_name = "hello";
    cout << worker << endl;

    Worker w1("f");
    cout << w1 << endl;

    Worker w2("f", 45);
    cout << w2 << endl;

    Worker w3("john", 35, "CC", "farmer");
    cout << w3 << endl;

    Worker w4(w3);
    cout << w4 << endl;
}

//using提权
void test_private_derive_and_using()
{
    Engineer eg;
    cout << eg.get_name() << endl;
    cout << eg.get_age() << endl;    
}

void test_static_member_and_derive()
{
    Person p1;
    Person p2;
    Worker w1;
    Worker w2;
    cout << "Worker count:" << Worker::m_count << endl; //希望只统计worker的数量,m_count需要在worker中重新声明，赋值等
    cout << "Worker count:" << Person::m_count << endl; //
}

int main() {
    cout << "------------Hello----------" << endl;
    //basic:https://www.bilibili.com/video/BV1S54y1Z7Wc/?spm_id_from=333.999.0.0&vd_source=601dbc960255506eb5f6390166996d67
    //basic_data_type();
    //test_lambda();
    //test_heap_array();
    //test_lvalue_rvalue();

    //OOP:https://www.bilibili.com/video/BV1eg411Q7nG/?spm_id_from=333.999.0.0&vd_source=601dbc960255506eb5f6390166996d67
    //OOP2:https://www.bilibili.com/video/BV1ZZ4y1e7zy/?spm_id_from=333.999.0.0&vd_source=601dbc960255506eb5f6390166996d67
    //test_const_object_method();
    //test_mutable();
    //test_implicit_conversion() ;
    //test_move_constructor() ;
    //test_friend();
    //test_derive();
    //private继承会将父类的属性全部降级为private.
    //可以通过using来重新赋给管理权限，protected, public.
    //test_private_derive_and_using();
    test_static_member_and_derive();
}