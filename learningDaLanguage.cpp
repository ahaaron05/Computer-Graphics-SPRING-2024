#include <iostream>
#include <string>


int main()
{
	int size; // statically allocated
	int* psize; // also statically allocated

	
	std::cout << "Enter size of an array: ";
	std::cin >> size;

	psize = new int[size];

	for (int i = 0; i < size; i++)
	{
		std::cin >> psize[i];
		std::cout << std::endl;
	}
	

	delete [] psize;
	return 0;
}