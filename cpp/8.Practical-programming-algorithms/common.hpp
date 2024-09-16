#ifndef __COMMON__
#define __COMMON__
#include <iostream>
template<typename T>
void print(T t) {
    for(typename T::iterator it = t.begin(); it != t.end(); it++) {
        std::cout << *it << ",";
    }
    std::cout << std::endl;
}
#endif //__COMMON__