#include "advancedmetatuplefilter.hpp"
#include "classtemplate.hpp"
#include "explicitinstantiation.hpp"
#include "functiontemplate.hpp"
#include "functiontemplatespecialization.hpp"
#include "temptempparam.hpp"
#include "typededuction.hpp"

#include "metafuncContainsType.hpp"
#include "metaproghelloworld.hpp"
#include "metatypelist.hpp"

#include "advancedmetatuple.hpp"
#include "advancedmetatuplecat.hpp"
#include "advancedmetatuplefilter.hpp"
#include "advancedmetatupletransform.hpp"

int main(int argc, char const *argv[]) {
    /* code */
    ////////////////////Basic Template programming////////////////
    type_deduction::do_test();
    // FUNCTION_TEMPLATE::do_test();
    // FUNCTION_TEMPLATE::vairadic_function_template();

    // functemp_specialization::do_test();
    // functemp_specialization::partial_specialization_delegate();

    // CLASS_TEMPLATE::do_test();
    // CLASS_TEMPLATE::CTAD_test();
    // CLASS_TEMPLATE::default_parameter_test();

    // TU::do_test();

    // temp_temp_param::do_test();

    //////////////////Template Metaprogramming////////////////////
    // meta_hello::do_test();
    // meta_containstype::runtime_ex();
    // meta_containstype::do_test();
    // meta_typelist_lib::runtime_ex();
    // meta_typelist_lib::do_test();

    ////////////////Advances template metaprogramming////////////////////
    adv_meta_programming::do_tuple_test();
    adv_meta_programming::do_tuple_cat_test();
    adv_meta_programming::test_framwork_use();
    adv_meta_programming::do_tuple_transform_test();
    adv_meta_programming::do_tuple_filter_test();
    return 0;
}
