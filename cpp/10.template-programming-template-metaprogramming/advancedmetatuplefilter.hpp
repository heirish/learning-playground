#ifndef __TUP_FILTER__
#define __TUP_FILTER__
#include "TestUtilities.h"
#include "advancedmetatuple.hpp"
#include "advancedmetatuplecat.hpp"
#include "advancedmetatupletransform.hpp"
#include "helpers.hpp"
#include <type_traits>
#include <utility>

namespace adv_meta_programming {
template <typename TUPLE, std::size_t index>
using tuple_element_t = typename meta_typelist_lib::at<TUPLE, index>::type;

namespace detail {
template <typename TUPLE, template <typename...> typename PREDICATE>
struct filter_result;

template <template <typename...> typename TUPLE, typename... ELEMS,
          template <typename...> typename PREDICATE>
struct filter_result<TUPLE<ELEMS...>, PREDICATE> {
    template <typename ELEM> struct element_match {
        using type =
            helpers::if_<PREDICATE<ELEM>::value, TUPLE<ELEM>, TUPLE<>>::type;
    };
    using type = tuple_cat_result_t<typename element_match<ELEMS>::type...>;
};

template <typename TUPLE, template <typename...> typename PREDICATE>
using filter_result_t = filter_result<TUPLE, PREDICATE>::type;

// template <typename TUP, std::size_t... indicies>
// constexpr auto cat_tuple_content(TUP &&tup, std::index_sequence<indicies...>)
// {
//     return tuple_cat(get<indicies>(std::forward<TUP>(tup))...);
// }

/////// support reference element type///////////////
template <typename RESULT_TYPE, typename TUP, std::size_t... indicies>
constexpr auto cat_tuple_content(TUP &&tup, std::index_sequence<indicies...>) {
    return detail::tuple_cat_impl<RESULT_TYPE>::template f(
        get<indicies>(std::forward<TUP>(tup))...);
}

template <template <typename...> typename PREDICATE, typename TUP,
          std::size_t... indicies>
constexpr auto pred_matches(TUP &&tup, std::index_sequence<indicies...>) {
    auto do_match = [](TUP &&tup, auto i) {
        if constexpr (PREDICATE<tuple_element_t<std::remove_cvref_t<TUP>,
                                                i.value>>::value) {
            return forward_as_tuple(get<i.value>(std::forward<TUP>(tup)));
        } else {
            return Tuple<>{};
        }
    };
    return Tuple{do_match(std::forward<TUP>(tup),
                          std::integral_constant<std::size_t, indicies>{})...};
}

} // namespace detail
/*
template <template <typename...> typename PREDICATE, typename TUP>
constexpr auto filter(TUP &&tup) {
    // 这里wrap_if_pred_matches, transfer tuple element as a forwarding
    // reference, since forwarding reference always deduced to a reference type
    // so there's no way for this lambda to distinguish between an element
    // between an lvalue or lvalue reference
    // 可以查看typededuction.md中的表格，当参数为T&&时，传入lvalue(A)与lvalue
    // reference(A&)都会被deduce成A&
    auto wrap_if_pred_matches = [&]<typename ELEM>(ELEM &&e) {
        if constexpr (PREDICATE<std::remove_cvref_t<ELEM>>::value) {
            // return Tuple{std::forward<ELEM>(e)};//cause unnecessary move
            return forward_as_tuple(std::forward<ELEM>(e));
        } else {
            // return Tuple<>{};
            return forward_as_tuple();
        }
    };

    auto wrap_tup = transform(std::forward<TUP>(tup), wrap_if_pred_matches);
    // example: Tuple<Tuple<int>, Tuple<>, Tuple<unsigned int>, Tuple<>>
    return detail::cat_tuple_content(
        std::move(wrap_tup),
        std::make_index_sequence<tuple_size_v<std::remove_cvref_t<TUP>>>{});
    // example: Tuple<int, unsigned int>
}
*/

/////// support reference element type///////////////
template <template <typename...> typename PREDICATE, typename TUP>
constexpr auto filter(TUP &&tup) {
    // 解决match时的reference element type问题
    auto wrap_tup = detail::pred_matches<PREDICATE>(
        std::forward<TUP>(tup),
        std::make_index_sequence<tuple_size_v<std::remove_cvref_t<TUP>>>{});
    // example: Tuple<Tuple<int>, Tuple<>, Tuple<unsigned int>, Tuple<>>

    // 解决cat时的reference element type问题
    return detail::cat_tuple_content<
        detail::filter_result_t<std::remove_cvref_t<TUP>, PREDICATE>>(
        std::move(wrap_tup),
        std::make_index_sequence<tuple_size_v<std::remove_cvref_t<TUP>>>{});
    // example: Tuple<int, unsigned int>
}

void do_tuple_filter_test() {
    constexpr std::size_t boq_tuple = 1;
    constexpr std::size_t std_tuple = 2;
    namespace boq = bits_of_q;
    using boq::testing::Tester;
    using boq::testing::TesterWithBuilder;

    TesterWithBuilder<1>::test("tuple_filter test", [](auto &&builder) {
        auto c = boq::make_copy_counter<boq_tuple>();
        auto &&tup = builder.build(Tuple{42, 2.3F, c, 3.4, 12U});
        c.reset();

        auto tup2 = filter<std::is_integral>(std::forward<decltype(tup)>(tup));
        static_assert(std::is_same_v<std::remove_cvref_t<decltype(tup2)>,
                                     Tuple<int, unsigned int>>);
        ASSERT_EQ(get<0>(tup2), 42);
        ASSERT_EQ(get<1>(tup2), 12U);
        ASSERT_EQ(c.stats, (boq::CopyStats{0, 0, 0}));
    });

    // check how many copies, moves for those elements left in tuple
    TesterWithBuilder<1>::test("tuple_filter test2", [](auto &&builder) {
        auto c = boq::make_copy_counter<boq_tuple>();
        static constexpr std::size_t ref_tuple = 3;
        auto c1 = boq::make_copy_counter<ref_tuple>();

        auto &&tup = builder.build(Tuple{42, 2.3F, c, 3.4, 12U});
        auto &&tup_ref = builder.build(Tuple{42, 2.3F, c1, 3.4, 12U});

        auto tup2 = filter<boq::not_<std::is_integral>::type>(
            std::forward<decltype(tup)>(tup));
        auto ref_tup2 = std::forward<decltype(tup_ref)>(tup_ref);

        static_assert(
            std::is_same_v<
                std::remove_cvref_t<decltype(tup2)>,
                Tuple<float, boq::IndexedCopyCounter<boq_tuple>, double>>);
        ASSERT_EQ(get<0>(tup2), 2.3F);
        ASSERT_EQ(get<1>(tup2),
                  get<2>(ref_tup2)); // check if assigning an element is just
                                     // efficient as assigning an element when
                                     // it passes the filter, such the filter
                                     // logic does not add any overhead
        ASSERT_EQ(get<2>(tup2), 3.4);
    });

    // tuple_cat, filter并沒有考慮到Tuple中的element是引用的情況
    Tester::test("tuple element with ref test", []() {
        int i = 10;
        Tuple<int, int &, int> tup{4, i, 11};

        auto tup2 = filter<std::is_reference>(tup);

        // TODO;后面的homework就是为了解决这个问题的
        static_assert(
            std::is_same_v<decltype(tup2), Tuple<int &>>); // assert fail
    });

    // Homework step 1: Update filter so the predicate is executed with the
    // correct type. In the current implementation we use the transform function
    // to pass the elements to a lambda. This has the inherent problem that the
    // lambda is unable to distinguish whether the element type is a value or a
    // lvalue reference.
    //
    // Hint: add a tuple_element_t alias using the at function from
    // Metaprogramming.h. Instead of using transform, create a similar function
    // that executes the predicate on the tuple_element_t at each index instead
    // of using the decltype of the passed element.
    // heirish: to test if match accept reference type
    Tester::test("tuple_filter_pred_passed_correct_types", []() {
        int i = 10;
        Tuple<int, int &, int> tup{4, i, 11};

        auto tup2 = filter<boq::not_<std::is_reference>::type>(
            std::forward<decltype(tup)>(tup));
        // static_assert(std::is_same_v<decltype(tup2), Tuple<int, int>>);
        std::cout << helpers::type_name<decltype(tup2)>() << std::endl;
        ASSERT((std::is_same_v<decltype(tup2), Tuple<int, int>>));
    });

    // Homework: step 2. Create a tuple_cat_result_t metafunction in the detail
    // namespace to help to determine the expected output type of a tuple_cat
    // operation on two tuples Hint: This is similar to the push_back operation
    // from Metaprogramming.h, only difference is that we "push_back" the
    // elements of the second tuple, not the whole tuple
    Tester::test("tuple_cat_result_2_inputs", []() {
        static_assert(
            std::is_same_v<detail::tuple_cat_result_t<Tuple<int, int &, int>,
                                                      Tuple<int &&>>,
                           Tuple<int, int &, int, int &&>>);
    });

    // Homework: step 3. Update tuple_cat_result_t metafunction to handle more
    // than 2 inputs Hint: Recursion should do the trick
    Tester::test("tuple_cat_result", []() {
        static_assert(
            std::is_same_v<detail::tuple_cat_result_t<Tuple<double &, double>,
                                                      Tuple<int, int &, int>,
                                                      Tuple<int &&>>,
                           Tuple<double &, double, int, int &, int, int &&>>);
    });

    // Homework: step 4. Make tuple_cat work with references.
    // The test below tests the concatenation of tuples with lvalue and rvalue
    // references. Current implementation ignores these references and will
    // create an output tuple with normal integers. std::tuple_cat is included
    // for reference so you can compare the expected outcome. Hint: use the
    // tuple_cat_result_t metafunction to ensure the return type of
    // make_tuple_from_fwd_tuple is correct Note: some filter tests may start
    // failing after updating tuple_cat to correctly handle references. This is
    // expected as the current filter implementation implicitly assumes that
    // tuple_cat strips references from the element type. You may want to
    // temporarily comment out the failing filter tests. We will re-enable them
    // in step 5
    Tester::test("tuple_cat_with_refs", []() {
        int i = 10;
        int j = 11;
        Tuple<int, int &, int> tup{4, i, 11};
        Tuple<int &&> tup2{std::move(j)};
        int j2 = 11;
        std::tuple<int, int &, int> stup{4, i, 11};
        std::tuple<int &&> stup2{std::move(j2)};

        auto t1_2 = tuple_cat(std::move(tup), std::move(tup2));
        auto st1_2 = std::tuple_cat(std::move(stup), std::move(stup2));

        static_assert(
            std::is_same_v<decltype(t1_2), Tuple<int, int &, int, int &&>>);
        static_assert(std::is_same_v<decltype(st1_2),
                                     std::tuple<int, int &, int, int &&>>);
        ASSERT(
            (std::is_same_v<decltype(t1_2), Tuple<int, int &, int, int &&>>));
        ASSERT((std::is_same_v<decltype(st1_2),
                               std::tuple<int, int &, int, int &&>>));
    });

    // Homework step5:
    // In order to make filter work correctly with reference type elements,
    // introduce a tuple_result_t metafunction in the detail namespace earlier
    // changes to execute predicate on correct type. Hint: you can use a similar
    // approach as in the current filter implementation when building the result
    // type: Wrapping element types that pass the filter into a tuple type and
    // inserting empty tuples for those that don't (use if_ from
    // Metaprogramming.h). Then pass that type to the tuple_cat_result_t
    // metafunction created in step 2.
    Tester::test("filter_result", []() {
        static_assert(
            std::is_same_v<detail::filter_result_t<Tuple<int, double, unsigned>,
                                                   std::is_integral>,
                           Tuple<int, unsigned>>);
        static_assert(
            std::is_same_v<detail::filter_result_t<Tuple<int, int &, int &&>,
                                                   std::is_reference>,
                           Tuple<int &, int &&>>);
    });

    // Homework step6: Make filter compatible with refences using the now
    // reference-compatible tuple_cat function and the filter_result_t
    // metafunction from step 5. Hint: Update detail::tuple_cat_content to
    // directly use tuple_cat_impl with the correct result tuple type. Note: if
    // you commented out some of the filter tests in step 4, make sure to
    // re-enable them. They should now pass.
    Tester::test("tuple_filter_with_refs", []() {
        int i = 10;
        Tuple<int, int &, int> tup{4, i, 11};

        auto tup2 = filter<boq::not_<std::is_reference>::type>(
            std::forward<decltype(tup)>(tup));
        static_assert(std::is_same_v<decltype(tup2), Tuple<int, int>>);
        ASSERT((std::is_same_v<decltype(tup2), Tuple<int, int>>));

        auto tup3 = filter<std::is_reference>(std::forward<decltype(tup)>(tup));
        static_assert(std::is_same_v<decltype(tup3), Tuple<int &>>);
        ASSERT((std::is_same_v<decltype(tup3), Tuple<int &>>));
    });
}
} // namespace adv_meta_programming
#endif //__TUP_FILTER__