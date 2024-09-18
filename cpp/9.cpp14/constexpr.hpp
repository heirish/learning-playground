#ifndef __CONSTEXPR__
#define __CONSTEXPR__
namespace CONSTEXPR {
constexpr int computeSomething(int mX) {
    int result{mX};
    for(int i{0}; i<10; ++i) {
        result += i;
    }

    if (result > 5) result += 10;
    return result;
}
template <int TValue> 
struct Test{};

void do_test() {
    //Compiles
    Test<computeSomething(10)> instance;
}
}
#endif //__CONSTEXPR__
