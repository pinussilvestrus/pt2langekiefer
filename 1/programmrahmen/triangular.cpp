
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

std::string to_string(int number){			// As it seems my compiler doesn't support std::to_string so I'm using this one!  Hope it doesn't bother anyone.(Yes my compiler is up to date and the library as well)
    std::string number_string = "";
    char ones_char;
    int ones = 0;
    while(true){
        ones = number % 10;
        switch(ones){
            case 0: ones_char = '0'; break;
            case 1: ones_char = '1'; break;
            case 2: ones_char = '2'; break;
            case 3: ones_char = '3'; break;
            case 4: ones_char = '4'; break;
            case 5: ones_char = '5'; break;
            case 6: ones_char = '6'; break;
            case 7: ones_char = '7'; break;
            case 8: ones_char = '8'; break;
            case 9: ones_char = '9'; break;
            default : ("Trouble converting number to string.");
        }
        number -= ones;
        number_string = ones_char + number_string;
        if(number == 0){
            break;
        }
        number = number/10;
    }
    return number_string;
}

void pretty_print(int decimal)
{
	// ToDo: Exercise 1.c - print number with decimal marks to console
	std::string num = to_string(decimal);
	int insertPosition = num.length() - 3;  // Because you need it to count up and then put the dot
	while (insertPosition > 0){
		num.insert(insertPosition, ".");
		insertPosition -=3;
		}
	
	std::cout << num;
}

int main(int argc, char * argv[])
{
	if(argc != 2)
		return 1;	// invalid number of parameters
		
	int n = std::atoi(argv[1]); 
	// ToDo: Exercise 1.b - check if n is in domain, if not print valid domain and codomain and return 2
	if(n < 1 || n > 32767){
		std::cout << "domain = [1;"; pretty_print(32767); std::cout << "], codomain = [1;"; pretty_print(536854528); std::cout << "]"; //domain = Definitionsbereich, codomain = Wertebereich
		return 2;
	}
	// ToDo: Exercise 1.c - print all numbers with decimal marks
	else{
	    pretty_print(triangular(n));
	}

	// ToDo: Exercise 1.a - print triangular number to console

	return 0;
}
