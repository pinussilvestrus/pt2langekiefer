#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <cfloat>
#include <iomanip>
#include <vector>
#include <stdexcept>

// transforms a string to a date. Throws a logic_error if year is *not* between 2005 and 2015
std::tm stringToTime(std::string date)
{
    std::tm t;
#if defined(__GNUC__) && (__GNUC__ < 5)
	strptime(date.c_str(), "%d.%m.%Y", &t);
#else
	std::istringstream ss(date);
	ss >> std::get_time(&t, "%d.%m.%Y");
#endif
    
    if(t.tm_year < 105 || t.tm_year > 115)
        throw std::logic_error("Year should be between 2005 and 2015");
    
    return t;
}

struct FormatException
{
    int m_actLine;
    std::string m_actFields;
};

void parseLine(std::string line, int lineNum)
{
	
	if (lineNum < 2){
		return; // don't parse header
	}
    const std::string fieldNames[3] = { "Date", "Temperature", "Rainfall" };
	const std::string delimiter = ";"; //for parsing
    
    // todo 3.2b: parse a given line, check dates by calling stringToTime, check temperature/rainfall by calling std::stof. Catch all exceptions thrown by these methods. If there have been any exceptions, aggregate all necessary information into an instance of FormatException and throw that instance.
    
	/******************** parsing *******/
	std::string lineDate = line.substr(0,line.find(delimiter)); // first
	line.erase(0,line.find(delimiter)+1);
	std::string lineTemperature = line.substr(0,line.find(delimiter)); // second
	line.erase(0,line.find(delimiter)+1);
	std::string lineRainfall = line; // third
	
	FormatException excp;
	excp.m_actLine = lineNum;
	int numOfFailures = 0;
	
	/***** Date ***/
	try {
		stringToTime(lineDate);
	} catch (std::logic_error e){
		excp.m_actFields += fieldNames[0] + ",";
		numOfFailures++;
	}
	
	/***** Temperature **/
	try {
		//std::stof(lineTemperature);
	} catch(std::invalid_argument e){
		excp.m_actFields += fieldNames[1] + ",";
		numOfFailures++;
	}
	
	/******* Rainfall **/
	
	try {
		//std::stof(lineRainfall);
	} catch (std::invalid_argument e){
		excp.m_actFields += fieldNames[2] + ",";
		numOfFailures++;
	}
	if (numOfFailures>0){
		throw excp;
	}
	
}

// todo 3.2c..
void writeOutFormatException(const FormatException & e)
{
    // todo 3.2d: export information (i.e., line number + invalid data fields) about exception to a logfile.
	// file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
	try {
		std::fstream file("./exceptions.log",std::ios_base::app | std::ios::out);
		file << "line " << e.m_actLine << ": " << e.m_actFields << "\n";
		file.close();
	}
    // todo 3.2d: catch ios_base::failure
	catch (std::ios_base::failure e) {
		std::cerr << "Exception opening/reading/closing file\n";
	}
}

// clears the log file
void clearFileFirst(){
	try {
		std::fstream file("./exceptions.log",std::ios::out);
		file << "";
		file.close();
	} catch (std::ios_base::failure e) {
		std::cerr << "Exception opening/reading/closing file\n";
	}
}

void checkData(std::string path)
{
	int validLines = 0;
    int invalidLines = 0;
    std::ifstream file;
	
	clearFileFirst(); // clears the log file
    
    // todo 3.2a: open file + read each line + call parseLine function (catch ifstream::failure)
	// file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
	try {
		file.open(path);

		std::string line;
		int lineNumber = 1;
		while (std::getline(file,line)){
			// todo 3.2c: read each line + call parseLine function (catch FormatException) + count valid + invalid lines
			try {
				//std::cout << line<<"\n";
				parseLine(line,lineNumber);
				validLines++;
			} catch(FormatException e){
				writeOutFormatException(e);
				invalidLines++;
			}
			lineNumber++;
		}
		file.close();
	}catch (std::ifstream::failure e) {
		std::cerr << "Exception opening/reading/closing file\n";
	}
    
    std::cout << "valid lines: " << validLines << " - invalid lines: " << invalidLines << std::endl;
}

int main(int argc, char * argv[])
{
    if(argc != 2)
    {
        std::cout << "Invalid number of arguments - USAGE: exceptions [DATASET]" << std::endl;
        return -1;
    }
    
    checkData(argv[1]);

	return 0;
}
