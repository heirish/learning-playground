#ifndef __LOGFILE__
#define __LOGFILE__
#include <fstream>
#include <mutex>
#include <string>
#include <iostream>
#include <thread>

namespace LAZY_INIT{
class LogFile {
public:
    explicit LogFile(const std::string& filename):_filename(filename) {}
    ~LogFile() {
        if (_f.is_open()) {
            _f.close();
        }
    }
    void shared_print(const std::string& id, int value) {
        std::call_once(_once_flag, [&](){
            _f.open(_filename);
        });
        std::lock_guard<std::mutex> lock(_mutex);
        _f << "From " << id << ":" << value << std::endl;
    }
private:
    std::string _filename{"log.txt"};
    std::ofstream _f;
    std::mutex _mutex;
    std::once_flag _once_flag;
};

void test_lazy_intialization();
}
#endif //__LOGFILE__