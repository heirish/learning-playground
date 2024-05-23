#include <iostream>
#include "shape.h"
#include "Rectangle.h"
#include "Square.h"
using namespace std;

void test_static_bind()
{
    Shape s1("Shape1");
    s1.draw();

    Rectangle r1("Rectangle1", 1.0, 2.0);
    r1.draw();

    Square sq1("Square", 3.0);
    sq1.draw();

    //以下实际上调用的都是Shape::draw()
    Shape *ptr = &s1;
    ptr->draw();
    ptr = &r1;
    ptr->draw();
    ptr = &sq1;
    ptr->draw();
}

void test_dynamic_bind()
{
    Shape s1("Shape1");

    Rectangle r1("Rectangle1", 1.0, 2.0);

    Square sq1("Square", 3.0);

    Shape *ptr = &s1;
    ptr->drawv();
    ptr = &r1;
    ptr->drawv();
    ptr = &sq1;
    ptr->drawv();
}

void draw_shape(Shape *s)
{
    s->drawv();
}
void test_poly_useage()
{
    Shape s1("Shape1");
    Rectangle r1("Rectangle1", 1.0, 2.0);
    Square sq1("Square", 3.0);

    Shape *ptr = &s1;
    draw_shape(ptr);
    ptr = &r1;
    draw_shape(ptr);
    ptr = &sq1;
    draw_shape(ptr);

    //值存储类型不能多态 
    Shape shapes[]{s1, r1, sq1};
    for (Shape &s:shapes)
    {
        s.drawv();
    }

    //指针可多态
    Shape* pshapes[]{&s1, &r1, &sq1};
    for(Shape *p: pshapes)
    {
        p->drawv();
    }
}

void test_overload_and_poly()
{
    Shape s1("Shape1");
    Rectangle r1("Rectangle1", 1.0, 2.0);
    Square sq1("Square", 3.0);

    Shape *ptr = &s1;
    ptr->drawv();
    //多态可以调用父类的重载，不能调用子类的重载
    ptr->drawv("red");//ok
    //ptr->drawv("black", 1); //no instance ov overloaded function
}

void test_dynamiccast_poly()
{
    Rectangle r1("Rectangle", 2.0, 3.0);
    cout << r1.get_x() << endl;
    Shape *p = new Rectangle("Rectangle", 1.0, 2.0);
    //p->get_x(); //error:class Shape has no member get_x;
    Rectangle *pr = dynamic_cast<Rectangle*>(p);
    cout << pr->get_x() << endl;
}

void test_typeid()
{
    cout << "typeid(float) " << typeid(float).name() << endl;
    cout << "typeid(int) " << typeid(int).name() << endl;
    if (typeid(1) == typeid(int)) {
        cout << "1 is int" << endl;
    } else {
        cout << "1 is not int" << endl;
    }

    Rectangle r1("Rect", 1.0, 2.0);
    Shape *p = &r1;
    Shape &ref = r1;
    cout << "typeid ptr:" << typeid(p).name() << endl; //Shape
    cout << "typeid ref:" << typeid(ref).name() << endl; //Rect
    cout << "typeid *ptr:" << typeid(*p).name() << endl; //Rect
}

int main() {
    //静态绑定的不足
    //test_static_bind();
    //test_dynamic_bind();

    //多态应用场景：函数，存储进collections
    //collections可以存储值类型（并不满足多态),存储指针(可多态),不可存储引用
    //test_poly_useage();
    //含virtual的类会比不含virtual的类大8bytes, 因为有虚表
    //override与final

    //多态可以调用父类的重载，不能调用子类的重载
    //test_overload_and_poly();
    //多态对象销毁时，只会调用父类的析构函数，将父类析构函数声明为virtual可以解决该问题

    //dynamic_cast和多态
    //多态对象的缺点：虽然可以动态地调用子类中的虚函数，但是却不能调用子类中的其它函数
    //通过dynamic_cast将父类指针转换成子类指针即可
    //test_dynamiccast_poly();
    //注:typeid是操作符，不是函数，它可以在运行时获知类型名称,typeid(变量).name()
    //test_typeid();
    //pure virtual and abstract class

    //接口式抽象类
    //c++中不存在interface关键字，但是可以模拟接口，一个只有pure virtual函数和没有成员变量的抽象类可以用来摸拟在其它OOP语言中的接口 
    std::cout << "------------Hello----------" << endl;
}