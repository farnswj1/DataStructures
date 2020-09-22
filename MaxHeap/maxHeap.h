/* Justin Farnsworth
 * September 21, 2020
 * maxHeap.h
 * 
 * This is the implementation of the max heap.
 */

#include <iostream>
#include "node.h"
using namespace std;

// Max heap class
template <class U>
class MaxHeap {
	int numElements = 0;
	int heapSize;
	Node<U>** heap; // Used to store pointers of nodes
	
	private:
	// Calculates the left child's index
	int leftChild(int index) {
		return 2*index + 1;
	}
	// Calculates the right child's index
	int rightChild(int index) {
		return 2*index + 2;
	}
	
	// Calculates the parent's index
	int parent(int index) {
		return (index-1) / 2;
	}
	
	// Checks if the node is a leaf (has no children)
	bool isLeaf(int index) {
		return ((leftChild(index) >= numElements) && (rightChild(index) >= numElements));
	}
	
	// Checks if the node has a left child
	bool hasOneChild(int index) {
		return ((leftChild(index) < numElements) && (rightChild(index) >= numElements));
	}
	
	// Checks if the heap maintains the max heap property. Used for debugging
	// Internal function. Cannot be called directly
	bool hasMaxProperty(int index) {
		if (isLeaf(index)) { // No children
			return true;
		}  else if (hasOneChild(index)) { // Left child
			if (heap[index]->SSN < heap[leftChild(index)]->SSN) {
				return false;
			} else {
				return hasMaxProperty(leftChild(index));
			}
		} else { // Node has two children
			if (heap[index]->SSN < heap[leftChild(index)]->SSN || 
				heap[index]->SSN < heap[rightChild(index)]->SSN) {
				return false;
			} else {
				return hasMaxProperty(rightChild(index)) && hasMaxProperty(leftChild(index));
			}		
		}
	}

	public:
	// Default constructor
	MaxHeap() {
		heapSize = 1000;
		heap = new Node<U>*[heapSize];
	}
	
	// Constructor with customizable size
	MaxHeap(int size) {
		heapSize = size;
		heap = new Node<U>*[heapSize];
	}
	
	// Destructor
	~MaxHeap() {
		for (int i = 0; i < numElements; i++){
			delete heap[i];
		}
		delete heap;
	}
	
	// Returns the max node
	Node<U>* maxNode() {
		return heap[0];
	}

	// Searches for the node with a specified value
	Node<U>* search(U item) {
		for (int index = 0; index < numElements; index++) {
			if (heap[index]->SSN == item) { // Match has been found
				return heap[index];
			}
		}
		return nullptr;
	}
	
	// Adds a node to the heap
	bool insert(U item1, U item2) {
		if (search(item1) == nullptr && numElements != heapSize) { // No duplicates and not full
			// Create the node
			Node<U>* node = new Node<U>;
			node->SSN = item1;
			node->name = item2;

			// Place the node at the first available index
			heap[numElements] = node;
			
			// Save the indices for a possible bubble-up
			int index = numElements;
			int parentIndex = parent(index);

			// Bubble-up
			while (heap[index]->SSN > heap[parentIndex]->SSN) { // Child is greater than the parent
					// Swap their data 
					U tempSSN = heap[index]->SSN;
					U tempName = heap[index]->name;
				
					heap[index]->SSN = heap[parentIndex]->SSN;
					heap[index]->name = heap[parentIndex]->name;

					heap[parentIndex]->SSN = tempSSN;
					heap[parentIndex]->name = tempName;
				
				// Move up a level
				index = parentIndex;
				parentIndex = parent(index);
			}
			// Insertion successful
			numElements++;
			return true;
		}
		return false; // No node was inserted
	}

