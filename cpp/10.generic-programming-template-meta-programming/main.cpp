#include "functiontemplate.hpp"
#include "classtemplate.hpp"
int main(int argc, char const *argv[])
{
    /* code */
    FUNCTION_TEMPLATE::do_test();
    FUNCTION_TEMPLATE::vairadic_function_template();

    CLASS_TEMPLATE::do_test();
    return 0;
}
