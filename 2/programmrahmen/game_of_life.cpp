#include <iostream>
#include <ctime>
#include "bitmap_image.hpp"
#include <string.h>
#include <cstring>

struct Raster {
	Raster(int w, int h) : width(w), height(h)
	{
		data = new int[width*height];
	}

	Raster(int w, int h, float seedProbability) : width(w), height(h)
	{
		data = new int[width*height];

		int numSeeds = width * height * seedProbability;

		//Todo Exercise 2.3a): Fill randomly. Probability of value 1 is seedProbability otherwise value is 0

		while (numSeeds > 0){
			for (int i = 0; i < (width*height); i++){
				int random = rand() % 2;
				if (random == 1 && data[i] != 1){
					data[i] = 1;
					numSeeds--;
				}
				else {
					data[i] = 0;
				}
			}
		}
	}

	Raster(const std::string &filename)
	{
		bitmap_image image(filename);

		if (!image)
		{
			std::cerr << "Could not open bitmap!" << std::endl;
		}

		height = image.height();
		width = image.width();

		unsigned char red;
		unsigned char green;
		unsigned char blue;

		data = new int[width*height];
		
		//Todo Exercise 2.3a): Load image by using image.get_pixel(...). A black pixels mean 1 - all other values 0.
		for (int i = 0; i < height; i++){ //lines
			for (int j = 0; j < width; j++){
				image.get_pixel(i, j, red, green, blue);
				if (red == 0 && green == 0 && blue == 0){
					data[i*width + j] = 1;
				}
				else {
					data[i*width+j] = 0;
				}
			}
		}
	}

	void save(const std::string &filename)
	{
		//Todo Exercise 2.3a): Save image by using image.set_pixel(...). Living cell should be stored as black pixels, all other pixels are white.
		bitmap_image image(height, width);
		unsigned char red;
		unsigned char green;
		unsigned char blue;
		std::cout << "start saving\n";
		for (int i = 0; i < height; i++){ //lines
			for (int j = 0; i < width; j++){
				if (data[i*width + j] > 1){
					break; //handles overflow
				}
				if (data[i*width+j] == 1){
					red = 0;
					blue = 0;
					green = 0;
					image.set_pixel(i, j, red,green,blue);
				}
				else {
					red = 255;
					blue = 255;
					green = 255;
					image.set_pixel(i, j, red, green, blue);
				}
			}
		}
		image.save_image(filename);
	}

	~Raster()
	{
		delete[] data;
	}

	int width;
	int height;
	int* data;
};

// This struct parses all necessary command line parameters. It is already complete and doesn't have to be modified. However - feel free to add support for additional arguments if you like.
struct CommandLineParameter
{
	CommandLineParameter(int argc, char* argv[])
		: width(0)
		, height(0)
		, invasionFactor(0)
		, isTorus(false)
		, maxIterations(20)
	{
		if (argc % 2 == 0)
		{
			std::cerr << "Missing value for " << argv[argc - 1] << std::endl;
			argc--;
		}

		for (int i = 1; i < argc; i += 2)
		{
			if (!strcmp(argv[i], "-w"))
			{
				width = atoi(argv[i + 1]);
			}
			else if (!strcmp(argv[i], "-h"))
			{
				height = atoi(argv[i + 1]);
			}
			else if (!strcmp(argv[i], "-s"))
			{
				seedProbability = atof(argv[i + 1]);
			}
			else if (!strcmp(argv[i], "-p"))
			{
				patternFilename = argv[i + 1];
			}
			else if (!strcmp(argv[i], "-o"))
			{
				outputDirectory = argv[i + 1];
			}
			else if (!strcmp(argv[i], "-iv"))
			{
				invasionFactor = atof(argv[i + 1]);
			}
			else if (!strcmp(argv[i], "-t"))
			{
				isTorus = strcmp(argv[i + 1], "0") != 0;
			}
			else if (!strcmp(argv[i], "-i"))
			{
				maxIterations = atoi(argv[i + 1]);
			}
		}

		if ((width != 0 || height != 0) && !patternFilename.empty())
		{
			std::cout << "Width and height are ignored, because pattern is defined." << std::endl;
		}

		if (width < 0 || height < 0)
		{
			std::cerr << "Width or height has a invalid value." << std::endl;
			width = 0;
			height = 0;
		}
	}

