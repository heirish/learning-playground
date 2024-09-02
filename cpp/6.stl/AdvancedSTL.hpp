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
}
#endif //__ADVANCED_STL__