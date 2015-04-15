
#include <cstdlib>
#include <iostream>


int fibonacci(int number)
{
	// ToDo: Exercise 2.c - count number of calculation steps

	// ToDo: Exercise 2.b - retun 0 on bad arguments

	// ToDo: Exercise 2.b - retrieve nth fibonacci number iteratively

	return 0;
}

int main(int argc, char * argv[])
{
	if(argc != 2)
		return 1;	// invalid number of parameters

	int n = std::atoi(argv[1]); 

	// ToDo: Exercise 2.c - print calculation steps

	std::cout << fibonacci(n);

	return 0;
}
