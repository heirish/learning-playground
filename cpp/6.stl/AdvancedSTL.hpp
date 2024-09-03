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
}
#endif //__ADVANCED_STL__