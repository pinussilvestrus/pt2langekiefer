#include <functional>
#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>

struct CommandLineParameter
{
	CommandLineParameter(int argc, char* argv[])
		: m_fibonacci(false)
		, m_centeredTriangular(false)
		, m_powSum(false)
	{
		for (int i = 1; i < argc; i++)
		{
			if (!strcmp(argv[i], "-fib"))
			{
				m_fibonacci = true;
			}
			else if (!strcmp(argv[i], "-ct"))
			{
				m_centeredTriangular = true;
			}
			else if (!strcmp(argv[i], "-pow"))
			{
				m_powSum = true;
			}
		}
	}

	bool m_fibonacci;
	bool m_centeredTriangular;
	bool m_powSum;
};

// ToDo 4.2a - Calculate and return the fibonacci number for the given input value, iterative
int fibonacci(int number)
{
	if (number <= 0 ){
		return 0;
	}
	
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
		}
		if (temp <= 32767) { //filter bad output
			return temp; 
		}
		else { return 0; }
	}
}

// ToDo 4.2a - Calculate and return the centered triangular number for the given input value
int centeredTriangular(int number)
{
	if (number<0){
		return 0;
	}
	
	return ((3*number*number + 3*number + 2) / 2);
}

// ToDo 4.2a - Calculate and return the sum of i^exp for all i in [1..number]
int powSum(int number, int exp)
{
	if (number <= 0){
		return 0;
	}
	
	int sum = 0;
	for (int i = 1; i <= number; i++){
		sum+=std::pow(i,exp);
	}
	return sum;
}

// ToDo 4.2c - Call each function inside the functions vector. Print the results via std::cout
void applyFuntions(std::vector<std::function<int(int)>> & functions, int number)
{
	std::cout << number << ": ";
	std::vector<std::function<int(int)>>::size_type i;
	for(i = 0; i != functions.size(); i++) {
		int result = functions[i](number);
		std::cout << result << " ";
	}
	std::cout << std::endl;
}

int main(int argc, char * argv[])
{
	std::vector<std::function<int(int)>> functions;
	CommandLineParameter cmd(argc, argv);
	
	if (cmd.m_fibonacci)
	{
		// ToDo 4.2b - Add the fibonacci function directly to the functions vector
		functions.push_back(fibonacci);
	}
	if (cmd.m_centeredTriangular)
	{
		// ToDo 4.2b - Add a lambda expression that calls the centeredTriangular function to the functions vector
		std::function<int (int)> ct = [](int i) {return centeredTriangular(i);};
		functions.push_back(ct);
	}
	if (cmd.m_powSum)
	{
		// ToDo 4.2b - Add the powSum function using a std::bind expression to the functions vector. Use a constant value (e.g., 2) for the exp argument 
		using std::placeholders::_1;
		std::function<int (int)> ps = std::bind(powSum,_1,2);
		functions.push_back(ps);
	}
	
	if (functions.size()==0){
		std::cout<<"Please choose at least one option: -fib (fibonacci), -ct (centeredTriangular), -pow (powSum)";
		return 1;
	}

	for (int i = 1; i < 45; i++)
	{
		applyFuntions(functions, i);
	}
}
