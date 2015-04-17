
#include <cstdlib>
#include <iostream>


int fibonacci(int number)
{
	// ToDo: Exercise 2.c - count number of calculation steps

	// ToDo: Exercise 2.b - retun 0 on bad arguments
	if (number <= 0 || number > 32767) { //32767 max for int
		return 0;
	}

	// ToDo: Exercise 2.a - retrieve nth fibonacci number recursively
	if (number==1) {
		return 1;
	}
	else {
		return fibonacci(number - 1) + fibonacci(number - 2);
	}
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
