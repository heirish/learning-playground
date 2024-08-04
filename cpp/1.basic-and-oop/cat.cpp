#include "cat.h"

std::string Cat::get_name() const
{
    return this->m_name;
}
int Cat::get_age() const
{
    return this->m_age;
}
void Cat::set_name(const std::string &name)
{
    this->m_name = name;
}
void Cat::set_age(int age) 
{
    this->m_age = age;
}
void Cat::print_object() const 
{
    std::cout << "Cat (" << this << "):name:" << this->m_name << ", age:" << this->m_age << std::endl;
    std::cout << "called time:" << m_count++ << std::endl;
}

std::ostream& operator<<(std::ostream &os, const Cat &cat)
{
    os << "Cat address:" << &cat << ",name:" << cat.m_name << ",age:" << cat.m_age ;
    return os;
}

