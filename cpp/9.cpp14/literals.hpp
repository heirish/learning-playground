#ifndef __LITERALS__
#define __LITERALS__
#include <chrono>
#include <string>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;
using namespace std::string_literals;

namespace LITERALS {
void do_test() {
    auto str = "hello"s; //std::string str;
    const char* ptr = str.c_str();
    auto hour = 2h; //std::chrono::hours hour;
    std::cout << hour.count() << std::endl;
    auto min = 30min; //std::chrono::minutes min;
    auto sec = 45s; //std::chrono::seconds sec;
    auto ms = 100ms; //std::chrono::milliseconds ms;
    auto us = 100us; //std::chrono::microseconds us;
    auto ns = 100ns; //std::chrono::nanoseconds ns;
    
    std::cout << "will sleep for 2 seconds" << std::endl;
    std::this_thread::sleep_for(2s);
    std::cout << "sleep done" << std::endl;
    //auto day = 1d; //std::chrono::days day;//c++20
    //auto year = 1y; //std::chrono::years year;//c++20
}
}
#endif //__LITERALS__