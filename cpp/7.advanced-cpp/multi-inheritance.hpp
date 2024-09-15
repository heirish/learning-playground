#ifndef __MULTI_INHERITANCE__
#define __MULTI_INHERITANCE__
#include <string>

namespace MULTI_INHERITANCE {
/*
*               File
                /   \
        InputFile   OutputFile
                \   /
                IOFile
*/
class File {
public:
    explicit File(const std::string& name):_name(name){}
    void open(){}
private:
    std::string _name;
};
class InputFile:virtual public File {
public:
    explicit InputFile(const std::string& name):File(name){}
};
class OutputFile:virtual public File{
public:
    explicit OutputFile(const std::string& name):File(name){}
};
class IOFile:public InputFile, public OutputFile{
    //Diamond shape of heiritance
public:
    explicit IOFile(const std::string& name):InputFile(name), OutputFile(name),File(name) { //awkward:the most derived class is responsible for initializing the virtual base class

    }
};

class OutputFileI{
public:
    virtual void open() = 0;
    virtual void write() = 0;
};
class InputFileI{
public:
    virtual void open() = 0;
    virtual void read() = 0;
};
class IOFileS:public OutputFileI, public InputFileI {
public: 
    explicit IOFileS(const std::string& name):_name(name){}
    virtual void open() override {}
    virtual void read() override {}
    virtual void write() override {}
private:
    std::string _name;
};
void do_test() {
    IOFile file("myfile.txt");
    file.open(); //will compile if InputFile/OutputFile virtual derived from File
    //file.InputFile::open(); //can also compile without virtual derive
    //file.OutputFile::open();

    //solution: PCAs
    IOFileS file1("myfile.txt");
    file.open();

}
}
#endif //__MULTI_INHERITANCE__