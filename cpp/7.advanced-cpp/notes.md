### const
- A **compile time constraint** that an object can not be modified
- why use const
  - guard against inadvertent write to the variable
  - self documenting
  - enable compiler to do more optimization, making code tighter
  - const means the variable can be put in ROM
### compiler generated functions
//这个是c++11以前的，在c++11中的新feature可以查看4.cpp11中的notes.md

- compiler silently writes 4 functions if they are not explicitly declared
    - default constructor(only if there is no constructor declared)
    - copy constructor
    - copy assignment operator
    - destructor
    ```
    class dog{};
    //equivalent to 
    class dog {
    public:
        dog() {...} // 1.call base class's defaut constructor
                    //2. call data member's default constructor
        dog(const dog&){...} //member by member initialization
        dog& operator=(const dog&){...} //member by member copying
        ~dog(){...} //1.call data member's destructor.
                    //2.call base class's destructor
    };
    ```
- if base class/member variable's class don't meet the requirements, then the default function would not be generated either.for example, if base class don't have default construct, then default construct will not be generated for this class because there's no way to do default constructor's job;
- all generated functions are public and line
- all generated functions are generated **only** if they are needed.
- c++11中，可以通过=default来显式让compiler生成default function,例如，自定义了带参数的constructor, compiler就不会自动生成默认的无参数的default constructor, 可以通过default显式生成。
- comipler generated functions are not alawys useful, sometime they're dangerous,
  how to prevent compiler generate those functions:before c++11, delcare it as private with out function body. from c++11, use `=delete`
- summary of disallowing functions
  - c++11: f() = delete;
  - c++03: Declare the function to be private, and not define it.
  - private destructor: stay out of stack
    ```
    //force Dog can only be created to stack, useful for limited stack size such as embedded programming
    class Dog {
    public:
        void destroyMe() {delete this;}
    private:
        ~Dog();
    };

    void dog_test {
        Dog* p = new Dog;
        p->destroyMe();
    }
    ```
### Virtual Destructor and Smart Destructor
- 带virtual function的base class都需要将destructor声明为virtual
- 当class object作为shared_ptr的polymorphic使用时，可以不用声明为virtual
- All classes in STL have no virtual destructor, so be careful inheiriting from them. if you have to do that, use share_ptr to use that object as much as possible.
### Preventing Exceptions from Leaving Destructors
Solutions
- Solution 1: Destructor swallow the exception
  ```
  ~dog() {
    try {
        //enclose all the exception prone code here
    } catch (MYEXCEPTION e) { //catch exception
    } catch (...) { //be careful of this
    }
  }
  ```
- Solution 2:move the exception-prone code to a different function, leave the destructor expcetion-free.
  ```
  ~dog{} {std::cout << "destroyed" << std::endl; throw 20;}

  //TO

  ~dog() {std::cout << "destroyed" << std::endl;}
  void prepareToDestruct() {//do somthing that might throw exception}
  //when use, call prepareToDestruct() before it get destroyed.

  ```