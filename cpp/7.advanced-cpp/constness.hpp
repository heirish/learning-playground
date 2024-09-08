#ifndef __CONST__
#define __CONST__
#include <iostream>
#include <string>
#include <vector>

namespace CONST_TEST {
void const_variable_test() {
    const int i = 9;
    //i = 6; //compile error

    const int* p1 = &i; //data is const, pointer is not
    //*p1 = 6; //compile error
    p1++; //compile ok

    int* const p2 = nullptr; //pointer is const, data is not
    const int * const p3 = nullptr; //data and pointer are both const
    int const *p4  = nullptr; //equivalence to p1, data is const, pointer is not
    //rule:
    //if const is on the left of *, data is const
    //if const is on the right of *, pointer is const

    //cast
    //const_cast can cast away the constness of i
    //const_cast<int&>(i) = 6;
    //std::cout << "i=" << i << std::endl; //why值没变?
    int& vi = const_cast<int&>(i);
    vi = 6;
    std::cout << "vi=" << vi << std::endl; //6
    std::cout << "i=" << i << std::endl; //9, i与vi的值不一样?
    //cast a changable variable to const
    int j;
    //static_cast<const int&>(j) = 7; //compile error, 

    //working const_cast
    volatile const int ii = 8;
    const_cast<int&>(ii) = 6;
    std::cout << "ii=" << ii << std::endl; //6
}

class Dog{
public:
    //const parameter
    void setAge(const int& a) {
        std::cout << "set Age const int&" << std::endl;
        _age = a; 
        //a++;
    }
    //const paremeter function can also be overloaded
    void setAge(int& a) {
        std::cout << "set Age int&" << std::endl;
        _age = a; 
        a++;
    }

    //const return value
    const std::string& getName() {return _name;}

    //const function
    void print() const {
        std::cout << "name:" << _name << std::endl;
        std::cout << "age:" << _age<< std::endl;
        //_age++; //compile error, modify member variable is not allowed(excpet it's decalred as mutable)
        //getName(); //comiler error, call other non-const function is not allowed
        _printTimes++;
        std::cout << "printTimes:" << _printTimes << std::endl;
    }

    //non-const overload of const function
    void printName() const { //will be invoked when it's a const Dog
        std::cout << _name << " const" << std::endl;
    }
    void printName() { //will be invoked when it'a a Dog
        std::cout << getName() << " non-const" << std::endl;
    }
private:
    int _age{3};
    std::string _name{"dummy"};
    mutable int _printTimes{0};
};
void const_function_test() {
    Dog d;
    int i = 9;
    d.setAge(i); //call setAge(int&)
    std::cout << i << std::endl;

    const std::string n = d.getName();
    std::cout << "name=" << n << std::endl;

    d.print();
    d.printName(); //<name> non-const

    const Dog d2;
    d2.printName(); //<name> const

    const int ci = 10;
    d.setAge(ci); //call setAge(const int&)
    d.setAge(2); //call setAge(const int&)
    d.setAge(std::move(i));//call setAge(const int&)
}

class BigArray {
public:
    //logic model it's const, because what matters to the class is the state of v
    //but bitwise it's not const, so compiler will raise error
    //solution: delcare the not-cared variable as mutable
    int getItem(int index) const {
        //accessCounter++; //way1
        const_cast<BigArray*>(this)->accessCounter++; //bad:way2
        return v[index];
    }
    
    //logic is not const
    //but declare it as const, 
    //compiler will be OK because it didn't change the class member values, so it don't voilate the bitwise const
    void setV2Item(int index, int x) const {
        *(v2 + index) = x;
    }
private:
    std::vector<int> v;
    //mutable int accessCounter; //way 1
    int accessCounter; //way2
    int* v2;
};
void logic_vs_bitwise_constness_test() {
    BigArray b;
}
}
#endif //__CONST__