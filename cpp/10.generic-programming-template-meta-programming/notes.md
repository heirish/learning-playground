编译器多态
### Generic programming - Templates
- side effect: code bloat
- template function: `template <typename T> T max(T, T);`
  - write one template function, let compiler do the code generation job.
  - 可以从参数自动推导出T的data type, 所以可以不用加<>指定参数类型
- template class
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