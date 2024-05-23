#pragma once
#include "shape.h"

class Rectangle: public Shape
{
public:
    Rectangle() = default;
    ~Rectangle() = default;
    Rectangle(std::string_view name, double x, double y);
public:
    void draw() const
    {
        std::cout << "Rectangle Drawing " << m_name << std::endl;
    }
    virtual void drawv() const
    {
        std::cout << "Rectangle Drawing " << m_name << ",x:" << get_x() << ",y:" << get_y() << std::endl;
    }
    virtual void drawv(std::string_view color, int x) const 
    {
        std::cout << "Rectangle Drawing " << m_name << ",color:" << color << ",x:" << x << std::endl;
    }
    double get_x() const {return m_x;}
    double get_y() const {return m_y;}    
private:
    double m_x{0.0};
    double m_y{0.0};
};