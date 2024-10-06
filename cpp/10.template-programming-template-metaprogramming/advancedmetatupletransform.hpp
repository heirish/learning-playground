#ifndef __TUPLE_TRANS__
#define __TUPLE_TRANS__
#include "TestUtilities.h"
#include "advancedmetatuple.hpp"
#include <utility>

namespace adv_meta_programming {

namespace detail {
template <typename TUP, typename FUNC, std::size_t... indicies>
constexpr auto transform_impl(TUP &&tup, const FUNC &func,
                              std::index_sequence<indicies...>) {
    return Tuple{func(get<indicies>(std::forward<TUP>(tup)))...};
}

}; // namespace detail

template <typename TUP, typename FUNC>
constexpr auto transform(TUP &&tup, const FUNC &func) {
    return detail::transform_impl(
        std::forward<TUP>(tup), func,
        std::make_index_sequence<tuple_size_v<std::remove_cvref_t<TUP>>>{});
}

void do_tuple_transform_test() {
    constexpr std::size_t boq_tuple = 1;
    constexpr std::size_t std_tuple = 2;
    namespace boq = bits_of_q;
    using boq::testing::Tester;
    using boq::testing::TesterWithBuilder;

    TesterWithBuilder<1>::test("tuple_transform", [](auto &&builder) {
        auto c = boq::make_copy_counter<boq_tuple>();
        auto &&tuple = builder.build(Tuple{42, c, 12U, 2.1f});
        c.reset();

        auto tup2 = transform(
            std::forward<decltype(tuple)>(tuple), [&c]<typename T>(T &&t) {
                constexpr bool is_integral =
                    std::is_integral_v<std::remove_cvref_t<T>>;
                constexpr bool is_copy_counter =
                    std::is_same_v<decltype(c), std::remove_cvref_t<T>>;
                if constexpr (is_integral) {
                    return int(t) + 2;
                } else if constexpr (is_copy_counter) {
                    return t.stats;
                } else {
                    return t;
                }
            });
        static_assert(std::is_same_v<decltype(tup2),
                                     Tuple<int, boq::CopyStats, int, float>>);
        ASSERT_EQ(get<0>(tup2), 44);
        ASSERT_EQ(get<1>(tup2), (boq::CopyStats{0, 0, 0}));
        ASSERT_EQ(get<2>(tup2), 14);
        ASSERT_EQ(get<3>(tup2), 2.1f);
    });
    // Tuple<int, CopyCounter, unsigned int> => Tuple<int, CopyStats, int>
}
} // namespace adv_meta_programming
#endif //__TUPLE_TRANS__