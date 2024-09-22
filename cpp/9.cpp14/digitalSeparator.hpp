#ifndef __DIGITAL_SEPARATOR__
#define __DIGITAL_SEPARATOR__
#include <iostream>
#include <bitset>
namespace Integer_Literal {

void do_test() {
    int b = 0b1010; //binary literal from c++14
    std::cout << "b=" << b << ",bin:0b" << std::bitset<4>(b) << std::endl;

    //Optional single quotes (') may be inserted between the digits as a separator; they are ignored when determining the value of the literal.
    int a = 1'000'000; //digit separator from c++14
    std::cout << "a=" << a << std::endl;
    uint32_t y = 0xDEAD'BEAF;
    std::cout << "y=" << y <<",hex:0x" << std::hex<< y << std::endl;
}
}
#endif //__DIGITAL_SEPARATOR__