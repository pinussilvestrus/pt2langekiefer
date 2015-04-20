
#include <cstdlib>
#include <iostream>

static int sum = 0;
int fibonacci(int number)
{
	// ToDo: Exercise 2.c - count number of calculation steps
	// we found out, that the correct number of summations when n is 8
	// has to be "33" and not 41 (given in task).... see this in:
	// http://www.maths.surrey.ac.uk/hosted-sites/R.Knott/Fibonacci/fibrab.html, 
	// "The number of additions when computing f(n)"

	// ToDo: Exercise 2.b - retun 0 on bad arguments
	if (number <= 0 || number > 23) { //32767 is max for int, and fib(24) goes over it
		return 0;
	}

	// ToDo: Exercise 2.a - retrieve nth fibonacci number recursively
	if (number==1) {
		return 1;
	}
	else {
		sum++; //count up one summation
		return fibonacci(number - 1) + fibonacci(number - 2);
	}
}

int main(int argc, char * argv[])
{
	if(argc != 2)
		return 1;	// invalid number of parameters

	int n = std::atoi(argv[1]); 

	// ToDo: Exercise 2.c - print calculation steps
	int fb = fibonacci(n);
	std::cout << n << " : " << fb << " : " << "#" << sum;

	return 0;
}
