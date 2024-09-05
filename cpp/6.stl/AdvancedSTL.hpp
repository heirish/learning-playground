#ifndef __ADVANCED_STL__
#define __ADVANCED_STL__
#include <unordered_set>
#include <map>
#include <list>
#include <algorithm>
#include <string>

namespace ADVANCED_STL {
void performance_compare() {
    //unordered container
    std::unordered_set<int> s{2,4,1,8,5,9};
    std::unordered_set<int>::iterator iter;
    //using member function, winner
    iter = s.find(4); //O(1);
    //using algorithm
    iter = std::find(s.begin(), s.end(), 4); //O(n)

    std::map<char, std::string> mymap{{'S', "Sunday"},
                                      {'M', "Monday"},
                                      {'W', "Wendesday"}};
    std::map<char, std::string>::iterator it;
    //using member function:only compare key. winner
    it = mymap.find('F'); //O(logn)
    //using Algorithm:compare both key and value
    //it = std::find(mymap.begin(), mymap.end(), std::make_pair('F', std::string("Friday"))); //O(n)
    it = std::find(mymap.begin(), mymap.end(), std::pair<const char, std::string>('F', std::string("Friday"))); //O(n)

    std::list<int> lst{2,4,1,8,5,9};
    //using member function:directly tweakking the pointer, winner
    lst.remove(4); //O(n), after function, content is {2,1,8,5,9}
    //using algorithm function:copy data from the later item
    std::remove(lst.begin(), lst.end(), 4); //O(n), 
    //after function, content is {2,1,8,5,9,9}, to clear it, need to call lst.erase(std::remove)
    //because the algorithm only know the data through iterator,the container is the only one that can actually remove the items

    //sort
    //member function
    lst.sort();
    //algorithm function
    //std::sort(lst.begin(), lst.end()); //undefined behavior:because std::sort need a random access iterator, which list doesn't have 
}

void reverse_iterator_test() {
    //two ways to declare a reverse iterator
    std::reverse_iterator<std::vector<int>::iterator> riter;
    std::vector<int>::reverse_iterator ritr;

    std::vector<int> vec{4,5,6,7};
    for(riter = vec.rbegin(); riter != vec.rend(); riter++) {
        std::cout << *riter << " "; //7 6 5 4
    }
    std::cout << std::endl;

    //coversation:
    std::vector<int>::iterator iter;
    ritr = std::vector<int>::reverse_iterator(iter);  //OK;
    //iter = std::vector<int>::iterator(ritr); //compile error
    iter = ritr.base();
    //c++ standard: base() return current iterator
    //what does current iterator mean?

    std::vector<int> iv{1,2,3,4,5};
    ritr = std::find(iv.rbegin(), iv.rend(), 3);
    std::cout << (*ritr) << std::endl; //3
    iter = riter.base();
    std::cout << (*iter) << std::endl; //4
}

class Lsb_less {
public:
    bool operator() (int x, int y) {
        return (x%10) < (y%10);
    }
};
void equivalence_vs_equality_test() {
    std::set<int, Lsb_less> s{21,23,26,27};
    std::set<int, Lsb_less>::iterator itr1, itr2;
    //algorithm std::find() looks for equality if (x==y)
    itr1 = std::find(s.begin(), s.end(), 36); //s.end()
    //std::set::find() looks for equivalence: if (!compare(x,y) && !compare(y,x))
    itr2 = s.find(36); //26
    if (itr1 != s.end()) {
        std::cout << "*itr1=" << *itr1 << std::endl;
    }
    if (itr2 != s.end()) {
        std::cout << "*itr2=" << *itr2 << std::endl;
    }

    //if s is defined as std::set<int>, which will use default std::less compare.
    //then iter1 and iter2 will return the same s.end()
}


template <typename T>
void print(T t, std::string msg) {
    std::cout << msg << "{";
    for(typename T::iterator it = t.begin(); it != t.end(); it++) {
        std::cout << *it << ", ";
    }
    std::cout << "}" << std::endl;
}
void remove_elements_test() {
    //removing elements from vector
    std::vector<int> c{1,4,6,1,1,1,1,12,18,16};
    print(c, "Original:");
    std::cout << "capacity:" << c.capacity() << std::endl;

    //for(std::vector<int>::iterator it = c.begin(); it !=c.end();) {
    //    if (*it == 1) {
    //        it = c.erase(it);
    //    } else {
    //        it++; 
    //    }
    //} //Complexity:O(n*m), elements after the deleted item is copying to the privous for each each erasing
    //print(c, "After erase():");
    //better solution
    std::vector<int>::iterator newend = std::remove(c.begin(), c.end(), 1); //it only move the unremoved items to the front once. complexity: O(n)
    print(c, "After move():");
    c.erase(newend, c.end()); //actually remove the items using member function erase
    print(c, "After erase():");
    std::cout << "capacity:" << c.capacity() << std::endl; //size is reduced to 5, but the capacity is still 10, which mean still 10 items memory is occupied.
    //if that memmory is imported for reuse, call shrink_to_fit to release the unused memory
    //c.shrink_to_fit(); //c++11
    std::vector<int>(c).swap(c);//before c++11
    std::cout << "after shrink_to_fit(), capacity:" << c.capacity() << std::endl; //size is reduced to 5, but the capacity is still 10, which mean still 10 items memory is occupied.


    //remove elements from a list
    std::list<int> lst{1,4,6,1,1,1,1,12,18,16};
    print(lst, "Original list:");
    //auto itr = std::remove(lst.begin(), lst.end(), 1); //Complexity O(n)
    //lst.erase(itr, lst.end());
    //print(lst, "after std::remove and erase(),list:");
    //beter solution
    lst.remove(1); //tweaking the pointer directly, more efficient and simple
    print(lst, "after list::remove(),list:");

    //remove elements from associative function or unordered container
    std::multiset<int> mc{1,4,6,1,1,1,1,12,18,16};
    print(mc, "Original multiset:");
    //auto iter = std::remove(mc.begin(), mc.end(), 1); //compile error, O(n)
    //mc.erase(iter, mc.end());
    //print(mc, "after std::remove and set::erase(), multiset:");
    mc.erase(1); //O(logn), for unordered container, it's even better - constant time
    print(mc, "after set::erase(), multiset:");

}

//bool equalTo(int e, int val) {
//    if (e == val) {
//        std::cout << e << " will be removed" << std::endl;
//        return true;
//    }
//    return false;
//}
class EqualTo {
public:
    explicit EqualTo(int val):_val(val){}
    bool operator() (int item) {return item == _val;}
private:
    int _val;
};
void remove_element_and_do_sth_test() {
    //print a message whenever an item is removed
    std::multiset<int> mc{1,4,6,1,1,1,1,12,18,16};
    //for(std::multiset<int>::iterator it = mc.begin(); it !=mc.end(); it++) {
    //    if (*it == 1) {
    //        mc.erase(it); //iterator for the erased item is invalidated after erase, so the next loop when it!=mc.end();it++, the behavior is undefined
    //        std::cout << "Erased one item of " << *it << std::endl;
    //    }
    //}
    //fix
    for(auto it = mc.begin(); it !=mc.end();) {
        if (*it == 1) {
            std::cout << "Erased one item of " << *it << std::endl;
            //mc.erase(it++); //it++ will return it to erase(), and it += 1; 
            it = mc.erase(it); //also works
        } else {
            it++;
        }
    }
    print(mc, "after erase multiset:");

    std::vector<int> vec{1,4,6,1,1,1,1,12,18,16};
    //for(auto it = vec.begin(); it !=vec.end();) {
    //    if (*it == 1) {
    //        std::cout << "Erased one item of " << *it << std::endl;
    //        vec.erase(it++); //it++ will return it to erase(), and it += 1; 
    //    } else {
    //        it++;
    //    }
    //} //only removed 3 items 1
    //print(vec, "after erase vec:"); //{4,6,1,1,12,18,16}
    //because for vector, after one element erased, ALL the iterator AFTER that erased element is INVALIDATED
    //fix
    for(auto it = vec.begin(); it !=vec.end();) {
        if (*it == 1) {
            std::cout << "Erased one item of " << *it << std::endl;
            it = vec.erase(it);
        } else {
            it++;
        }
    }
    print(vec, "after erase vec:"); //{4,6,1,1,12,18,16}
    //better solution
    auto equalTo = [](int e, int val) -> bool {
        if (e == val) {
            std::cout << e << " will be removed" << std::endl;
            return true;
        }
        return false;
    };
    auto newend = std::remove_if(vec.begin(), vec.end(), std::bind(equalTo, std::placeholders::_1, 12));
    //auto newend = std::remove_if(vec.begin(), vec.end(), EqualTo(12)); //also works using a functor
    vec.erase(newend, vec.end());
    print(vec, "after std::remove_if and erase, vec:");
}

class Dog {};
void vector_vs_deque_test() {
    std::vector<int> vec{2,3,4,5};
    std::cout << "vec's size:" << vec.size() << std::endl; //4
    std::cout << "vec's capacity:" << vec.capacity() << std::endl; //4
    vec.push_back(6);
    std::cout << "after push_back(6), vec's size:" << vec.size() << std::endl; //5
    std::cout << "after push_back(6), vec's capacity:" << vec.capacity() << std::endl; //8

    std::vector<Dog> dogs(6); //6 Dogs created with default constructor
    std::cout << "dogs' size:" << dogs.size() << std::endl; //6
    std::cout << "dogs' capacity:" << dogs.capacity() << std::endl; //6
    std::vector<Dog> dogs2; //dogs2 size() == 0, capacity() == 0
    dogs2.resize(6); //6 dogs created iwth default constructor
    std::cout << "dogs2' size:" << dogs2.size() << std::endl; //6
    std::cout << "dogs2' capacity:" << dogs2.capacity() << std::endl; //6
    std::vector<Dog> dogs3; //dogs3 size() == 0, capacity() == 0
    dogs3.reserve(6); //no dog's default constructor invoked
    std::cout << "dogs3' size:" << dogs3.size() << std::endl; //0
    std::cout << "dogs3' capacity:" << dogs3.capacity() << std::endl; //6
    //the expensive reallocation of a vector happens only when the capacity of the vector is full
    //if we already know how many item that the vector will hold
    //we can reserve that amount of memory for this vector
    //so that we can avoid the expensive reallocation all together.

    std::vector<int> v;
    for(int i=0; i<1025; i++) { 
        v.push_back(i); //11 reallocations performed(when growth ratio=2)
    }
    //better solution: call v.reserve(1024);before push_back

    std::vector<int> v1{2,3,4,5};
    int* p=&v1[3];
    v1.push_back(6); //reallocation, invalidate pointers/references/iterators
    //here it might still can print 5, that because of the memory_chunk recycle strategy in libc++, 
    //if the item is class type, here would crash
    std::cout << *p << std::endl; //undefined behavior, reallocation happened, *p is wild pointer
    std::cout << "before reallocation, &v1[3]:" << std::hex << std::showbase << p << std::endl;
    std::cout << "after reallocation, &v1[3]:" << std::hex << std::showbase << &v1[3] << std::endl;
    //adress of v1[3] changed

    std::deque<int> deq{2,3,4,5};
    p = &deq[3];
    deq.push_back(6); //push_front() is Ok too
    std::cout << std::dec << *p << std::endl; //5, OK
    std::cout << "before reallocation, &deq[3]:" << std::hex << std::showbase << p << std::endl;
    std::cout << "after reallocation, &deq[3]:" << std::hex << std::showbase << &deq[3] << std::endl;
    //adress of deq[3] not changed
    //deque:inserting at either end won't invalidate pointers
    //!!!Note:removing or inserting in the middle still will invalidate pointers/references/interator

    auto c_fun = [](const int* arr, int size) {};
    c_fun(&v1[0], v1.size());
    //passing data from a list to C
    std::list<int> mylist{2,3,4,5};
    std::vector<int> vlist(mylist.begin(), mylist.end());
    c_fun(&vlist[0], vlist.size());

    auto cpp_fun = [](const bool* arr, int size) {};
    std::vector<bool> bv{true, true, false, false};
    //cpp_fun(&bv[0], bv.size()); //compile error
}
}
#endif //__ADVANCED_STL__