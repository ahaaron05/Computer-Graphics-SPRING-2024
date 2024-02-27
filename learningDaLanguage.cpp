#include <iostream>
#include <string>

using namespace std;

void TagMaker(string n, int m, int d)
{
	cout << "***********************\n";
	cout << "*\t Programming Assignment 1\t *\n";
	cout << "*\t Computer Programming 1\t *\n";
	cout << "*\t Author: " + n + "\t *\n";
	cout << "*\t Date: " + m + '/' + d + '\t' + '*\n';
	cout << "***********************\n";
}

int main()
{
	TagMaker("Aaron", 10, 13);

	return 0;
}