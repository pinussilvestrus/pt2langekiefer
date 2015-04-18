
#include <cstdlib>
#include <iostream>


// ToDo: Exercise 2.d - adapt and implement combinations

int combinations(int number)
{
	/*it works like fibonacci --> Say you are at the beginning and have the choice to make one or two steps at first:
	a) one step: there are n-1 steps left
	b) two steps: there are n-2 steps left
		--> combinations(n) = combinations(n-1) + combinations(n-2),combinations(0)=combinations(1)=1
	**/
	if (number < 0) {
		return 0;
	}

	if (number == 0 || number == 1) {
		return 1;
	}
	else {
		/**
		choose the iterative way, because it's faster
		*/
		int temp = 0;
		int a = 1;
		int b = 1;
		for (int i = 2; i <= number; i++) {
			temp = a + b;
			a = b;
			b = temp;
		}
		return temp;
	}

	return 0;
}


int main(int argc, char * argv[])
{
	if(argc != 2)
		return 1;	// invalid number of parameters

	int n = std::atoi(argv[1]); 

	std::cout << combinations(n);

	return 0;
}