	// Removes the node with a specified value
	bool remove(U item) {
		// Check if the key exists in the heap
		int index = searchIndex(item);

		// Deletes the node if found
		if (index != -1) { // The node was found
			// Replace the max node's data with the last node's data
			heap[index]->SSN = heap[numElements-1]->SSN;
			heap[index]->name = heap[numElements-1]->name;

			// Delete the node and update the number of nodes in the heap
			delete heap[numElements-1];
			numElements--;

			// Save the parent's index for a possible bubble-up
			int parentIndex = parent(index);

			// Save the children's indices for a possible bubble-down
			int leftChildIndex = leftChild(index);
			int rightChildIndex = rightChild(index);

			// Checks if the node needs to bubble up or down (depends on the parent's value)
			if (numElements > 0 && index < numElements) { // Empty or last node was deleted
				if (heap[index]->SSN > heap[parentIndex]->SSN) {
					// Bubble-up
					while (heap[index]->SSN > heap[parentIndex]->SSN) { // Greater than the parent
						// Swap their data
						U tempSSN = heap[index]->SSN;
						U tempName = heap[index]->name;
					
						heap[index]->SSN = heap[parentIndex]->SSN;
						heap[index]->name = heap[parentIndex]->name;

						heap[parentIndex]->SSN = tempSSN;
						heap[parentIndex]->name = tempName;
				
						// Move up a level
						index = parentIndex;
						parentIndex = parent(index);
					}
				} else {
					// Terminates the bubble-down when necessary
					bool terminateLoop = false;

					// Bubble-down
					while (!terminateLoop) {
						if (isLeaf(index)) { // Has no children
							terminateLoop = true;
						} else if (hasOneChild(index)) { // Node has one child (left child)
							if (heap[index]->SSN < heap[leftChildIndex]->SSN) {
								// Swap current node's data with its left child's data
								U tempSSN = heap[index]->SSN;
								U tempName = heap[index]->name;

								heap[index]->SSN = heap[leftChildIndex]->SSN;
								heap[index]->name = heap[leftChildIndex]->name;

								heap[leftChildIndex]->SSN = tempSSN;
								heap[leftChildIndex]->name = tempName;
							}
							terminateLoop = true; // No more nodes beyond this point
						} else { // Has both children
							U leftSSN = heap[leftChildIndex]->SSN;
							U rightSSN = heap[rightChildIndex]->SSN;

							// Checks if the node's key is less than any of the children's keys
							if (heap[index]->SSN < (leftSSN < rightSSN ? rightSSN : leftSSN)) {
								// Save the current node's data for a swap
								U tempSSN = heap[index]->SSN;
								U tempName = heap[index]->name;

								if (heap[index]->SSN < leftSSN && leftSSN > rightSSN) {
									// Swap their data
									heap[index]->SSN = heap[leftChildIndex]->SSN;
									heap[index]->name = heap[leftChildIndex]->name;

									heap[leftChildIndex]->SSN = tempSSN;
									heap[leftChildIndex]->name = tempName;

									index = leftChildIndex; // Go to the left for the next loop
								} else if (heap[index]->SSN < rightSSN && leftSSN < rightSSN) {
									// Swap their data
									heap[index]->SSN = heap[rightChildIndex]->SSN;
									heap[index]->name = heap[rightChildIndex]->name;

									heap[rightChildIndex]->SSN = tempSSN;
									heap[rightChildIndex]->name = tempName;

									index = rightChildIndex; // Go to the right for the next loop
								}
								// Move down a level
								leftChildIndex = leftChild(index);
								rightChildIndex = rightChild(index);
							} else { // Cannot bubble-down any further
								terminateLoop = true;
							}
						}
					}
				}
			}
			return true; // Deletion successful
		} else {
			return false; // No node was deleted
		}
	}

	// Returns the number of nodes in the heap
	int size() {
		return numElements;
	}

	// Returns the maximum number of nodes the heap can hold
	int getHeapSize() {
		return heapSize;
	}

	// Returns the index of the node with the specified key
	int searchIndex(U item) {
		for (int index = 0; index < numElements; index++) {
			if (heap[index]->SSN == item) {
				return index; // Node was found
			}
		}
		return -1; // No node was found
	}

	// Prints the keys in the order of the array
	void print() {
		for (int i = 0; i < numElements; i++) {
			cout << heap[i]->SSN << endl;
		}
	}

	// Checks if the heap maintains the max heap property. Used for debugging
	bool hasMaxProperty() {
		if (numElements > 0) { // Heap is not empty
			return hasMaxProperty(0);
		} else { // Heap is empty
			return true;
		}
	}
};