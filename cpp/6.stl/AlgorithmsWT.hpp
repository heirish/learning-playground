#ifndef _AWT_
#define  _AWT_

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <random>

namespace ALGORITHM_TEST{
void none_modifying_algs_test() {
    std::vector<int> vec{24,5,6,4,4,24,667,654,765,85,23,33};
    
    //1.counting
    int n = std::count(vec.cbegin(), vec.cend(), 69);
    std::cout << n << " items equals 69" << std::endl;
    n = std::count_if(vec.cbegin(), vec.cend(), [](int item){return item < 10;});
    std::cout << n << " items <10" << std::endl;

    //2.min, max
    //returns the FIRST max value
    std::vector<int>::iterator it = std::max_element(vec.begin() + 2, vec.end());
    if (it != vec.end()) {
        std::cout << "max element from the 3rd element to the end is :" << *it << std::endl;
    }
    //most algorithms have a simple form and a generialized form
    it = std::max_element(vec.begin(), vec.end(), [](int x, int y){return (x%10) < (y%10);});
    if (it != vec.end()) {
        std::cout << "max last digital element is:" << *it << std::endl;
    }
    it = std::min_element(vec.begin(), vec.end());
    if (it != vec.end()) {
        std::cout << "min element is:" << *it << std::endl;
    }
    //returns a pair of FIRST min and LAST max element
    std::pair<std::vector<int>::iterator, std::vector<int>::iterator> ret = 
        std::minmax_element(vec.begin(), vec.end(), [](int x, int y){return (x%10) < (y%10);});
    if (ret.first != vec.end() && ret.second != vec.end()) {
        std::cout << "min last digital element is:" << *(ret.first)<< ", max last digital element is:" << *(ret.second) << std::endl;
    }

    //3.linear searching(Note:only use it when data is not sorted, use binary_search if data is sorted)
    //returns the first match
    it = std::find(vec.begin(), vec.end(), 55);
    it = std::find_if(vec.begin(), vec.end(), [](int x){return x>80;});
    it = std::find_if_not(vec.begin(), vec.end(), [](int x){return x>80;});
    it = std::search_n(vec.begin(), vec.end(), 2, 4);
    if (it != vec.end()) {
        std::cout << "consecutive 2 items of " << *it << "," << *(it+1) << std::endl;
    }
    //search subrange
    std::vector<int> sub{6,4,4};
    //search first subrange
    it = std::search(vec.begin(), vec.end(), sub.begin(), sub.end());
    if (it != vec.end()) {
        std::cout << "first subrange found at index:" << std::distance(vec.begin(), it) << std::endl;
    }
    //search last subrange
    it = std::find_end(vec.begin(), vec.end(), sub.begin(), sub.end());
    if (it != vec.end()) {
        std::cout << "last subrange found at index:" << std::distance(vec.begin(), it) << std::endl;
    }
    //search any_of
    std::vector<int> items{ 87, 69};
    it = std::find_first_of(vec.begin(), vec.end(), items.begin(), items.end()); //search any onre of the item in items
    //search any onre of the item in the items that satisfy: x == y*4
    it = std::find_first_of(vec.begin(), vec.end(), items.begin(), items.end(), [](int x, int y){return x == y*4;});
    //search adjacent:相邻items是一样的
    it = std::adjacent_find(vec.begin(), vec.end());
    if (it != vec.end()) {
        std::cout << "item at:" << std::distance(vec.begin(), it) << "and items after that is the same, value:" << *it << std::endl;
    }
    it = std::adjacent_find(vec.begin(), vec.end(), [](int x, int y){return x%3 == 0 && y%3 == 0;});
    if (it != vec.end()) {
        std::cout << "first pair of values that can be devided by 3 is:" << *it << "," << *(it+1) << std::endl;
    }

    //4.comparing ranges
    std::vector<int> vec2{455645,44,6,4};
    if (std::equal(vec.begin(), vec.end(), vec2.begin())) {
        std::cout << "vec and vec2 are same" << std::endl;
    }
    if (std::is_permutation(vec.begin(), vec.end(), vec2.begin())) {
        std::cout << "vec and vec2 have same items, but in different order." << std::endl;
    }
    //find first difference, ret.first is an iterator of vec, ret.second is an iterator of vec2
    ret = 
        std::mismatch(vec.begin(), vec.end(), vec2.begin());
    std::cout << "first mismatch between vec and vec2 is " << *(ret.first) << "<>" << *(ret.second) << std::endl;
    //Lexicographical comparison: one-by-one compoarison with "less than"
    bool res = std::lexicographical_compare(vec.begin(), vec.end(), vec2.begin(), vec2.end());
    //{1,2,3,5} < {1,2,4,5}
    //{1,2} < {1,2,5}
    std::cout << "vec is " << (res?"":"not") << "lexicographical less than vec2" << std::endl; 

    //5.Check Attributes
    res = std::is_sorted(vec.begin(), vec.end());
    std::cout << "vec is sorted?" << res << std::endl;
    it = std::is_sorted_until(vec.begin(), vec.end());
    std::cout << "vec is sorted until" << *it << std::endl;
    res = std::is_partitioned(vec.begin(), vec.end(), [](int x){return x > 80;});
    std::cout << "vec is partitioned according to the condition of x > 80, ?" << res << std::endl;
    res = std::is_heap(vec.begin(), vec.end());
    std::cout << "vec is a heap?" << res << std::endl;
    it = std::is_heap_until(vec.begin(), vec.end());
    std::cout << "first element in vec that is not a heap:" << *it << std::endl;
    //All, any, none
    res = std::all_of(vec.begin(), vec.end(), [](int x){return x>80;});
    std::cout << "all elements in vec greater than 80?" << res << std::endl;
    res = std::any_of(vec.begin(), vec.end(), [](int x){return x>80;});
    std::cout << "any lements in vec greater than 80?" << res << std::endl;
    res = std::none_of(vec.begin(), vec.end(), [](int x){return x>80;});
    std::cout << "none elements in vec greater than 80?" << res << std::endl;
}    

void modifying_algs_test(){
    std::vector<int> vec{9,60,70,80,45,87,90};
    std::vector<int> vec2(vec.size()+3, 0);

    //1.copy
    //must make sure vec2 is at least as big as vec, otherwise it's undefined behavior
    //std::copy(vec.begin(), vec.end(), vec2.begin()); //{9,60,70,80,45,87,90,0,0,0}
    //std::copy_if(vec.begin(), vec.end(), vec2.begin(), [](int x){return x > 80;});{87,90,0,0,0,0,0,0,0,0}
    //std::copy_n(vec.begin(), 4, vec2.begin()); //{9,60,70,80,0,0,0,0,0,0}
    std::copy_backward(vec.begin(), vec.end(), vec2.end()); //{0,0,0,9,60,70,80,45,87,90}
    auto printItem = [](int item){std::cout << item << " ";};
    std::for_each(vec2.begin(), vec2.end(), printItem);
    std::cout << std::endl;

    //2.move
    //if move semantic are defined for the element type, elements are moved over.
    //otherwisde they are copied over with the copy constructor, just like copy()
    std::vector<std::string> svec{"apple", "orange", "pear", "grape"};
    std::vector<std::string> svec2(svec.size()+2, "");
    //std::move(svec.begin(), svec.end(), svec2.begin());
    std::move_backward(svec.begin(), svec.end(), svec2.end());
    auto printSItem = [](const std::string& item){std::cout << item << ",";};
    //std::for_each(svec.begin(), svec.end(), printSItem); //undefined behavior, string item already moved.
    std::for_each(svec2.begin(), svec2.end(), printSItem); 
    std::cout << std::endl;

    //3.transform
    vec = {9,60,70,8,45,87,90};
    vec2 = vec;
    std::vector<int> vec3(vec2.size() + 3, 0);
    std::transform(vec.begin(), vec.end(),//source
                    vec3.begin(), //destination
                    [](int x){return x-1;}); //Operation
    std::for_each(vec3.begin(), vec3.end(), printItem);
    std::cout << std::endl;
    //vec3[i] = vec[i]+vec2[i]
    std::transform(vec.begin(), vec.end(), //source1
                    vec2.begin(), //source2
                    vec3.begin(), //destination
                    [](int x, int y){return x+y;}); //Operation
    std::for_each(vec3.begin(), vec3.end(), printItem);
    std::cout << std::endl;

    //4.Swap - two way copying
    std::swap_ranges(vec.begin(), vec.end(), vec2.begin());

    //5.Fill
    std::vector<int> iv(6);
    std::fill(iv.begin(), iv.end(), 9);
    std::for_each(iv.begin(), iv.end(), printItem);
    std::cout << std::endl;
    std::fill_n(iv.begin(), 3, 0);
    std::for_each(iv.begin(), iv.end(), printItem);
    std::cout << std::endl;
    std::generate(iv.begin(), iv.end(), rand);
    std::for_each(iv.begin(), iv.end(), printItem);
    std::cout << std::endl;
    std::generate_n(iv.begin(), 4, rand);
    std::for_each(iv.begin(), iv.end(), printItem);
    std::cout << std::endl;

    //6.replace
    iv = std::vector<int>(vec.size(), 7);
    std::replace(iv.begin(), iv.end(),
        7,
        9);
    std::for_each(iv.begin(), iv.end(), printItem);
    std::cout << std::endl;
    std::replace_if(iv.begin(), iv.end(), [](int x){return x > 7;}, 2);
    std::for_each(iv.begin(), iv.end(), printItem);
    std::cout << std::endl;
    vec2 = std::vector<int>(iv.size() + 2);
    std::replace_copy(iv.begin(), iv.end(),
        vec2.begin(),
        2,3);
    std::for_each(vec2.begin(), vec2.end(), printItem);
    std::cout << std::endl;

    //7.remove
    //Note: remove returns the last valid iterator for the new value range, 
    //so you need to call erase to delete the removed value completed
    std::for_each(vec.begin(), vec.end(), printItem);
    std::cout << std::endl;
    vec.erase(std::remove(vec.begin(), vec.end(), 9), vec.end());
    std::for_each(vec.begin(), vec.end(), printItem);
    std::cout << std::endl;
    vec.erase(std::remove_if(vec.begin(), vec.end(), [](int x){return x%3 == 0;}), vec.end());
    std::for_each(vec.begin(), vec.end(), printItem);
    std::cout << std::endl;
    std::vector<int> morevalue{45,67,82,34,1,7,9,0};
    std::copy(morevalue.begin(), morevalue.end(), std::back_inserter(vec));
    //worst function name in STL:这里实际并没有remove from vec,还在, 跟copy_if没啥区别
    //应该是理解为copy vec to vec2 and remove predicate satisfied item
    auto vec_new_end = std::remove_copy_if(vec.begin(), vec.end(),  //-------remove 能被3整除的数
            vec2.begin(), //将剩下的数copy到vec2
            [](int x){return x%3 == 0;});
    std::for_each(vec.begin(), vec.end(), printItem);
    std::cout << std::endl;
    std::for_each(vec2.begin(), vec2.end(), printItem);
    std::cout << std::endl;
    vec2.erase(std::unique(vec2.begin(), vec2.end()), vec2.end()); //相邻重复去除, 返回的是new end, 也需要erase
    std::for_each(vec2.begin(), vec2.end(), printItem);
    std::cout << std::endl;
    vec2.erase(std::unique(vec2.begin(), vec2.end(), [](int x, int y){return x<y;}), vec2.end());//移除比前一个数字大的值
    std::for_each(vec2.begin(), vec2.end(), printItem);
    std::cout << std::endl;
    std::unique_copy(vec2.begin(), vec2.end(), vec.begin()); //将vec2中非相邻重复的数字都copy到vec
}

void modifying_order_changing_algs_test() {
    std::vector<int> vec{9,60,70,8,45,87,90};
    std::vector<int> vec2(vec.size());

    auto printVec = [&vec](){
        std::for_each(vec.cbegin(), vec.cend(), [](int item){std::cout << item << ",";});
        std::cout << std::endl;
    };
    auto printVec2 = [&vec2](){
        std::for_each(vec2.cbegin(), vec2.cend(), [](int item){std::cout << item << ",";});
        std::cout << std::endl;
    };

    //1.reverse
    printVec();
    std::reverse(vec.begin(), vec.end());
    printVec();
    std::reverse_copy(vec.begin()+1, vec.end()-1, vec2.begin()); //vec is not reversed.
    printVec();
    printVec2();

    //2.rotate
    std::rotate(vec.begin(), vec.begin()+3, vec.end()); 
    printVec();
    std::rotate_copy(vec.begin(), vec.begin()+3, vec.end(),vec2.begin()); //no change in vec. just copy vec and change to vec2
    printVec();
    printVec2();

    //3.Permute
    //lexicographical comparison: compares data one by one from beginning to the end until a difference is found
    std::next_permutation(vec.begin(), vec.end()); //Lexicographically next greater permutation
    printVec();
    std::prev_permutation(vec.begin(), vec.end());//Lexicographically next smaller permutation
    printVec();
    //{1,2,3,5} < {1,2,4,4}
    //{1,2} < {1,2,3}
    //Sorted in ascending order: Lexicographically smallest
    //Sorted in descending order: Lexicographically greatest

    //4.shuffle:rearrange the elements randomly
    //swap each item with a randomly selected item
    std::shuffle(vec.begin(), vec.end(), std::default_random_engine());
    printVec();
}


}
#endif //_AWT_