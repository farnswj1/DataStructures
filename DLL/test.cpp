/* Justin Farnsworth
 * November 5, 2017
 * test.cpp
 * 
 * This program tests the doubly-linked list by reading a file full of input data.
 * The data may be inserted, deleted, or retrieved.
 * At the end, the number of insertions, deletions, and retrivals will be displayed
 * as well as the amount of time taken to complete.
 * 
 * Compile Command:
 * g++ test.cpp DLL.cpp DLLNode.cpp -o test
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

#include "DLL.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

// Main function
int main(int argc, char* argv[]){
	// Keeps track of how long it takes to complete the program
	clock_t start, end;
	double duration;
	
	// Records the current time
	start = clock();
	
	DLL listMembers;
	
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
	while(!input.eof()){
		input >> operation >> SSN >> firstName >> lastName;
		fullName = firstName + " " + lastName;
		
		switch(operation) {
			case 'i': // Insertion
				if (listMembers.insert(SSN, fullName)) {
					iCounter++;
				}
				break;
			case 'd': // Deletion
				if (listMembers.remove(SSN)) {
					dCounter++;
				}
				break;
			case 'r': // Retrieval
				if (listMembers.search(SSN) != nullptr) {
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
	cout << "Number of items in the list: " << listMembers.size() << endl;
	cout << "Time elapsed: " << duration << endl;
	
	return 0;
}