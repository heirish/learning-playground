#ifndef __OPERATOR_ALLOCATION__
#define __OPERATOR_ALLOCATION__
#include <iostream>
#include <string>
namespace OPERATOR_DELETE_NEW{
class Person{
public:
    explicit Person(const std::string& name, int age): _name(name), _age(age) {
        std::cout << "Person::Person()" << std::endl;
        std::cout << "constructor is called automatically.Person:" << _name << "," << _age << std::endl;
    }
    virtual ~Person() {
        std::cout << "Person::~Person()" << std::endl;
        std::cout <<  "destructor should be delcared as virtual if polymorhpism is used. " << std::endl;
    }

    static void* operator new(std::size_t size) //throw (std::bad_alloc) , deprecated since c++11
    {
            std::cout << "Person::new()" << std::endl;
            return ::operator new(size);
    }
    static void operator delete(void* pmem) {
        std::cout << "Person::delete()" << std::endl;
        ::operator delete(pmem);
    }
private:
    std::string _name;
    int _age;
};
class Student: public Person {
public:
    explicit Student(const std::string& name, int age):Person(name, age) {
        std::cout << "Student::Student()" << std::endl;
    }
    ~Student() {
        std::cout << "Student::~Student()" << std::endl;
    }
    static void* operator new(std::size_t size) /*throw (std::bad_alloc)*/ {
        std::cout << "Student::new()" << std::endl;
        return ::operator new(size);
    }
};
void do_test() {
    //Person* p = new Person("Bob", 13);
    //delete p;
    //output
    //Person::new()
    //Person::Person()
    //Person::~Person()
    //Person::delete()

    //Student* p1 = new Student("Jane", 14);
    //delete p1;
    //output
    //Student::new()
    //Person::Person()
    //Student::Student()
    //Student::~Student()
    //Person::~Person()
    //Person::delete()

    Person* p2 = new Student("Amy", 15);
    delete p2;
    //output
    //Student::new()
    //Person::Person()
    //Student::Student()
    //Student::~Student() //this line will not printed if ~Person() is not delcared as virtual
    //Person::~Person()
    //Person::delete()
}



void nomoreMem() {
    std::cerr << "Unable to allocate memory.";
    std::abort();
}
//class specific new-handler
//NOTE!!!!!!!!!not thread-safe
class dog {
public:
    static void NoMemForDog() {
        std::cerr << "No More memory for doggy.";
        std::set_new_handler(origHandler);
        throw std::bad_alloc();
    }
    static void* operator new(std::size_t size) /*throw(std::bad_alloc)*/ {
        origHandler = std::set_new_handler(NoMemForDog);
        void* pV = ::operator new(size); //call global operator new
        std::set_new_handler(origHandler);
        return pV;
    }
private:
    double hair[1'000'000'000'000L]; 
    static std::new_handler origHandler;
};
std::new_handler dog::origHandler;
void new_handler_test() {
    //double* p = new double[1'000'000'000'000L]; //exception bad_alloc
    //delete[] p;

    //std::set_new_handler(nomoreMem);
    //double* p = new double[1'000'000'000'000L]; //call nomoreMem, then program terminated
    //delete[] p;

    std::shared_ptr<dog> pd(new dog()); //use the class defined new operator, will call NoMemForDog
    //std::shared_ptr<dog> pd = std::make_shared<dog>(); //using global operator new, will not call  NoMemForDog
}
}
#endif //__OPERATOR_ALLOCATION__