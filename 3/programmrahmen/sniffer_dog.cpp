#include <climits>
#include <iostream>
#include <vector>
#include <algorithm>

// todo 3.3: Calculate minimum time needed for both dogs to return 
int minTimeDogTraining(int searchValueX, int searchValueY, const std::vector<int> &boxes)
{
	int num1 = -1;
	int num2 = -1;
	int num3 = -1;
	int num4 = -1;
	
	/**** dog x and y start left **/
	int foundX = 0; //time to find searchValueX;
	int foundY = 0; //time to find searchValueY;
	while ((foundX==0) && (foundY==0)) {
		for (int i=0;i<boxes.size();i++){
			if (searchValueX==boxes[i]){
				foundX=i+1;
			}
			if (searchValueY==boxes[i]){
				foundY=i+1;
			}
		}
	}
	num1 = std::max(foundX,foundY);
	/***********************/
	
	/**** dog x and y start right**/
	foundX = 0;
	foundY = 0;
	while ((foundX==0) && (foundY==0)) {
		for (int i=0;i<boxes.size();i++){
			if (searchValueX==boxes[boxes.size()-i-1]){
				foundX=i+1;
			}
			if (searchValueY==boxes[boxes.size()-i-1]){
				foundY=i+1;
			}
		}
	}
	num2 = std::max(foundX,foundY);
	/*******************************/
	
	/***** dog x starts at left and y at right **/
	foundX = 0;
	foundY = 0;
	while ((foundX==0) && (foundY==0)) {
		for (int i=0;i<boxes.size();i++){
			if (searchValueX==boxes[i]){
				foundX=i+1;
			}
			if (searchValueY==boxes[boxes.size()-i-1]){
				foundY=i+1;
			}
		}
	}
	num3 = std::max(foundX,foundY);
	/*******************************/
	
	/***** dog x starts at right and y at left **/
	foundX = 0;
	foundY = 0;
	while ((foundX==0) && (foundY==0)) {
		for (int i=0;i<boxes.size();i++){
			if (searchValueX==boxes[boxes.size()-i-1]){
				foundX=i+1;
			}
			if (searchValueY==boxes[i]){
				foundY=i+1;
			}
		}
	}
	num4 = std::max(foundX,foundY);
	/*******************************/
	
	return std::min(num1,std::min(num2,std::min(num3,num4)));
}

int main(int argc, char * argv[])
{
	if (argc < 3)
	{
		std::cout << "Missing parameters. Usage: <searchValue1> <searchValue2> [box1] [box2] [...]" << std::endl;
		return 0;
	}

	const int searchValueX = std::atoi(argv[1]);
	const int searchValueY = std::atoi(argv[2]);
	if(searchValueX < 1 || searchValueY < 1)
	{
		std::cerr << "Search values must be greater than zero!";
	}
	
	if (searchValueX == searchValueY)
	{
		std::cerr << "Search values must be different!";
		return 1;
	}

	std::vector<int> boxes;
	for (int i = 3; i < argc; i++)
	{
		int value = std::atoi(argv[i]);
		if (value < 1)
		{
			std::cerr << "Box value must be greater than zero!";
			return 2;
		}

		boxes.push_back(std::atoi(argv[i]));
	}

	int minTime = minTimeDogTraining(searchValueX, searchValueY, boxes);
	if (minTime == -1)
	{
		std::cout << "There exists no two boxes with the given search values!" << std::endl;
	}
	else
	{
		std::cout << "The coach will have to wait at least " << minTime << " seconds!" << std::endl;
	}
	
	return 0;
}