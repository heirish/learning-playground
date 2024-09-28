#ifndef __TRANSLATION_UNIT__
#define __TRANSLATION_UNIT__
#include <iostream>
#include <algorithm>

//
namespace TU {
struct ascii; struct charset4; //just some dummy types

//primary template的定义只能放在头文件中
template<typename Charset>
int mblen(const char* str, int n){
    return -1;
}

//全特化
//全特化可以将声明和定义分开放，声明放头文件，定义放.cpp文件
template<>
int mblen<ascii>(const char* str, int n); 
template<>
int mblen<charset4>(const char* str, int n);


//如果不想在头文件中暴露任何实现，则可以使用explicit instantiation.
//但是这样做的缺点是只有声明了instantiation的类型才能使用。
//因为头文件中不包含primary template,除了显示声明的其它类型没有定义，所以不能使用。
template<typename Charset>
void reverse(char* str, int n);
//explicit instantiation
extern template void reverse<ascii>(char* str, int n);
extern template void reverse<charset4>(char* str, int n);

void do_test();

}
#endif //__TRANSLATION_UNIT__