#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>


bool isValueCorrect(const std::string &teststring, const int &column)
{
	std::regex regExp;
	
	switch (column)
	{
		//regExp for column 1
        /*case 1:
            regExp = "[a-zA-Z]+";
            break;*/

		//Todo implement cases for other columns

		default:
			regExp = ".*";
			break;
	}
	
	return std::regex_match(teststring, regExp);
}

void readTokensAndLines(char* path)
{
	std::ifstream file(path);
	std::string parsed, line;
	std::string name;
	std::string timezone;
	int i = 1;
	int pos;
	
	while (std::getline(file, line)) {
		std::istringstream linestream;
		linestream.str(line);
		
			if (std::string::npos != (line.find("\"U\""))){
				timezone = "Unknown";
			}
			else if (std::string::npos != (line.find("\"E\""))){
				timezone = "Europe";
			}
			else if (std::string::npos != (line.find("\"A\""))){
				timezone = "US/Canada";
			}
			else if (std::string::npos != (line.find("\"S\""))){
				timezone = "South America";
			}
			else if (std::string::npos != (line.find("\"O\""))){
				timezone = "Australia";
			}
			else if (std::string::npos != (line.find("\"N\""))){
				timezone = "None";
			}
			else if (std::string::npos != (line.find("\"Z\""))){
				timezone = "New Zealand";
			}
			
			int posEnd = line.find("\",\"");
			int posBegin = line.find(",\"");
			
			std::cout << "[" << name << "]" << "-" << "[" << timezone << "]" << '\n';
			i++;
	
		// ToDo: Exercise 2.2a - Split line and write result to std::cout
		// ToDo: Exercise 2.2b - Check each part of line with isValueCorrect and log if values are not supported. Use and extend isValueCorrect function for this.
		
	}
}

int main(int argc, char * argv[])
{
	if(argc != 2)
	{
		std::cout << "not enough arguments - USAGE: fileio [DATASET]" << std::endl;
		return -1;	// invalid number of parameters
	}
	
	std::cout << "Given path to airports.dat: " << argv[1] << std::endl;

	// ToDO: Exercise 2.2a - Parse the stream by lines and every line by its delimiter
	//					   - Print the name of the airport and the timeZone for each airport
	readTokensAndLines(argv[1]);

	return 0;
}
