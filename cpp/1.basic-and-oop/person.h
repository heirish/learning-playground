#pragma once
#include <iostream>
#include <string>
#include <string_view>
#include "cat.h"

class Person 
{
friend std::ostream& operator<<(std::ostream &os, const Person &person);
public:
    Person() {m_count++;}
    Person(std::string_view fullName, int age, std::string_view address);
    ~Person();

    Person(const Person &rhs);
    //Person& operator=(const Person &rhs);
public:
    std::string get_name() const {return m_name;}
    int get_age() const {return m_age;}
    std::string get_address() const {return m_address;}

public:
    void do_something() const;
    void cat_info(const Cat &cat) const{
        std::cout << "Cat name:" << cat.m_name << ",age" << cat.m_age << std::endl;
    }

public:
    std::string m_name{"None"};
    static int m_count;
protected:
    int m_age{0};
private:
    std::string m_address{"None"};
};