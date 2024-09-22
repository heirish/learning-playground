#ifndef __TEMPLATE_CLASS__
#define __TEMPLATE_CLASS__
#include <iostream>
namespace CLASS_TEMPLATE{

//below is a template class
template <typename T>
class MyVector{
public:
    MyVector() = default;
    void push(T x) {_arr[_size] = x; _size++;}
    void print() const {
        for(int i=0; i<_size; i++) {
            std::cout << _arr[i] << ",";
        }
        std::cout << std::endl;
    }

    T get(int i) const;
    std::size_t getSize() const;

    template <typename U>
    T getbyU(U u) const;
private:
    T _arr[1000];
    std::size_t _size{0};
};

template <typename T>
MyVector<T> operator*(const MyVector<T>& lhs, const MyVector<T>& rhs) {
    MyVector<T> ret;
    for(int i=0; i<std::min(lhs.getSize(), rhs.getSize()); i++) {
        ret.push(lhs.get(i) * rhs.get(i));
    }
    return ret;
}

template <typename T>
T MyVector<T>::get(int i) const {
    return _arr[i];
}
template <typename T>
std::size_t MyVector<T>::getSize() const {
    return _size;
}

template <typename T>
template <typename U>
T MyVector<T>::getbyU(U u) const {
    return _arr[0];
}


template<typename T>
T square(T t) {
    return t*t;
}
void do_test() {
    MyVector<int> v;
    v.push(2);    
    v.push(5);    
    v.push(8);    
    v.push(9);    
    v.push(4); 
    v.print();   

    v = square(v);
    v.print();
}
}
#endif //__TEMPLATE_CLASS__