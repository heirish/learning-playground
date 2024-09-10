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
### Calling Virtual Function in Constructor or Destructor
- DO NOT call any virtual function in constructor or destructor
### Assignment to Self in Assignment Operator
### RAII:Resource acquisition is initialization
use objects to manager resources:memory, hardware device, network handle, etc.
- Conclusion: 
  - the only code that can be guaranteed to be executed after exception is thrown are the destructor of objects residing on the stack.
  - resource management therefore needs to be tied to the lifespan of suitable objects in order to gain automaic deallocation and reclamation.
- std::shared_ptr
  ```
  class dog;
  class Trick
  void train(std::shared_ptr<dog> pd, Trick dogtrick);
  Trick getTrick();

  //Question: what's the problem with below line code
  train(std::shared_ptr<dog>(new dog()), getTrick());

  //what Happens in train()'s parameter passing:
  //1.new dog()
  //2.getTrick()
  //3.construct std::shared_ptr<dog>
  //the order of these operations are determined by compiler, if step2 throws an exception, step2 will not be executed. memory of step 1 will be leaked
  
  //conclusion: Don't combine storing objects in shared pointer wit other statements.
  //use std::make_shared instead
  //or
  std::shared_ptr<dog> pd(new dog());
  train(pd, getTrick());
  ````
- what happens when resource management object is copied?
  - solution 1: prohibit copying, disallow copy constructor and copy assignment operator from being used
  - solution 2:reference-count the underlying resource by using std::shared_ptr, `template <class Other, class D>shared_ptr(Other *ptr, D deleter);`, a deleter is a function that will be invoked when the shared pointer is destroyed, the default value for D is delete. deleter can be customized
    ```
    class Lock {
    public:
      explicit Lock(Mutex_t *pm):_pMutex(pm, Mutex_unlock){
        Mutex_lock(pm);
        //the second parameter of shared_ptr constructor is "deleter" function.
      }
    private:
      std::shared_ptr<Mutex_t> _pMutex;
    };
    {
      Lock L1(&mu);
      Lock L2(L1);
    } //mu will be unlocked here
    
    ```