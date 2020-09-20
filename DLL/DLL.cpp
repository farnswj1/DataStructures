/* Justin Farnsworth
 * November 5, 2017
 * DLL.cpp
 * 
 * This is the implementation of the doubly-linked list.
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
#include <string>
using namespace std;

// Constructor
DLL::DLL(){
    headPtr = nullptr;
	tailPtr = nullptr;
    listSize = 0;
}

// Deepcopy constructor
DLL::DLL(DLL& n){
	if (n.getHeadPtr() != nullptr) { // List is not empty
		// Copy the contents of the head
		DLLNode* head = new DLLNode(n.getHeadPtr()->ssn, n.getHeadPtr()->name);
		head->pred = nullptr;
		this->headPtr = head;

		DLLNode* oldNodeCurr = n.getHeadPtr()->succ;
		DLLNode* newNodePrev = head;

		// Copy the subsequent nodes	
		while (oldNodeCurr != nullptr) {
			// Copy the contents of the current node
			DLLNode* temp = new DLLNode(oldNodeCurr->ssn, oldNodeCurr->name);
			temp->pred = newNodePrev;
			newNodePrev->succ = temp;
			
			// Move to the next node
			newNodePrev = newNodePrev->succ;
			oldNodeCurr = oldNodeCurr->succ;
		}

		// Sets the final node's successor as the tail pointer
		newNodePrev->succ = nullptr; // Sets the final node's successor to null
		tailPtr = newNodePrev;

		listSize = n.size();
	}
}

// Destructor
DLL::~DLL(){
	DLLNode* link = headPtr;
	DLLNode* temp = headPtr;

	// Deletes the nodes one by one
	while (link != nullptr) {
		link = link->succ;
		delete temp;
		temp = link;
	}

	// Set the head and tail pointers to null
	headPtr = nullptr;
	tailPtr = nullptr;
}

// Returns the head pointer of the list
DLLNode* DLL::getHeadPtr(){
    return headPtr;
}

// Returns the head pointer of the list
DLLNode* DLL::getTailPtr(){
    return tailPtr;
}

// Searches for the node with key value ss
DLLNode* DLL::search(string ss)const{
	DLLNode* node = headPtr;

	// Checks each node for a match
	while (node != nullptr) {
		if (node->ssn == ss) { // The node has been found
			return node;
		} else { // Move to the next node
			node = node->succ;
		}
	}
    return nullptr; // No node has been found
}

// Returns the index of the node with key value ss
int DLL::getIndex(string ss)const{
	DLLNode* node = headPtr;
	int index = 0;

	// Checks each node for a match
	while (node != nullptr) {
		if (node->ssn == ss) { // The node has been found
			return index;
		} else { // Move to the next node
			node = node->succ;
			index++;
		}
	}
    return -1; // No node has been found
}

// Inserts data to the list while keeping it sorted
bool DLL::insert(string ss, string name){
	if (headPtr == nullptr) { // List is empty
		// Put the new node at the head and tail
		DLLNode* temp = new DLLNode(ss, name);
		headPtr = temp;
		tailPtr = temp;
		listSize++;
		return true; // Insertion successful
	} else if (ss < headPtr->ssn) { // Key value is less than the head's key value
		DLLNode* temp = new DLLNode(ss, name);
		temp->succ = headPtr; // Old head node is the successor of the new node
		headPtr->pred = temp; // Old head node's predecessor is the new node
		headPtr = temp; // The new head is the new node
		listSize++;
		return true; // Insertion successful
	} else if (ss > tailPtr->ssn) { // Key value is greater than the tail's key value
		DLLNode* temp = new DLLNode(ss, name);
		temp->pred = tailPtr; // Old tail node is the predecessor of the new node
		tailPtr->succ = temp; // Old tail node's successor is the new node
		tailPtr = temp; // The new head is the new node
		listSize++;
		return true; // Insertion successful
	} else { // Key value is betweem the head's and tail's key values
		// These pointers are used to traverse the list
		DLLNode* current = headPtr;
		DLLNode* successor = current->succ;
			
		// Traverse the list for a spot to place the new node
		while (current != tailPtr) {
			if ((current->ssn < ss) && (ss < successor->ssn)) { // Key value fits in between
				DLLNode* temp = new DLLNode(ss, name);

				// Link the nodes to each other
				temp->succ = successor;
				temp->pred = current;
				current->succ = temp;
				successor->pred = temp;
				
				listSize++;
				return true; // Insertion successful
			} else if (current->ssn == ss) { // Duplicate has been found
				return false; // Abort insertion
			} else { // Key value doesn't fit between the two nodes
				// Move up one node
				current = successor;
				successor = successor->succ;
			}
		}
	}
    return false; // No node was inserted
}

// Deletes data from the list while keeping it sorted
bool DLL::remove(string ss){
	if (headPtr != nullptr) { // The list is not empty
		if (ss == headPtr->ssn) { // Head pointer
			DLLNode* oldHeadPtr = headPtr; // Save the old head pointer
			headPtr = headPtr->succ; // Head's successor is the new head
			headPtr->pred = nullptr;
			delete oldHeadPtr;
			listSize--;
			return true; // Deletion successful
		} else if (ss == tailPtr->ssn) { // Tail pointer
			DLLNode* oldTailPtr = tailPtr; // Save the old tail pointer
			tailPtr = tailPtr->pred; // Tail's predecessor is the new tail
			tailPtr->succ = nullptr;
			delete oldTailPtr;
			listSize--;
			return true; // Deletion successful
		} else { // Node is possibly in between the head and tail
			// These pointers are used to traverse the list
			DLLNode* current = headPtr;
			DLLNode* successor = current->succ;
			
			// Traverse the list for the node with ss
			while (current != tailPtr) {
				if (ss == successor->ssn) { // Match has been found
					// Reroute the list around the successor
					successor->succ->pred = current;
					current->succ = successor->succ;

					delete successor;
					listSize--;
					return true; // Deletion successful
				} else { // Not a match
					// Move up one node
					current = successor;
					successor = successor->succ;
				}
			}
		}
	}
    return false; // No node was deleted
}

// Returns the number of nodes in the list
int DLL::size(){
    return listSize;
}

// Prints out the key and memory address of each node
void DLL::display(){
    DLLNode* temp = headPtr;
    while (temp != nullptr) {
        cout << temp->ssn << "\t" << temp << endl;
        temp = temp->succ;
    }
}
