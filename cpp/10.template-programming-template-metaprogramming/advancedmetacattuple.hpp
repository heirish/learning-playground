#ifndef __CAT_TUPLE__
#define __CAT_TUPLE__
#include <cassert>
#include <cxxabi.h>
#include <functional>
#include <ios>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

#include "TestUtilities.h"
#include "metatypelist.hpp"

namespace cat_tuple {

template <typename...> struct Tuple {
  constexpr Tuple() = default;
};
// template<typename ELEM0, typename... ELEM1ToN>
// struct Tuple<ELEM0, ELEM1ToN...> : Tuple<ELEM1ToN...> {
//     explicit constexpr Tuple(ELEM0 e1, ELEM1ToN...
//     rest):Tuple<ELEM1ToN...>(rest...), data(e1){} ELEM0 data;
// };
template <typename ELEM0, typename... ELEM1ToN>
struct Tuple<ELEM0, ELEM1ToN...> : Tuple<ELEM1ToN...> {
  // 不能直接写成Tuple(ELEM0&& e1, ELEM1ToN&&... rest)
  // 是因为ELEM0 is already deduced at this stage(constructor), ELEM0&& would
  // make this an rvalue reference, then constructor only accept rvalues,
  // Tuple{1,c,false} will not work because c is an lvalue. (int&& is an rvalue
  // reference, while T&& is universal reference) to implement a forwarding
  // reference, there has to be a type deduction involved.. need to make
  // constructor as template.
  template <typename T, typename... Ts>
  // 这里T, Ts都忘记加&&了，std::forward会导致其move,因此stats输出会多两个.moves
  // explicit constexpr Tuple(T e1, Ts...
  // rest):Tuple<ELEM1ToN...>(std::forward<Ts>(rest)...),
  // data(std::forward<T>(e1)){}
  explicit constexpr Tuple(T &&e1, Ts &&...rest)
      : Tuple<ELEM1ToN...>(std::forward<Ts>(rest)...),
        data(std::forward<T>(e1)) {}
  ELEM0 data;
};

// CTAD
// deduction guide to make template argument deduction for constructors work
// (c++17)
template <typename T, typename... Ts>
Tuple(T t, Ts... rest)
    -> Tuple<std::unwrap_ref_decay_t<T>, std::unwrap_ref_decay_t<Ts>...>;
// deduction guide is just to find the constructor to call when a tuple is
// constructed, it's just doing that, it is not going to be evaluated so you
// don't need to worry about the forwarding reference

// template<typename... ELEMS>
// auto make_tuple(ELEMS... elems) {
//     //std::unwrap_ref_decay_t since c++20
//     return Tuple<std::unwrap_ref_decay_t<ELEMS>...>{elems...};
// }
// make copies -1
template <typename... ELEMS> auto make_tuple(ELEMS &&...elems) {
  // std::unwrap_ref_decay_t since c++20
  return Tuple<std::unwrap_ref_decay_t<ELEMS>...>{
      std::forward<ELEMS>(elems)...};
}

//////////////////////get////////////////////////
namespace detail {
template <std::size_t i, typename TUPLE>
struct get_impl : get_impl<i - 1, meta_typelist_lib::pop_front_t<TUPLE>> {};

// 因为这里的TUPLE己不是最初传入的TUPLE，到这里时己经pop_front_t过很多次了
// 所以get函数需要以原始的tuple作为参数
template <typename TUPLE> struct get_impl<0, TUPLE> {
  // template<typename T>
  // constexpr static decltype(auto) get(T& t) {
  //     //这里是将原始Tuple类型转换成了经过i次pop_front_t之后的Tuple,
  //     并取其data成员 constexpr bool is_const = std::is_const_v<T>; if
  //     constexpr (is_const) { //to make it work for const Tuple also
  //         return static_cast<const TUPLE&>(t).data;
  //     } else {
  //         return static_cast<TUPLE&>(t).data;
  //     }
  // }

  // to make get working for get<2>(Tuple{2,3,4}) too
  // template<typename T>
  // constexpr static decltype(auto) get(T&& t) {
  //     //这里是将原始Tuple类型转换成了经过i次pop_front_t之后的Tuple,
  //     并取其data成员 constexpr bool is_lvalue =
  //     std::is_lvalue_reference_v<T>;
  //     //constexpr bool is_const = std::is_const_v<T>;
  //     //becarefull, as a forward reference, it's always deduced to a
  //     reference type,
  //     //we need to strip off this reference before we composite it to
  //     is_const_v, otherwise it won't work correctly constexpr bool is_const =
  //     std::is_const_v<std::remove_reference_t<T>>; if constexpr (is_const &&
  //     is_lvalue) { //to make it work for const Tuple also
  //         return static_cast<const TUPLE&>(t).data;
  //     } else if constexpr (!is_const && is_lvalue){
  //         return static_cast<TUPLE&>(t).data;
  //     } else if constexpr (is_const && !is_lvalue) {
  //         return static_cast<const TUPLE&&>(t).data;
  //     } else if constexpr (!is_const && !is_lvalue) {
  //         return static_cast<TUPLE&&>(t).data;
  //     }
  // }

  // to make get also assignable, working as get<1>(tuple2) = false;
  template <typename T> constexpr static decltype(auto) get(T &&t) {
    // 这里是将原始Tuple类型转换成了经过i次pop_front_t之后的Tuple,
    // 并取其data成员
    constexpr bool is_lvalue = std::is_lvalue_reference_v<T>;
    // constexpr bool is_const = std::is_const_v<T>;
    // becarefull, as a forward reference, it's always deduced to a reference
    // type, we need to strip off this reference before we composite it to
    // is_const_v, otherwise it won't work correctly
    constexpr bool is_const = std::is_const_v<std::remove_reference_t<T>>;
    using data_t = meta_typelist_lib::front_t<TUPLE>;
    if constexpr (is_const &&
                  is_lvalue) { // to make it work for const Tuple also
      return static_cast<const data_t &>(static_cast<const TUPLE &>(t).data);
    } else if constexpr (!is_const && is_lvalue) {
      return static_cast<data_t &>(static_cast<TUPLE &>(t).data);
    } else if constexpr (is_const && !is_lvalue) {
      return static_cast<const data_t &&>(static_cast<const TUPLE &&>(t).data);
    } else if constexpr (!is_const && !is_lvalue) {
      return static_cast<data_t &&>(static_cast<TUPLE &&>(t).data);
    }
  }
};
} // namespace detail

// template<std::size_t i, typename TUPLE>
// constexpr decltype(auto) get(TUPLE& tuple)
//     return detail::get_impl<i, std::remove_cvref_t<TUPLE>>::get(tuple);
// }
// to make get working for get<2>(Tuple{2,3,4}) too
template <std::size_t i, typename TUPLE>
constexpr decltype(auto) get(TUPLE &&tuple) {
  return detail::get_impl<i, std::remove_cvref_t<TUPLE>>::get(
      std::forward<TUPLE>(tuple));
}
/////////////////////////////tuple_size/////////////////////////
template <typename TUPLE> struct tuple_size;
template <typename... ELEMS>
struct tuple_size<Tuple<ELEMS...>>
    : std::integral_constant<std::size_t, sizeof...(ELEMS)> {};

template <typename TUPLE>
// static constexpr std::size_t tuple_size_v =
// tuple_size<std::remove_cvref_t<TUPLE>>::value;
static constexpr std::size_t tuple_size_v = tuple_size<TUPLE>::value;

void do_tuple_test() {
  //////////////////basic tuple manipulation support////////////////////
  auto tup = make_tuple(8, true, 1.5);
  std::cout << tup.data << "\n";
  std::cout << get<2>(tup) << "\n";
  get<1>(tup) = false;
  std::cout << std::boolalpha << get<1>(tup) << std::endl;

  // need CTAD
  const Tuple tuple2{2, true, 2.3};
  std::cout << tuple2.data << "\n";
  std::cout << get<2>(tuple2) << "\n"; // 2.3

  std::cout << get<2>(Tuple{2, 3, 4}) << std::endl;

  assert(tuple_size_v<decltype(tup)> == 3);
  assert(tuple_size_v<std::remove_cvref_t<decltype(tuple2)>> == 3);
  ////////////////////////////consider performance/////////////////////////////
  // 检查构造Tuple时，一个object会被copy,move多少次
  bits_of_q::CopyCounter c;
  c.reset();
  make_tuple(1, c, 2.7, false);
  // make_tuple(1, bits_of_q::CopyCounter(), 2.7,false);
  std::cout << c.stats << std::endl;
  // default constucts:0, copies:3, moves:0
  // after considering reference forwarding, constructs:1, copies:1, moves:0

  bits_of_q::CopyStats our_stats =
      c.reset(); // record our copystats in tuple construction and reset.
  std::make_tuple(1, c, 2.7, false);
  bits_of_q::CopyStats std_stats =
      c.reset(); // record our copystats in tuple construction and reset.
  std::cout << "our make_tuple copy stats:" << our_stats << std::endl;
  std::cout << "std::make_tuple copy stats:" << std_stats << std::endl;
  assert(our_stats == std_stats);

  // get tuple时，object的copy, move统计
  auto tp1 = make_tuple(1, c, 3.1f);
  c.reset();
  get<1>(tp1);
  auto ourget_stats = c.reset();
  auto tp2 = std::make_tuple(1, c, 3.2f);
  c.reset();
  std::get<1>(tp2);
  auto stdget_stats = c.reset();
  std::cout << "our get copy stats:" << ourget_stats << std::endl;
  std::cout << "std::get copy stats:" << stdget_stats << std::endl;
  assert(ourget_stats == stdget_stats);
}

namespace detail {

struct tuple_cat_impl {
  // template<typename TUPLE1, typename TUPLE2>
  // static auto f(TUPLE1&& tuple1, TUPLE2&& tuple2) {
  //     return cat_from_indicies(std::forward<TUPLE1>(tuple1),
  //                             std::forward<TUPLE2>(tuple2),
  //                             std::make_index_sequence<tuple_size_v<std::remove_cvref_t<TUPLE1>>>(),
  //                             std::make_index_sequence<tuple_size_v<std::remove_cvref_t<TUPLE2>>>());
  // }

