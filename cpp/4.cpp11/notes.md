### initializer_list
### auto
### range-based for loop
### nullptr
  - 可以解决参数为指针，int型的函数重载时的ambiguity问题
### enum class
  - 相比于之前的enum类型(只是一个int类型)，strongly typed enum, more safer
### static_assert
  ```
  //run-time assert
  assert(mypointer);
  //compile time assert (c++11)
  static_assert(sizeof(int) == 4);
  ```
### Delegating constructors
  ```
  //before c++11
  class A {
    public:
        A() {init();}
        A(int val) {
            init(); 
            otherThings(val);
        }
    private:
        void init();
  };
  //before c++11
  class A {
    public:
        A(){}
        A(int val) {
            A{};  
            otherThings(val);
        }
  };
  //c++11
  class A {
    public:
        A(){}
        A(int val):A() {otherThings(val);}
  }
  ```
- non-static member initialization
  ```
    class A {
    private:
        int _value{10};
    };
  ```
### override, final关键字
 - 在重写virtual函数时添加上这个关键字，防止因为typo error意外创建新的函数
 - final:for virtual function and for class, class:can not be derived, function: can not be override
### default, delete函数
 - default
  ```
  class dog {
    dog(int age){}
  };
  dog d; //compile error: compiler will not generate the default constructor

  //c++11, default
  class dog {
    dog(int age){}
    dog() = default; //For compiler to generate the default constructor
  }
  ```
 - big 3, big 5 
    ![](images/big3-big5.png)

 - 对于不想让编译器自动生成的函数，可以用delete限定符
### constexpr
 - force the computation to happen at compile time.
  ```
  //write faster program with constexpr
  constexpr int cubed(int x) { return x*x*x;}
  int y = cubed(1789);
  ```
### string literals
### lambda function
- 函数式编程范式
### Rvalue Reference
- https://www.youtube.com/watch?v=UTUdhjzws5g&t=4s&ab_channel=BoQian
- https://www.youtube.com/watch?v=0xcCNnWEMgs
- lvalue, rvalue
  - lvalue:An object that occupies some identifiable location in memory
  - rvalue:Any object that is not a lvalue
- moving semantics
- perfect forwarding:rvalue is forwarded as rvalue, lvalue is forwarded as lvalue.
- Reference Collapsing Rules(c++11)
  - T& & => T&
  - T& && => T&
  - T&& & => T&
  - T&& && => T&&
- template <typename T> struct remove_reference;   
  - it removes reference on type T
  - remove_reference<int&>::type i;  //int i
  - remove_reference<int>::type i: //int i;
- T&& is Universal Reference: rvalue, lvalue, const, non-const, etc.
  when 
  - T is a template type
  - Type deduction(reference collasping) happens to T
     - T is a function template type, not class template type.
  - int&& => rvalue, T&& => universal reference.
- std::move vs std::forward
  - std::move<T>(arg); //Turn arg into rvalue type
  - std::forward<T>(arg); //Turn arg to type of T&&