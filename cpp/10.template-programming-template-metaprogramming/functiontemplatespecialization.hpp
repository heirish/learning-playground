#ifndef __FUNCTION_TEMPLATE_SPECIALIZATION__
#define __FUNCTION_TEMPLATE_SPECIALIZATION__
#include <iostream>
namespace functemp_specialization{
template<typename T>
void foo1(T t) {
    std::cout << "primary template:" << __PRETTY_FUNCTION__ << std::endl;
}
template <>
void foo1<void*>(void*) {
    std::cout << "full specialization:" << __PRETTY_FUNCTION__ << std::endl;
}
template <typename Tp>
void foo1(Tp* ) { //这个不是partial specialization, 是另一个primary template
    std::cout << "another primary template:" << __PRETTY_FUNCTION__ << std::endl;
}

/*comile error:
template <typename Tp>
void foo1<Tp*>(Tp*) {
    std::cout << "partial specialization is not supported for function template, compiler error." << std::endl;
}
*/

void do_test() {
    void* ptr = nullptr;
    foo1(ptr); 
    //定义template<typename Tp> void foo1之前: 调的是template<typename T>的全特化, 输出full psecialization
    //定义template<typename Tp> void foo1之后: 调的是template<typename Tp>生成的函数, 输出another primary template

}

template <typename T>
struct is_pointer_impl { static bool _() {return false;}};
template <typename Tp>
struct is_pointer_impl<Tp*>{static bool _() {return true;}};
template <>
struct is_pointer_impl<std::nullptr_t>{static bool _() {return true;}};
template <typename T>
bool is_pointer(T  x) {
    return is_pointer_impl<T>::_();
}
//function template本身不支持partial specialization,
//但是可以通过将处理delegate到class来达到类似的效果
void partial_specialization_delegate() {
    //function template can not be partial specialized, 
    //if you need partial specialization.
    //then you should delegate all the work to a class template, which can be partially specialized
    //non object-type template parameter
    int* p;
    std::cout << "is_pointer(p)" << is_pointer(p) << std::endl; //1
    std::cout << "is_pointer(nullptr)" << is_pointer(nullptr) << std::endl; //1, 调的是全特化的is_pointer_impl<std::nullptr_t>
    std::cout << "is_pointer(NULL)" << is_pointer(NULL) << std::endl; //0
}
}
#endif //__FUNCTION_TEMPLATE_SPECIALIZATION__