  // to support more than 2 tuple cats
  // template <typename RET_TUPLE, typename TUPLE, typename... TUPLES>
  // static constexpr auto f(RET_TUPLE &&ret, TUPLE &&t, TUPLES &&...tuples) {
  //  return f(
  //      cat_from_indicies(std::forward<RET_TUPLE>(ret),
  //      std::forward<TUPLE>(t),
  //                        std::make_index_sequence<
  //                            tuple_size_v<std::remove_cvref_t<RET_TUPLE>>>(),
  //                        std::make_index_sequence<
  //                            tuple_size_v<std::remove_cvref_t<TUPLE>>>()),
  //      std::forward<TUPLES>(tuples)...);
  //}

  //// at last, the ret is returned from cat_from_indicies, whish is an rvalue.
  //// and std::forward will causing rvalue move, so this will cause more moves
  //// than standard library's tuple_cat
  //// Plan:
  //// 1, recursively build forwarding tuple from inputs.
  //// 2. once done, convert forwarding tuple to output tuple
  // template <typename RET_TUPLE> static constexpr auto f(RET_TUPLE &&ret) {
  //   return std::forward<RET_TUPLE>(ret);
  // }
  //
  // template <typename TUPLE1, typename TUPLE2, std::size_t... indicies1,
  //          std::size_t... indicies2>
  // static auto cat_from_indicies(TUPLE1 &&tuple1, TUPLE2 &&tuple2,
  //                              std::index_sequence<indicies1...>,
  //                              std::index_sequence<indicies2...>) {
  //  return Tuple{get<indicies1>(std::forward<TUPLE1>(tuple1))...,
  //               get<indicies2>(std::forward<TUPLE2>(tuple2))...};
  //}

