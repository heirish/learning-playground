#ifndef __FPA__
#define __FPA__
#include <future>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

namespace FPA {
int factorial(int N) {
    int res = 1;
    for(int i=N; i>1; i--) {
        res *= i;
    }
    std::cout << "thread id:" << std::this_thread::get_id() << std::endl;
    return res;
}

std::mutex resMu;
std::condition_variable resCond;
void factorial1(int N, int& out) {
    int res = factorial(N);
    std::cout << "result is :" << res << std::endl;
    std::lock_guard<std::mutex> lock(resMu);
    out = res;
    resCond.notify_all();
    //other stuff
}


int factorial2(std::future<int>& fu) {
    int x = fu.get();
    return factorial(x);
}

void factorial3(std::shared_future<int> fu) {
    std::cout << factorial(fu.get()) << std::endl;
}
void get_result_from_thread_test() {
    //方法一:ugly, global resMu + resCond + std::ref
    int x;
    std::thread t1(factorial1, 4, std::ref(x));
    {
        std::unique_lock<std::mutex> lock(resMu);
        resCond.wait(lock);
        std::cout << "global var:result:" << x << std::endl;
    }
    t1.join();

    //方法二:async
    std::cout << "main thread id:" << std::this_thread::get_id() << std::endl;
    std::future<int> fu = std::async(factorial, 4); //will create new thread immediately
    //std::future<int> fu = std::async(std::launch::deferred, factorial, 4); //will not create new thread, and function is executed when future.get() is called.
    std::cout << "std::async, result is:" << fu.get() << std::endl;
    //fu.get(); //crash, future.get() can only been called once.

    //promise: pass value to thread LATER.
    std::promise<int> prm;
    std::future<int> fu1 = prm.get_future();
    std::future<int> res = std::async(factorial2, std::ref(fu1)); //create thread here
    std::this_thread::sleep_for(2s);
    prm.set_value(5); //set parame to thread there
    std::cout << "result:" << res.get() << std::endl;


    //shared_future can pass one promise to multi threads
    {
        std::promise<int> prm1;
        std::future<int> f = prm1.get_future();
        std::shared_future<int> sf = f.share();

        auto res1 = std::async(factorial3, sf);
        auto res2 = std::async(factorial3, sf);
        auto res3 = std::async(factorial3, sf);
        prm1.set_value(6);
    }
}

};
#endif //__FPA__