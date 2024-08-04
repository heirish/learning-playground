#pragma once
#include "Rectangle.h"

class Square:public Rectangle
{
public:
    Square() = default;
    ~Square() = default;
    Square(std::string_view name, double x);
public:
    void draw() const
    {
        std::cout << "Square Drawing " << m_name << " with x" << get_x() << std::endl;
    }    
    virtual void drawv() const
    {
        std::cout << "Square Drawing " << m_name << " with x" << get_x() << std::endl;
    }    
};