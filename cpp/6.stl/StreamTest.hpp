#ifndef __STREAM_TEST__
#define __STREAM_TEST__
#include <iostream>
#include <fstream>
#include <bitset>
#include <complex>
#include <iomanip>
#include <sstream>

//advantage of stream class
//IO Operation two steps:
//1.formatting the data, stream class provides a common api to format the data
//2.communicating the data with external devices(iostream -->stdin/stdout, fstream--->file)
//Software Engineer Principle: low coupling -> reusability
namespace STREAM_TEST {
void iostream_test() {
    std::cout << "Hello" << std::endl;
    //cout: a global object of ostream(typedef basic_ostream<char> ostream;)
    //<<: ostream& ostream::operator<<(string v);
    //endl: '\n' + flush
}

void ftream_test() {
    {
        std::ofstream of("mylog.txt"); //create a new file for write, if the file didn't exist
        //file is open when of is constructed, close when of is destructed, RAII
        of << "Experience is the moth of wisdom"<< std::endl;
        of << 234 << std::endl;
        of << 2.3 << std::endl;
        of << std::bitset<8>(14) << std::endl; //00001110
        of << std::complex<int>(2,3) << std::endl; //(2,3)
    }

    {
        //std::ofstream of("mylog.txt"); //open file for write, clean the content of the file
        std::ofstream of("mylog.txt", std::ofstream::app); //open file for write, move the output pointer to the end of the file
        of << "Honey is the best policy" << std::endl;
    }
 
    {
        std::ofstream of("mylog.txt", std::ofstream::in | std::ofstream::out); //open file for write, move the output pointer to the end of the file
        of.seekp(10, std::ios::beg); //move the output pointer to 10 chars after begin
        of << "12345";//overrite 5 chars
        of.seekp(-5, std::ios::end); //move the output pointer 5 chars before end
        of << "Nothing ventured, nothing gained." << std::endl; 
        of.seekp(-5, std::ios::cur); //move the output pointer 5 chars before current position
    }

    {
        std::ifstream inf("mylog.txt");
        int i;
        //will fail
        inf  >> i; //read one word from the file, and parse it as an integer and save it into i

        //for input stream, we need to handle the errors
        //handle the errors with state bit
        //goodbit, badbit, failbit, eofbit 
        std::cout << "read a integer word from file failed?" << inf.fail() << std::endl;
        inf.good(); //everything is OK(goodbit== 1)
        inf.bad(); //unrecoverable error (badbit== 1)
        inf.fail(); //failed stream operatrion (failbit == 1 badbit== 1)
        inf.eof(); //end of file (eofbit == 1)
        inf.clear(); //clear all the error status and move on, equivalent to clearn(std::ios::goodbit)
        inf.clear(std::ios::badbit); //set a new value to the error flag, info.bad() == true
        inf.rdstate(); //read the current status flag
        inf.clear(inf.rdstate() & ~std::ios::failbit); //clean only the failbit

        if (inf) { //equivalent to: if(!inf.fail())
            std::cout << "Read successfully" << std::endl;
        }

        //Handle the errors with exceptions
        inf.clear();
        //setting the exception mask, if badbit or failbit set to 1, will throw exception ios::failure
        //eofbit set to 1, will not throw exception
        inf.exceptions(std::ios::badbit | std::ios::failbit); 
        //inf.exceptions(std::ios::goodbit);  //exception mask clear, will not throw exception
        if (inf >> i) {
            std::cout << "Read successfully" << std::endl;
        }

    }
}    

void iofromatting_test() {
    int i = 34;
    std::cout << "十进制:" << i << std::endl; //34, 十进制
    std::cout.setf(std::ios::oct, std::ios::basefield); 
    std::cout << "八进制:" << i << std::endl; //42
    std::cout.setf(std::ios::showbase); //显示进制前缀
    std::cout << "八进制带前缀:" << i << std::endl; //042
    std::cout.setf(std::ios::hex, std::ios::basefield); 
    std::cout << "十六进制带前缀:" << i << std::endl; //0x22
    std::cout.unsetf(std::ios::showbase); //不再显示进制前缀
    std::cout << i << std::endl; //22

    std::cout.width(10);
    std::cout.setf(std::ios::dec, std::ios::basefield); 
    std::cout << i << std::endl; //         34, 右对齐，10个字符宽 
    std::cout.setf(std::ios::left, std::ios::adjustfield); //左对齐
    std::cout << i << "," << std::endl; //34, 左对齐

    //floating point value
    float j = 340.1;
    std::cout.setf(std::ios::scientific, std::ios::floatfield);
    std::cout << j << std::endl; //3.401000e+002
    std::cout.setf(std::ios::fixed, std::ios::floatfield);
    std::cout << j << std::endl; //340.100000
    std::cout.precision(3);
    std::cout << j << std::endl; //340.100

    //can also set formatting for input
    int x;
    std::cin.setf(std::ios::hex, std::ios::basefield);
    std::cin >> x; //input 12
    std::cout << x << std::endl; //18

    std::ios::fmtflags f = std::cout.flags(); //get current format settings
    std::cout << f << std::endl;
    //set formating flags; same as  std::cout.setf(std::ios::oct, std::ios::basefield); std::cout.setf(std::ios::showbase); //显示进制前缀
    std::cout.flags(std::ios::oct | std::ios::showbase); 

    //member functions for unformatted IO:they will handle the input/output data as raw text
    char buf[80];
    {
        //input
        std::ifstream inf("mylog.txt");
        inf.read(buf, 80); //read up to 80 chars and save into buf
        inf.getline(buf, 80); //read up to 80 chars or until '\n'
        inf.ignore(3); //ignore next 3 chars in the the stream
        inf.peek(); //ignore the char on top of the stream
        inf.unget(); //return a char back to the stream which you just read, do not mix it with inf.putback('z'); which can change the return char to a different value
        inf.get();
        inf.gcount(); //return the number of chars being read by last unformatted read
    }

    {
        //output
        std::ofstream of("mylog.txt");
        of.put('c');//put 1 char to the stream
        of.write(buf, 6); //write the first 6 chars of buf to the stream
        of.flush(); //flush the output
    }
}

//操作stream的外部函数, 大部份功能与直接调用stream.func()一样
//如std::cout << std::setw(8) <==> std::cout.width(8);
//std::cout << std::left <==> std::cout.setf(std::ios::left, std::ios::adjustfield);
//std::cout << std::hex <==> std::cout.setf(std::ios::hex, std::ios::basefield);
//std::cout << std::showbase <==> std::cout.setf(std::ios::showbase);
void manipulators_test() {
    std::cout << "Hello" << std::endl; //endl, put '\n' to stream and flush
    std::cout << std::ends; //'\0'
    std::cout << std::flush; //flush the stream
    std::cin >> std::ws; //read and discard white spaces;

    std::cout << std::setw(8) << std::left << std::setfill('_') << 99 << std::endl; //99______
    std::cout << std::hex << std::showbase << 14 << std::endl; //0xe
    //more manipulators see head <iomanip>
}

//stream buffer is responsible for communicating data to external devices
void streambuffer_test() {
    std::cout << 34;
    std::streambuf* pbuf = std::cout.rdbuf(); //to get a pointer to the internal buffer of std::cout

    std::ostream myCout(pbuf); //another ostream has the same stream buffer as std::cout, which means they have the same transferring channel
    myCout << 34 << std::endl; //print 34 to standard output device
    myCout.setf(std::ios::showpos); //change formating of myCout, 只会作用在myCout上，对std::cout的formatting无影响
    myCout << 34 << std::endl; //+34
    std::cout << 34 << std::endl; //34

    //Redirecting
    std::ofstream of("mylog.txt");
    std::streambuf* origbuf = std::cout.rdbuf();
    std::cout.rdbuf(of.rdbuf());
    std::cout << "Hello" << std::endl; //mylog.txt has hello;
    //restore
    std::cout.rdbuf(origbuf);
    std::cout << "Goodbye" << std::endl; //stdout print Goodbye

    //stream buffer iterator
    std::istreambuf_iterator<char> i(std::cin);
    std::ostreambuf_iterator<char> o(std::cout);
    while (*i != 'x') { //copy all input to output until char 'x'
        *o = *i;
        ++o;
        ++i;
    }
    std::cout << std::endl;
    std::cout << "do it using std::copy" << std::endl;
    //equivalent to except it does not have the terminate char 'x'
    //std::copy(std::istreambuf_iterator<char>(std::cin), std::istreambuf_iterator<char>(),
    //    std::ostreambuf_iterator<char>(std::cout));
    std::copy_if(std::istreambuf_iterator<char>(std::cin), std::istreambuf_iterator<char>(),
        std::ostreambuf_iterator<char>(std::cout), [](char c){return c != 'x';});
}

void stringstream_test() {
    int i = 89;
    std::stringstream ss;
    ss << i << " Hex: " << std::hex << i
        << " Oct: " << std::oct << i; //89 Hex: 59 Oct: 131
    std::cout << ss.str() << std::endl;

    int a,b,c;
    std::string s1;
    ss >> std::hex >> a; //formatting input works token by token. tokens serparated by spaces, tabs, newlines
    std::cout << a << std::endl; //a == 137
    ss >> s1; //Hex:
    ss >> std::dec >> b; //59
    ss.ignore(6); //ignore the next 6 chars
    ss >> std::oct >> c; //89

    //ostringstream -- formatted output
    //istringstream -- formatted input
}

struct Dog {
friend std::ostream& operator<<(std::ostream& os, const Dog& d);
friend std::istream& operator>>(std::istream& is, Dog& d);
public:
    Dog(int age, const std::string& name):_age(age), _name(name){}
private:
    int _age;
    std::string _name;
};
std::ostream& operator<<(std::ostream& os, const Dog& d) {
    os << "My name is "<< d._name << " and my age is " << d._age << std::endl;
    return os;
}
std::istream& operator>>(std::istream& is, Dog& d) {
    is >> d._name;
    is >> d._age;
    return is;
}
void streamenabled_class_test() {
    Dog d{2,"Bob"}; //Universal Initialization
    std::cout << d;
    std::cin >> d;
    std::cout << d;
}

}
#endif //__STREAM_TEST__