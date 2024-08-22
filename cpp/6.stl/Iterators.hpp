#ifndef __ITERATORS__
#define __ITERATORS__

#include <set>
#include <vector>
#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>

namespace BASIC_STL_ITERATORS {
void const_iterator_test() {
   std::set<int> myset{2,4,5,1,9};
   for(std::set<int>::const_iterator it = myset.begin(); it != myset.end(); it++) {
    std::cout << *it << std::endl;
   }
   std::for_each(myset.cbegin(), myset.cend(), [](const auto& item){std::cout << item << std::endl;});
}

void insert_iterator_test() {
    std::vector<int> vec1{4,5};
    std::vector<int> vec2{12,14,16,18};
    std::vector<int>::iterator it = std::find(vec2.begin(), vec2.end(), 16);
    std::insert_iterator<std::vector<int>> ins_iter(vec2, it);
    std::copy(vec1.begin(), vec1.end(), ins_iter);
    std::for_each(vec2.cbegin(), vec2.cend(), [](const auto& item){std::cout << item << std::endl;});
    //other insert iterators
    //back_insert_iterator, 
    std::copy(vec1.begin(), vec1.end(), std::back_inserter(vec2));
    std::for_each(vec2.cbegin(), vec2.cend(), [](const auto& item){std::cout << item << std::endl;});
    //front_insert_iterator
}

void stream_iterator_test() {
    std::vector<std::string> vec;
    std::copy(std::istream_iterator<std::string>(std::cin), std::istream_iterator<std::string>(),
        std::back_inserter(vec));
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<std::string>(std::cout, " "));

    //make it terse:
    //std::copy(std::istream_iterator<std::string>(std::cin), std::istream_iterator<std::string>(),
     //   std::ostream_iterator<std::string>(std::cout, " "));
}

void reverse_iterator_test() {
    std::vector<int> vec{4,5,6,7};
    std::vector<int>::reverse_iterator it;
    for(it = vec.rbegin(); it != vec.rend(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void move_iterator_test() {

}
};
#endif //__ITERATORS__