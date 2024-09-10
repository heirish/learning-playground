#ifndef __self_assignment__
#define __self_assignment__
#include <iostream>

namespace SELF_ASSIGNMENT {
class collar{};
class Dog {
public:
    //Solution 1
    Dog& operator=(const Dog& rhs) {//rhs:right hand side
        //point 1:
        if (this == &rhs) return *this;
        
        //without above check condition, below would cause program crash

        //still have a problem: what if the copy constructor of collar from (*rhs._pCollar) throw an exception?
        //then this has already deleted it's _pCollar but it failed to create a new _pCollar
        //then _pCollar is pointing a an invalid object
        //delete _pCollar;
        //_pCollar = new collar(*rhs._pCollar);
        
        //point 2
        collar* pOrigCollar = _pCollar;
        _pCollar = new collar(*rhs._pCollar);
        delete pOrigCollar;
        return *this;
    }
    /*solution2: decrease performance
    Dog& operator=(const Dog& rhs) {//rhs:right hand side
        //solution2: delegation
        *_pCollar = *rhs._pCollar; //member by member copying of collars or call collar's operator=
        //no need to check self assignment here, it will be checked in collar's operator=
        return *this;
    }
    */

private:
    collar* _pCollar;
};
void handle_self_assignment_test() {
    Dog d;
    d = d;
    std::cout << "not crash?" << std::endl;
}
};
#endif //__self_assignment__