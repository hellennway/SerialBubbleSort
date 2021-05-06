#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include<chrono>
#include <algorithm>
using namespace std;

// Function for formatted data output
void PrintData(double* pData, int Size) {
	for (int i = 0; i < Size; i++)
		printf("%7.4f ", pData[i]);
	printf("\n");
}

void DummyDataInitialization(double*& pData, int& Size) {
	for (int i = 0; i < Size; i++)
		pData[i] = Size - i;
}

void RandomDataInitialization(double*& pData, int& Size) {
	srand((unsigned)time(0));
	for (int i = 0; i < Size; i++)
		pData[i] = rand() / double(1000);
}

// Function for allocating the memory and setting the initial values
void ProcessInitialization(double*& pData, int& Size) {
	do {
		printf("Enter the size of array: ");
		scanf_s("%d", &Size);
		if (Size <= 0)
			printf("Size should be greater than zero\n");
	} while (Size <= 0);
	printf("\nChosen objects size = %d\n", Size);
	pData = new double[Size];
	DummyDataInitialization(pData, Size);
	//RandomDataInitialization(pData, Size);
}
// Function for computational process termination
void ProcessTermination(double* pData) {
	delete[]pData;
}
// Function for the serial bubble sort algorithm
void SerialBubble(double* pData, int Size) {
	double Temp;
	for (int i = 1; i < Size; i++)
		for (int j = 0; j < Size - i; j++)
			if (pData[j] > pData[j + 1]) {
				Temp = pData[j];
				pData[j] = pData[j + 1];
				pData[j + 1] = Temp;
			}
}
void OddEvenSort(double* pData, int Size){
	for (int i = 0; i < Size; i++)
	{
		if (i%2 == 1) // 'i' is odd
		{
			for (int j = 2; j < Size; j += 2)
			{
				if (pData[j] < pData[j - 1])
					swap(pData[j - 1], pData[j]);
			}
		}
		else
		{
			for (int j = 1; j < Size; j += 2)
			{
				if (pData[j] < pData[j - 1])
					swap(pData[j - 1], pData[j]);
			}
		}
	}
}
int main(int argc, char* argv[]) {
	double* pData = 0;
	int Size = 0; 
	//time_t start, finish;
	//double duration;

	printf("Serial bubble sort program\n");
	// Process initialization
	ProcessInitialization(pData, Size);
	//printf("Unsorted array\n");
	//PrintData(pData, Size);
	// Serial bubble sort
	auto start = std::chrono::high_resolution_clock::now();
	//start = clock();
	SerialBubble(pData, Size);
	//OddEvenSort(pData, Size);
	auto end = std::chrono::high_resolution_clock::now();
	//printf("Sorted array\n");
	//PrintData(pData, Size);
	double duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	std::cout << duration << '\n';
	std::string timeMeasure = "ns";
	if (duration >= 1e6)
	{
		duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		timeMeasure = "ms";
	}
	std::cout << "Time of execution: " << duration <<" " << timeMeasure << "\n";
	// Process termination
	ProcessTermination(pData);
	return 0;
}
