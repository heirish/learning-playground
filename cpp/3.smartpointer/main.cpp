#include <iostream>
#include <memory>
#include "cat.h"
using namespace std;

void test_unique_ptr()
{
    Cat c1("name", 2);
    c1.print_object();

    {
        Cat c2("ok", 3);
        c2.print_object();
    }
    //raw pointer, need to call delete manually
    Cat *ptr = new Cat("mini", 1);
    delete ptr;

    //raw pointer can not delete more than once
    //int *p_i = new int{100};
    //{
    //    p_i = new int {0};
    //    delete p_i;
    //} 
    //delete p_i;

    //三种方式创建unique_ptr:1.from raw pointer, 2. from new, 3.make_unique(推荐)
    //1.
    Cat *p_c1 = new Cat("yz", 1);
    std::unique_ptr<Cat> up_c1 (p_c1);
    up_c1->print_object();
    //p_c1依然可用,需要手动释放，并且这里up_c1并不是独占的，不推荐用这种方式创建unique_ptr
    p_c1->print_object();
    delete p_c1;
    p_c1 = nullptr;

    //2.这种方式的危险是，如果在Cat的构造函数里如果报异常，因为没有地方调用析构，可能会造成内存泄漏
    std::unique_ptr<Cat> up_c2(new Cat("abc", 3));
    
    //3.
    std::unique_ptr<Cat> up = std::make_unique<Cat>("cc", 5);
    //get获取内存地址 
    cout << "cat address:" << up.get() << endl;
}

void do_with_cat_pass_by_value(std::unique_ptr<Cat> c)
{
    c->print_object();
}
void do_with_cat_pass_by_ref(std::unique_ptr<Cat> &c)
{
    c->set_name("hmm");
    c->print_object();
    c.reset();
}
void do_with_cat_pass_by_const_ref(const std::unique_ptr<Cat> &c)
{
    c->set_name("hmm");
    c->print_object();
    //c.reset(); //const unique_ptr ref, 不能调用reset等会改会c指向的函数
}
std::unique_ptr<Cat> get_unique_ptr()
{
    std::unique_ptr<Cat> c = std::make_unique<Cat>("local cat", 3);
    cout << "address:" << c.get() << endl;
    cout << "address:" << &c << endl;
    return c;
}
void test_unique_fun_call()
{
    //Passing by value
    //需要用std::move来转移内存拥有所有权
    //如果参数直接传入std::make_unique语句，自动转换为move
    std::unique_ptr<Cat> c1 = std::make_unique<Cat>("cc", 2);
    do_with_cat_pass_by_value(std::move(c1));
    do_with_cat_pass_by_value(std::make_unique<Cat>("aa", 1));
    //passing by reference(常用)
    //如果设置参数为const则不能改变指向,比方说reset
    //reset方法为智能指针清空方法
    std::unique_ptr<Cat> c2 = std::make_unique<Cat>("gg", 3);
    do_with_cat_pass_by_ref(c2);
    std::cout << "address after reset:" << c2.get() << std::endl;
    std::unique_ptr<Cat> c3 = std::make_unique<Cat>("33", 3);
    do_with_cat_pass_by_const_ref(c3);
    std::cout << "address :" << c3.get() << std::endl;
    c3->print_object();

    //return by value
    //指向一个local object
    //可以用作链式函数。
    get_unique_ptr()->print_object();
}

void test_shared_ptr()
{
    //std::shared_ptr<int> iptr1=std::make_shared<int>(10);
    //std::cout << *iptr1 << std::endl;
    //std::cout << "use count:" << iptr1.use_count() << std::endl;
    //std::shared_ptr<int> iptr2=iptr1;
    //std::shared_ptr<int> iptr3=iptr1;
    //std::cout << "use count:" << iptr1.use_count() << std::endl;
    //std::cout << "use count:" << iptr2.use_count() << std::endl;
    //std::cout << "use count:" << iptr3.use_count() << std::endl;
    //iptr2 = nullptr;
    //std::cout << "use count:" << iptr1.use_count() << std::endl;
    //std::cout << "use count:" << iptr2.use_count() << std::endl;
    //std::cout << "use count:" << iptr3.use_count() << std::endl;

    std::shared_ptr<Cat> cp1 = std::make_shared<Cat>("cc", 1);
    cout << "use count:" << cp1.use_count() << endl;
    std::shared_ptr<Cat> cp2 = cp1;
    std::shared_ptr<Cat> cp3 = cp1;
    cout << "cp2 use count:" << cp2.use_count() << endl;
    cout << "cp3 use count:" << cp3.use_count() << endl;
    cp1.reset();
    cout << "use count:" << cp1.use_count() << endl;
    cout << "cp2 use count:" << cp2.use_count() << endl;
    cout << "cp3 use count:" << cp3.use_count() << endl;
}

