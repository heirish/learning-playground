#ifndef ENUM_CLASS_DEMO
#define ENUM_CLASS_DEMO
#include <iostream>

namespace ENUM_CLASS_DEMO {
    //before c++11, enum value is integer
    enum apple{green_a, read_a};
    enum orange{big_o, small_o};

    enum class Apple{green, red};
    enum class Orange{big, small};
    
    void do_enum_demo_test() {
        //before c++11
        apple a = apple::green_a;
        orange o = orange::big_o;
        if (a == o) {
            std::cout << "before c++11, green apple is the same as big orange." << std::endl;
        } else {
            std::cout << "before c++11, green apple is NOT the same as big orange." << std::endl;
        }

        //c++11
        Apple aa = Apple::green;
        Orange oo = Orange::big;
        //if (aa == oo) { //compile error:
        //    std::cout << "in c++11, green apple is the same as big orange." << std::endl;
        //} else {
        //    std::cout << "in c++11, green apple is NOT the same as big orange." << std::endl;
        //}
    }
}


#endif //ENUM_CLASS_DEMO
