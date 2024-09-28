#include "explicitinstantiation.hpp"
namespace TU {
void do_test() {
    char ascii_buffer[] = "Hello World";
    std::cout << sizeof(ascii_buffer) << std::endl; 
    reverse<ascii>(ascii_buffer, sizeof(ascii_buffer)-1);
    std::cout << ascii_buffer << std::endl;

    char charset4_buffer[] = "abcd1234efgh4567";
    std::cout << sizeof(charset4_buffer) << std::endl; 
    reverse<charset4>(charset4_buffer, sizeof(charset4_buffer)-1);
    for(int c:charset4_buffer) {
        std::cout << std::hex << c << " ";
    }
    std::cout << std::endl;
    std::cout << charset4_buffer << std::endl;

    char unknown_buffer[] = "awefx";
    //mblen的primary template在explicitinstaniation.hpp中有，所以以下可以deduce出来
    std::cout << std::dec << mblen<void>(unknown_buffer, sizeof(unknown_buffer)) << std::endl;
    //reverse在explicitinstantiation.hpp中没有primary template的定义。
    //因此reverse<void>并不能被deduce出来，所有下面这一行会报错
    //reverse<void>(unknown_buffer, sizeof(unknown_buffer)); //comile error: undefined reference to TU::reverse<void>()
}
}