#ifndef __CONTAINS_TYPE__
#define __CONTAINS_TYPE__
#include <iostream>
#include <tuple>
#include <vector>

namespace meta_containstype {

bool contains(const std::string& search, const std::vector<std::string>& vec, std::size_t start_from=0) {
    if (start_from >= vec.size()) {
        return false;
    } else if (vec[start_from] == search) {
        return true;
    } else {
        return contains(search, vec, start_from+1);
    }
}
//no std::Find, no loop.
//so that we can translate it to compiler time version easily
void runtime_ex() {
    std::vector<std::string> vec{"int", "bool", "float"};
    std::cout << "contains(\"bool\", vec) = " << std::boolalpha << contains("bool", vec) << std::endl;
    std::cout << "contains(\"double\", vec) = " << std::boolalpha << contains("double", vec) << std::endl;
}

template<bool condition, typename THEN, typename ELSE>
struct if_;
template<typename THEN, typename ELSE>
struct if_<true, THEN, ELSE> {
    using type = THEN;
};
template <typename THEN, typename ELSE>
struct if_<false, THEN, ELSE> {
    using type = ELSE;
};

template <typename SEARCH, typename TUPLE, std::size_t start_from=0>
struct contains_type:
    if_< //这里不需要加typename关键字是因为template默认的继承的类型即为type
        (start_from < std::tuple_size<TUPLE>::value), //IF, here I do not use start_from >= std::tuple_size<TUPLE>::size,  because it will also reqire ELSE clousure which will caust tuple_element_t index overflow
        typename if_< //THEN
            std::is_same<SEARCH, typename std::tuple_element_t<start_from, TUPLE>>::value, //IF
            std::true_type, //THEN
            typename if_< //ELSE
                (start_from == std::tuple_size<TUPLE>::value-1), //IF check start_from index again
                std::false_type, //THEN
                contains_type<SEARCH, TUPLE, start_from+1>  //ELSE
            >::type
        >::type,
        std::false_type //ELSE
    >::type
{};
//partial specialization
template<typename SEARCH>
struct contains_type<SEARCH, std::tuple<>>:std::false_type{};


//resolve the start_from size exceed the tuple size
//因为即使开始己经判断start_from<std::tuple_size<TUPLE>::value, 
// when the compiler is instantiating a template, all the arguments that are mentioned in the that declaration have to be valid C++
//在deduce的时候IF,THEN,ELSE三个还是都需要参与，就导致在deduce THEN的时候会在is_same中调用std::tuple_element_t<tuple_size, TUPLE>而报越界错误
//解决方法是添加一个metafunction,使越界时返回一个nonetype
//to let tuple_element return NoneType if start_from larger than tuple size
//这个办法可能会隐藏一些代码错误，更好的方法见metatypelist.hpp中的contains_type的处理
struct NoneType_t{};
template<bool out_of_range, std::size_t index, typename TUPLE>
struct tuple_element;
template<std::size_t index, typename TUPLE>
struct tuple_element<true, index, TUPLE> {
    using type = NoneType_t;
};
template<std::size_t index, typename TUPLE>
struct tuple_element<false, index, TUPLE> {
    using type = std::tuple_element_t<index, TUPLE>;
};

//template variable
template<std::size_t start_from, typename TUPLE>
static bool constexpr index_out_of_range = (start_from >= std::tuple_size<TUPLE>::value);

//template alias
template<std::size_t start_from, typename TUPLE>
using tuple_element_t = typename tuple_element<index_out_of_range<start_from, TUPLE>, start_from, TUPLE>::type; 

template <typename SEARCH, typename TUPLE, std::size_t start_from=0>
struct contains_type1:
    if_<
        //(start_from >= std::tuple_size<TUPLE>::value),
        index_out_of_range<start_from, TUPLE>,
        std::false_type,
        typename if_<
            //std::is_same<SEARCH, typename tuple_element<(start_from >= std::tuple_size<TUPLE>::value), start_from, TUPLE>::type>::value,
            //std::is_same<SEARCH, tuple_element_t<start_from, TUPLE>>::value,
            std::is_same_v<SEARCH, tuple_element_t<start_from, TUPLE>>,
            std::true_type,
            contains_type1<SEARCH, TUPLE, start_from+1>
        >::type
    >::type
{};


template <typename T, typename... Args>
struct contains_type2:
std::false_type{};
template<typename T, typename... Args>
struct contains_type2<T, std::tuple<T, Args...>>:
std::true_type{};
template<typename T, typename T1, typename...Args>
struct contains_type2<T, std::tuple<T1, Args...>>:contains_type2<T, std::tuple<Args...>>{};

void do_test() {
    std::cout << "if (10>5)?" << std::boolalpha << std::is_same<int, if_<(10>5), int, float>::type>::value << std::endl;
    std::cout << "if (10<5)?" << std::boolalpha << std::is_same<int, if_<(10<5), int, float>::type>::value << std::endl;
    std::tuple<int, bool, float> tuple;
    std::cout << "============Solution 1 ================\n";
    std::cout << "contains_type<bool, decltype(tuple)>::value = " << contains_type<bool, decltype(tuple)>() << std::endl;
    std::cout << "contains_type<float, decltype(tuple)>::value = " << contains_type<float, decltype(tuple)>() << std::endl;
    std::cout << "contains_type<double, decltype(tuple)>::value = " << contains_type<double, decltype(tuple)>() << std::endl;
    std::cout << "contains_type<double, std::tuple<>>::value = " << contains_type<double, std::tuple<>>() << std::endl;
    //std::cout << "contains_type<bool, decltype(tuple), 3>::value = " << contains_type<bool, decltype(tuple), 3>() << std::endl; //compile error, 3 is out of index range

    std::cout << "============Solution 2 ================\n";
    std::cout << typeid(tuple_element<false, 0, decltype(tuple)>::type).name() << std::endl;
    std::cout << typeid(tuple_element<false, 1, decltype(tuple)>::type).name() << std::endl;
    std::cout << typeid(tuple_element<false, 2, decltype(tuple)>::type).name() << std::endl;
    std::cout << typeid(tuple_element<true, 3, decltype(tuple)>::type).name() << std::endl;
    std::cout << "contains_type1<bool, decltype(tuple)>::value = " << contains_type1<bool, decltype(tuple)>() << std::endl;
    std::cout << "contains_type1<float, decltype(tuple)>::value = " << contains_type1<float, decltype(tuple)>() << std::endl;
    std::cout << "contains_type1<double, decltype(tuple)>::value = " << contains_type1<double, decltype(tuple)>() << std::endl;
    std::cout << "contains_type1<double, std::tuple<>>::value = " << contains_type1<double, std::tuple<>>() << std::endl;
    std::cout << "contains_type1<bool, decltype(tuple), 3>::value = " << contains_type1<bool, decltype(tuple), 3>() << std::endl; //compile error, 3 is out of index range

    //variadic template solution shared by someone
    std::cout << "============Solution 3 ================\n";
    std::cout << "contains_type2<bool, decltype(tuple)>::value = " << contains_type2<bool, decltype(tuple)>() << std::endl;
    std::cout << "contains_type2<float, decltype(tuple)>::value = " << contains_type2<float, decltype(tuple)>() << std::endl;
    std::cout << "contains_type2<double, decltype(tuple)>::value = " << contains_type2<double, decltype(tuple)>() << std::endl;
    std::cout << "contains_type2<double, std::tuple<>>::value = " << contains_type2<double, std::tuple<>>() << std::endl;
}
}
#endif //__CONTAINS_TYPE__