  // to resolve unneccessary moves
  //.......慢慢的就聽不懂了
  template <typename FWD_TUPLE, typename TUPLE, typename... TUPLES>
  static constexpr auto f(FWD_TUPLE &&ret, TUPLE &&t, TUPLES &&...tuples) {
    return f(
        concat_with_fwd_tuple<std::make_index_sequence<
                                  tuple_size_v<std::remove_cvref_t<FWD_TUPLE>>>,
                              std::make_index_sequence<
                                  tuple_size_v<std::remove_cvref_t<TUPLE>>>>::
            concat(std::forward<FWD_TUPLE>(ret), std::forward<TUPLE>(t)),
        std::forward<TUPLES>(tuples)...);
  }

  template <typename FWD_TUPLE> static constexpr auto f(FWD_TUPLE &&ret) {
    return make_tuple_from_fwd_tuple<std::make_index_sequence<
        tuple_size_v<FWD_TUPLE>>>::make(std::forward<FWD_TUPLE>(ret));
  }

  template <typename FWD_INDEX_SEQ, typename TUPLE_INDEX_SEQ>
  struct concat_with_fwd_tuple;

  template <std::size_t... fwd_indicies, std::size_t... tuple_indicies>
  struct concat_with_fwd_tuple<std::index_sequence<fwd_indicies...>,
                               std::index_sequence<tuple_indicies...>> {

    template <typename FWD_TUPLE, typename TUPLE>
    static constexpr auto concat(FWD_TUPLE &&fwd, TUPLE &&t) {
      // return std::forward_as_tuple(
      return forward_as_tuple(
          get<fwd_indicies>(std::forward<FWD_TUPLE>(fwd))...,
          get<tuple_indicies>(std::forward<TUPLE>(t))...);
    }
  };

