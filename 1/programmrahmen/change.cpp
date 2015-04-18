
#include <cstdlib>
#include <iostream>
#include <fstream>

const int coins[] = { 5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5, 2, 1 };
const int size = 12;
static int nums[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
/*i: cents
0: 5000 (50€)
1: 2000
2: 1000
3: 500
4: 200
5: 100
6: 50
7: 20
8: 10
9: 5
10: 2
11: 1 (50 €)*/
void change(const int due, const int paid)
{
	// ToDo: Exercise 3.a - return set of change tuples
	int diff = paid - due;
	for (int i = 0; i < size; i++) {
		while ((diff - coins[i]) >= 0) { //counts down as long as possible for one value
			diff -= coins[i];
			nums[i]++; //save if a value is matching
		}
		if (diff == 0) break; //break the loop for saving time
	}
}

int main(int argc, char * argv[])
{
	if(argc < 3)
		return 1;	// invalid number of parameters

	const int due  = std::atoi(argv[1]); 
	const int paid = std::atoi(argv[2]); 

	// ToDo: Exercise 3.c - catch invalid arguments
	if ((paid - due) <= 0 || due < 0 || paid < 0){
		return 1;
	}

	change(due, paid);	

	// ToDo: Exercise 3.b - print change data as CSV to console 
	if (argc > 3) {
		if (argc != 5) {
			std::cout << "Usage: ./change due paid -o file.csv";
			return 1;
		}
		std::ofstream write(argv[4]);
		write << "coin,num\n";
		for (int i = 0; i < size; i++) {
			if (nums[i] != 0) {
				write << coins[i] << "," << nums[i] << "\n";
			}
		}
		write.close();
		return 0;
	} //normal way
	std::cout << "coin,num\n";
	for (int i = 0; i < size; i++) {
		if (nums[i] != 0) {
			std::cout << coins[i] << "," << nums[i] << "\n";
		}
	}
	return 0;
}
