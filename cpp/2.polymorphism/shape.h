#pragma once
#include <string>
#include <string_view>
#include <iostream>

class Shape
{
public:
    Shape() = default;
    ~Shape() = default;
    explicit Shape(std::string_view name);

public:
    void draw() const 
    {
        std::cout << "Shappe Drawing " << m_name << std::endl;
    }
    virtual void drawv() const 
    {
        std::cout << "Shappe Drawing " << m_name << std::endl;
    }
    virtual void drawv(std::string_view color) const
    {
        std::cout << "Shappe Drawing " << m_name << ",color:" << color << std::endl;
    }

protected:
    std::string m_name;
};