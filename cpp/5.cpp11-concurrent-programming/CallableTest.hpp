#ifndef __CALLABLE_TEST_
#define __CALLABLE_TEST_
#include <thread>
namespace CALLABLE_TEST {
class A {
public:
    void f(int x, char c) {}
    long g(double x) {return 0;}
    int operator()(int N){return 0;}
};

void foo(int x){}

void do_callable_test() {
    A a;
    std::thread t(a, 6); //copy_of_a() in a different thread
    std::thread t2(std::ref(a), 6); //a() in a different thread
    std::thread t3(A(), 6); //temp A;
    std::thread t4([](int x){return x*x;}, 6);
    std::thread t5(foo, 6);
    std::thread t6(&A::f, a, 8, 'w'); //copy_of_a.f(8, 'w') in a different thread
    std::thread t7(&A::f, &a, 8, 'w'); //a.f(8, 'w') in a different thread
    std::thread t8(std::move(a), 6); //a is no long usable in this thread

    t.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
}
}
#endif //__CALLABLE_TEST_