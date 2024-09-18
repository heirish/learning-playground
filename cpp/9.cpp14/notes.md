## cpp14
https://www.youtube.com/watch?v=WZYKzCsACiw&ab_channel=VittorioRomeo
### std::make_unique
### variable templates:
 ```
 template <typename T>
 constexpr bool is_float = std::is_same<T, float>::value;
 ```
 - 变量模板也能全特化，偏特化
### generic lambdas: auto parameter
 ```
 auto f = [](auto x, auto y) {return x+y;};
 ```
### lambda init-capture: delcare new variable and init in lambda capture
 ```
 int x = 10;
 auto f = [y=2](int val) {return val + y;};
 f(x); //12
 ```
### binary literals: '0b', `int x= 0b0101;`
### digit separators: ',  `int x = 1000'000'000;`
 > Optional single quotes (') may be inserted between the digits as a separator; they are ignored when determining the value of the literal.
### decltype(auto): 
- 总结下来就是decltype可以保留references, cv_qualifiers, 但是在c++11中不能用decltype(auto), c++14支持了，其中的auto实际用的就是=右边的表达式
- 也可以只用auto声明变量，只不过reference, const属性会消失，需要手动加上
    ```
    const int x = 1;
    auto x2 = x; //int
    const auto x3 = 1; //const int
    ```
- c++11只能decltype变量名或表达式
    ```
    const int x = 1;
    dectype(x) x4 = x; //const int
    ```
- c++14, 添加decltype(auto)
    ```
    dectype(auto) x4 = x; //const int, dectype(auto) is equivalent to decltype(x), 也就是与decltype(等号右边的表达式)等效
    ```
- summary:
    - `auto` will always deduce a non-reference type.
    - `auto&&` will always deduce a reference type.
    - `decltype(auto)` deduces a non-reference or reference type depending upon the value category and the nature of a particular expression
### return type deduction for function: use 'auto' in return type
- use auto in return type without delctype()
  > in c++11, you need decltype(var) to tell the compiler about the return type
- use decltype(auto) in return type: 推导出的类型的与decltype(return statement);一样
  > If the return type is decltype(auto), the return type is as what would be obtained if the expression used in the return statement were wrapped in decltype:
### User-defined literals for string, duration, complex
    - string: `using namespace std::string_literals`
    - duration:`using namespace std::chrono_literals`
    - complex: `using namespace std::complex_literals`
### Aggregate Member initializers and aggregates
    ```
    struct Test {
        int x;
        int y{0};
    };
    
    Test t{ 5.5, 10 }; // c++11: compile Error
                       // c++14: Ok
    ```
### deprecated attribute
    ```
    //before c++14,using compiler extension, not portable
    #ifdef __GNUC__
    void foo( int )__attribute__ ((deprecated("Replaced by foov2")))
    #elif defined(_MSC_VER)
      __declspec(deprecated("Replaced by foov2")) void foo( int );
    #endif
    
    //c++14, using standard [[deprected]] attribute, protable
    [[deprecated]]
    void deprecated_fn_test();
     
    [[deprecated("deprecated, using fnv2 instead")]]
    void deprecated_fn_test();
    ```
### relaxed restrictions on constexpr functions
- Allows  `constexpr` functions to have multiple instructions and common language constructs such as branches and loops.
- C++14 has lifted most restrictions, except: try-block, asm-declaration, static variable, thread local storage, goto statement
    ```
    //c++11
    constexpr long foo(unsigned int i)
    { 
        return (i <= 1) ? i : (foo(i-1) + foo(i-2));
    }
    
    //c++14
    constexpr long foo(unsigned int i) {
        switch (i) {
         case 0: return 0;
         case 1: return 1;
         default: return foo(i-1) + foo(i-2);
        }
    }
    ```
### TODO: shared_lock