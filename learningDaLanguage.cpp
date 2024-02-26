#include <iostream>

using namespace std;


float CalculateAvg(float s1, float s2, float s3, float s4)
{
	return (s1 + s2 + s3 + s4) / 4;
}

float CalculateHighest(float s1, float s2, float s3, float s4)
{
	return max({ s1, s2, s3, s4 });
}

void PrintBelow(float avg, float s1, float s2, float s3, float s4)
{
	if (s1 < avg)
		cout << "Bill\n";
	else if (s2 < avg)
		cout << "Tom\n";
	else if (s3 < avg)
		cout << "Joe\n";
	else if (s4 < avg)
		cout << "Sarah\n";
}

void PrintHighest(float highest, float s1, float s2, float s3, float s4)
{
	if (s1 == highest)
		cout << "Bill\n";
	else if (s2 == highest)
		cout << "Tom\n";
	else if (s3 == highest)
		cout << "Joe\n";
	else if (s4 == highest)
		cout << "Sarah\n";
}

int main()
{
	float avg = CalculateAvg(95, 22, 87, 90);
	float highest = CalculateHighest(95, 22, 87, 90);

	PrintBelow(avg, 95, 22, 87, 90);
	PrintHighest(highest, 95, 22, 87, 90);
}