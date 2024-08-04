#pragma once

#include "person.h"

class Worker : public Person
{
friend std::ostream& operator<< (std::ostream &os, const Worker& worker);
public:
    Worker() {m_count++;}
    explicit Worker(std::string_view job);
    Worker(std::string_view job, int age);
    Worker(std::string_view fullName, int age, std::string_view address, std::string_view job);
    ~Worker() {m_count--;}

    Worker(const Worker &rhs);
    //Worker& operator=(const Worker &rhs);
public:
    static int m_count;
private:
    std::string m_job{"None"};

};