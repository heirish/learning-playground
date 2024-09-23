编译期多态
### Generic programming - Templates
https://www.youtube.com/watch?v=S2OFJe73fxA&list=PLvv0ScY6vfd8j-tlhYVPYgiIyXduu6m-L&index=71&ab_channel=MikeShah

https://www.bilibili.com/video/BV1et4y1u75A?p=6&vd_source=601dbc960255506eb5f6390166996d67
- avoid code copy&paste
- serve as a blueprint for the compiler to generate code for us.
- side effect: code bloat
- "function template" vs. "tempalte function".
  - The term "function template" refers to a kind of template. The term "template function" is sometimes used to mean the same thing, and sometimes to mean a function instantiated from a function template. 
  - This ambiguity is best avoided by using "function template" for the former and something like "function template instance" or "instance of a function template" for the latter. 
  - Note that a function template is not a function. 
  - The same distinction applies to "class template" versus "template class".
### function template
-  `template <typename T> T max(T, T);`
- 可以从参数自动推导出T的data type, 所以可以不用加<>指定参数类型
- 可以为类的构造函数和普通成员函数创建function template, 但不能为虚函数和析构函数创建
- function template Specialization
  - 可以提供一个具体化(特化)的函数定义，当编译器找到与函数调用匹配的具体化定义时，将使用该定义，不再寻找模板.`template<> func(params)`, 这样可以为特定类型的数据定义特定类型的逻辑。
  - 函数匹配顺序:普通函数>特化函数模板>普通函数模板
  - partial specialization
- 函数模板一般放在头文件中，函数模板只是函数的描述，并没有实体
  - 函数模板的特化有实体，编译的原理的普通函数一样，所以，声明放在头文件，定义放在源文件
       ```
       .h
       template <typename T>
       T max(T a, T b) {return (a>b)?a:b}
       template<> 
       DogI& max(DogI d1, DogI d2);

       .cpp
       template<>
       DogI& max(DogI d1, DogI d2) {
         return d1.age > d2.age ? d1: d2;
       }
       ```
- template parameters
    - can have more than one parameters, `template <typename T>`, `template <typename T1, typename T2>`
    - non object-type parameters, `template <typename T, std::size_t N> struct array;`
    - can have non parameters, template full specialization:`template <>`
- Variadic function templates, since c++11
  - C, variadic functions:`int printf(const char* fmt, ...)`
- abbreviated function templates (since c++20): `auto square2(auto input) {return input*input;}`
### class template
- 声明时在class前加上`template <typename T>`
- 如果成员函数是在class声明外写函数体，函数体前面也要加上 `template <typename T>`, 并且类名也要加上`<T>`
  ```
  template <typename T>
  class Obj{
  public:
      void print() const;
  }
  template <typename T>
  void Obj<T>::print() const{}
  ```
- 成员函数还可以是另一个个数据类型的template function.`template <typename U>`