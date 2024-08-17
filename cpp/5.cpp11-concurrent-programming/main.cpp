#include <thread>
#include <iostream> 
#include "LazyInit.hpp"

void function_1() {
    std::cout << "Beauty is only skin-deep" << std::endl;
}
void join_with_without_exc() {
    std::thread t1(function_1);

    //solution1: try...catch
    try {
        for(int i=0; i<100; i++) {
            std::cout << "from test:" << i << std::endl;
        }
    } catch(...) {
        t1.join();
        throw;
    }
    t1.join();

    //solution2: using RAII
    //Wrapper w(t1);
}

class Fctor {
public:
    void operator()(std::string& msg) {
        std::cout << "t1 says:" << msg << std::endl;
        msg = "Trust is the mother of deceit.";
    }
};
void thread_parameter_test() {
    {
        std::string s="Where there is no trust, there is no love";
        Fctor f1;
        f1(s);
        std::thread t1(f1,std::ref(s));
        t1.join();
        std::cout << "from main:" << s << std::endl;
    }

}



int main(int argc, char const *argv[])
{
    /* code */
    //oversubscription
    //do not create number of threads more that the number of cores. context swith
    //indication of how many thread can be truly running concurrently for my program
    std::cout << "do not create more than " << std::thread::hardware_concurrency() << " thread" << std::endl;
    //join_with_without_exc();
    //thread_parameter_test();
    
    LAZY_INIT::test_lazy_intialization();
    return 0;
}
