#include <iostream>
#include "Containers.hpp"
#include "Iterators.hpp"
#include "Algorithms.hpp"

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
    
    BASIC_STL_ALGORITHM::basic_test();
    return 0;
}
