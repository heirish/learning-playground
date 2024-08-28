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

//copy, find,compare
void member_fn_algs() {
    std::string s1 = "abcdefg";
    char buf[20];
    size_t len = s1.copy(buf, 3); //buf: abc len==3
    std::cout <<  "len = " << len << ",buf = " << buf << std::endl;
    len = s1.copy(buf, 4, 2); //buf: cdef len==4

    s1 = "If a job is worth doing, it's worth doing well";
    size_t found = s1.find("doing");
    std::cout << "found doing at position:" << found << std::endl;
    found = s1.find("doing", 20);
    std::cout << "second found doing at position:" << found << std::endl;
    found = s1.find("doing well", 0, 5); //only search for doing from index 0
    std::cout << "found doing at position:" << found << std::endl;
    found = s1.find_first_of("doing");  //find the first character that in doing
    std::cout << "the first character appears in s1 that is in doing is:" << found << ",char:" << s1[found] << std::endl;
    found = s1.find_last_of("doing");  //g
    std::cout << "the last character appears in s1 that is in doing is:" << found << ",char:" << s1[found] << std::endl;
    found = s1.find_first_not_of("doing");  //I
    std::cout << "the first character appears in s1 that is not in doing is:" << found << ",char:" << s1[found] << std::endl;
    found = s1.find_last_not_of("doing");  //l
    std::cout << "the last character appears in s1 that is not in doing is:" << found << ",char:" << s1[found] << std::endl;

    //compare
    std::string s2;
    s1.compare(s2); // positive if (s1>s2); 0 if(s1==s2); negative if(s1<s2)
    if (s1 > s2) {} //equivalent to if(s1.compare(s2) > 0), .compare() is more flexible
}

void non_member_fns() {
    std::string s1;
    //std::cin >> s1;
    //getline(std::cin, s1);

    //convert a number into a string
    s1 = std::to_string(8);
    s1 = std::to_string(2.3e7); //23000000.000000
    s1 = std::to_string(0xa4); //164  十六进制
    s1 = std::to_string(034); //28 八进制  

    //convert a string into a number
    int i = stoi(s1);
    s1 = "190 monkeys";
    size_t pos;
    i = stoi(s1, &pos); //i:190 pos==3
    std::cout << "parsed integer :" << i << " from string, stopped at pos:" << pos << std::endl;
    s1 = "a monkey";
    //i = stoi(s1); //exception of invalid_argument
    i = stoi(s1, &pos, 16); //will try to extrace hex decimal number from the string.
    std::cout << i << std::endl; //10 <-> hex:a
    
    //other string conversion
    //stol, stod, stof, 
    //stringstream
    //lexical_cast()
}

void string_and_algs() {
    std::string s1 = "Variety is the spice of life";
    int num = std::count(s1.begin(), s1.end(), 'e'); //4
    num = std::count_if(s1.begin(), s1.end(), [](char c){return (c<='e' && c>='a');}); //6

    s1 = "Goodness is better than beauty";
    std::string::iterator it = std::search_n(s1.begin(), s1.end()+20, 2, 's');//itr->first 's
    s1.erase(it, it+5); //Goodne better than beauty
    std::cout << s1 << std::endl;
    s1.insert(it, 3, 'x');//Goodnexxx better than beauty
    std::cout << s1 << std::endl;
    s1.replace(it, it+3, 3, 'y');//Goodneyyy better than beauty, replacing substring
    std::cout << s1 << std::endl;

    std::string s2;
    std::is_permutation(s1.begin(), s1.end(), s2.begin());
    std::replace(s1.begin(), s1.end(), 'e', ' '); //replacing character
    s2 = std::string(s1.size(), ' ');
    std::transform(s1.begin(), s1.end(), 
                   //std::back_inserter(s2), 
                   s2.begin(), 
                   [](char c){
                        if (c<'n') return 'a';
                        else return 'z';});
    std::cout << s2 << std::endl;

    s1 = "abcdefg";
    std::rotate(s1.begin(), s1.begin()+3, s1.end()); //defgabc, s1.begin()+3 became the first character
    std::cout << s1 << std::endl;
}

}
#endif //_STRING_TEST_