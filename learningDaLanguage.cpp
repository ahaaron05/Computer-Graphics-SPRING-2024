#include <iostream>

float gallons[5] = {15.75f, 16.3f, 10.95f, 20.65f, 30.0f};
float totalGalls = 0;


float AvgMilePerGall(int starting, int ending)
{
	for (int i = 0; i < sizeof(gallons); i++)
		totalGalls += gallons[i];

	return (ending - starting) / totalGalls;
}


int main()
{
	std::cout << AvgMilePerGall(68723, 71289);
}