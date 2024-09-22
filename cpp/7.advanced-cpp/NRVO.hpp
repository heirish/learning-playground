#ifndef __NRVO__
#define __NRVO__
#include <iostream>
namespace NRVO {
class Dog {
public:
    Dog() {std::cout <<"Dog()" << std::endl; }
    Dog(const Dog&) {std::cout << "Dog(const Dog&)"<<std::endl;}
    Dog(Dog&&) {std::cout << "Dog(Dog&&)"<<std::endl;}
};
Dog simple(){
    Dog d;
    //简单返回对象，一般有NRVO
    return d;
}
Dog simple_with_move(){
    Dog d;
    //move会禁止NRVO
    return std::move(d);
}

Dog Complicated(int n) {
    Dog d1;
    Dog d2;
    //有分支，一般无NRVO
    if (n%2 == 0) {
        return d1;
    } else {
        return d2;
    }
}

void do_test() {
   std::cout << "=====simple====" << std::endl;
   auto d1 = simple(); //NRVO.直接给d1构造.输出:Dog() 
   std::cout << "=====simple_with_move====" << std::endl;
   auto d2 = simple_with_move(); //没有NRVO，而是采用了函数里构造+move return. 输出:Dog(), Dog(Dog&&)
   std::cout << "=====complicated====" << std::endl;
   auto d3 = Complicated(42);//没有NRVO，输出:Dog(), Dog(), Dog(Dog&&)
}
}
#endif //__NRVO__