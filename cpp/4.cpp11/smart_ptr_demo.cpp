#include "smart_ptr_demo.h"

namespace SMART_PTR_DEMO {

void do_shared_ptr_test() {
    //two steps: 1."Gunner" is created, 2.p is created.
    //if exception happened in step 2, memory leak happens
    std::shared_ptr<Dog> p(new Dog("Gunner"));
    {
        std::shared_ptr<Dog> p2 = p;
        p2->bark();
        std::cout << "p reference count:" << p.use_count() << std::endl;
        std::cout << "p2 reference count:" << p2.use_count() << std::endl;
    }
    p->bark();
    std::cout << "p reference count:" << p.use_count() << std::endl;
    Dog* rp = p.get(); //bad idea, do not mix use raw pointer and shared_ptr

    //{ //bad way
    //    Dog* d = new Dog("Tank");
    //    std::shared_ptr<Dog> bp(d); //reference count: 1
    //    std::shared_ptr<Dog> bp2(d); //reference count:1
    //} //here  bp and bp2 will go out of scope, d will be delete twice, undefined behavior

    {
        std::shared_ptr<Dog> sp = std::make_shared<Dog>("Tank"); //faster and safer, exception safe
        (*sp).bark();
        //static_pointer_cast
        //dynamic_pointer_cast
        //const_pointer_cast
    }

    //customized deleter
    {
        std::shared_ptr<Dog> dp = std::make_shared<Dog>(); //using default deleter: operator delete
        std::shared_ptr<Dog> dp1 = std::shared_ptr<Dog>(new Dog("Tank"), [](Dog* p){
            std::cout << "custom deleting." << std::endl;
            delete p;
        });
        //std::shared_ptr<Dog> dp2(new Dog[3]); //Dog[1], Dog[2] have memory leaks;
        std::shared_ptr<Dog> dp3(new Dog[3], [](Dog* p){delete [] p;});
    }
}

void do_weak_ptr_test() {
    {
        std::shared_ptr<Cat> pc = std::make_shared<Cat>("Gunner");
        std::shared_ptr<Cat> pc1 = std::make_shared<Cat>("Smokey");
        pc->makeFriend(pc1);
        pc1->makeFriend(pc);
        pc->showFriend();
        pc1->showFriend();
        std::cout << "pc reference count:" << pc.use_count() << std::endl;
        std::cout << "pc1 reference count:" << pc1.use_count() << std::endl;
    } //memory leak if friend is delcared as std::shared_ptr
}

void do_unique_ptr_test()
{
    {
        std::unique_ptr<Dog> p = std::make_unique<Dog>("Gunner");
        p->bark();
    } // p will call Dog destructor

    {
        std::unique_ptr<Dog> p = std::make_unique<Dog>("Gunner");
        p->bark();
        Dog* pd = p.release(); //it's totally different with shared_ptr.get()
        if (!p) { std::cout << "unique_ptr becomes empty" << std::endl;}
    } //p will not call Dog destructor

    {
        std::unique_ptr<Dog> p = std::make_unique<Dog>("Smokey");
        p->bark();
        p.reset(new Dog("Gunner")); //"smokey" is destructed here
        if (!p) {std::cout << "empty" << std::endl;}
        else {std::cout << "not empty" << std::endl;}

        p.reset(); //equivilant to p = nullptr, "Gunner" will be destroyed
        if (!p) {std::cout << "empty" << std::endl;}
        else {std::cout << "not empty" << std::endl;}

    }

    { //unique_ptr can not share ownership of object at the same, but it can share ownership of the object at different time
        std::unique_ptr<Cat> p = std::make_unique<Cat>("Tank");
        std::unique_ptr<Cat> p1 = std::make_unique<Cat>("Cute");
        p1->mow();
        p1 = std::move(p);
        //1. Cute is destroyed
        //2. p becomes empty
        //3. p1 owns Tank
        if (!p) {std::cout << "p is empty" << std::endl;}
        p1->mow();
    } 

    {
        std::unique_ptr<Dog[]> p(new Dog[3]); //no need to define customized deleter
    }

}
}