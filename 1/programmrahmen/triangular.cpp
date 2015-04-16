
#include <cstdlib>
#include <iostream>


int triangular(int number)
{
	// ToDo: Exercise 1.a - return triangular number
	int i = 1;
	int temp = 0;
	
	while (i <= number){
		temp += i;
		i++;
	}

	return temp;
}

void pretty_print(int decimal)
{
	// ToDo: Exercise 1.c - print number with decimal marks to console

	std::cout << decimal;
}

int main(int argc, char * argv[])
{
	if(argc != 2)
		return 1;	// invalid number of parameters

	int n = std::atoi(argv[1]); 

	// ToDo: Exercise 1.c - print all numbers with decimal marks

	// ToDo: Exercise 1.b - check if n is in domain, if not print valid domain and codomain and return 2

	// ToDo: Exercise 1.a - print triangular number to console

	std::cout << triangular(n);

	return 0;
}
