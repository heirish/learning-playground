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
 - user defined literals: <return> operator"" <suffix>(<parameters>);
   - it can only work with following parameters:
      ```
      char const *
      unsigned long long
      long double
      char const*, std::size_t
      wchar_t const*, std::_size_t
      char16_t const*, std::size_t
      char32_t const*, std::size_t
      ```
      return value can be be any types
  - suffix must start with underscore `_`
- 标准库提供的字面量都不带下划线"_"
### lambda function
- 函数式编程范式
### Rvalue Reference
- https://www.youtube.com/watch?v=UTUdhjzws5g&t=4s&ab_channel=BoQian

- https://www.youtube.com/watch?v=0xcCNnWEMgs

- lvalue, rvalue
  - lvalue:An object that occupies some identifiable location in memory
  
  - rvalue:Any object that is not a lvalue
  
    ```
    //Lvalues examples
    int i;  //i is a lvalue
    int* p = &i; //i's address is identifiable
    i = 2; //memory content is modified
    
    class dog;
    dog d1; //lvalue of user defined type(class),
    		//most variables in c++ code are lvalues
    		
    
    //Rvalue examples
    int x = 2; //2 is an rvalue
    int x = i+2; //(i+2) is an rvalue <---lvalue can be used to create a rvalue
    int* p = &(i+2); //Error, can not get (i+2)'s address
    i+2 = 4; //Error, can not assign value to 
    2 = i; //Error, an not assign value to 
    
    dog d1;
    d1 = dog();  //dog() is rvlaue of user defined type(class)
    
    int sum(int x, int y) {return x+y;}
    int i = sum(3,4); //sum(3,4) is rvalue
    
    
    //Rvalues: 2, i+2, dog(), sum(3,4), x+y
    //Lvalues: x, i, d1, p
    
    int i = 1;
    int x = i+2; //(i+2) is a rvalue <---lvalue can be used to create a rvalue
    int x = i; //i itself is a lvalue, but in this context, it's a rvalue.lvalue can be implicitly transformed to rvalue
    //but rvalue can not be implicily transformed to lvalue, rvalue should be explicitly used to create lvalue
    //rvalue can be used to create a lvalue
    int v[3];
    *(v+2) = 4; //(v+2) is rvalue, *(v+2) is lvalue
    ```
    
  - misconceptions:
  
    ```
    //1.function or operator always yields rvalues
    int x = i+3; //i+3 is rvalue
    int y = sum(3,4); //sum(3,4) is rvalue
    
    int myglobal;
    int& foo() {return myglobal;}
    foo() = 50; 
    
    array[3] = 50;//operator [] almost always generates lvalue
    
    //2.lvalues are modifiable
    //C language:lvalues means "value suitable for left-hand-side of assignment" <---no long true in cpp
    const int c = 1; //c is lvalue
    c = 2; //Error, c is not modifiable
    
    //3.rvalues are not modifiable <---only true for the build-in types
    i+3 = 6;//error
    sum(3,4) = 7; //error
    //It is not true for user defined type(class)
    class dog;
    dog().bark(); //bark() may change the state of the dog object
    ```
    
  - summary:
  
    - every c++ expression yield either a rvalue or a lvalue
    - if the expression has an identifiable memory address, it's lvalue; otherwise, rvalue
  
- reference

  ```
  //reference (or lvalue reference)
  int i;
  int& r = i;
  int& = 5; //Error
  //exception:constant lvalue reference can be assigned a rvalue.
  const int& = 5; //ok
  
  int square(int& x) {return x*x;}
  square(i); //ok
  square(50); //error
  //workaround:
  int square(const int& x) {return x*x;} //square(i) and square(50) will work
  ```
  
- moving semantics

- perfect forwarding:rvalue is forwarded as rvalue, lvalue is forwarded as lvalue.

