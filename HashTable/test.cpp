/* Justin Farnsworth
 * December 7, 2017
 * test.cpp
 * 
 * This program tests the hash table by reading a file full of input data.
 * The data may be inserted, deleted, or retrieved.
 * At the end, the number of insertions, deletions, and retrivals will be displayed
 * as well as the amount of time taken to complete.
 * 
 * This project works best with a Linux. NOT recommended for the Windows!
 * 
 * Compile Command:
 * g++ test.cpp -o test
 * 
 * Run Command:
 * Unix: 
 * 	  ./test.exe [textfile]
 * 	    -ex: ./test.exe ../60000-idr.txt
 * 
 * Windows:
 *   test.exe [textfile]
 * 	   -ex: test.exe ../60000-idr.txt
 */

#include <iostream>
#include <fstream>
#include "hashTable.h"
#include <string>
#include <time.h>
#include <ctime>
#include <cstdlib>
using namespace std;

// Main function
int main(int argc, char* argv[]){
    // Keeps track of how long it takes to complete the program
    clock_t start, end;
	double duration;

	// Records the current time
	start = clock();

	// The array size inside the hash table is set to 10007
	HashTable<string>* data = new HashTable<string>(10007);
	
	
	int iCounter = 0; // Counts the number of insertions
	int dCounter = 0; // Counts the number of deletions
	int rCounter = 0; // Counts the number of retrievals

	// Variables used for input values
	char operation;
	string SSN;
	string firstName;
	string lastName;
	string fullName; // Combines the first name and last name

	// Opens the input file to retrieve the data
	fstream input(argv[1]);

	// Processes the data line by line
	while (!input.eof()) {
		input >> operation >> SSN >> firstName >> lastName;
		fullName = firstName + " " + lastName;

		switch(operation) {
			case 'i': // Insertion
				if (data->insert(SSN, fullName)) {
					iCounter++;
				}
				break;
			case 'd': // Deletion
				if (data->erase(SSN)) {
					dCounter++;
				}
				break;
			case 'r': // Retrieval
				if (data->find(SSN) != nullptr) {
					rCounter++;
				}
				break;
		}
	}

	// Closes the input file
	input.close();

	// Records the current time and computes the difference
	end = clock();
	duration = (end - start) / (double) CLOCKS_PER_SEC;

	// Summary of the results
	cout << "Number of valid insertations: " << iCounter << endl;
	cout << "Number of valid deletions: " << dCounter << endl;
	cout << "Number of valid retrievals: " << rCounter << endl;
	cout << "Number of items in the list: " << data->size() << endl;
	cout << "Time elapsed: " << duration << endl;
	
	// Deletes the hash table
	delete data;

	return 0;
}
