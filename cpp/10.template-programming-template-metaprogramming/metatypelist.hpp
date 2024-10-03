//this is a metaprogramming library for typelist container.
//support for push, pop, front, contains_type
#ifndef __META_TYPELIST__
#define __META_TYPELIST__
#include <list>
#include <string>
#include <iostream>

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

template<>
struct empty<type_list<>>:std::true_type{};

static_assert(empty<type_list<>>::value);
static_assert(!empty<type_list<float>>::value);

////////////////////////front///////////////////
template<typename>
struct front;

template<typename T0, typename... T1toN>
struct front<type_list<T0, T1toN...>> { //直接用variadic template parameter deduce， 获取第一个参数 
    using type = T0;
};

static_assert(std::is_same_v<bool, front<type_list<bool, int>>::type>);

/////////////////////pop_front//////////////////
template<typename>
struct pop_front;

template<typename T0, typename... T1toN>
struct pop_front<type_list<T0, T1toN...>> { //直接用variadic template parameter deduce
    using type = type_list<T1toN...>;
};

template <typename LIST>
using pop_front_t = typename pop_front<LIST>::type;

static_assert(std::is_same_v<pop_front<type_list<bool, int, float>>::type, type_list<int, float>>);

////////////////back///////////////////
template<typename LIST>
struct back{
    using type = typename back<pop_front_t<LIST>>::type;
};

template<typename T0>
struct back<type_list<T0>> {
    using type = T0;
};

//直接用variadic template parameter deduce行不能，因为variadic template parameter是greedy的，如果放在第一个参数,会匹配所有接下来的参数，这样Tn就无法deduce
//template<typename... T0toN_1, typename Tn>
//struct back<type_list<T0toN_1..., Tn>>{ //compile error, Tn can not be deduced, using recurring tempalte instead
//    using type = Tn;
//}

static_assert(std::is_same_v<typename back<type_list<int, bool, float>>::type, float>);

template<typename LIST>
using back_t = typename back<LIST>::type;

//////////////////////push_back////////////////////////////
template<typename LIST, typename T>
struct push_back;

template<typename... T0toN, typename T>
struct push_back<type_list<T0toN...>, T> {
    using type = type_list<T0toN..., T>;
};

template<typename LIST, typename T>
using push_back_t = typename push_back<LIST, T>::type;

static_assert(std::is_same_v<type_list<int>, push_back_t<type_list<>, int>>);
static_assert(std::is_same_v<type_list<bool, bool, int>, push_back_t<type_list<bool,bool>, int>>);

///////////////////////////////pop_back//////////////////
template<typename LIST, typename RET_LIST = type_list<>>
struct pop_back; //直接用variadic template parameter deduce也行不通，还是用recursive template

template<typename T0, typename RET_LIST>
struct pop_back<type_list<T0>, RET_LIST> {
    using type = RET_LIST;
};
template<typename T0, typename T1, typename... T2toN, typename RET_LIST>
struct pop_back<type_list<T0, T1, T2toN...>, RET_LIST> 
    :pop_back<type_list<T1, T2toN...>, push_back_t<RET_LIST, T0>>{};

template<typename LIST>
using pop_back_t = typename pop_back<LIST>::type;

static_assert(std::is_same_v<pop_back_t<type_list<int,bool,float>>, type_list<int,bool>>);
static_assert(std::is_same_v<pop_back_t<type_list<int>>, type_list<>>);

///////////////////template aliasies////////////////////////////////
template <typename LIST>
using front_t = typename front<LIST>::type;


//template variables
template<typename LIST>
static constexpr bool empty_v = empty<LIST>::value;

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
template<typename SEARCH>
struct contains_type2<SEARCH, type_list<>>:std::false_type{};


void do_test() {
    std::cout << "do_test:metaprogramming library\n";
    type_list<int, bool, double> types;
    std::cout << "contians_type<bool, decltype(types)>::value = " << contains_type<bool, decltype(types)>::value << "\n";
    //std::cout << "contains_type<float, decltype<types)>::value = " << contains_type<float, decltype(types)>::value << "\n"; //compiling error because of front_t on empty list

    std::cout << "contians_type1<bool, decltype(types)>::value = " << contains_type1<bool, decltype(types)>::value << "\n";
    std::cout << "contains_type1<float, decltype<types)>::value = " << contains_type1<float, decltype(types)>::value << "\n"; //compiling error because of front_t on empty list

    std::cout << "contians_type2<bool, decltype(types)>::value = " << contains_type2<bool, decltype(types)>::value << "\n";
    std::cout << "contains_type2<float, decltype<types)>::value = " << contains_type2<float, decltype(types)>::value << "\n"; //compiling error because of front_t on empty list
}
}
#endif //__META_TYPELIST__