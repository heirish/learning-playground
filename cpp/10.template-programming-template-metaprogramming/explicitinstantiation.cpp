#include "explicitinstantiation.hpp"
#include <cstdlib>

//问题: 按每N个字符作为一个item,翻转整个字符串, item内部不翻转
//如Hello world, N=1 => dlrow olleH
//abcd1234efgh4567, N=4 =>4567efgh1234abcd
namespace TU {

template<>
int mblen<ascii>(const char* str, int n) {
    return 1;
}
template<>
int mblen<charset4>(const char* str, int n) {
    return 4;
}
template<typename Charset>
void reverse(char* str, int n) {
    char *end = str + n;
    char *p = str;
    while(p != end) {
        int len_this_char = mblen<Charset>(p, end-p);
        if (len_this_char <=0) {
            std::cout << "corrupted string, can not reverse." << std::endl;
            return;
        }
        std::cout << len_this_char << std::endl;
        std::reverse(p, p+len_this_char);
        p += len_this_char;
    }
    std::reverse(str, end);
}
template void reverse<ascii>(char* str, int n);
template void reverse<charset4>(char* str, int n);
}