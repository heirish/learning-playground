#ifndef __STREAM_TEST__
#define __STREAM_TEST__
#include <iostream>
#include <fstream>
#include <bitset>
#include <complex>

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

}
}
#endif //__STREAM_TEST__