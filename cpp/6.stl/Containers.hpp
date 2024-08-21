#ifndef __BASIC_STL__
#define __BASIC_STL__

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <array>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <typeinfo>

namespace BASIC_STL_CONTAINERS{
//one direction grow: at the end of the vector
void vector_test() {
    std::vector<int> vec{4,1,8};
    vec.push_back(9); //O(1)

    std::cout << vec[3]; //no range check
    std::cout << vec.at(3); //throw range_error expcetion if out of range

    for(int i=0; i<vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    for(std::vector<int>::const_iterator it = vec.begin(); it!=vec.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    for(int i:vec) { //c++11
        std::cout << i << " ";
    }
    std::cout << std::endl;

    int *p = &vec[0]; //vector is a dynamically allocated contiguous array in memory
    p[2] = 6;
}

//two direction grow: front, end
//underlying doesn't provide contiguous data.
//has similar interface with vector
void deque_test() {
    std::deque<int> deq{4,6,7};
    deq.push_front(2); 
    deq.push_back(3); 

    std::cout << deq[1];
}

//double linked_list
//fast insert/remove at any place: O(1)
//slow search: O(n)
//no random access, no [] operator
//big advantage:很高效的切片插入 mylist1.splice(iter, mylist2, iter_a, iter_b) //O(1)
void  list_test(){
    std::list<int> lst{4,6,7};
    lst.push_back(3);
    lst.push_front(2);

    auto printlist = [&](){
        for(const int& i:lst) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    };
    printlist();
    std::list<int>::iterator it = std::find(lst.begin(), lst.end(), 7);
    lst.insert(it, 8);
    printlist();

    it++;
    lst.erase(it);
    printlist();
}

//only forward pointer
//single linked list
void forward_list_test() {

}

//size can not be changed
//two arrays may have different type
void array_test() {
    //int a[3] = {3,4,5}; //no a.begin(), a.end(), a.size(), a.swap()
    std::array<int, 3> a = {3,4,5};
    //a.begin();
    //a.end();
    //a.size();
    std::array<int, 4> b = {3,4,5,6};  //一个接受array<int,3>作为参数的函数并不能接受array<int,4>的值 
    if (typeid(a) == typeid(b)) {
        std::cout << "array<int,3> and array<int,4> has the same type" << std::endl;
    } else {
        std::cout << "array<int,3> :" << typeid(a).name() << std::endl;
        std::cout << "array<int,4> :" << typeid(b).name() << std::endl;
    }
}

//fast search:O(logn)
//tranversing is low(compare to vector&deque)
//no random access, no [] operator
//set:no duplicated
//multiset: allow duplicated items
void set_test() {
    std::set<int> myset;
    myset.insert(3);
    myset.insert(1);
    myset.insert(7);  //O(logn)

    std::set<int>::iterator it = myset.find(7);  //O(logn)
    //sequence containers don't event have find() member function
    //*it = 10; //value of the elements cannot be modified. *it is ready only 

    std::pair<std::set<int>::iterator, bool> ret;
    ret = myset.insert(3); //no new element inserted
    if (ret.second == false) {
        it = ret.first; //it now points to element 3
        std::cout << "item " << *it << " already exist." << std::endl;
    }

    myset.insert(it, 9); //it actually is used has a hint to find the actual position of insert data.
    myset.erase(it); 
    myset.erase(7); //this kind of erase by value is not available in sequence containers
}

//has same interfaces as set
//sorted by key
// keys can not be modified, type of *it: pair<const char, int>
//map: no duplicated key
//multimap: a map that allows duplicated keys
void map_test() {
    std::map<char, int> mymap;
    mymap.insert(std::pair<char, int>('a', 100));
    mymap.insert(std::make_pair('z', 200));

    std::map<char, int>::iterator it = mymap.begin();
    mymap.insert(it, std::pair<char, int>('b', 300)); //it is a hint to find the actual insert location more quickly
    it = mymap.find('z'); //O(logn)
    //(*it).first = 'd' //Error, type of *it:pair<const char, int>
    for(it = mymap.begin(); it != mymap.end(); it++) {
        std::cout << it->first << "=>" << it->second << std::endl;
    }
}

//unordered multiset:unordered set that allows duplicated elements
//unordered map: unordered set of pairs
//unordered multimap: unordered map that allows duplicated keys 
//hash collision => performance degrade
void unordered_test() {
    std::unordered_set<std::string> myset{"red", "green", "blue"};
    std::unordered_set<std::string>::const_iterator it = myset.find("green"); //O(1)
    if (it != myset.end()) {
        std::cout << *it << std::endl;
    }
    myset.insert("yellow");

    std::vector<std::string> vec{"purple", "pink"};
    myset.insert(vec.begin(), vec.end());

    //hashtable specific APIS
    std::cout << "load_factor=" << myset.load_factor() << std::endl;
    std::string x = "red";
    std::cout << x << " is in bucket #" << myset.bucket(x) << std::endl;
    std::cout << "Total buckets #" << myset.bucket_count() << std::endl;

    
}

//Associative array
//1.Search time: unordered_map:O(1), map:O(logn)
//2.Unordered_map may degrade to O(n)
//3.Can't use multimap and unordered_multimap, they don't have [] operator
void unordered_test1() {
    //Associative array
    //map and unordered_map
    std::unordered_map<char, std::string> day = {
        {'S', "Sunday"},
        {'M', "Monday"},
    };
    std::cout << day['S'] << std::endl;
    std::cout << day.at('S') << std::endl;
    
    std::vector<int> vec1{1,2,3};
    //vec1[5] = 5; //range check, compiler errror
    day['W'] = "Wednesday"; //insert 
    day.insert(std::make_pair('F', "Friday")); //insert

    std::pair<std::unordered_map<char, std::string>::iterator, bool> ret = day.insert(std::make_pair('M', "MONDAY")); //Fail to modify, it's an unordered_map,can not change pair key
    if (!ret.second) {
        std::cout << "pair with key " << ret.first->first <<  " already exist, value:" << ret.first->second << std::endl;
    }
    day['M'] = "MONDAY"; //succeed to modify value
    

    //consequence of [] operator provide write access
    //need to write more code for printing
    auto foo = [](const std::unordered_map<char, std::string>& m){
        //std::cout << m['S'] << std::endl; //will not compile. because [] provide write access to unordered_map
        auto iter = m.find('S');
        if (iter != m.end()) {
            std::cout << "found " << iter->first << "=>" << iter->second << std::endl;
        }
    };
    foo(day);
}

}
#endif //__BASIC_STL__