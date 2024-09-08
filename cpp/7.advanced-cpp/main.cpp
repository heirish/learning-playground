#include "constness.hpp"
#include "default_genrated_funcs.hpp"
#include "destructor.hpp"

int main(int argc, char const *argv[])
{
    /* code */
    //CONST_TEST::const_variable_test();
    //CONST_TEST::const_function_test();
    //CONST_TEST::logic_vs_bitwise_constness_test();

    //DEFAULT_GEN::generated_func_test();

    //DESTRUCTOR_TEST::virtual_destructor_test();
    DESTRUCTOR_TEST::exception_destructor_test();
    return 0;
}
