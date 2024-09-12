#ifndef __TYPE_CONVERSION__
#define __TYPE_CONVERSION__
#include <iostream>
#include <string>

/*Categories of Type Conversion:
                                Implicit    Explicit
Standard Type Conversion        A           B
User Define Type Conversion     C           D
                                            (casting)
*/

namespace TYPE_CONVERSION {
void f(int i){}

 /*category C:Implicit User defined type conversion
 * 
 * Defined inside class (user defined type)
 * There are 2 methods to define implicit user defined type conversion:
 * 1. Use constructor that can accept a single parameter. - convert other types of object into your class
 * 2. Use the Type conversion function. - convert an object of your class into other types
 */
class dog{
public:
    dog() = default;
    //method 1
    dog(std::string name):_name(name){} //no explicit
    //If you only want to define a constructor, and no implicit type conversion.
    //always put 'explicit' before the constructor to avoid in advertent type conversion.   
    std::string getName() const {return _name;}
    //method 2
    operator std::string() const {
        std::cout << "type conversion function called" << std::endl;
        return _name;
    }

    virtual void bark(){std::cout<<"bark"<<std::endl;}
    virtual ~dog(){}
private:
    std::string _name;
};
/*implicit type conversion is useful when creating numerical types of class such as a rational class*/
class Rational {
public:
    int num; //demo only, public data members are not recommended
    int den;
    //works for r1
    Rational(int numerator = 0, int dennominator = 1)
    :num(numerator)
    ,den(dennominator)
    {}

    //const Rational operator*(const Rational& rhs) {
    //   return Rational(num*rhs.num, den*rhs.den);
    //}

    //type convert function, convert rational to int
    //operator int () const {return num/den;}
};
const Rational operator*(const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.num*rhs.num, lhs.den*lhs.den);
}
void implicit_type_conversion_test() {
    //Category A: Implicit standard type conversion
    char c = 'A';
    int i = c; //integral promotion
    char* pc = 0;//int -> null pointer
    f(c);

    //category C:Implicit User defined type conversion
    std::string dogname = "Bob";
    dog dog1 = dogname; //test method 1
    //std::cout << "my name is " << dog1.getName() << std::endl;
    std::string dog2 = dog1;
    std::cout << "my name is " << dog2 << std::endl; //test method 2

    Rational r1 = 23; 
    //if both operator*, and operator int are defined, below two lines will not compile, ambiguous problem
    //principle: don't define two-way(Rational<->int) implicit conversion.
    //Rational r2 = r1 * 2; 
    //Rational r3 = 3 * r1; 
    //solutin: define Rational operator * as global
    Rational r2 = r1 * 2; 
    Rational r3 = 3 * r1; 

}

class yellowdog:public dog {
};
void casting_test() {
    //static_cast
    int i = 9;
    float f = static_cast<float>(i); //convert object from one type to another
    dog d1 = static_cast<dog>(std::string("Bob")); //type conversion needs to be defined, method 1
    dog *pd = static_cast<dog*>(new yellowdog()); // convert pointer/reference from ont type to a related type(down/up cast)

    //dynamic_cast
    dog* pg = new yellowdog();
    yellowdog* py = dynamic_cast<yellowdog*>(pg);
    //a.it convert pointer/reference from one type to related type(down cast)
    //b.run-time type check. If succeed, py == pd, if fail, py == 0, (better solution for polymorphic class compare to static_cast)
    //c.It requires the 2 types to be polymorphic(have virtual function)

    //const_cast
    const char* str = "Hello";
    char* modifiable = const_cast<char*>(str);
    //only works on pointer/reference
    //only works on same type
    //cast away constness of the object being pointed to

    //reinterpret_cast
    long p = 0x51110980;
    dog* dd = reinterpret_cast<dog*>(p);
    //re-interpret the bits of the object pointed to
    //the ultimate cast that can cast one pointer to any other type of pointer

    //C-style casting
    short a = 2000;
    int l = (int)a; //c-like cast notaion
    int k = int(a); //functinal notation
    //A mixture of static_cast, const_cast and reinterpret_cast
}

class WhiteDog:public dog {
public:
    virtual void bark() override{
        std::cout << "Woof." << _age << std::endl;
    }
private:
    int _age;
};
void casting_test2() {
    dog* pd = new dog();
    //WhiteDog* pw = dynamic_cast<WhiteDog*>(pd); //pw == nullptr, cast fail, run-time check
    WhiteDog* pw = static_cast<WhiteDog*>(pd); //cast succeed without run-time check, pw is valid,but it will not work as WhiteDog as expected. so for class down cast, use dynamic_cast
    if (pw) {
        pw->bark(); 
    }
    std::cout << "pw = " << pw << std::endl;
    std::cout << "pd = " << pd << std::endl;
}
}
#endif //__TYPE_CONVERSION__