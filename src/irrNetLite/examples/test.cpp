#include <iostream>
#include <string>
using namespace std;

struct CandyBar
{
	std::string name;
	float weight;
	int calories;
};

int main()
{
	CandyBar * pointer = new CandyBar[3];
	cout << "Enter the nameof snack: ";
	getline(cin, pointer[0].name);
	cout << pointer[0].name;
	int test =0;
	++test;
	cout << "           " <<test << endl;
	delete [] pointer;
               // system("pause");
	return 0;
}
