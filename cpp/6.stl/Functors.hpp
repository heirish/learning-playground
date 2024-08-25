#ifndef __FUNCTORS__
#define __FUNCTORS__
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <functional>
#include <cmath>

namespace BASIC_STL_FUNCTORS{
int add2(int i) {
    return i+2;
}
void add2ref(int& i) {
    i = i+2;
}
//more flexiable
//but still have problem: template varialbe is resolved at compile time
//, so it has to be compile time constant.
template <int N>
void addN(int& i) {
    i += N;
}

class AddN {
public:
    explicit AddN(int val):_val(val){}
    void operator()(int& x) {x += _val;}
private:
    int _val;
};

void do_test() {
    std::vector<int> vec{2,3,4,5};
    std::for_each(vec.begin(), vec.end(), add2); //not working
    std::for_each(vec.begin(), vec.end(), [](int item){std::cout << item << " ";});
    std::cout << std::endl;

    std::for_each(vec.begin(), vec.end(), add2ref); //working
    std::for_each(vec.begin(), vec.end(), [](int item){std::cout << item << " ";});
    std::cout << std::endl;

    std::for_each(vec.begin(), vec.end(), addN<3>);
    std::for_each(vec.begin(), vec.end(), [](int item){std::cout << item << " ";});
    std::cout << std::endl;

    //most flexiable solution
    //can add to runtime variable
    int x = 10;
    AddN addNf(x);
    std::for_each(vec.begin(), vec.end(), addNf); 
    std::for_each(vec.begin(), vec.end(), [](int item){std::cout << item << " ";});
    std::cout << std::endl;
} 

void build_in_functors_test() {
    int x = std::multiplies<int>()(3,4);
    if (std::not_equal_to<int>()(x,10)) {
        std::cout << x << std::endl;
    }
}

void parameter_binding_test() {
    std::set<int> myset{2,3,4,5};
    std::vector<int> vec;

    int x = std::multiplies<int>()(3,4);

    //multiply myset's elements by 10 and save in vec
    std::transform(myset.cbegin(), myset.cend(),  //source
        std::back_inserter(vec), //destination
        std::bind(std::multiplies<int>(), std::placeholders::_1, 10)); //functor
        //first parameter of multiplies<int>() is substituted with myset's element
    std::for_each(vec.begin(), vec.end(), [](int item) {std::cout << item << " ";});
    std::cout << std::endl;
}

double mypow(double x, double y) {
    return std::pow(x, y);
}
void convert_function_to_functor_test() {
    std::set<int> myset{2,3,4,5};
    std::deque<int> d;
    auto f = std::function<double (double, double)>(mypow);
    std::transform(myset.cbegin(), myset.cend(),
        std::back_inserter(d),
        std::bind(f, std::placeholders::_1, 2));
    std::for_each(d.begin(), d.end(), [](int item) {std::cout << item << " ";});
    std::cout << std::endl;
}

void fancy_complex_usage() {
    std::set<int> myset{2,3,4,5};
    std::deque<int> d;

    //copy from myset to d when (x>20||(x<5))
    //std::transform(myset.cbegin(), myset.cend(), 
    std::copy_if(myset.cbegin(), myset.cend(), 
        std::back_inserter(d),
        std::bind(
            std::logical_or<bool>(),
                std::bind(std::greater<int>(), std::placeholders::_1, 20),
                std::bind(std::less<int>(), std::placeholders::_1, 5)
        ));
    std::for_each(d.begin(), d.end(), [](int item) {std::cout << item << " ";});
    std::cout << std::endl;

    //above is too complex and not readable
    //simpler resolution
    std::copy_if(myset.cbegin(), myset.cend(), 
        std::back_inserter(d),
        [](int x)->bool{return x>20 || x <5;}
    );
    std::for_each(d.begin(), d.end(), [](int item) {std::cout << item << " ";});
    std::cout << std::endl;

}

}
#endif //__FUNCTORS__