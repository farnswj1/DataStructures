/* Justin Farnsworth
 * September 21, 2020
 * minHeap.h
 * 
 * This is the implementation of the min heap.
 */

#include <iostream>
#include "node.h"
using namespace std;

// Min heap class
template <class U>
class MinHeap {
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

	// Checks if the heap maintains the min heap property. Used for debugging
	// Internal function. Cannot be called directly
	bool hasMinProperty(int index) {
		if (isLeaf(index)) { // No children
			return true;
		} else if (hasOneChild(index)) { // Left child
			if (heap[index]->SSN > heap[leftChild(index)]->SSN) {
				return false;
			} else {
				return hasMinProperty(leftChild(index));
			}
		} else { // Node has two children
			if (heap[index]->SSN > heap[leftChild(index)]->SSN || 
				heap[index]->SSN > heap[rightChild(index)]->SSN) {
				return false;
			} else {
				return hasMinProperty(rightChild(index)) && hasMinProperty(leftChild(index));
			}		
		}
	}

	// Swaps the two nodes
	void swap(Node<U>*& node1, Node<U>*& node2) {
		Node<U>* temp = node1;
		node1 = node2;
		node2 = temp;
	}
	
	public:
	// Default constructor
	MinHeap() {
		heapSize = 1000;
		heap = new Node<U>*[heapSize];
	}
	
	// Constructor with customizable size
	MinHeap(int size) {
		heapSize = size;
		heap = new Node<U>*[heapSize];
	}
	
	// Destructor
	~MinHeap() {
		for (int i = 0; i < numElements; i++) {
			delete heap[i];
		}
		delete heap;
	}
	
	// Returns the min node
	Node<U>* minNode() {
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
			while (heap[index]->SSN < heap[parentIndex]->SSN) { // Child is less than the parent
				// Swap their data
				swap(heap[index], heap[parentIndex]);
				
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
			// Replace the min node's data with the last node's data
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
				if (heap[index]->SSN < heap[parentIndex]->SSN) {
					// Bubble-up
					while (heap[index]->SSN < heap[parentIndex]->SSN) { // Less than the parent
						// Swap their data
						swap(heap[index], heap[parentIndex]);
				
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
							if (heap[index]->SSN > heap[leftChildIndex]->SSN) {
								// Swap current node's data with its left child's data
								swap(heap[index], heap[leftChildIndex]);
							}
							terminateLoop = true; // No more nodes beyond this point
						} else { // Has both children
							U leftSSN = heap[leftChildIndex]->SSN;
							U rightSSN = heap[rightChildIndex]->SSN;

							// Checks if the node's key is greater than any of the children's keys
							if (heap[index]->SSN > leftSSN && leftSSN < rightSSN) {
								// Swap their data
								swap(heap[index], heap[leftChildIndex]);

								index = leftChildIndex; // Go to the left for the next loop
							} else if (heap[index]->SSN > rightSSN && leftSSN > rightSSN) {
								// Swap their data
								swap(heap[index], heap[rightChildIndex]);

								index = rightChildIndex; // Go to the right for the next loop
							} else {
								terminateLoop = true;
							}

							// Move down a level
							leftChildIndex = leftChild(index);
							rightChildIndex = rightChild(index);
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

	// Returns the minimum number of nodes the heap can hold
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

	// Checks if the heap maintains the min heap property. Used for debugging
	bool hasMinProperty() {
		if (numElements > 0) { // Heap is not empty
			return hasMinProperty(0);
		} else { // Heap is empty
			return true;
		}
	}
};