	int width;
	int height;
	float seedProbability;
	std::string patternFilename;
	std::string outputDirectory;
	float invasionFactor;
	bool isTorus;
	int maxIterations;
};

int neighborValue(const Raster &raster, int x, int y, bool isTorus)
{
	int* data = raster.data;
	int width = raster.width;
	int height = raster.height;
    //Todo Exercise 2.3b): Extract information for the given cell. Return 0 (dead) if the color equals white. Otherwise return 1

	//Todo Exercise 2.3b): In case isTorus is false and (x, y) is outside of raster, return 0
	if (!isTorus && (x > width || y > height)){
		return 0;
	}
	//Todo Exercise 2.3b): In case isTorus is true and (x, y) is outside of raster use value of matching cell of opposite side
	if (isTorus && (x > width || y > height)){
		int coordinate = y* width + (x - width);
		return data[coordinate];
	}

	int coordinate = y*width + x; //e.g. x=3, y=2, width=4 --> fourth element in third line and the 11th element in data 
	if (data[coordinate] == 0){
		return 0;
	}

    return 1;
}

void simulateInvasion(Raster &raster, float invasionFactor)
{
	if (invasionFactor <= 0)
	{
		return;
	}

	//Todo Exercise 2.3c): Flip random cells (probability to flip for each cell is invasionFactor)

}

void simulateNextState(Raster &raster, bool isTorus)
{
	//Todo Exercise 2.3b): Play one iteration of Game of Life
	int* data = raster.data;
	int width = raster.width;
	int height = raster.height;

	for (int i = 0; i < height; i++){ //lines
		for (int j = 0; j < width; j++){
			int counterNeighbors = 0; //check all 8 neighbors
			counterNeighbors += neighborValue(raster, i + 1, j, isTorus);
			counterNeighbors += neighborValue(raster, i + 1, j + 1, isTorus);
			counterNeighbors += neighborValue(raster, i, j + 1, isTorus);
			counterNeighbors += neighborValue(raster, i - 1, j, isTorus);
			counterNeighbors += neighborValue(raster, i - 1, j - 1, isTorus);
			counterNeighbors += neighborValue(raster, i, j - 1, isTorus);
			counterNeighbors += neighborValue(raster, i + 1, j - 1, isTorus);
			counterNeighbors += neighborValue(raster, i - 1, j + 1, isTorus);

			std::cout << counterNeighbors << "\n";
			//check rules
			int index = i*width + j;
			if (data[index] == 0 && counterNeighbors == 3){
				data[index] == 1;
			} else if (data[index] == 1 && counterNeighbors <= 1){
				data[index] = 0;
			} else if (data[index] == 1 && counterNeighbors >= 4){
				data[index] = 0;
			}
			else if (data[index] == 1 && (counterNeighbors == 2 || counterNeighbors == 3)){
				data[index] = 1;
			}
		}
	}
}

std::string to_string(int number){	// As it seems my compiler doesn't support std::to_string so I'm using this one!  Hope it doesn't bother anyone.(Yes my compiler is up to date and the library as well)
	std::string number_string = "";
	char ones_char;
	int ones = 0;
	while (true){
		ones = number % 10;
		switch (ones){
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
		default: ("Trouble converting number to string.");
		}
		number -= ones;
		number_string = ones_char + number_string;
		if (number == 0){
			break;
		}
		number = number / 10;
	}
	return number_string;
}


int main(int argc, char* argv[])
{
	Raster* raster = nullptr;

	CommandLineParameter cmd(argc, argv);
	if (!cmd.patternFilename.empty())
	{
		raster = new Raster(cmd.patternFilename);
	}
	else
	{
		raster = new Raster(cmd.width, cmd.height, cmd.seedProbability);
	}

	//Todo Exercise 2.3a): Initialize random seed before this loop
	cmd.invasionFactor = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	for (int iteration = 0; iteration <= cmd.maxIterations; iteration++)
	{
		raster->save(cmd.outputDirectory + "game_of_life_" + to_string(iteration) + ".bmp");
		//simulateInvasion(*raster, cmd.invasionFactor);
		simulateNextState(*raster, cmd.isTorus);
	}

	delete raster;

	return 0;
}