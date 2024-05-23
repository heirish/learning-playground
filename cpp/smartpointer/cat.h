#pragma once
#include <iostream>
#include <string>
#include <memory>

class Cat 
{
friend class Person;   //friend class是单向的，Person是Cat的friend类，可以访问Cat中的私有成员。但Cat不一定是Person的friend类，需要在Person类中声明了才是。
friend std::ostream& operator<<(std::ostream &, const Cat  &);
public:
    Cat(const std::string &name, int age, int* ptr):m_name(name), m_age(age), m_pt(new int(*ptr)){}
    Cat(const std::string &name, int age):Cat(name, age, new int{0}) {}
    Cat(const std::string &name):Cat(name,0){}
    //explicit Cat(const std::string &name):Cat(name,0){}
    ~Cat() {
        if (m_pt) {
            delete m_pt;
            m_pt = nullptr;
        }
        std::cout << "destructor of cat name:" << m_name << ",age:" << m_age << std::endl;
    }
    Cat(const Cat& rhs) {
        this->m_name = rhs.m_name;
        this->m_age = rhs.m_age;
        this->m_pt = new int{*(rhs.m_pt)};
        std::cout << "copy constructor" << std::endl;
    }
    Cat(Cat&& cat):Cat(std::move(cat.m_name), std::move(cat.m_age), cat.move_ptr()) {
        std::cout << "move constructor" << std::endl;
    }
    Cat& operator=(const Cat& rhs) {
        if (&rhs == this) return *this;
        
        delete this->m_pt;

        this->m_name = rhs.m_name;
        this->m_age = rhs.m_age;
        this->m_pt = new int{*(rhs.m_pt)};
        std::cout << "copy operator=" << std::endl;
        return *this;
    }
    Cat& operator=(Cat&& cat) {
        delete this->m_pt;

        this->m_name = cat.m_name;
        this->m_age = cat.m_age;
        this->m_pt = cat.move_ptr();
        std::cout << "move operator=" << std::endl;
        return *this;
    }
public:
    std::string get_name() const;
    int get_age() const;
    void set_name(const std::string &name);
    void set_age(int age);
    void print_object() const;
public:
    std::string& name()
    {
        return this->m_name;
    }
    const std::string& name() const{
        return this->m_name;
    }
    void set_friend(std::shared_ptr<Cat> cat)
    {
        m_friend = cat;
    }
private:
    int* move_ptr()
    {
        int *new_ptr(this->m_pt);
        this->m_pt = nullptr;
        return new_ptr;
    }
private:
    std::string m_name;
    int m_age;
    mutable int m_count{0}; //可以在const函数中修改的值，一般用于记录调用次数
    int* m_pt;
    //std::shared_ptr<Cat> m_friend{nullptr};
    std::weak_ptr<Cat> m_friend;
};

std::ostream& operator<<(std::ostream &os, const Cat& cat);