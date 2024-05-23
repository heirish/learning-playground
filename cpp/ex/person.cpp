#include "person.h"

int Person::m_count{0};
Person::Person(std::string_view fullName, int age, std::string_view address)
:m_name(fullName), m_age(age), m_address(address) { m_count++;}

Person::~Person() {m_count--;}

Person::Person(const Person &rhs):Person(rhs.m_name, rhs.m_age, rhs.m_address) {m_count++;}

void Person::do_something() const
{
    std::cout << "some" << std::endl;
}

std::ostream& operator<< (std::ostream &os,  const Person &person)
{
    os << "name:" << person.m_name << ",age:" << person.m_age << ",address:" << person.m_address;
    return os;
}