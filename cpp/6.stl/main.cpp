#include <iostream>
#include "Containers.hpp"
#include "Iterators.hpp"
#include "Algorithms.hpp"
#include "Functors.hpp"
#include "AlgorithmsWT.hpp"
#include "StringTest.hpp"
#include "StreamTest.hpp"
#include "AdvancedSTL.hpp"

int main(int argc, char const *argv[])
{
    /* code */
    //sequence containers
    //BASIC_STL_CONTAINERS::vector_test();
    //BASIC_STL_CONTAINERS::deque_test();
    //BASIC_STL_CONTAINERS::list_test();
    //BASIC_STL_CONTAINERS::forward_list_test();
    //BASIC_STL_CONTAINERS::array_test();
    
    //associate containers
    //BASIC_STL_CONTAINERS::set_test();
    //BASIC_STL_CONTAINERS::map_test();

    //unordered containers
    //BASIC_STL_CONTAINERS::unordered_test();
    //BASIC_STL_CONTAINERS::unordered_test1();

    //BASIC_STL_ITERATORS::const_iterator_test();
    //BASIC_STL_ITERATORS::insert_iterator_test();
    //BASIC_STL_ITERATORS::stream_iterator_test();
    //BASIC_STL_ITERATORS::reverse_iterator_test();
    //BASIC_STL_ITERATORS::move_iterator_test();
    
    //BASIC_STL_ALGORITHM::basic_test();

    //BASIC_STL_FUNCTORS::do_test();
    //BASIC_STL_FUNCTORS::build_in_functors_test();
    //BASIC_STL_FUNCTORS::parameter_binding_test();
    //BASIC_STL_FUNCTORS::convert_function_to_functor_test();
    //BASIC_STL_FUNCTORS::fancy_complex_usage();
    

    //algorithms walkthrough
    //ALGORITHM_TEST::none_modifying_algs_test();
    //ALGORITHM_TEST::modifying_algs_test();
    //ALGORITHM_TEST::modifying_order_changing_algs_test();
    //ALGORITHM_TEST::sorting_algs_test();
    //ALGORITHM_TEST::sorted_data_algs_test();
    //ALGORITHM_TEST::numeric_algs_test();
    
    //STRING_TEST::string_ctor_size();
    //STRING_TEST::character_access();
    //STRING_TEST::member_fn_algs();
    //STRING_TEST::non_member_fns();
    //STRING_TEST::string_and_algs();
    
    //STREAM_TEST::iostream_test();
    //STREAM_TEST::ftream_test();
    //STREAM_TEST::iofromatting_test();
    //STREAM_TEST::manipulators_test();
    //STREAM_TEST::streambuffer_test();
    //STREAM_TEST::stringstream_test();
    //STREAM_TEST::streamenabled_class_test();
    
    ADVANCED_STL::performance_compare();
    return 0;
}