  template <typename... Ts>
  static constexpr auto forward_as_tuple(Ts &&...ts) noexcept {
    return Tuple<Ts &&...>(std::forward<Ts>(ts)...);
  };

  template <typename INDEX_SEQ> struct make_tuple_from_fwd_tuple;

  template <std::size_t... indicies>
  struct make_tuple_from_fwd_tuple<std::index_sequence<indicies...>> {
    template <typename FWD_TUPLE> static constexpr auto make(FWD_TUPLE &&fwd) {
      return Tuple{get<indicies>(std::forward<FWD_TUPLE>(fwd))...};
    }
  };
};
} // namespace detail

template <typename... TUPLES> constexpr auto tuple_cat(TUPLES &&...tuples) {
  return detail::tuple_cat_impl::template f(std::forward<TUPLES>(tuples)...);
  // return detail::tuple_cat_impl::template f(tuples...); //make tuple_cat test
  // fail
}
void do_tuple_cast_test() {
  Tuple t1{8, true};
  Tuple t2{3.5, std::string{"hello"}};
  auto t1_2 = tuple_cat(
      t1, t2); // t1_2 = Tuple<int,bool,double,std::string>(8,true,3.5,"hello");
  assert(tuple_size_v<decltype(t1_2)> == 4);
  assert(get<0>(t1_2) == 8);
  assert(get<3>(t1_2) == "hello");
}

// to get the deduced type info,
// better solution is to use boost,
// type_id_with_cvr<decltype<T>>().pretty_name()
template <typename T> std::string type_name() {
  typedef typename std::remove_reference<T>::type TR;
  std::string r = typeid(TR).name();

  int status = 0;
  char *demangled = abi::__cxa_demangle(r.c_str(), NULL, NULL, &status);
  if (0 == status) {
    r = std::string(demangled);
    free(demangled);
  }

  if (std::is_const<TR>::value)
    r += " const";
  if (std::is_volatile<TR>::value)
    r += " volatile";
  if (std::is_lvalue_reference<T>::value)
    r += "&";
  else if (std::is_rvalue_reference<T>::value)
    r += "&&";
  return r;
}
void test_framwork_use() {
  // TestUtilities is just a simple test framework so that we do not involve any
  // third-party libraries for serious project, do not use it, use available
  // mature framework such as Gtest
  constexpr std::size_t boq_tuple = 1;
  constexpr std::size_t std_tuple = 2;
  namespace boq = bits_of_q;
  using boq::testing::Tester;
  using boq::testing::TesterWithBuilder;

  // check if tuple construction takes the same construct,copies,moves as std
  // library std::tuple
  Tester::test("constructor", []() {
    auto c1 = boq::make_copy_counter<boq_tuple>();
    auto c2 = boq::make_copy_counter<std_tuple>();

    Tuple t1{9, c1, 1.4};
    std::tuple t2{9, c2, 1.4};

    ASSERT(c1 == c2);
  });

  Tester::test("make_tuple", []() {
    auto c1 = boq::make_copy_counter<boq_tuple>();
    auto c2 = boq::make_copy_counter<std_tuple>();

    make_tuple(9, c1, 1.4, false);
    std::make_tuple(9, c2, 1.4, false);
    ASSERT(c1 == c2);
  });

  // to test const,non-const, lvalue, rvalue in a single test
  // builder will create 4 types of Tuple, Tuple&, Tuple const&, Tuple&&, Tuple
  // const&& and the test will be ran for 4 times
  TesterWithBuilder<1>::test("bulder demo", [](auto &&builder) {
    auto &&t1 = builder.build(Tuple{42, true});
    std::cerr << "built:" << type_name<decltype(t1)>() << "\n"; // 4 print
  });

  // 每个t有四种类型:&, const&, &&, const&&.
  // 每个test中有两个t, 进行组合，最终就是4*4种组合:(&, &), (&, const&), ....
  TesterWithBuilder<2>::test("builder demo2", [](auto &&builder) {
    auto &&[t1, t2] = builder.build(Tuple{42, true}, Tuple{1.5});
    std::cerr
        << "built:" << type_name<decltype(t1)>() << "\t\t\t"
        << type_name<decltype(t2)>()
        << "\n"; // 16 print, foreach t, it will create 4, then combine mix,4^2
  });

  TesterWithBuilder<1>::test("get", [](auto &&builder) {
    auto c1 = boq::make_copy_counter<boq_tuple>();
    auto c2 = boq::make_copy_counter<std_tuple>();

    auto &&t1 = builder.build(Tuple{42, c1, true});
    auto &&t2 = builder.build(std::tuple{42, c2, true});

    auto v1 = get<0>(std::forward<decltype(t1)>(t1));
    auto v2 = std::get<0>(std::forward<decltype(t2)>(t2));

    auto v3 = get<1>(std::forward<decltype(t1)>(t1));
    auto v4 = std::get<1>(std::forward<decltype(t2)>(t2));

    ASSERT(v1 == v2);
    ASSERT(v3 == v4);
  });

  TesterWithBuilder<2>::test("tuple_cat with 2 args", [](auto &&builder) {
    auto c1 = boq::make_copy_counter<boq_tuple>();
    auto c2 = boq::make_copy_counter<std_tuple>();

    auto &&[boq_t1, boq_t2] =
        builder.build(Tuple{42, c1, true}, Tuple{false, c1, 1.2});
    auto &&[std_t1, std_t2] =
        builder.build(std::tuple{42, c2, true}, std::tuple{false, c2, 1.2});

    auto boq1_2 = tuple_cat(std::forward<decltype(boq_t1)>(boq_t1),
                            std::forward<decltype(boq_t2)>(boq_t2));
    auto std1_2 = std::tuple_cat(std::forward<decltype(std_t1)>(std_t1),
                                 std::forward<decltype(std_t2)>(std_t2));

    ASSERT(get<0>(boq1_2) == std::get<0>(std1_2));
    auto boq_s1 = get<1>(boq1_2);
    auto std_s2 = std::get<1>(std1_2);
    std::cerr << "boq static:" << boq_s1.stats << std::endl;
    std::cerr << "std static:" << std_s2.stats << std::endl;
    ASSERT(get<1>(boq1_2) == std::get<1>(std1_2));

    boq::static_for<0, tuple_size_v<decltype(boq1_2)>>(
        [&](auto i) { ASSERT(get<i>(boq1_2) == std::get<i>(std1_2)); });
  });

  TesterWithBuilder<3>::test("tuple_cat with 3 args", [](auto &&builder) {
    auto c1 = boq::make_copy_counter<boq_tuple>();
    auto c2 = boq::make_copy_counter<std_tuple>();

    auto &&[boq_t1, boq_t2, boq_t3] = builder.build(
        Tuple{42, c1, true}, Tuple{false, c1, 1.2}, Tuple{7, 'c'});
    auto &&[std_t1, std_t2, std_t3] =
        builder.build(std::tuple{42, c2, true}, std::tuple{false, c2, 1.2},
                      std::tuple{7, 'c'});

    auto boq1_2_3 = tuple_cat(std::forward<decltype(boq_t1)>(boq_t1),
                              std::forward<decltype(boq_t2)>(boq_t2),
                              std::forward<decltype(boq_t3)>(boq_t3));
    auto std1_2_3 = std::tuple_cat(std::forward<decltype(std_t1)>(std_t1),
                                   std::forward<decltype(std_t2)>(std_t2),
                                   std::forward<decltype(std_t3)>(std_t3));
    boq::static_for<0, tuple_size_v<decltype(boq1_2_3)>>(
        [&](auto i) { ASSERT(get<i>(boq1_2_3) == std::get<i>(std1_2_3)); });
  });
}

} // namespace cat_tuple
#endif //__CAT_TUPLE__