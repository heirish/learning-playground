#include "engineer.h"

std::ostream& operator<<(std::ostream &os, const Engineer& eg)
{
    os << "name:" << eg.m_name << ",age" << eg.m_age;
    return os;
}