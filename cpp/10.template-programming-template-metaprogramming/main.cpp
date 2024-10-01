#include "functiontemplate.hpp"
#include "functiontemplatespecialization.hpp"
#include "classtemplate.hpp"
#include "explicitinstantiation.hpp"

#include "metaproghelloworld.hpp"
int main(int argc, char const *argv[])
{
    /* code */
    //FUNCTION_TEMPLATE::do_test();
    //FUNCTION_TEMPLATE::vairadic_function_template();

    //functemp_specialization::do_test();
    //functemp_specialization::partial_specialization_delegate();

    //CLASS_TEMPLATE::do_test();
    //CLASS_TEMPLATE::CTAD_test();
    //CLASS_TEMPLATE::default_parameter_test();
    
    //TU::do_test();
    
    meta_hello::do_test();
    return 0;
}
