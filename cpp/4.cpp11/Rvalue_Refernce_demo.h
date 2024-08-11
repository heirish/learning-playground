#ifndef RVALUEF_DEMO
#define RVALUEF_DEMO
#include <iostream>

namespace RVALUE_DEMO {
void printInt(int& i); 
void printInt(int&& i);
class MyVector final {
    public:
        explicit MyVector(int size, double init_value = 0.0):_size(size), _arr(nullptr) {
            if (size > 0) {
                _arr = new double[_size];
                for(int i=0; i<_size; i++) {
                    _arr[i] = init_value;
                }
            }
            std::cout << "MyVector()" << std::endl;            
        }
        MyVector(const MyVector& rhs) { //copy constructor
            std::cout << "copy constructor" << std::endl;            
            if (this == &rhs) return;
            _size = rhs._size;
            _arr = new double[_size];
            for(int i=0;i<_size;i++) {
                _arr[i] = rhs._arr[i];
            }
        }
        MyVector(MyVector&& rhs) { //copy constructor
            std::cout << "move constructor" << std::endl;
            _size = rhs._size;
            _arr = rhs._arr;

            //important:clear rhs
            rhs._size = 0;
            rhs._arr = nullptr; 
        }
        MyVector& operator=(const MyVector&) = delete;
        MyVector& operator=(MyVector&&) = delete;

        ~MyVector() {
            std::cout << "~MyVector" << std::endl;
            if(_arr) {
                delete _arr;
                _arr = nullptr;
            }
        }

        void print() {
            if (_size <=0) {
                std::cout << "empty object";
            }
            for(int i=0; i<_size; i++) {
                std::cout << _arr[i] << " ";
            }
            std::cout << std::endl;
        }
    private:
        int _size;
        double* _arr; //a big array
};
void foo(MyVector v);
MyVector createMyVector();
void do_move_semantic_test();
void do_perfect_forwarding_test();
}
#endif //RVALUEF_DEMO