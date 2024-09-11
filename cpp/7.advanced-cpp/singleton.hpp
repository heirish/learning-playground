#ifndef __singleton__
#define __singleton__
#include "cat.hpp"
#include "dog.hpp"
namespace STATIC_INIT_FIASCO {
class Singtone {
public:
    static Dog& getDog() {
        static Dog d("Gunner");
        return d;
    }
    static Cat& getCat() {
        static Cat c("Tom");
        return c;
    }
};
}
#endif //__singleton__