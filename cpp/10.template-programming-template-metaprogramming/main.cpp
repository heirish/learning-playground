#include "functiontemplate.hpp"
#include "functiontemplatespecialization.hpp"
#include "classtemplate.hpp"
#include "explicitinstantiation.hpp"
#include "temptempparam.hpp"

#include "metaproghelloworld.hpp"
#include "metafuncContainsType.hpp"
#include "metatypelist.hpp"
int main(int argc, char const *argv[])
{
    /* code */
    ////////////////////Basic Template programming////////////////
    //FUNCTION_TEMPLATE::do_test();
    //FUNCTION_TEMPLATE::vairadic_function_template();

    //functemp_specialization::do_test();
    //functemp_specialization::partial_specialization_delegate();

    //CLASS_TEMPLATE::do_test();
    //CLASS_TEMPLATE::CTAD_test();
    //CLASS_TEMPLATE::default_parameter_test();
    
    //TU::do_test();

    temp_temp_param::do_test(); 


    //////////////////Template Metaprogramming////////////////////
    //meta_hello::do_test();
    //meta_containstype::runtime_ex();
    //meta_containstype::do_test();
    //meta_typelist_lib::runtime_ex();
    //meta_typelist_lib::do_test();
    return 0;
}
