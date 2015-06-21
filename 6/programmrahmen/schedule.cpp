
#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>


struct Interval
{
    Interval(const int i, const int start, const int length) 
    : index(i)
    , start(start)
    , end(start + length)
    { 
    }

    int index;
    int start;
    int end;
};

const static int MaxEnd = 74;
const static int MaxDuration = 10;

const static int N = 20;

std::ostream & operator<<(std::ostream & os, const std::vector<Interval> & I) 
{
	os << I.size() << std::endl;
    
	//TODO 6.3 
	//Implement a nice print function
	
	return os;
}

//creates data
void randomize(std::vector<Interval> & intervals)
{
    intervals.clear();
    srand(time(0));

    for (int i = 0; i < N; i++)
    {
        int duration = rand() % MaxDuration + 1;
        int start = rand() % (MaxEnd - duration);

        intervals.push_back(Interval(i, start, duration));
    }
}

/** comparing function for sorting the intervals in a vector from their given start-value **/
bool compareFunc (Interval i1, Interval i2){
	return i1.start < i2.start;
}


void schedule(const std::vector<Interval> & intervals)
{
    // unsorted

    std::cout << std::endl << "intervals (randomized):" << std::endl << intervals;

    // ToDo: Exercise 6.3 - sort and schedule intervals
	

	auto sorted = intervals;
    // sort intervals
	
	std::sort(sorted.begin(), sorted.end(), compareFunc);

    std::cout << std::endl << "intervals (sorted):" << std::endl << sorted;

    // scheduled
    
    auto scheduled = std::vector<Interval>();
    
    //ToDo 6.3
	//implement greedy scheduling
	
	// power point page 37
	
	schedule.push_back(sorted[0]); // insert first interval from sorted to new vector
	int endLast = sorted[0].end;
	std::vector<Route>::size_type i;
	for (i=1; i<= sorted.size(); i++) { // start from second element
		if (sorted[i].start >= endLast) {
			schedule.push_back(sorted[i]);
			endLast = sorted[i].end;
		}
	}

    std::cout << std::endl << "intervals (scheduled, " << scheduled.size() << " of " << sorted.size() << " possible)" 
        << std::endl << scheduled << std::endl;
}

int main(int argc, char** argv) {

    auto intervals = std::vector<Interval>();

    randomize(intervals);
    schedule(intervals);

    return 0;
}