#pragma once
#include "person.h"

class Engineer:private Person
{
friend std::ostream& operator<<(std::ostream &os, const Engineer& eg);
public:
    Engineer() = default;
    ~Engineer() = default;
    void work() 
    {
        this->m_name = "ff";
        this->m_age = 23;
    }
public:
    using Person::get_name; //using提权，提权前为private, 提权后为public, 可直接通过Engineer访问 
    using Person::get_age;
protected:
    using Person::m_name; //using提权，提权前为private(因为private继承), 提权后，Engineer的子类可以继承访问这些属性
    using Person::m_age;
};