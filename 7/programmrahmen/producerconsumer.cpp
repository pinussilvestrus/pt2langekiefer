
#include <iostream>
#include <chrono>
#include <thread>
#include <queue>
#include <list>
#include <random>


using namespace std::chrono;


// uint64_t is defined in stdint.h -> typedef unsigned long long uint64_t
// -> it's a standardized abbreviation/shortcut for unsigned long long for convinience


// Protoypical Item class - could conatin any application specific data..
class Item
{
public:
	Item()
		: m_uid{ s_counter++ }
		, m_spawntime{ system_clock::now() }
	{
		++s_items;
		std::cout << "create " << m_uid << std::endl;
	}

	~Item()
	{
		--s_items;
		std::cout << "delete " << m_uid << std::endl;
	}

	uint64_t uid() const
	{
		return m_uid;
	}

	long long lifeTime() const
	{
		return duration_cast<milliseconds>(system_clock::now() - m_spawntime).count();
	}

	static uint64_t items()
	{
		return s_items;
	}

protected:
	uint64_t m_uid;
	system_clock::time_point m_spawntime;

	// s_items is used to count the number of instances of Item
	static uint64_t s_items;

	// counter for incrementing unique item ids
	static uint64_t s_counter;

};

uint64_t Item::s_items = 0;
uint64_t Item::s_counter = 0;


using Queue = std::queue<Item *>;

class Consumer
{
public:
	Consumer(Queue & queue) : m_queue{ queue }, m_terminate{ false } { }

	~Consumer()
	{
	}

	void work()
	{
		while (!m_terminate)
		{
			// make worker thread sleep for short random time
			std::this_thread::sleep_for(milliseconds(rand() % 200 + 1));

			cleanup();
			consume();
		}
	}

	void consume()
	{
		// ToDo: implement consumption...
	}

	void cleanup()
	{
		// ToDo: remove and delete all items with their actual lifetime exceeding a threshold.

		// this is done in two phases, retrieve first and then delete, to keep the 
		// logic simple and avoid container changes within for loops (bad!).

		// hint: use std::cout << "\t\t"; before deleting ... makes the output prettier

		// Note: unless you remove some items, no new items will be processed obviously ...
	}

	void terminate()
	{
		std::cout << "\t\tTERMINATE" << std::endl;
		m_terminate = true;
	}

protected:
	Queue & m_queue;
	std::list<Item *> m_todo;

	bool m_terminate;
};


int main(int /*argc*/, char * /*argv*/[])
{
	Queue queue; // queue of items that are to be processed/consumed by worker thread

	// instanciate a single Consumer item and run its work method in a local thread, the consumer thread
	auto consumer = new Consumer{ queue };
	std::thread t_work(&Consumer::work, consumer);

	// reset random generator, using the system time
	srand(static_cast<unsigned int>(time(0)));

	auto prob = 500;
	while (rand() % --prob) // prob is used as a hack to randomly and deterministically terminate 
	{
		// ToDo: make producer thread sleep for short random time
		
		// ToDo: we generate a small number of items that are to be processed by the consumer 
		
	}
	std::cout << std::endl << "TERMINATE " << std::endl;

	// ToDo: delete remaining items, i.e., items that are still in the queue 
	// and are not processed by the consumer; they got lost.


	consumer->terminate(); // (soft)terminate the consumer thread -> see while loop in Cosumer::work
	t_work.join(); // block until consumer thread has terminated

	// ToDo: make sure to also delete items left in consumer


	// number of items left should be 0 -> precisely counted by Items constructor and destructor
	std::cout << std::endl << Item::items() << " items left in memory ..." << std::endl;

	return 0;
}