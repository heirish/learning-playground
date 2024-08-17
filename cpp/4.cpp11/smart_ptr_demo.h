#ifndef __SMART_PTR_DEMO__
#define __SMART_PTR_DEMO__
#include <string>
#include <memory>
#include <iostream>

namespace SMART_PTR_DEMO {
class Dog {
    std::string _name{"nameless"};
public:
    explicit Dog(const std::string& name):_name(name) {std::cout << "Dog is created:" << _name << std::endl;}
    Dog() {std::cout << "Nameless dog created." << std::endl;}
    ~Dog() {std::cout << "dog is destroyed:" << _name << std::endl;}
    
    void bark() { std::cout << "Dog " << _name << " rules!" << std::endl;}
};
void do_shared_ptr_test();


class Cat {
    //std::shared_ptr<Cat> _friend;
    std::weak_ptr<Cat> _friend;
public:
    std::string _name{"nameless"};
    explicit Cat(const std::string& name):_name(name){std::cout << "Cat is created:" << _name << std::endl;}
    void mow() { std::cout << "Cat " << _name << "mow" << std::endl;}
    ~Cat() { std::cout << "Cat is destroyed: " << _name << std::endl;}
    void makeFriend(std::shared_ptr<Cat> f) { _friend = f;}
    void showFriend() {
        if (!_friend.expired()) {
            std::cout << "My friend is :" << _friend.lock()->_name << std::endl;
        }
        std::cout << "my friend is owned by " << _friend.use_count() << " shared_ptrs" << std::endl;
    }
};
void do_weak_ptr_test();

void do_unique_ptr_test();
}

#endif //__SMART_PTR_DEMO__