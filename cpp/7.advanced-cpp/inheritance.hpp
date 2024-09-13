#ifndef __INHERITANCCE__
#define __INHERITANCCE__
#include <iostream>

namespace INHERITANCE {
class B {
public:
    void f_pub() {std::cout << "f_pub is called.\n";}
protected:
    void f_prot() { std::cout << "f_prot is called.\n";}
private:
    void f_priv() {std::cout << "f_priv is called.\n";}
};
class D_pub:public B {
public:
 void f() {
        f_pub(); //OK: D_pub's public function
        f_prot(); //OK: D_pub's protected function
        //f_priv();//comple error inaccessible
    }    
};
class D_priv: private B {
public:
 void f() {
        f_pub();  //Ok, D_priv's private function
        f_prot(); //ok, D_priv's private function
        //f_priv();//comple error inaccessible
    } 
};
class D_prot: protected B {public:
 void f() {
        f_pub(); //ok, D_prot's protected function
        f_prot(); //ok, D_prot's protected function
        //f_priv();//comple error inaccessible
    } 
};
void do_test() {
    D_pub d1;
    d1.f_pub();
    D_prot d2;
    //d2.f_pub(); //error:inaccessible, 如果想让其不报错，则需要在D_prot的public下使用using B:f_pub;进行声明。

    B* pb = &d1;
    //pb = &d2; //error:conversion to inaccesible base class is not allowed
}

class dog{
public:
    //void bark() { std::cout << "I am just a dog" << std::endl;}//NOK case 1
    //virtual void bark(std::string name = "a yellow dog") { std::cout << "I am " << name << std::endl;}//NOK case 2
    virtual void bark() { std::cout << "I am just a dog" << std::endl;} //ok
    void bark(int age) { std::cout << "my age is " << age << std::endl;} //nok case 3
};
class yellowdog:public dog {
public:
    //void bark() { std::cout << "I am a yellow dog" << std::endl;}//NOK case 1
    //virtual void bark(std::string name="just a dog") { std::cout << "I am " << name << std::endl;}//NOK case 2
    virtual void bark() { std::cout << "I am a yellow dog" << std::endl;}//OK 
    using dog::bark; //fix for nok case 3
};
void is_a_test() {
    //NOK case 1:override non-virtual functions bark. pointer to derived class and base class behave differently
    //yellowdog* py = new yellowdog();
    //py->bark(); //I am a yellow dog
    //dog* pd = py;
    //pd->bark(); //I am just a dog

    //NOK case 2:override default parameter values for virtual function
    //yellowdog* py = new yellowdog();
    //py->bark(); //I am just a dog
    //dog* pd = py;
    //pd->bark(); //I am a yellow dog
    
    //ok:
    yellowdog* py = new yellowdog();
    py->bark(); //I am a yellow dog
    dog* pd = py;
    pd->bark(); //I am a yellow dog

    //NOK case 3:not inherit shadowed function, bark(int age) is shadowed.
    py->bark(5); //compile error if without the fix for nok case 3
    pd->bark(5);  
}
}
#endif //__INHERITANCCE__