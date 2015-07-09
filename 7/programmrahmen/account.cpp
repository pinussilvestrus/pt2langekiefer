#include <iostream>
#include <cassert>
#include <list>
#include <cstdlib>
#include <string>
#include <sstream>

using namespace std;


class Account {
public:
    Account(long accountNo, double balance, double limit, bool locked);
    ~Account();

    long accountNo() const { return accountNo_; }

    void setLimit(double limit) { limit_ = limit; }
    double getLimit() const { return limit_; }

    bool credit(double amount);
    bool debit(double amount);
    double balance() const { return balance_; }

    void setLock(bool locked) { locked_ = locked; }
    bool getLock() const { return locked_; }

private:
    long accountNo_;
    double balance_;
    double limit_;
    bool locked_;
};

Account::Account(long accountNo, double balance, double limit, bool locked) :
    accountNo_{accountNo},
    balance_{balance},
    limit_(limit),
    locked_{locked} {
}

Account::~Account() {
}

bool Account::credit(double amount) {
    assert(amount>=0.0);

    // cannot use locked account
    if(locked_) return false;

    balance_ = balance_ + amount;
    return true;
}

bool Account::debit(double amount) {
    assert(amount>=0.0);

    // cannot use locked account
    if(locked_) return false;

    // check if limit is hit
    if(balance_-amount<limit_) return false;

    // change balance
    balance_ = balance_ - amount;
    return true;
}

class LoggedAccount : public Account{
private:
    std::list<std::string> internList;
public:
    LoggedAccount(long accountNo, double balance, double limit, bool locked);
    void credit(double amount);
    void debit(double amount);
    void setLimit(double amount);
    void printList(double balance);
};

LoggedAccount::LoggedAccount(long accountNo, double balance, double limit, bool locked)
: Account(accountNo, balance, limit, locked){
  internList.push_back(" initial balance: ");
  std::ostringstream strs;
  strs << balance;
  std::string str = strs.str();
  internList.push_back(str);
  internList.push_back("\n");
}

void LoggedAccount::credit(double amount){
    Account::credit(amount);
    internList.push_back("credit: ");
    std::ostringstream strs;
    strs << amount;
    std::string str = strs.str();
    internList.push_back(str);
    internList.push_back("\n");
}

void LoggedAccount::debit(double amount){
    Account::debit(amount);
    internList.push_back("debit:  ");
    std::ostringstream strs;
    strs << amount;
    std::string str = strs.str();
    internList.push_back(str);
    internList.push_back("\n");
}

void LoggedAccount::setLimit(double amount){
    Account::setLimit(amount);
    internList.push_back("limit change:  ");
    std::ostringstream strs;
    strs << amount;
    std::string str = strs.str();
    internList.push_back(str);
    internList.push_back("\n");
}

void LoggedAccount::printList(double balance){
    list<std::string>::iterator i;
    internList.push_back("current balance: ");
    std::ostringstream strs;
    strs << balance;
    std::string str = strs.str();
    internList.push_back(str);
    internList.push_back("\n");
    for( i = internList.begin(); i != internList.end(); ++i){
      std::cout << *i << " ";
    }
}


int main(int argc, char** argv) {
  Account A1(19920, 0.0, -1000.0, false);
  LoggedAccount A2(20020, 0.0, -1000.0, false);

  A1.credit(500.0);
  A2.credit(500.0);
  A2.debit(100.0);
  A2.setLimit(-2000.);
  A2.printList(A2.balance());

  return 0;
}
