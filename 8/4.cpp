#include <iostream>
#include <string>

class Test{
public:
	const string getLabel() const {
		return label_;
	}
	
private:
	Test(){};
	Test(string label) : label_(label){};
	~Test(){};
	string label_;
};

int main(int argc, char** agrv){
	Test* t1 = new Test("Test1");
	Test t2("Test2");
	
	std::cout << t1.getLabel() << endl;
	std::cout << t2->getLabel() << endl;
	
	return 0;
}