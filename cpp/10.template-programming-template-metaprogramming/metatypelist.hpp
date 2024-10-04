//this is a metaprogramming library for typelist container.
//support for push, pop, front, contains_type
#ifndef __META_TYPELIST__
#define __META_TYPELIST__
#include <list>
#include <string>
#include <iostream>
#include <type_traits>

namespace meta_typelist_lib {
bool contains(const std::string& search, std::list<std::string> l) {
    if (l.empty()) {
        return false;
    } else {
        if (search == l.front()) {
            return true;
        } else {
            l.pop_front();
            return contains(search, l);
        }
    }
}
void runtime_ex() {
    std::cout << "runtime_ex\n";
    std::list<std::string> types{"list", "bool", "double"};
    std::cout << std::boolalpha << contains("bool", types) << std::endl;
    std::cout << std::boolalpha << contains("float", types) << std::endl;
}

template<typename...>
struct type_list{};

///////////////////////empty///////////////////
template<typename>
struct empty:std::false_type{};

//template<>
//struct empty<type_list<>>:std::true_type{};

//make metafunction also works for other tempalte type, such as tuple
//using template template parameters
template<template<typename...> typename LIST>
struct empty<LIST<>>:std::true_type{};//LIST<>还是一个tempalte, 并不是被实例化的

//template variables
template<typename LIST>
static constexpr bool empty_v = empty<LIST>::value;

static_assert(empty<type_list<>>::value);
static_assert(!empty<type_list<float>>::value);
static_assert(empty<std::tuple<>>::value);
static_assert(!empty<std::tuple<float>>::value);

////////////////////////front///////////////////
template<typename>
struct front;

//template<typename T0, typename... T1toN>
//struct front<type_list<T0, T1toN...>> { //直接用variadic template parameter deduce， 获取第一个参数 
//    using type = T0;
//};

//make metafunction also works for other tempalte type, such as tuple
//using template template parameters
template<template<typename...> typename LIST, typename T0, typename... T1toN>
struct front<LIST<T0, T1toN...>> { //直接用variadic template parameter deduce， 获取第一个参数 
    using type = T0;
};

template <typename LIST>
using front_t = typename front<LIST>::type;

static_assert(std::is_same_v<bool, front<type_list<bool, int>>::type>);
static_assert(std::is_same_v<bool, front<std::tuple<bool, int>>::type>);

/////////////////////pop_front//////////////////
template<typename>
struct pop_front;

//template<typename T0, typename... T1toN>
//struct pop_front<type_list<T0, T1toN...>> { //直接用variadic template parameter deduce
//    using type = type_list<T1toN...>;
//};

//make metafunction also works for other tempalte type, such as tuple
//using template template parameters
template<template<typename...>typename LIST, typename T0, typename... T1toN>
struct pop_front<LIST<T0, T1toN...>> { //直接用variadic template parameter deduce
    using type = LIST<T1toN...>;
};

template <typename LIST>
using pop_front_t = typename pop_front<LIST>::type;

static_assert(std::is_same_v<pop_front<type_list<bool, int, float>>::type, type_list<int, float>>);
static_assert(std::is_same_v<pop_front<std::tuple<bool, int, float>>::type, std::tuple<int, float>>);

////////////////back///////////////////
template<typename LIST>
struct back{
    using type = typename back<pop_front_t<LIST>>::type;
};


//template<typename T0>
//struct back<type_list<T0>> {
//    using type = T0;
//};

//make metafunction also works for other tempalte type, such as tuple
//using template template parameters
template<template<typename...> typename LIST, typename T0>
struct back<LIST<T0>> {
    using type = T0;
};

//直接用variadic template parameter deduce行不能，因为variadic template parameter是greedy的，如果放在第一个参数,会匹配所有接下来的参数，这样Tn就无法deduce
//template<typename... T0toN_1, typename Tn>
//struct back<type_list<T0toN_1..., Tn>>{ //compile error, Tn can not be deduced, using recursive template instead
//    using type = Tn;
//}

static_assert(std::is_same_v<typename back<type_list<int, bool, float>>::type, float>);
static_assert(std::is_same_v<typename back<std::tuple<int, bool, float>>::type, float>);

template<typename LIST>
using back_t = typename back<LIST>::type;

//////////////////////push_back////////////////////////////
template<typename LIST, typename T>
struct push_back;

//template<typename... T0toN, typename T>
//struct push_back<type_list<T0toN...>, T> {
//    using type = type_list<T0toN..., T>;
//};
template<template<typename...>typename LIST, typename... T0toN, typename T>
struct push_back<LIST<T0toN...>, T> {
    using type = LIST<T0toN..., T>;
};

template<typename LIST, typename T>
using push_back_t = typename push_back<LIST, T>::type;

static_assert(std::is_same_v<type_list<int>, push_back_t<type_list<>, int>>);
static_assert(std::is_same_v<type_list<bool, bool, int>, push_back_t<type_list<bool,bool>, int>>);
static_assert(std::is_same_v<std::tuple<bool, bool, int>, push_back_t<std::tuple<bool,bool>, int>>);

///////////////////////////////pop_back//////////////////
///////////////don't know to how make it work for tuple///////////
//////////////solution: assign the empty list in the pop_back_t using helper metafunction make_empty
//template<typename LIST, typename RET_LIST = type_list<>>
//struct pop_back; //直接用variadic template parameter deduce也行不通，还是用recursive template
//
//template<typename T0, typename RET_LIST>
//struct pop_back<type_list<T0>, RET_LIST> {
//    using type = RET_LIST;
//};
//template<typename T0, typename T1, typename... T2toN, typename RET_LIST>
//struct pop_back<type_list<T0, T1, T2toN...>, RET_LIST> 
//    :pop_back<type_list<T1, T2toN...>, push_back_t<RET_LIST, T0>>{};
//
//template<typename LIST>
//using pop_back_t = typename pop_back<LIST>::type;

//make it workf for std::tuple too
template<typename LIST, typename RET_LIST>
struct pop_back; //直接用variadic template parameter deduce也行不通，还是用recursive template

template<template<typename...>typename LIST, typename T0, typename RET_LIST>
struct pop_back<LIST<T0>, RET_LIST> {
    using type = RET_LIST;
};

template<template<typename...>typename LIST, typename T0, typename T1, typename... T2toN, typename RET_LIST>
struct pop_back<LIST <T0, T1, T2toN...>, RET_LIST> 
    :pop_back<LIST <T1, T2toN...>, push_back_t<RET_LIST, T0>>{};

template<typename LIST>
struct make_empty;

template<template<typename...>typename LIST, typename... Args>
struct make_empty<LIST<Args...>> {
    using type = LIST<>;
};

template<typename LIST>
using pop_back_t = typename pop_back<LIST, typename make_empty<LIST>::type>::type;

static_assert(std::is_same_v<pop_back_t<type_list<int,bool,float>>, type_list<int,bool>>);
static_assert(std::is_same_v<pop_back_t<type_list<int>>, type_list<>>);
static_assert(std::is_same_v<pop_back_t<std::tuple<int,bool,float>>, std::tuple<int,bool>>);
static_assert(std::is_same_v<pop_back_t<std::tuple<int>>, std::tuple<>>);

////////////////////////AT///////////////////////
//可以定义一个metafunction用于写using type, 后面需要写using type的metafunction继承于它
template <typename T>
struct has_type{
    using type = T;
};

template<typename LIST,  std::size_t index>
struct at :has_type<typename at<pop_front_t<LIST>, index-1>::type>{
    //using type = typename at<pop_front_t<LIST>, index-1>::type;
};

template<typename LIST>
struct at<LIST, 0> :has_type<front_t<LIST>>{
    //using type = front_t<LIST>;
};
template<typename LIST, std::size_t index>
using at_t = typename at<LIST, index>::type; 

static_assert(std::is_same_v<typename at<type_list<int, bool, float>, 1>::type, bool>);
static_assert(std::is_same_v<at_t<type_list<int, bool, float>, 2>, float>);
static_assert(std::is_same_v<at_t<type_list<int, bool, float>, 0>, int>);
static_assert(std::is_same_v<at_t<std::tuple<int, bool, float>, 0>, int>);

/////////////////if_////////////////
template <bool, typename THEN, typename ELSE>
struct if_;
template<typename THEN, typename ELSE>
struct if_<true, THEN, ELSE> {
    using type = THEN;
};
template<typename THEN, typename ELSE>
struct if_<false, THEN, ELSE> {
    using type = ELSE;
};

///////////////////////////////contains_type////////////////////
template<typename SEARCH, typename LIST>
struct contains_type: 
    if_<
        empty_v<LIST>,
        std::false_type,
        typename if_<
            std::is_same_v<SEARCH, front_t<LIST>>,
            std::true_type,
            contains_type<SEARCH, pop_front_t<LIST>>
        >::type
    >::type
{};

///////////////////////////////contains_type////////////////////
template<typename SEARCH, typename LIST>
struct contains_type1;

template<typename SEARCH, typename LIST>
struct none_empty_contains_type: 
        if_<
            std::is_same_v<SEARCH, front_t<LIST>>,
            std::true_type,
            contains_type1<SEARCH, pop_front_t<LIST>>
        >::type
{};
template<typename SEARCH, typename LIST>
struct contains_type1:
    if_<
        empty_v<LIST>,
        std::false_type,
        none_empty_contains_type<SEARCH,  LIST> //当LIST为空的时候，只要保证ELSE clouse里的是一个type就行了，并不会去instantiate它
    >::type
{};

//////////////////contains_type2:solution 2 for empty list//////////////////////
////////////////这个方法不好的就是需要为每一个支持的LIST类型写偏特化///////////////////
////////////////解决:用templat template parameter///////////////////
template<typename SEARCH, typename LIST>
struct contains_type2: 
    if_<
        empty_v<LIST>,
        std::false_type,
        typename if_<
            std::is_same_v<SEARCH, front_t<LIST>>,
            std::true_type,
            contains_type2<SEARCH, pop_front_t<LIST>>
        >::type
    >::type
{};
//template<typename SEARCH>
//struct contains_type2<SEARCH, type_list<>>:std::false_type{};
template<typename SEARCH, template <typename...> typename LIST>
struct contains_type2<SEARCH, LIST<>>:std::false_type{};

/////////////////////////////////ANY//////////////////////////////////////
template<template<typename>typename PREDICATE, typename LIST>
struct any;

template<template<typename> typename PREDICATE, template<typename...>typename LIST>
struct any<PREDICATE, LIST<>>:std::false_type{};


template<template<typename> typename PREDICATE, typename LIST>
struct any:
    if_<
        PREDICATE<front_t<LIST>>::value,
        std::true_type,
        typename any<PREDICATE, pop_front_t<LIST>>::type
    >::type
{};

template<template<typename>typename PREDICATE, typename LIST>
static constexpr bool any_v = any<PREDICATE, LIST>::value;

static_assert(any_v<std::is_integral, type_list<int, bool, std::string>>);
static_assert(!any_v<std::is_integral, type_list<float, double, std::string>>);

///////////////////////using any_v to implemnt contains///////////////////////
//类似于functional中的programming, 将其中一个不变操作数封装到functor,然后去跟另外一个可变的操作数进行比较
template<typename T>
struct same_as_pred{
    template<typename U>
    struct predicate : std::is_same<T, U>{};
};

//predicate is a dependent type name, need classname<T>::template to reference
template<typename SEARCH, typename LIST>
static constexpr bool contains_type_v = any_v<same_as_pred<SEARCH>::template predicate, LIST>;

static_assert(contains_type_v<bool, type_list<bool, int, float>>);
static_assert(contains_type_v<bool, std::tuple<bool, int, float>>);
static_assert(!contains_type_v<bool, std::tuple<double, int, float>>);
static_assert(!contains_type_v<bool, type_list<double, int, float>>);

void do_test() {
    std::cout << "do_test:metaprogramming library\n";
    type_list<int, bool, double> types;
    std::cout << "contians_type<bool, decltype(types)>::value = " << contains_type<bool, decltype(types)>::value << "\n";
    //std::cout << "contains_type<float, decltype(types)>::value = " << contains_type<float, decltype(types)>::value << "\n"; //compiling error because of front_t on empty list

    std::cout << "contians_type1<bool, decltype(types)>::value = " << contains_type1<bool, decltype(types)>::value << "\n";
    std::cout << "contains_type1<float, decltype(types)>::value = " << contains_type1<float, decltype(types)>::value << "\n"; //compiling error because of front_t on empty list

    std::cout << "contians_type2<bool, decltype(types)>::value = " << contains_type2<bool, decltype(types)>::value << "\n";
    std::cout << "contains_type2<float, decltype(types)>::value = " << contains_type2<float, decltype(types)>::value << "\n"; //compiling error because of front_t on empty list

    //let it work for tuple too
    //test
    std::cout << "==========let it work for tuple too ================\n";
    std::tuple<int, bool, double> tuple;
    std::cout << "contians_type<bool, decltype(tuple)>::value = " << contains_type<bool, decltype(tuple)>::value << "\n";
    //std::cout << "contains_type<float, decltype(tuple)>::value = " << contains_type<float, decltype(tuple)>::value << "\n"; //compiling error because of front_t on empty list

    std::cout << "contians_type1<bool, decltype(tuple)>::value = " << contains_type1<bool, decltype(tuple)>::value << "\n";
    std::cout << "contains_type1<float, decltype(tuple)>::value = " << contains_type1<float, decltype(tuple)>::value << "\n"; //compiling error because of front_t on empty list

    std::cout << "contians_type2<bool, decltype(tuple)>::value = " << contains_type2<bool, decltype(tuple)>::value << "\n";
    std::cout << "contains_type2<float, decltype(tuple)>::value = " << contains_type2<float, decltype(tuple)>::value << "\n"; //compiling error because of front_t on empty list
}
}
#endif //__META_TYPELIST__