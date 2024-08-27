#ifndef _STRING_TEST_
#define _STRING_TEST_
#include <string>
#include <iostream>

namespace STRING_TEST {
void string_ctor_size() {
    std::string s1("Hello");
    std::string s2("Hello", 3); //s2:Hel
    std::string s3(s1, 2); //s3:llo
    std::string s4(s1, 2, 2); //s4:ll
    std::string s5(5, 'a'); //s5:aaaaa
    std::string s6({'a','b', 'c'}); //s6:abc

    s1 = "Goodbye";
    auto printInfo = [](const std::string& s) {
        std::cout << "value:" << s << std::endl;
        std::cout << "size():" << s.size() << ",length():" << s.length() << std::endl; //synonyouns, both returns 7
        std::cout << "capacity():" << s.capacity() << std::endl;// size of storage space currently allocated for s1, bigger than size()
    };
    printInfo(s1);
    s1.reserve(100); //reserve doesn't change the content or size of the string, it only work on capacity
    printInfo(s1);
    s1.reserve(5); //might be different value on different compiler, but it is definitely not less than 7
    printInfo(s1);
    s1.shrink_to_fit(); //shrink the capacity to hold the content of s1
    printInfo(s1);
    s1.resize(9); //change the size, and will pad with null characters '\0'
    printInfo(s1);
    s1.resize(12, 'x'); //change the size, and will pad with characters 'x'
    printInfo(s1);
    s1.resize(3); //change the size, s1:Goo
    printInfo(s1);
}

void character_access() {
    //1.single element access
    std::string s1{"Goodbye"};
    std::cout << s1[2] << std::endl;
    s1[2] = 'x'; //will not check the range, if out of range, it's undefined behavior
    std::cout << s1 << std::endl;
    s1.at(2) = 'y'; //will check the range, throw exception if out of range
    std::cout << s1 << std::endl;

    std::cout << "s.front():" << s1.front() << std::endl;
    std::cout << "s.back():" << s1.back() << std::endl;
    s1.push_back('z');
    std::cout << s1 << std::endl;
    s1.pop_back();
    s1.begin(); s1.end();
    //Like vector, string doesn't have push_front(), and pop_front()

    std::string s3(s1.begin(), s1.begin() + 3); //Goy
    std::cout << s3 << std::endl;

    //2.ranged access
    //assign, append, insert, replace
    std::string s2{"Dragon land"};
    s1.assign(s2); //more flexible than  s1 = s2
    s1.assign(s2, 2, 3); //gon
    s1.assign("Wisdom");  //Wisdom
    s1.assign("Wisdom", 3); //Wis 
    std::cout << s1 << std::endl;
    s1.assign(s2, 3);
    s1.assign(3, 'x');
    s1.assign({'a','b','c'});
    std::cout << s1 << std::endl;

    s1.append(" def"); //abc def
    std::cout << s1 << std::endl;
    s1.insert(2, "mountain", 4); //abmounc def
    std::cout << s1 << std::endl;
    s1.replace(2,5,s2,3,3);//abgon def 
    std::cout << s1 << std::endl;

    s1.erase(1,4); //a def
    std::cout << s1 << std::endl;
    s1.substr(2,4); //agon

    s1 = "abc";
    s1.c_str(); //"abc\0"
    s1.data(); //"abc\0"

    s1.swap(s2);
    std::cout << s1 << std::endl;
}

void member_fn_algs() {

}

}
#endif //_STRING_TEST_