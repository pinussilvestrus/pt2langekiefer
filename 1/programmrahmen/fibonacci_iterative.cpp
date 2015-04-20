
#include <cstdlib>
#include <iostream>

static int sum = 0;
int fibonacci(int number)
{
	// ToDo: Exercise 2.c - count number of calculation steps

	// ToDo: Exercise 2.b - retun 0 on bad arguments
	if (number <= 0 || number > 32767) { //32767 max for int
		return 0;
	}

	// ToDo: Exercise 2.b - retrieve nth fibonacci number iteratively
	
	if (number == 1) {
		return 1;
	}
	else {
		int temp = 0;
		int a = 0; 
		int b = 1;
		for (int i = 2;i<=number;i++) {
			temp = a + b;
			a = b;
			b = temp;
			sum++; //counting up ine summation
		}
		if (temp <= 32767) { //filter bad output
			return temp; 
		}
		else { return 0; }
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
