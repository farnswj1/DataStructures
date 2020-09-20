/* Justin Farnsworth
 * December 7, 2017
 * test.cpp
 * 
 * This program tests the AVL tree by reading a file full of input data.
 * The data may be inserted, deleted, or retrieved.
 * At the end, the number of insertions, deletions, and retrivals will be displayed
 * as well as the amount of time taken to complete.
 * 
 * Compile Command:
 * g++ test.cpp AVLNode.cpp AVLTree.cpp -o test
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
#include "AVLTree.h"
#include <string>
#include <time.h>
#include <ctime>
using namespace std;

// Main function
int main(int argc, char* argv[]) {
	// Keeps track of how long the program takes to complete
	clock_t start, end;
	double duration;
	
	// Record the current time
	start = clock();
	
	AVLTree listMembers;
	
	// Records the number of insertions, deletions, and retrievals
	int iCounter = 0;
	int dCounter = 0;
	int rCounter = 0;
	
	// Variables used for input data
	char operation;
	string SSN;
	string firstName;
	string lastName;
	string fullName;
	
	// Opens the input file
	fstream input(argv[1]);

	// Processes the data line by line
	while (!input.eof()) {
		input >> operation >> SSN >> firstName >> lastName;
		fullName = firstName + " " + lastName;
		
		switch(operation) {
			case 'i': // Insertion
				if (listMembers.insert(SSN, fullName)) {
					iCounter++;
				}
				break;
			case 'd': // Deletion
				if (listMembers.deleteNode(SSN)) {
					dCounter++;
				}
				break;
			case 'r': // Retrieval
				if (listMembers.find(SSN) != nullptr) {
					rCounter++;
				}
				break;
		}
	}

	// Closes the input file
	input.close();
	
	// Computs the total time taken to complete
	end = clock();
	duration = (end - start) / (double) CLOCKS_PER_SEC;
	
	// Summary of the results
	cout << "Number of valid insertations: " << iCounter << endl;
	cout << "Number of valid deletions: " << dCounter << endl;
	cout << "Number of valid retrievals: " << rCounter << endl;
	cout << "Height of the AVL tree: " << listMembers.height(listMembers.getRoot()) << endl;
	cout << "Tree size: " << listMembers.size() << endl;
	cout << "Time elapsed: " << duration << endl;
		
	return 0;
}
