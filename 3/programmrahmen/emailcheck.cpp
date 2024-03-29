#include <iostream>
#include <string>
#include <algorithm>

#define ENTRIES 7

std::wstring dataset[ENTRIES][4] = { { L"max.muestermann@bmw.de", L"Max", L"Mustermann", L"SAP" },
    { L"juergen.doellner@hpi.de", L"Jürgen", L"Döllner", L"HPI" },
    { L"soeren.discher@hpi.de", L"Sören", L"Discher", L"HPI" } ,
    { L"daniel.maeller@hpi.de", L"Daniel", L"Mäller", L"HPI" },
    { L"paul.deissler@hertha.de", L"Sebastian", L"Deißler", L"herTha" },
	{ L"mueller.marga@sap.com", L"Marga", L"Müller", L"SAP" },
    { L"h.boss@service.bayer.com", L"Hugo", L"Boss", L"Bayer" }};

//Replaces [from] with [to] in [str]
void ReplaceAll(std::wstring& str, const std::wstring& from, const std::wstring& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::wstring::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
}

//ToDo 3.1a - implement use std::transform()
void caseConvert(std::wstring& str) {
  std::transform(str.begin(), str.end(), str.begin(), (int(*)(int))std::tolower);
}

//ToDo 3.1b - implement replacement for ä, ö, ü, ß with ae,oe,ue,ss
//			- use ReplaceAll. wstrings are declared the same way as normal strings but with an "L" in front
void replace(std::wstring& str) {
  const std::wstring umlaute[] = { L"ä", L"ö", L"ü", L"ß"};
  const std::wstring umlauteReplace[] = { L"ae", L"oe", L"ue", L"ss"};
  int i = 0;
  while(i < 4){
    ReplaceAll( str, umlaute[i], umlauteReplace[i]);
    i++;
  }
}

//ToDo 3.1c - check if email is correct
bool emailCheck(std::wstring mail, std::wstring firstname, std::wstring name, std::wstring company)
{
  int a = 0;
  int b = 0;
  int c = 0;

  int posDot = mail.find(L".");
  int posDotLast = mail.rfind(L".");
  int posAt = mail.find(L"@");
  //int diffName = posAt-posDot-1;
  //int diffCompany = posDotLast-posAt-1;

  std::wstring firstnameSub = mail.substr(0,posDot);
  //std::wstring nameSub = mail.substr(posDot+1,diffName);
  //std::wstring companySub = mail.substr(posAt+1,diffCompany);

while(a != 1 || b != 1 || c != 1){
  if(mail.find(firstname) < posAt && mail.find(name) < posAt){
    a = 1;
    b = 1;
  } else if(firstnameSub == firstname.substr(0,1) && mail.find(name) < posAt){
    a = 1;
    b = 1;
  } else {
    break;
  }
  if(mail.find(company) < posDotLast && mail.find(company) > posAt){
      c = 1;
    } else {
      break;
    }
}
  if(a == 1 && b == 1 && c == 1){
    return true;
  } else {
    return false;
  }
}

int main(int argc, char * argv[])
{
    for (int i = 0; i < ENTRIES; i++)
    {
        for (int j = 1; j < 4; j++)
        {
            replace(dataset[i][j]);
            caseConvert(dataset[i][j]);
        }
        std::cout << emailCheck(dataset[i][0], dataset[i][1], dataset[i][2], dataset[i][3]) << std::endl;
    }
    return 0;
}
