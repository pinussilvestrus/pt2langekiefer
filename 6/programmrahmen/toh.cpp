
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
        if (A[i] == 1) std::cout << "     ###     " << std::endl << std::endl;
        if (A[i] == 2) std::cout << "    #####    " << std::endl << std::endl;
        if (A[i] == 3) std::cout << "   #######   " << std::endl << std::endl;
        if (A[i] == 4) std::cout << "  #########  " << std::endl << std::endl;
    }
    
    for(auto i = B.size() - 1; B.size() > i; --i) { // iterate backwards so that the biggest disc is at the bottom
    }

    
    for(auto i = B.size() - 1; B.size() > i; --i) { // iterate backwards so that the biggest disc is at the bottom
    }
    
    // plateau
    std::cout << "######A#######   #######B#######   #######C#######" << std::endl; // my terminal does not support extended ascii :(
}

void ToH(const int n, const int a, const int b, const int c, int & moves) 
{
    //TODO 6.2
	//Implement Towers of Hanoi and print
    
    if (n == 1) {
        // move disc from a directly to c (no auxiliary stapel required)
        moves++;
        print();

        //todo: move last element from old to new, sort both, so that biggest is on first

        std::cout << "Move " << (char)('A' + a) << " -> " << (char)('A' + c) << std::endl;
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