void cat_by_value(std::shared_ptr<Cat> cat)
{
    cat->set_name("abc");
    cout << cat->get_name() << endl;
    cout << "func use count:" << cat.use_count() << endl;
}
void cat_by_ref(std::shared_ptr<Cat> &cat)
{
    cout << cat->get_name() << endl;
    cat->set_name("abc");
    cat.reset(new Cat("rrr", 3));
    cout << "func use count:" << cat.use_count() << endl;
}
void cat_by_const_ref(const std::shared_ptr<Cat> &cat)
{
    cout << cat->get_name() << endl;
    cat->set_name("const");
    //cat.reset(new Cat("rrr", 3)); //const &,不能更改指向
    cout << "func use count:" << cat.use_count() << endl;
}
std::shared_ptr<Cat> get_shared_ptr()
{
    std::shared_ptr<Cat> c = std::make_shared<Cat>("local", 4);
    return c;
}
void test_sharedptr_fun_call()
{
    //passing by value
    //copy, 函数内部计数器加1
    std::shared_ptr<Cat> c1 = std::make_shared<Cat>("c1", 2);
    cout << "before func use count:" << c1.use_count() << endl;
    cat_by_value(c1);
    cout << "after func use count:" << c1.use_count() << endl;
    cout << "after func name:" << c1->get_name() << endl;

    //passing by reference
    //const表示不可改变指向
    cat_by_ref(c1);
    cat_by_const_ref(c1);

    //returning by value
    //链式调用
    get_shared_ptr()->print_object();
}

void test_ptr_convert()
{
    auto cp1 = std::make_unique<Cat>("dd", 2);
    std::shared_ptr<Cat> cp2 = std::move(cp1);
    cout << cp2.use_count() << endl;

    std::shared_ptr<Cat> cp3 = get_unique_ptr();
    if(cp3) {
        cp3->print_object();
        std::cout << cp3.use_count() << endl;
    }
}

void test_weak_ptr()
{
    //weak_ptr不能单独存在,会与share_ptr同时存在
    std::shared_ptr<Cat> cp1 = std::make_shared<Cat>("c1", 1);
    std::weak_ptr<Cat> wp(cp1);
    cout << "cp1 use count:" << cp1.use_count() << endl;
    cout << "wp use count:" << wp.use_count() << endl;
    //wp->print_object(); //weak_ptr不能用->以及解引用*
    std::shared_ptr<Cat> cp2 = wp.lock();
    cout << "cp1 use count:" << cp1.use_count() << endl;
    cout << "wp use count:" << wp.use_count() << endl;
    cout << "cp2 use count:" << cp2.use_count() << endl;

    auto c3 = std::make_shared<Cat>("c3", 2);
    auto c4 = std::make_shared<Cat>("c4", 2);
    c3->set_friend(c4);
    c4->set_friend(c3);
}

int main() {
    //https://www.bilibili.com/video/BV18B4y187uL/?spm_id_from=333.999.0.0&vd_source=601dbc960255506eb5f6390166996d67
    //std::unique_ptr, std::shared_ptr, stdk::weak_ptr
    //并不是所有指针都可以封装成智能指针，很多时原始指针要更方便
    //各种指针中，最常用的是raw pointer,其次是unique_ptr和shared_ptr
    //weak_ptr是shared_ptr的一个补充，应用场景较少。

    //智能指针与Rust的内存安全
    //智能指针只解决一部分问题，即独占/共享所有权指针的释放，传输
    //智能指针没有从根本上解决c++内存安全问题，不加以注意依然会造成内存安全问题。 
    
    //unique_ptr
    //test_unique_ptr();
    //unique_ptr只可move,不可copy,在做函数参数或是返回值中一定要注意所有权
    //test_unique_fun_call();

    //shared_ptr
    //shared_ptr创建了一个计数器与类对象所指的内存相关联
    //api为use_count()
    //test_shared_ptr();
    //test_sharedptr_fun_call();
    

    //shared_ptr与unique_ptr
    //不能将shared_ptr转换为unique_ptr
    //可以将unique_ptr转换为shared_ptr,通过std::move
    //常见设计：将你的函数返回unique_ptr是一种常见的设计模式，这样可以提高代码的复用率，你可以随时改变为shared_ptr
    //test_ptr_convert();

    //weak_ptr
    //weak_ptr不拥有所有权，并不能调用->和解引用*
    //weak_ptr为什么会存在
    //A类中有一个需要存储其它A类对象的信息
    //如果使用shared_ptr,那么在销毁时会遇到循环依赖问题(cyclic dependency problem)
    //所以我们需要用一个不需要拥有所有权的指针来标记该同类对象。
    //weak_ptr可以通过lock()函数来提升为shared_ptr(类型转换)
    test_weak_ptr();
    cout << "------------Hello----------" << endl;
}