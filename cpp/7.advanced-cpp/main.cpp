#include "constness.hpp"
#include "default_genrated_funcs.hpp"
#include "destructor.hpp"
#include "selfassignment.hpp"
#include "static_init_fiasco.hpp"
#include  "typeconversion.hpp"
#include "inheritance.hpp"

int main(int argc, char const *argv[])
{
    /* code */
    //CONST_TEST::const_variable_test();
    //CONST_TEST::const_function_test();
    //CONST_TEST::logic_vs_bitwise_constness_test();

    //DEFAULT_GEN::generated_func_test();

    //DESTRUCTOR_TEST::virtual_destructor_test();
    //DESTRUCTOR_TEST::exception_destructor_test();
    //DESTRUCTOR_TEST::call_virtual_in_cons_destructor_test();
    
    //SELF_ASSIGNMENT::handle_self_assignment_test();

    //STATIC_INIT_FIASCO::do_test();

    //TYPE_CONVERSION::implicit_type_conversion_test();
    //TYPE_CONVERSION::casting_test();
    //TYPE_CONVERSION::casting_test2();
    
    //INHERITANCE::do_test();
    INHERITANCE::is_a_test();
    return 0;
}
