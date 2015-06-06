#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <cassert>

// function template for printing contents of containers to std::cout
template<class T>
void printContainer(T& container)
{
	std::cout << "{";
	for (auto element : container)
		std::cout << element << " ";
	std::cout << "}" << std::endl;
}

// ToDo 5.3 - Merge the given lists [leftIt..midIt) and [midIt..rightIt)
template<class T>
void merge(T leftIt, T midIt, T rightIt)
{

	assert(leftIt <= midIt && midIt <= rightIt);

    T temp[10]; // temporary storage
    T a = leftIt, b=midIt;
    while (a < midIt && b < rightIt) {
        if (*a < *b) *temp++ = *a++;
        else *temp++ = *b++;
    }
    
    while (a < midIt) *temp++ = *a++;
    while (b < rightIt) *temp++ = *b++;
    while (leftIt < rightIt) *leftIt++ = *temp++;
}

// ToDo 5.3 - Sort the given container using merge sort.
template<class T>
void mergeSort(T leftIt, T rightIt)
{
	if(*leftIt < *rightIt){
		auto midIt = (*leftIt + *rightIt)/2;
		mergeSort(leftIt,midIt);
		mergeSort(midIt,rightIt);
		merge(leftIt,midIt,rightIt);
	}
	assert(leftIt < rightIt);
}

int main(int argc, char** argv)
{
	// define sample data
	std::vector<int> sampleDataInt = { 10, 1, 12, 33, 24, 5, 6, -7, -2, 19 };
	std::vector<std::string> sampleDataString = { "Die", "eines", "ist", "Gebrauch", "der", "Sprache", "in", "sein", "Wortes", "Bedeutung" };

	// test for integer vector
	printContainer(sampleDataInt);
	mergeSort(sampleDataInt.begin(), sampleDataInt.end());
	printContainer(sampleDataInt);

	// test for string vector
	printContainer(sampleDataString);
	mergeSort(sampleDataString.begin(), sampleDataString.end());
	printContainer(sampleDataString);

	return 0;
}
