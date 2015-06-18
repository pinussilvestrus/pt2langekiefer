
#include <cassert>
#include <iostream>
#include <string>
#include <cstddef>
#include <vector>
#include <cstring>
#include <cmath>


static const auto N = 4;

auto A = std::vector<int>(); /// saves current discs in A...
auto B = std::vector<int>();
auto C = std::vector<int>();


void print()
{
    #ifdef _WIN32
    std::system("cls");
    #else
    std::system("clear");
    #endif

    //TODO 6.2
	//print state
    
    // check which discs A,B and C has, print the specific discs above the plateau (biggest at the bottom)
    
    
    for(auto i = A.size() - 1; A.size() > i; --i) { // iterate backwards so that the biggest disc is at the bottom
        if (A[i] == 1) std::cout << std::endl << "     ###      " << std::endl;
        if (A[i] == 2) std::cout << std::endl << "    #####     " << std::endl;
        if (A[i] == 3) std::cout << std::endl << "   #######    " << std::endl;
        if (A[i] == 4) std::cout << std::endl << "  #########   " << std::endl;
    }
    
    // plateau for A
    std::cout << "######A#######" << std::endl; // my terminal does not support extended ascii :(
    
    for(auto i = B.size() - 1; B.size() > i; --i) { // iterate backwards so that the biggest disc is at the bottom
        if (B[i] == 1) std::cout << std::endl << "     ###     " << std::endl;
        if (B[i] == 2) std::cout << std::endl << "    #####    " << std::endl;
        if (B[i] == 3) std::cout << std::endl << "   #######   " << std::endl;
        if (B[i] == 4) std::cout << std::endl << "  #########  " << std::endl;
    }
    
    std::cout << "######B#######" << std::endl;

    
    for(auto i = C.size() - 1; C.size() > i; --i) { // iterate backwards so that the biggest disc is at the bottom
        if (C[i] == 1) std::cout << std::endl << "     ###     " << std::endl;
        if (C[i] == 2) std::cout << std::endl << "    #####    " << std::endl;
        if (C[i] == 3) std::cout << std::endl << "   #######   " << std::endl;
        if (C[i] == 4) std::cout << std::endl << "  #########  " << std::endl;
    }
    
    std::cout << "######C#######" << std::endl;
    
    //todo: print all next to each other
    
    
}

void ToH(const int n, const int a, const int b, const int c, int & moves) 
{
    //TODO 6.2
	//Implement Towers of Hanoi and print
    
    if (n == 1) {
        // move disc from a directly to c (no auxiliary stapel required)
        moves++;

        //todo: move last element from old to new, sort both, so that biggest is on first
        
        char oldPlat = (char)('A' + a);
        char newPlat = (char)('A' + c);
        
        switch (oldPlat) {
            case 'A': if (newPlat=='B') {
                    B.push_back(A.back()); // move last from A to B
                    std::sort(B.begin(),B.end(), std::greater<int>());
                    A.erase(A.end()-1); // delete last
                }
                else {
                    C.push_back(A.back());
                    std::sort(C.begin(),C.end(), std::greater<int>());
                    A.erase(A.end()-1);
                } break;
            case 'B': if (newPlat=='A') {
                    A.push_back(B.back());
                    std::sort(A.begin(),A.end(), std::greater<int>());
                    B.erase(B.end()-1);
                }
                else {
                    C.push_back(B.back());
                    std::sort(C.begin(),C.end(), std::greater<int>());
                    B.erase(B.end()-1);
                } break;
            case 'C': if (newPlat=='A') {
                    A.push_back(C.back());
                    std::sort(A.begin(),A.end(), std::greater<int>());
                    C.erase(C.end()-1);
                }
                else {
                    B.push_back(C.back());
                    std::sort(B.begin(),B.end(), std::greater<int>());
                    C.erase(C.end()-1);
                } break;
            }
        
        print();
        std::cout << "Move " << oldPlat << " -> " << newPlat << std::endl;
        getchar();
    }
    else {
        ToH(n-1, a, c, b, moves); //move n-1 stapel of a to stapel b
        ToH(1, a, b, c, moves); // move remaining disc of a to c
        ToH(n - 1, b, a, c, moves); // move n-1 stapel b to stapel c
    }
   
}

int main(int argc, char ** argv) 
{
    int moves = 0;

    for (int i = N; i > 0; --i)
        A.push_back(i); // A = {4,3,2,1} => A have all {N=4} discs

	print();
	getchar();
    ToH(N, 0, 1, 2, moves);
    std::cout << "minimal number of moves: " << moves << std::endl;

	getchar();
    return 0;
}
