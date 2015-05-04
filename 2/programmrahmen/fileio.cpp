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
        case 1:
            regExp = "[a-zA-Z]+";
            break;
		case 2:
			regExp = "[\"][A-Z]{0,4}[\"]";
			break;
		case 3:
			regExp = "[0-9]{1,5}";
			break;
		case 4:
			regExp = "[\"][EASOUZN][\"]";
			break;

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
	std::string altitude;
	std::string country;
	std::string icao;
	
	int pos = 0;
	std::ofstream write;
		write.open("fileio.log");
		write << "Errors found" << "\n";
	
	while (std::getline(file, line)) {
		std::istringstream linestream;
		linestream.str(line);
		
			while(std::getline(linestream, parsed, ',')){
				if(pos == 1){
					pos++;std::cout << "\"[NAME] - [DATABASE Time Zone]\" -> "<<parsed<<" - ";
					name = parsed;
					}else if(pos == 12){
						pos++;std::cout << parsed << "\n"; //continue;
						timezone = parsed;
						if(isValueCorrect(country, 4) != true){
							write << "\"[NAME] - [DATABASE Time Zone]\" -> "<<name<<" - "<<timezone<< " - " << "wrong country " << country << "\n";
						}
						if(isValueCorrect(icao, 2) != true){
							if(icao == "\\N"){
								
							}else {
								write << "\"[NAME] - [DATABASE Time Zone]\" -> " << name << " - " << timezone <<
								" - " << "wrong ICAO " << icao << "\n";
							}
						}
						if(isValueCorrect(altitude, 3) != true){
							write << "\"[NAME] - [DATABASE Time Zone]\" -> "<<name<<" - "<<timezone<< " - " << "wrong altitude " << altitude << "\n"; //Die Aufgabe ist nicht korrekt gestellt, da die Niederlande und teile Asiens unter der dem Meeresspiegel liegen und dementsprechend auch negativ werte vorkommen
						}	
					}else if(pos == 11){
						country = parsed;
					}else if(pos == 6){
						icao = parsed;
					}else if(pos == 9){
						altitude = parsed;
					}
					pos++;
			}
			pos = 0;
			}
			write.close();
		// ToDo: Exercise 2.2a - Split line and write result to std::cout
		// ToDo: Exercise 2.2b - Check each part of line with isValueCorrect and log if values are not supported. Use and extend isValueCorrect function for this.
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
