/* Justin Farnsworth
 * December 7, 2017
 * SLL.h
 * 
 * This is the implementation of the singly-linked list.
 */

#include <iostream>
#include "node.h"
using namespace std;

// Singly-linked list class
template <class U>
class SLL {
    Node<U>* headPtr;
    int size;

    public:
    // Default constructor
    SLL(){
      headPtr = nullptr;
      size = 0;
    }

    // Destructor
    ~SLL(){
        Node<U>* current = headPtr;
        Node<U>* successor;

        // Traverse through the list and delete the nodes
        while(current != nullptr){
            // Get the next node before deleting the current node
            successor = current->next;
            delete current;
            
            // Move to the next node
            current = successor;
        }
        
        headPtr = nullptr;
    }

    // Retrieves the head node
    Node<U>* getHeadPtr(){
        return headPtr;
    }

    // Inserts (item1, item2) to the list
    bool insert(U item1, U item2){
        if (headPtr == nullptr){ // Nothing is in the list (no head pointer)
            Node<U>* link = new Node<U>;
            link->SSN = item1;
            link->name = item2;
			link->next = nullptr;
            headPtr = link; // Creates the head node
            size++;
		} else { // The list isn't empty (head pointer exists)
			Node<U>* previous;
            Node<U>* current = headPtr;

            // Check the list for duplicate keys (item1)
            while (current != nullptr) {
                if (current->SSN == item1) { // Duplicate found. Abort insertion
                    return false;
                }
                // The current node isn't a duplicate. Move to the next node
                previous = current;
                current = current->next;
                
            }

            // At the end of the list, create the node and add to the list
            Node<U>* link = new Node<U>;
            link->SSN = item1;
            link->name = item2;
			link->next = nullptr;
            previous->next = link;
            size++;
        }
        // Node has been successfully inserted
        return true;
    }

    // Searches for a node containing the value of item1.
    // If the item1 value is found, it returns true. Otherwise, it returns false
    Node<U>* search(U item1){
        // Start at the head pointer
        Node<U>* current = headPtr;

        // Traverse the list until a match is found or the list ends
        while(current != nullptr){
            if (current->SSN == item1){ // Value exists in the list
                return current;
            }
            current = current->next;
        }
        // The value doesn't exist in the list
        return nullptr;
    }

    // Removes the node with key value item1
    bool remove(U item1){
		if (headPtr == nullptr) { // Nothing is in the list
			return false;
		}

        // Start at the head
        Node<U>* current = headPtr;
        if (headPtr->SSN == item1) { // The head has the key
            headPtr = headPtr->next; // The next node becomes the head
            delete current;
            size--;
            return true; // Deletion successful
        } else { // Subsequent nodes
            // The current point is the 2nd node, the previous pointer is the head
			Node<U>* previous = current;
			current = current->next;

            // Traverse through the list until the node is found
            while (current != nullptr) {
				if (current->SSN == item1) { // Found the node
					previous->next == current->next;
					delete current;
					size--;
					return true; // Deletion successful
				}
                
                // Move onto the next node
				previous = current;
				current = current->next;
            }
        }
        return false; // No node was deleted
    }

    // Returns the size of the list
    int getSize(){
        return size;
    }

    // Displays the key values of each node in the linked list
    void display(){
        // Start at the head
        Node<U>* temp = headPtr;
		
        // Print the key for each node
        while (temp != nullptr) {
            cout << temp->SSN << endl;
            temp = temp->next;
        }
    }
};
