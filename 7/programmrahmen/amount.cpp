#include <string>
#include <iostream>
#include <algorithm>

class Amount {
	//ToDo 7.2
	//Implement class Amount

private:
	double mws = 19;
	double brutto = 0;
	double netto = brutto/(mws/100+1); // standart is EUR
	enum Currency { USD, EUR};
	std::string beschreibung = "";
	int activated = 0; //whether change to USD was used
	const double usdFaktor = 1.10804;
public:
		Amount(double number, double tax);
		~Amount();
		void changeBrutto(double amount){
		brutto = amount;
		netto = brutto/(mws/100+1);
		std::cout << "Changed brutto to " << brutto << " as result netto is " << netto << "\n";
		}
	void changeToCurrency(std::string currency){
		Currency taken;
		if(currency == "USD"){
			taken = USD;
		}else{
			taken = EUR;
		}
		switch(taken){
			case USD: brutto = brutto*usdFaktor; activated = 1; break;
			//case EUR: if(activated == 1){brutto = brutto/1,10804;}else{brutto = brutto;}; break;
			default: if(activated == 1){brutto = brutto/usdFaktor;}else{brutto = brutto;}; activated = 0; break;
		}
		netto = brutto/(mws/100+1);
		std::cout << "Currency changed to " << currency << "\n" << "Brutto: " << brutto << "\n" << "Netto: " << netto << "\n";
	}
	void defineDescription(std::string yourString){
			beschreibung = yourString;
			std::cout << "Changed description to: " << beschreibung << "\n";
	}
	void changeTaxes(double newTax){
		mws = newTax;
		netto = brutto/(mws/100+1);
		std::cout << "Changed the tax to " << mws << "\n" << "New netto: " << netto << "\n";
	}
};

Amount::Amount(double number, double tax):
	brutto{number},
	mws{tax},
	netto{brutto/(mws/100+1)}{
	std::cout << "Object created with following values: " << "\n" << "Brutto: " << brutto << "\n" << "Netto: " << netto << "\n" << "Mehrwertsteuer: " << mws << "\n";
}

Amount::~Amount(void){
	std::cout << "Object has been deleted" << "\n";
}

void test() {
	Amount amount(200,19);
	//amount.changeBrutto(200);
	amount.changeToCurrency("EUR");
	amount.changeToCurrency("USD");
	amount.changeToCurrency("EUR");
	amount.defineDescription("I did not pay my bills");
	amount.changeTaxes(7);

	//ToDo 7.2
	//implement tests
}

int main() {
	test();
    return 0;
}
