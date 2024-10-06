#ifndef __HELPERS__
#define __HELPERS__
#include <cxxabi.h>
#include <string>
#include <type_traits>
#include <typeinfo>

namespace helpers {

template <bool, typename THEN, typename ELSE> struct if_;

template <typename THEN, typename ELSE> struct if_<true, THEN, ELSE> {
    using type = THEN;
};
template <typename THEN, typename ELSE> struct if_<false, THEN, ELSE> {
    using type = ELSE;
};

// to get the deduced type info,
// better solution is to use boost,
// type_id_with_cvr<decltype<T>>().pretty_name()
// or check it using compiler error: declare an template struct, no
// implementation.template<typename T> struct showtype;
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
} // namespace helpers
#endif //__HELPERS__