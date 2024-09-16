#ifndef __LIS__
#define __LIS__
#include <vector>
#include <iostream>
#include "common.hpp"

namespace LIS {
void calc_LIS(std::vector<int>& D) {
    std::vector<std::vector<int>> L(D.size());  //the longest increasing subsequence ends with D(i)
    L[0].push_back({D[0]});

    for(int i=1; i<D.size(); i++) {
        for (int j = 0; j<i; j++) {
            if (D[j] < D[i] 
                && (L[i].size() < L[j].size() + 1 )) { //去掉+1之后，就是相同长度的subsequence取前面的
                L[i] = L[j];
            }
        }
        L[i].push_back(D[i]);
    } //complexicy: O(N^2)
    
    int index = 0;
    for(int i=0; i< L.size(); i++) {
        if (L[i].size() >= L[index].size()) {
            index = i;
        }
        print(L[i]);
    }
    std::cout << "the largest increasing subsequence is:" << std::endl;
    print(L[index]);
}

void do_test() {
    int a[]={3,2,6,4,5,1};
    std::vector<int> arr(a, a+sizeof(a)/sizeof(a[0]));
    print(arr);
    calc_LIS(arr);
}
}
#endif //__LIS__