#ifndef _AWT_
#define  _AWT_

#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <string>
#include <random>
#include <numeric>
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

void sorting_algs_test() {
    std::vector<int> vec{9,1,10,2,45, 3,90,4,9,5,8}; 
    auto printVec = [&vec](){
        std::for_each(vec.cbegin(), vec.cend(), [](int item){std::cout << item << ",";});
        std::cout << std::endl;
    };

    std::sort(vec.begin(), vec.end()); //default comparator std::less
    printVec();
    auto lsb_less = [](int x, int y){return (x%10) < (y%10);};
    std::sort(vec.begin(), vec.end(), lsb_less); //按最后一位排序
    printVec();

    //sometimes we don't need complete sorting.
    //Problem #1:Finding top N with sorted - partial sort
    vec = {2,60,70,8,46,87,90,87,23};
    std::partial_sort(vec.begin(), vec.begin()+5, vec.end(), std::greater<int>());
    printVec(); //{90,87,87,70,60,...}
    //Problem #2: Finding top N without sorted - nth
    vec = {2,60,70,8,46,87,90,87,23};
    std::nth_element(vec.begin(), vec.begin()+5, vec.end(), std::greater<int>());
    printVec();//{87,87,90,70,60,...}
    //Problem #3:Move the item which <10 to the front
    vec = {2,60,70,8,46,87,90,87,23,6};
    std::partition(vec.begin(), vec.end(), [](int x){return x<10;});
    printVec();//{2,6,8,...}
    vec = {2,60,70,8,46,87,90,87,23,6};
    std::stable_partition(vec.begin(), vec.end(), [](int x){return x<10;}); //to preserve the original order within each partition
    printVec();//{2,8,6,...}

    //heap algorithm
    vec = {2,60,70,8,46,87,90,87,23,6};
    std::make_heap(vec.begin(), vec.end());
    printVec();
    //Remove the largets element:
    //1.swap vec[0] with last item vec[size-1]
    //2.heapify [vec.begin(), vec.end()-1]
    std::pop_heap(vec.begin(), vec.end()); //并没有删除元素，只是将要remove的放到最后了，
    printVec();
    vec.pop_back(); //在这里删除元素
    printVec();
    //add a new elemnt
    vec.push_back(100);
    std::push_heap(vec.begin(), vec.end());//heapify the last itme in vec
    printVec();
    //Heap sorting
    std::sort_heap(vec.begin(), vec.end()); //can only work on a heap
    printVec();
}

void sorted_data_algs_test() {
    std::vector<int> vec{8,9,9,9,45,87,90};
    auto printVec = [&vec](){
        std::for_each(vec.cbegin(), vec.cend(), [](int item){std::cout << item << ",";});
        std::cout << std::endl;
    };

    //1.Binary search
    ///////////////search element: 
    bool found = std::binary_search(vec.begin(), vec.end(), 9);
    std::vector<int> s{9,45,66};
    //both vec and s must be sorted
    bool all_found = std::includes(vec.begin(), vec.end(),
                                s.begin(), s.end());
    /////////////search position
    //find the first position where 9 could be inserted and still keep the sorting.
    auto iter = std::lower_bound(vec.begin(),vec.end(),9);
    if (iter != vec.end()) {
        std::cout << "the first item that not less than 9 is:" << *iter 
            << ",index:" << std::distance(vec.begin(), iter) << std::endl;
    }
    //find the last position where 9 could be inserted and still keep the sorting
    iter = std::upper_bound(vec.begin(),vec.end(),9);
    if (iter != vec.end()) {
        std::cout << "the first item that greater than 9 is:" << *iter
            << ",index:" << std::distance(vec.begin(), iter) << std::endl;
    }
    //return both first and last position
    auto pair_iter = std::equal_range(vec.begin(), vec.end(), 9);
    std::cout << "total " << std::distance(pair_iter.first, pair_iter.second) << " items equal to 9,"
              << "index from " << std::distance(vec.begin(), pair_iter.first)
              << " to " << std::distance(vec.begin(), pair_iter.second) << std::endl;


    //2.Merge
    vec = {8,9,9,10};
    std::vector<int> vec2{7,9,16};
    std::vector<int> vecOut(vec.size() + vec2.size());//must ensure vecOut has enough space, or else using back_inserter
    std::merge(vec.begin(), vec.end(),
                vec2.begin(), vec2.end(),
                vecOut.begin()); //must ensure vecOut has enough space
                //std::back_inserter(vecOut)); 
    auto printVecOut = [&vecOut](){
        std::for_each(vecOut.begin(), vecOut.end(), [](int item){std::cout << item << ",";});
        std::cout << std::endl;
    };
    printVecOut();
    vec = {1,2,3,4,1,2,3,4,5}; //begin ~ begin+4 sorted, begin+5 ~ end sorted
    std::inplace_merge(vec.begin(), vec.begin()+4, vec.end()); //one step of merge sort
    printVec();

    //3.Set operations
    //both vec and vec2 should be sourted, the result data is also sorted
    vec = {8,9,9,10};
    vec2 = {7,9,16};
    vecOut = std::vector<int>(vec.size() + vec2.size());//must ensure vecOut has enough space, or else using back_inserter
    //并集
    std::set_union(vec.begin(), vec.end(),
                   vec2.begin(), vec2.end(),
                   vecOut.begin()); //if X is in both vec and vec2, only one X is kept in vecOut
    printVecOut(); //{7,8,9,9,10,16}
    //交集
    std::set_intersection(vec.begin(), vec.end(),
                        vec2.begin(), vec2.end(),
                        std::back_inserter(vecOut)); //only the items that are in both vec and vec2 are inserted to vecOut
    printVecOut();//加了item{9} 
    //差集?
    vecOut.clear();
    //only the items that are in vec but not in vec2 are saved in vecOut
    std::set_difference(vec.begin(), vec.end(),
                        vec2.begin(),vec2.end(),
                        std::back_inserter(vecOut));
    printVecOut(); //{8,9,10} = A - (A&B)
    //
    vecOut.clear();
    //vecout has items for either vec or vec2 but not from both
    std::set_symmetric_difference(vec.begin(), vec.end(),
                                  vec2.begin(), vec2.end(),
                                  std::back_inserter(vecOut));
    printVecOut();//{7,8,9,10,16} = (A|B) - (A&B)
}