- Reference Collapsing Rules(c++11)
  
  - A& & => A&
  
  - A& && => A&
  - A&& & => A&
  - A&& && => A&&
  
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
  
     ```
     //type deduction is involved = Forward reference
     //forward reference: accpet both lvalue and rvalue references
     //makes use of "reference collapsing" to "perserve" value category.
     template<typename A, typename B, typename C>
     void foo(A&& a, B&& b, C&& c){bar(a,b,c,true,42);}
     
     //typde deduction is not involved = Rvalue reference
     void foo(int&& a, int&& b, int&& c){bar(a,b,c,true,42);}
     ```
  
- std::move vs std::forward
  - std::move<T>(arg); //Turn arg into rvalue type
  
  - std::forward<T>(arg); //Turn arg to type of T&&
  
    ```
    //std::forward(conteptually)
    template<typename T>
    T&& std:forward(T&& param) {
    	if (is_lvalue_reference<T>::value>) {  //if T indicates lvalue
    		return param;					   //do nothing
    	} else {							   //else
    		return std::move(param);		   //cast to rvalue
    	}
    }
    
    //std::forward == conditional cast
    //Returns T& or T&&(reference collapsing!)
    ```

### Compiler Generated Functions
- C++03
   ```
   1.default constructor(generated only if no constructor is declared by user)
   2.copy constructor(generated only if no 5,6 declared by user)(c++11: 3,4,5,6)
   3.copy assignment operator(generated only if no 5,6 declared by user) (c++11: 2,4,5,6)
   4.destructor
   ```
   
   in c++11: if 3,4 is declared, then the generation rule of 2 is deprecated, if 2,4 is declared,  the generation rule of 3 is deprecated.
   
- C++11
  
  ```
   5.move constructor(generated only if 2,3,4,6 not declared by user)
   6.move assignment operator(generated only if 2,3,4,5 not declared by user)
  ```
  
- class Dog{}; is equivalent to something like below
  ```
  class Dog {
    //c++03
    Dog();
    Dog(const Dog&);
    Dog& operator=(const Dog&);
    ~Dog();
  
    //c++11
    Dog(Dog&&);
    Dog& operator=(Dog&&);
  };
  ```
  
- Test
  ```
  class Cat {//3,4 will be generated (3 is deprecated)
    Cat(const Cat&){} //copy constructor < - user defined constructor
  };
  class Duck { //4
    Duck(Duck&&) {} //move constructor
  };
  class Frog { //4
    Frog(Frog&&, int=0) {} //move constructor
    Frog(int=0){} //default constructor
    Frog(const Frog&, int=0) {} //copy constructor
  };
  class Fish{ //1,2,3(c++11:2,3 are deprecated)
    ~Fish(){}
  };
  class Cow { //1,2,4 (c++11: 2 is deprecated)
    Cow& operator=(const Cow&) = delete;  //delete statement is still counted as delcared by user
  };
  ```
### smart_ptr
- An object should be assigned to a smart pointer as soon as it is created,  Raw pointer should not be used again. `std::make_shared, std::make_unique`
- shared_ptr:std::make_shared
- weak_ptr:resolve cyclic reference.
  - weak_ptr has no ownershipo of the pointed object.
  - I only want to access that object, when and how that object will be delete is none of my business.
  - weak_pointer is similar to raw pointer, but it also provide one level protection that object an not be deleted through weak_ptr
  - weak_pointer also provide safe access to the pointer.weak_ptr is not always valid,
   before you use it, you need to call .lock() to create a shared_ptr from it.
- unique_ptr: exclusive ownership, light weighted smart pointer
  - unique_ptr.release() give up the ownership, while shared_ptr.get() doesn't give up the ownership
### integer_sequence
```
template<typename T, T...Ints>
struct integer_sequence;
```
实际就是一个整型数列的metafunction wrapper,主要用于template programming
用得多的是其alias: index_sequence及其helper函数
template<std::size_t... Ints>
using index_sequence = std::integer_sequence<std::size_t, Ints...>;
template<std::size_t N>
using make_index_sequence = std::make_integer_sequence<std::size_t, N>; //自动生成从0~N-1的sequence
### Regex