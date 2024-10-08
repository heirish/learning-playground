#ifndef __destructor__
#define __destructor__
#include <iostream>
#include <memory>

namespace DESTRUCTOR_TEST {
//use virtual destructors in polymorhic base classes
class Dog {
public:
    //virtual ~Dog() {std::cout << "Dog destruced." << std::endl;}
    ~Dog() {std::cout << "Dog destruced." << std::endl;}
    virtual void bark() {}
};
class YellowDog: public Dog {
public:
    ~YellowDog() {std::cout << "YellowDog destructed." << std::endl;}
};
class DogFactory {
public:
    //static Dog* createYellowDog(){return (new YellowDog());}
    static std::shared_ptr<Dog> createYellowDog() {
        return std::make_shared<YellowDog>();
    }
     //... create other dogs
};
void virtual_destructor_test() {
    //need to declare virtual ~Dog()
    //Dog* d = DogFactory::createYellowDog();
    ////...Do something
    //delete d;

    //no need to delcare ~Dog() as virtual
    //only shared_ptr can be used to play this magic
    //unique_ptr can not work
    std::shared_ptr<Dog> pd = DogFactory::createYellowDog();
}

class Cat {
public:
    Cat(const std::string& name):_name(name) {std::cout << _name << " is born" << std::endl;}
    void miow() { std::cout << _name << " miow"<< std::endl;}
    ~Cat() {std::cout << _name << " is destroyed." << std::endl;}
private:
    std::string _name;
};
class ECat {
public:
    ECat(const std::string& name):_name(name) {std::cout << _name << " is born" << std::endl;}
    void miow() { std::cout << _name << " miow"<< std::endl;}
    ~ECat() {std::cout << _name << " is destroyed." << std::endl;throw 20;}
private:
    std::string _name;
};
class EECat {
public:
    EECat(const std::string& name):_name(name) {std::cout << _name << " is born" << std::endl;}
    void miow() { std::cout << _name << " miow"<< std::endl;}
    ~EECat() {std::cout << _name << " is destroyed." << std::endl;}
    void prepareToDestruct() {throw 20;}
private:
    std::string _name;
};

void exception_destructor_test() {
    try {
        Cat cat1("Henry");
        Cat cat2("Bob");
        throw 20;
        cat1.miow();
        cat2.miow();
    } catch (int e) { //before the exception is caught,the stack will unwind and all the local variables in the try block will be destoryed
        std::cout << e << " is caught." << std::endl;
    }
    //output:
    //Henry is born
    //Bob is born
    //Bob is destroyed
    //Henry is destroyed
    //20 is caught

    //what if an exception is thrown out of a destructor
    //program will crash
    //try {
    //    ECat cat1("Henry");
    //    ECat cat2("Bob");
    //    cat1.miow();
    //    cat2.miow();
    //} catch (int e) {
    //    std::cout << e << " is caught." << std::endl;
    //}

    //solution2: process will not crash
    //one problem: cat1.prepareToDestruct() throw exception, the cat1, cat2 will be destructed before exception is caught.
    //if there's memory related function in prepareToDestruct, memory leak would happen
    try {
        EECat cat1("Henry");
        EECat cat2("Bob");
        cat1.miow();
        cat2.miow();
        cat1.prepareToDestruct();
        cat2.prepareToDestruct();
    } catch (int e) {
        std::cout << e << " is caught." << std::endl;
    }
}

class DDog {
public:
    DDog() {std::cout << "Dog born." << std::endl;bark();}
    virtual void bark() { std::cout << "I am just a dog" << std::endl;}
    void seeCat() { bark();}
    ~DDog() { bark();}
};
class YellowDDog:public DDog {
public:
    YellowDDog() {std::cout << "Yellow dog born" << std::endl;}
    //virtual attribute can be derived, but it's a good practice to also give virtual in the derived class too.
    virtual void bark() {std::cout << "I am a yellow dog" << std::endl;}
};
void call_virtual_in_cons_destructor_test(){
    YellowDDog d; //I am just a dog
    d.seeCat(); //I am a yellow dog
} //I an just a dog
}
#endif //__destructor__