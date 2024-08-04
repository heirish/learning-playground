#include "Rectangle.h"

Rectangle::Rectangle(std::string_view name, double x, double y):Shape(name), m_x(x), m_y(y) {}