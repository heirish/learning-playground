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
    std::cout << "hello world"s.substr(0, 5) << std::endl;
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

struct length {
    double value;
    enum unit{
        meter,
        kilometer,
        millimeter, 
        centimeter,
        inch,
        foot,
        yard,
        mile
    };
    static constexpr double factors[] = {
        1.0, 
        1000.0,
        1e-3,
        1e-2,
        0.0254,
        0.3048,
        0.9144,
        1609.344
    };
    explicit length(double v, unit u=meter) {
        value = v * factors[u];
    }
};
length operator+(const length& lhs, const length& rhs) {
    return length(lhs.value + rhs.value);
}
length operator"" _m(long double v) {
    return length(v);
}
length operator"" _cm(long double v) {
    return length(v, length::unit::centimeter);
}

void selfdef_literal_test() {
    length ret = 1.0_m + 20.0_cm;
    std::cout << "1.0_m + 20_cm = " << ret.value << "m" << std::endl;
}
}
#endif //__LITERALS__