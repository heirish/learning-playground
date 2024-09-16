#ifndef __LCS__
#define __LCS__
#include "common.hpp"
#include <string>
#include <vector>
#include <algorithm>

namespace LCS {
void print_LCS(std::vector<std::vector<char>>& S, std::string& X, int i, int j) {
    if (i==0 || j==0) return ;

    if ('s' == S[i][j]) {
        print_LCS(S, X, i-1, j-1);
        std::cout << X[i];
    } else if ('j' == S[i][j]) {
        print_LCS(S, X, i, j-1);
    } else {
        print_LCS(S, X, i-1, j);
    }
}
void calc_LCS(std::string& X, std::string& Y) {
    std::vector<std::vector<int>> C; //Length of LCS of sequence X[1..i] and Y[1..j]
    std::vector<std::vector<char>> S; //Position of LCS
    for(int i=0; i<X.size(); i++) {
        C.push_back(std::vector<int>(Y.size(), 0));  //initialize C to a N*M matric, each entry contains 0 
        S.push_back(std::vector<char>(Y.size()));
    }

    for(int i=1; i<X.size(); i++) {
        for (int j=1; j<Y.size(); j++) {
            if (X[i] == Y[j]) {
                C[i][j] = C[i-1][j-1] + 1;
                S[i][j] = 's'; //X[i] or Y[j] is one item of LCS
            } else {
                C[i][j] = std::max(C[i][j-1], C[i-1][j]);
                if (C[i][j-1] > C[i-1][j]) {
                    S[i][j] = 'j'; //LCS(X[1..i]Y[1..j]) == LCS(X[1..i]Y[1..j-1])
                } else {
                    S[i][j] = 'i';
                }
            }
        }
    }
    std::for_each(C.begin(), C.end(), [](const std::vector<int>& vec) {
        print(vec);
    });

    print_LCS(S, X, X.size()-1, Y.size()-1);
}

void do_test() {
    std::string X = " ACCGGGTTAC"; //To simplify notation, first char will be ignored.
    std::string Y = " AGGACCA";
    std::cout << "X:" << X << std::endl;
    std::cout << "Y:" << Y << std::endl;
    calc_LCS(X, Y);
}
}
#endif //__LCS__