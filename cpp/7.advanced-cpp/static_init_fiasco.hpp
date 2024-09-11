#ifndef __STATIC_INIT_FIASCO
#define __STATIC_INIT_FIASCO
#include "cat.hpp"
#include "dog.hpp"
#include "singleton.hpp"

namespace STATIC_INIT_FIASCO {
//Dog d("Gunner");
void do_test() {
    //d.bark();
    Singtone::getDog().bark();
}
}
#endif //__STATIC_INIT_FIASCO
