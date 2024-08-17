#include "LazyInit.hpp"

namespace LAZY_INIT{
void function_t1(LogFile& log) {
    for(int i=0; i<100; i++) {
        log.shared_print("t1", i);
    }
}
void test_lazy_intialization()
{
    std::cout << "test_lazy_init" << std::endl;
    LogFile log("log.txt");
    std::thread t1(function_t1, std::ref(log));

    for(int i=0; i>-100; i--) {
        log.shared_print("main", i);
    }
    if (t1.joinable()) {
        t1.join();
    }
}
}