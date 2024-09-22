#include <iostream>
#include "VariableTemplate.hpp" 
#include "Lambdas.hpp"
#include "digitalSeparator.hpp"
#include "autodeduction.hpp"
#include "literals.hpp"
#include "constexpr.hpp"

[[deprecated("deprecated, using fnv2 instead")]]
void deprecated_fn_test() {
    std::cout << "old fn" << std::endl;
}

int main(int argc, char* argv[]) {
    std::cout << "Hello cpp14" << std::endl;
    //VAR_TEMPLATE::do_test();
    Integer_Literal::do_test();
    //LAMBDA::generic_lambda_test();
    //LAMBDA::lambda_init_capture_test();
    //AUTO_DEDUCTION::autovartype_test();
    //AUTO_DEDUCTION::autoreturntype_test();
    //AUTO_DEDUCTION::autoreturntype_test1();
    //LITERALS::do_test();
    LITERALS::selfdef_literal_test();
    //deprecated_fn_test();

    //CONSTEXPR::do_test();
    //TODO: shared_lock

    return 0;
}