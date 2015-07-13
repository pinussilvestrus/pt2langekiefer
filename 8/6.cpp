#include <iostream>

class Test1{
public:
	Test1(){}
	virtual ~Test1(){}
};

class Test2 : public Test1 {
public:
	Test2(int id = 3) : id_{ id }{}
	
	int getId(){return id_; }
	
protected:
	int id_;
};

int main(){
	Test1* p = new Test1;
	
	Test2* p2 = static_cast<Test2*>(p);
	std::cout << p2->getId() << std::endl;
	
	Test2* p3 = dynamic_cast<Test2*>(p);
	std::cout << p3->getId() << std::endl;
	
	return 0;
}