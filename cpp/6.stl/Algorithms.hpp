#ifndef __ALGORITHM__
#define __ALGORITHM__

#include <vector>
#include <algorithm>
#include <iostream>

namespace BASIC_STL_ALGORITHM {
void basic_test() {
    std::vector<int> vec{4,2,3,1,5,9};
    std::vector<int>::iterator it = std::min_element(vec.begin(), vec.end());

    std::sort(vec.begin(), it);
    auto printelement = [](const auto& item){std::cout << item << " ";};
    std::for_each(vec.cbegin(), vec.cend(), printelement);
    std::cout << std::endl;

    std::reverse(it, vec.end()); //it => 9
    std::for_each(vec.cbegin(), vec.cend(), printelement);
    std::cout << std::endl;

    std::vector<int> vec2(3); //here we make sure there's enough space in vec2 for new insert.
    std::copy(it, vec.end(), vec2.begin()); //the range of vec2 is deducted by vec's range, so you should ensure vec2 has enough space for the new element, or else undefined behavior would be expected 
    std::for_each(vec2.cbegin(), vec2.cend(), printelement);
    std::cout << std::endl;

    std::vector<int> vec3;
    //back_insert_iterator //not efficient
    std::copy(it, vec.end(), std::back_inserter(vec3)); //inserting instead of overwritin
    vec3.insert(vec3.end(), it, vec.end()); //efficent and safe

    auto isOdd=[](int i)->bool{return i%2;};
    it = std::find_if(vec.begin(), vec.end(), isOdd);
    if (it == vec.end()) {
        std::cout << "no odd element in vec." << std::endl;
    } else {
        std::cout << "first odd element in vec is:" << *it << std::endl;
    }

    //algorithm with native c++ array
    //a pointer can be think of an iterator
    int arr[4] = {5,3,6,4};
    std::sort(arr, arr+4);
    for(int i:arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}
}
#endif //__ALGORITHM__