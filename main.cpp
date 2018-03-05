// Chad Cooper
// Ryan Gray
// Anna McMaster



#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int RoboStaxMemo(int B, int N, int K, int **arr);

unsigned long long factorial(int n);

unsigned long long  C(int n, int r);

int sum(int* arr, int n);

void fillMat(int **arr, int rows, int colums, int value);

int main(int argc, char *argv[])
{
	//check number of parameters
	if (argc != 3)
	{
		std::cout << "Usage: ./executable_name inputFile.txt outputFile.txt" << std::endl;
		return 1;
	}

	//reading in inputFile
	ifstream inputFile;
	inputFile.open(argv[1]);
	
	int numInstances = 0;
	int* b = new int[numInstances];
	int* n = new int[numInstances];
	int* k = new int[numInstances];

	if (inputFile.is_open()) {

		inputFile >> numInstances;

		while (!inputFile.eof()) {
			for (int i = 0; i < numInstances; i++){
				//reads in and takes out commas
				char ch;
				//reading in values
				inputFile >> b[i] >> ch >> n[i] >> ch >> k[i];
			}
		}
		inputFile.close();
	}

	ofstream outputFile;
	outputFile.open(argv[2]);
	for (int i = 0; i < numInstances; i++) {
		// Create the DP array and initialize it to -1.
		int** roboArray = new int*[b[i]]; // b[i] rows
		for (int j = 0; j < b[i]; j++) {
			roboArray[j] = new int[n[i]]; // n[i] columns
		}
		fillMat(roboArray, b[i], n[i], -1);

		int result = RoboStaxMemo(b[i] - 1, n[i] - 1, k[i], roboArray);
		outputFile << result << endl;
		cout << "\nWritten to " << argv[2] << "... \n";

		// Delete the 2D array,,,
		for (int j = 0; j < b[i]; j++) {
			delete[] roboArray[j];
		}
		delete[] roboArray;
	} // All instances have been calculated.
	outputFile.close();


	return 0;
}


int RoboStaxMemo(int B, int N, int K, int** arr) {


	if (arr[B][N] != -1) { // If arr[B][N] != -1 then this value has been calculated already.

		return arr[B][N];

	}
	
	/* Note: For the base cases, all instances of B and N were changed to B + 1
	 and N + 1 respectively, so that the base cases are checked correctly and the 
	 array indexes correctly. */
	
	else if (K >= (B + 1)) {

		arr[B][N] = C(((B + 1) + (N + 1) - 1), ((N + 1) - 1)); // (b + n -1)choose(n-1)
		
		return arr[B][N];

	}
	else if (K < (B + 1) / (N + 1)) { 

		arr[B][N] = 0;

		return arr[B][N];

	}
	else {

		int* partialSums = new int[K + 1]; // There are K+1 children
		
		/* If drawing the DP array by hand, this says the value at position (B, N) is the 
		sum of the values in the column N-1 from B to B-K */
		for (int i = 0; i <= K; i++) {
			partialSums[i] = RoboStaxMemo(B - i, N - 1, K, arr);
		}

		arr[B][N] = sum(partialSums, K + 1);

		return arr[B][N];
	}
}


/* Utility Functions */

int sum(int* arr, int n) {
	int sum = 0;
	for (int i = 0; i < n; i++) {
		sum += arr[i];
	}
	return sum;
}

unsigned long long  C(int n, int r) {
	return factorial(n) / (factorial(r)*factorial(n - r));
}

unsigned long long factorial(int n)
{
    unsigned long long fact = 1;
    for(int i = 1; i <=n; ++i) // if n = 0, fact = 1 which is correct.
    {
        fact *= i;
    }
    
    return fact;
}

void fillMat(int **arr, int rows, int colums, int value) {

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < colums; j++) {
			arr[i][j] = value;
		}
	}
}
