#ifndef __INITIAL_DEMO
#define __INITIAL_DEMO
#include <initializer_list>
#include <vector>

namespace InitDemo {
    class MyVec{
        public:
            //initializer_list as a constructor parameter
            MyVec(const std::initializer_list<int>& v) {
                for(std::initializer_list<int>::iterator it = v.begin(); it !=v.end(); it++) {
                    m_vec.push_back(*it);
                }
            }
    private:
        std::vector<int> m_vec;
    };
}
#endif// __INITIAL_DEMO