#include <iostream>
#include <list>

int main() {
	int myints[] = {17,89,7,14,89};
	std::list<int> mylist(myints, myints + 5);
	
	mylist.remove(8);
	mylist.remove(7);
	
	for (auto it = mylist.begin(); it != mylist.end(); ++it) {
		std::cout << ' ' << *it;
	}
}