void numeric_algs_test() {
    std::vector<int> vec{6,7,8,9,10};

    //1.accumulate
    int x = std::accumulate(vec.begin(), vec.end(), 10); //10+vec[0]+vec[1] + ...
    std::cout << "sum(10, vec[i]) = " << x << std::endl;
    x = std::accumulate(vec.begin(), vec.end(), 10, std::multiplies<int>()); //10*vec[0]*vec[1] * ...
    std::cout << "multi(10, vec[i]) = " << x << std::endl;

    //2.Inner product
    std::vector<int> vec2 = {3,4,5,6,2};
    x = std::inner_product(vec.begin(), vec.end(), //range 1
                           vec2.begin(), //range 2
                           10); //10 + vec[i] * vec2[i]
    std::cout << "sum(10, vec[i]*vec2[i]) = " << x << std::endl;
    x = std::inner_product(vec.begin(), vec.end(), //range 1
                           vec2.begin(), //range 2
                           10, //init value
                           std::multiplies<int>(),
                           std::plus<int>()); //10 * (vec[i] + vec2[i])
    std::cout << "multi(10, vec[i]+vec2[i]) = " << x << std::endl;

    //3.partial sum
    std::vector<int> vecOut;
    auto printVecOut = [&vecOut](){
        std::for_each(vecOut.begin(), vecOut.end(), [](int x) {std::cout << x << ",";});
        std::cout << std::endl;
    };
    std::partial_sum(vec.begin(), vec.end(), std::back_inserter(vecOut));
    //fibonacci sequence
    //vecOut[0] = vec[0]
    //vecOut[1] = vec[0] + vec[1]
    //vecOut[2] = vec[0] + vec[1] + vec[2]
    //vecOut[3] = vec[0] + vec[1] + vec[2] + vec[3]
    printVecOut();
    vecOut.clear();
    std::partial_sum(vec.begin(), vec.end(), std::back_inserter(vecOut), std::multiplies<int>());
    //vecOut[0] = vec[0]
    //vecOut[1] = vec[0] * vec[1]
    //vecOut[2] = vec[0] * vec[1] * vec[2]
    //vecOut[3] = vec[0] * vec[1] * vec[2] * vec[3]
    printVecOut();

    //adjacent difference, 差分
    vecOut.clear();
    std::adjacent_difference(vec.begin(), vec.end(), std::back_inserter(vecOut));
    //vecOut[0] = vec[0]
    //vecOut[1] = vec[1] - vec[0]
    //vecOut[2] = vec[2] - vec[1]
    printVecOut();
}


}
#endif //_AWT_