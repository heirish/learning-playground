#ifndef __ADV_META_ALGORITHM__
#define __ADV_META_ALGORITHM__
#include "TestUtilities.h"
#include "advancedmetatuple.hpp"
#include "helpers.hpp"

namespace adv_meta_programming {

template <typename... Ts>
static constexpr auto forward_as_tuple(Ts &&...ts) noexcept {
    return Tuple<Ts &&...>(std::forward<Ts>(ts)...);
};

namespace detail {
// struct tuple_cat_impl {
//  template<typename TUPLE1, typename TUPLE2>
//  static auto f(TUPLE1&& tuple1, TUPLE2&& tuple2) {
//      return cat_from_indicies(std::forward<TUPLE1>(tuple1),
//                              std::forward<TUPLE2>(tuple2),
//                              std::make_index_sequence<tuple_size_v<std::remove_cvref_t<TUPLE1>>>(),
//                              std::make_index_sequence<tuple_size_v<std::remove_cvref_t<TUPLE2>>>());
//  }

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

//// at last, the ret is returned from cat_from_indicies, whish is an
/// rvalue. and std::forward will causing rvalue move, so this will cause
/// more moves than standard library's tuple_cat
// Plan:
// 1, recursively build forwarding tuple from inputs.
// 2. once done, convert forwarding tuple to output tuple
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

// reduce move operations
// struct tuple_cat_impl {
//     // to resolve unneccessary moves
//     //.......慢慢的就聽不懂了
//     template <typename FWD_TUPLE, typename TUPLE, typename... TUPLES>
//     static constexpr auto f(FWD_TUPLE &&ret, TUPLE &&t, TUPLES &&...tuples) {
//         return f(concat_with_fwd_tuple<
//                      std::make_index_sequence<
//                          tuple_size_v<std::remove_cvref_t<FWD_TUPLE>>>,
//                      std::make_index_sequence<tuple_size_v<std::remove_cvref_t<
//                          TUPLE>>>>::concat(std::forward<FWD_TUPLE>(ret),
//                                            std::forward<TUPLE>(t)),
//                  std::forward<TUPLES>(tuples)...);
//     }
//
//     template <typename FWD_TUPLE> static constexpr auto f(FWD_TUPLE &&ret) {
//         return make_tuple_from_fwd_tuple<std::make_index_sequence<
//             tuple_size_v<FWD_TUPLE>>>::make(std::forward<FWD_TUPLE>(ret));
//     }
//
//     template <typename FWD_INDEX_SEQ, typename TUPLE_INDEX_SEQ>
//     struct concat_with_fwd_tuple;
//
//     template <std::size_t... fwd_indicies, std::size_t... tuple_indicies>
//     struct concat_with_fwd_tuple<std::index_sequence<fwd_indicies...>,
//                                  std::index_sequence<tuple_indicies...>> {
//
//         template <typename FWD_TUPLE, typename TUPLE>
//         static constexpr auto concat(FWD_TUPLE &&fwd, TUPLE &&t) {
//             // return std::forward_as_tuple(
//             // return adv_meta_programming::forward_as_tuple(
//             return tuple_cat_result<FWD_TUPLE, TUPLE>{
//                 get<fwd_indicies>(std::forward<FWD_TUPLE>(fwd))...,
//                 get<tuple_indicies>(std::forward<TUPLE>(t))...};
//         }
//     };
//
//     template <typename INDEX_SEQ> struct make_tuple_from_fwd_tuple;
//
//     template <std::size_t... indicies>
//     struct make_tuple_from_fwd_tuple<std::index_sequence<indicies...>> {
//         template <typename FWD_TUPLE>
//         static constexpr auto make(FWD_TUPLE &&fwd) {
//             return Tuple{get<indicies>(std::forward<FWD_TUPLE>(fwd))...};
//         }
//     };
// };

// tuple_cat_result is to refer the cat result type, is the key to support
// reference type element in tuple.
template <typename... TUPLES> struct tuple_cat_result;
template <typename TUPLE> struct tuple_cat_result<TUPLE> {
    using type = TUPLE;
};
template <template <typename...> typename TUPLE, typename... ELEMS1,
          typename... ELEMS2, typename... TUPLES>
struct tuple_cat_result<TUPLE<ELEMS1...>, TUPLE<ELEMS2...>, TUPLES...>
    : tuple_cat_result<TUPLE<ELEMS1..., ELEMS2...>, TUPLES...> {};

template <typename... TUPLES>
using tuple_cat_result_t = typename tuple_cat_result<TUPLES...>::type;

template <typename TUPLE_CAT_RESULT_T> struct tuple_cat_impl {
    template <typename FWD_TUPLE, typename TUPLE, typename... TUPLES>
    static constexpr auto f(FWD_TUPLE &&ret, TUPLE &&t, TUPLES &&...tuples) {
        return f(concat_with_fwd_tuple<
                     std::make_index_sequence<
                         tuple_size_v<std::remove_cvref_t<FWD_TUPLE>>>,
                     std::make_index_sequence<tuple_size_v<std::remove_cvref_t<
                         TUPLE>>>>::concat(std::forward<FWD_TUPLE>(ret),
                                           std::forward<TUPLE>(t)),
                 std::forward<TUPLES>(tuples)...);
    }

    template <typename FWD_TUPLE> static constexpr auto f(FWD_TUPLE &&ret) {
        return make_tuple_from_fwd_tuple<
            TUPLE_CAT_RESULT_T,
            std::make_index_sequence<tuple_size_v<FWD_TUPLE>>>::
            make(std::forward<FWD_TUPLE>(ret));
    }

    template <typename FWD_INDEX_SEQ, typename TUPLE_INDEX_SEQ>
    struct concat_with_fwd_tuple;

    template <std::size_t... fwd_indicies, std::size_t... tuple_indicies>
    struct concat_with_fwd_tuple<std::index_sequence<fwd_indicies...>,
                                 std::index_sequence<tuple_indicies...>> {

        template <typename FWD_TUPLE, typename TUPLE>
        static constexpr auto concat(FWD_TUPLE &&fwd, TUPLE &&t) {
            return adv_meta_programming::forward_as_tuple(
                get<fwd_indicies>(std::forward<FWD_TUPLE>(fwd))...,
                get<tuple_indicies>(std::forward<TUPLE>(t))...);
        }
    };

    template <typename RESULT_TUPLE, typename INDEX_SEQ>
    struct make_tuple_from_fwd_tuple;

    template <typename RESULT_TUPLE, std::size_t... indicies>
    struct make_tuple_from_fwd_tuple<RESULT_TUPLE,
                                     std::index_sequence<indicies...>> {
        template <typename FWD_TUPLE>
        static constexpr auto make(FWD_TUPLE &&fwd) {
            return RESULT_TUPLE{get<indicies>(std::forward<FWD_TUPLE>(fwd))...};
        }
    };
};
} // namespace detail

// template <typename... TUPLES> constexpr auto tuple_cat(TUPLES &&...tuples) {
//     return detail::tuple_cat_impl::template
//     f(std::forward<TUPLES>(tuples)...);
//     // return detail::tuple_cat_impl::template f(tuples...); //make tuple_cat
//     // test fail
// }

//  support to reference type element in tuple
template <typename... TUPLES> constexpr auto tuple_cat(TUPLES &&...tuples) {
    return detail::tuple_cat_impl<
        detail::tuple_cat_result_t<std::remove_cvref_t<TUPLES>...>>::
        template f(std::forward<TUPLES>(tuples)...);
}

void do_tuple_cat_test() {

    Tuple t1{8, true};
    Tuple t2{3.5, std::string{"hello"}};
    auto t1_2 = tuple_cat(
        t1,
        t2); // t1_2 =
             // Tuple<int,bool,double,std::string>(8,true,3.5,"hello");
    assert(tuple_size_v<decltype(t1_2)> == 4);
    assert(get<0>(t1_2) == 8);
    assert(get<3>(t1_2) == "hello");
}

void test_framwork_use() {
    // TestUtilities is just a simple test framework so that we do not
    // involve any third-party libraries for serious project, do not use it,
    // use available mature framework such as Gtest
    constexpr std::size_t boq_tuple = 1;
    constexpr std::size_t std_tuple = 2;
    namespace boq = bits_of_q;
    using boq::testing::Tester;
    using boq::testing::TesterWithBuilder;

    // check if tuple construction takes the same construct,copies,moves as
    // std library std::tuple
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
    // builder will create 4 types of Tuple, Tuple&, Tuple const&, Tuple&&,
    // Tuple const&& and the test will be ran for 4 times
    TesterWithBuilder<1>::test("bulder demo", [](auto &&builder) {
        auto &&t1 = builder.build(Tuple{42, true});
        std::cerr << "built:" << helpers::type_name<decltype(t1)>()
                  << "\n"; // 4 print
    });

    // 每个t有四种类型:&, const&, &&, const&&.
    // 每个test中有两个t, 进行组合，最终就是4*4种组合:(&, &), (&, const&),
    // ....
    TesterWithBuilder<2>::test("builder demo2", [](auto &&builder) {
        auto &&[t1, t2] = builder.build(Tuple{42, true}, Tuple{1.5});
        std::cerr << "built:" << helpers::type_name<decltype(t1)>() << "\t\t\t"
                  << helpers::type_name<decltype(t2)>()
                  << "\n"; // 16 print, foreach t, it will create 4, then
                           // combine mix,4^2
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
} // namespace adv_meta_programming
#endif //__ADV_META_ALGORITHM__