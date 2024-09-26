#ifndef __TEMPLATE_CLASS__
#define __TEMPLATE_CLASS__
#include <iostream>
#include <typeinfo>
namespace CLASS_TEMPLATE{

template <typename T>
class MyVector{
public:
    MyVector() = default;
    void push(T x) {_arr[_size] = x; ++_size;++_variable;}
    void print() const {
        for(int i=0; i<_size; i++) {
            std::cout << _arr[i] << ",";
        }
        std::cout << std::endl;
        std::cout << "_variable:" << _variable << std::endl;
    }

    T get(int i) const;
    std::size_t getSize() const;

    template <typename U>
    T getbyU(U u) const;
private:
    T _arr[1000];
    std::size_t _size{0};
    //static data member declare
    static T _variable;
};
//static data member definition
template <typename T> 
T MyVector<T>::_variable = T();

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

template<typename first, typename second>
struct Entry {
    Entry(first key, second value):_key(key), _value(value) {
    }
    first _key;
    second  _value;
};

void CTAD_test() {
    Entry entry(5,100.0f); //no need to provide the template argument, compiler will deduce it directly to Entry<int,float>
    //if compiler deuction failed, you can provide the template argument specificlly
    std::cout << typeid(entry._key).name() << std::endl; //i
    std::cout << typeid(entry._value).name() << std::endl; //f
}

template<typename T=int, std::size_t N=10>
class Container {
public:
    Container(){_data = new T[N];}
    ~Container(){delete[] _data;}
    Container(const Container<T>&) = delete;
    Container& operator=(const Container<T>&) = delete;
    void print() {
        std::cout << N << " items of type:" << typeid(T).name()<<std::endl;
    }
private:
    T* _data{nullptr};
};
void default_parameter_test() {
    Container c1;
    Container<float> c2;
    c1.print();
    c2.print();
}
}
#endif //__TEMPLATE_CLASS__