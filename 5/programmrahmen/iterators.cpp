#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

// function template for printing contents of containers to std::cout
template<class T>
void printContainer(T& container)
{
    std::cout << "{";
    for(auto element : container)
        std::cout << element << " ";
    std::cout << "}" << std::endl;
}


// ToDo 5.1a - Merge front-back pairings of elements of inContainer into outContainer. Do *not* use the []-operator.
template<class T>
void front_back_pairing(T& inContainer, T& outContainer)
{
    int start = 0;
    int i = inContainer.size();
    auto value = inContainer.end();
    auto valueStart = inContainer.begin();
     for(int j = 0; j < i; j++){
       if(start == 0){
         outContainer.push_back(*valueStart);
         *valueStart++;
         start = 1;
       }else{
         *value--;
           outContainer.push_back(*value);
           start = 0;
       }
     }
}

// ToDo 5.1b - Remove all duplicates from the given container. Do *not* use the []-operator.
template<class T>
void remove_duplicates(T& container)
{
    std::sort(container.begin(), container.end());
    auto last = std::unique(container.begin(), container.end());
    container.erase(last, container.end());
/**
    int counter = 0;
    for(int i = 0; i < container.size(); i++){
      auto value = container.begin()+i;
      for(int j = 1; j < container.size(); j++){
        auto secondValue = container.begin()+j;
        if(*value == *secondValue){
          container.erase(secondValue);
          container.push_back(*secondValue);
          counter++;
          }
      }
    }
    int position = container.size();
    container.erase(position-counter,position);**/
}

// ToDo 5.1c - Expand the given container by inserting the numerical differences of each element to its neighbors. Do *not* use the []-operator.
template<class T>
void insert_differences(T& container)
{

}

void testFrontBackPairingFunctionality()
{
    // define sample data
    std::vector<int> sampleDataInt = { 10,11,12,13,14,15,16,17,18,19 };
    std::list<std::string> sampleDataString = { "Die", "eines", "ist", "Gebrauch", "der", "Sprache", "in", "sein", "Wortes", "Bedeutung" };

    // test for integer vector
    std::vector<int> helpIntVector;
    front_back_pairing(sampleDataInt, helpIntVector);
    printContainer(sampleDataInt);
    printContainer(helpIntVector);

    // test for string list
    std::list<std::string> helpStringList;
    front_back_pairing(sampleDataString, helpStringList);
    printContainer(sampleDataString);
    printContainer(helpStringList);
}

void testRemoveDuplicateFunctionality()
{
    // define sample data
    std::vector<int> sampleDataInt = { 10,11,10,13,14,15,15,15,18,19,12,11,17 };
    std::vector<std::string> sampleDataString = { "Die", "___", "eines", "ist", "Gebrauch", "der", "Sprache", "in", "sein", "Wortes", "Bedeutung", "Die", "ist", "blabla" };

    // test for integer vector
    printContainer(sampleDataInt);
    //remove_duplicates(sampleDataInt, std::less<int>() );
    remove_duplicates(sampleDataInt);
    printContainer(sampleDataInt);

    // test for string vector
    printContainer(sampleDataString);
    remove_duplicates(sampleDataString);
    printContainer(sampleDataString);
}

void testAddDifferenceFunctionality()
{
    // define sample data
    std::vector<int> sampleDataInt = { 10,11,14,16,1,18 };

    // test for integer vector
    printContainer(sampleDataInt);
    insert_differences(sampleDataInt);
    printContainer(sampleDataInt);
}

int main(int argc, char** argv)
{
    testFrontBackPairingFunctionality();
    testRemoveDuplicateFunctionality();
    testAddDifferenceFunctionality();

    return 0;
}
