/* Justin Farnsworth
 * November 7, 2017
 * AVLTree.cpp
 * 
 * This is the implementation of the AVL tree.
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
#include <string>
#include "AVLTree.h"
#include <iomanip>
#include <queue>
using namespace std;

// Constructor
AVLTree::AVLTree(){
    root = nullptr;
	treeSize = 0;
}

// Destructor (uses level order traversal to delete the nodes)
AVLTree::~AVLTree(){
    if (root != nullptr) { // Tree is not empty
		// Use a queue to traverse the tree
		queue<AVLNode*> q;
		q.push(root);
		int nodeCount = 1;

		// Deletes the nodes row by row until none remain
		while (nodeCount > 0) {
			AVLNode* node = q.front();
			q.pop();
			nodeCount--;

			// Add the left child to the queue if it exists
			if (node->left != nullptr) {
				q.push(node->left);
				nodeCount++;
			}

			// Add the right child to the queue if it exists
			if (node->right != nullptr) {
				q.push(node->right);
				nodeCount++;
			}

			// Delete the current node
			delete node;	
		}
	}
}

// Returns the root
AVLNode* AVLTree::getRoot(){
    return root;
}

// Searches ss value in the AVL tree
AVLNode* AVLTree::find(string ss){
    if (root != nullptr) { // Tree is not empty
		AVLNode* node = root;

		// Uses the key values to navigate down the tree to the projected location
    	while (node != nullptr) {
        	if (ss.compare(node->ssn) == 0) { // Node has been found
            	return node;
        	} else if (ss.compare(node->ssn) < 0) { // Current value is greater than ss. Go left
            	node = node->left;
        	} else { // Current value is less than ss. Go right
            	node = node->right;
        	}
    	}
	}
    return nullptr; // The value ss doesn't exist in the tree
}

// Returns the height of the subtree rooted at node.
// If the subtree is empty, then it returns -1.
// If the subtree has one node, then it returns 0
int AVLTree::height(AVLNode* node){
    if (node != nullptr) {
        return node->height;
    } else {
        return -1;
    }
}

// Returns the balance factor of the node
int AVLTree::balanceFactor(AVLNode* node){
    return height(node->left) - height(node->right);
}

// Updates the height value of a given node
void AVLTree::updateHeight(AVLNode* node){
    int hl = height(node->left);
    int hr = height(node->right);
    node->height = (hl>hr ? hl : hr) + 1;
}

// Rotates right the subtree rooted at node and
// returns the new root of the subtree.
AVLNode* AVLTree::rotateRight(AVLNode* node){
    AVLNode* lp = node->left; // Left child of node
    if (node->parent != nullptr) { // Node is not the root
        if (node->parent->left == node) { // Node is a left child
            node->parent->left = lp;
        } else { // Node is a right child
            node->parent->right = lp;
        }
    }

    if (lp->right != nullptr) { // Pointer update
        lp->right->parent = node;
    }
    
    lp->parent = node->parent;
    node->left = lp->right;
    lp->right = node;
    node->parent = lp;

	// After rotation, updates height
    updateHeight(node); 
    updateHeight(lp);

    if (node == root) { // Node is the root
        root = lp;
    }

    return lp; // lp is the new root of the subtree
}


// Rotates left the subtree rooted at the node and
// returns the new root of the subtree
AVLNode* AVLTree::rotateLeft(AVLNode* node){
    AVLNode* rp = node->right; // Right child of node
    if (node->parent != nullptr) { // Node is not the root
        if (node->parent->left == node) {
            node->parent->left = rp;
        } else { // Node is a left child
            node->parent->right = rp;
        }
    }

    if (rp->left != nullptr) { // Pointer update
       rp->left->parent = node;
    }
    
    rp->parent = node->parent;
    
    node->right = rp->left;
    rp->left = node;
    node->parent = rp;
    node->parent = rp;
	
	// After rotation, updates height
    updateHeight(node);
    updateHeight(rp);

    if (node == root) { // Node is the root
        root = rp;
    }

    return rp;// lp is the new root of the subtree
}

// Balances the tree and returns the new root of the subtree
AVLNode* AVLTree::balance(AVLNode* node){
    updateHeight(node);

    if (balanceFactor(node) == 2) { // Tree leans to the left
        if (balanceFactor(node->left) < 0) { // Left-right case
            node->left = rotateLeft(node->left);
        }
        
		// Rotates to the right
        AVLNode* temp = rotateRight(node);
        updateHeight(temp);

        return temp;
    }
    
    if (balanceFactor(node) == -2) { // Tree leans to the right
        if (balanceFactor(node->right) > 0) { // Right-left case
            node->right = rotateRight(node->right);
        }

		// Rotates to the left
        AVLNode* temp2 = rotateLeft(node);
        updateHeight(temp2);

        return temp2;
    }
    
	return node; // No rotation occurred
}


// Inserts data to the tree and rebalances if necessary
bool AVLTree::insert(string ss, string na){
    if (root == nullptr) { // Tree is empty
		AVLNode* link = new AVLNode(ss, na);
		root = link;
		treeSize++;
		return true;
	} else { // Tree is not empty
		AVLNode* curr = root;

		// Traverse down the tree
		while (curr != nullptr) {
			if (ss < curr->ssn) { // ss is less than the current node's key
				if (curr->left == nullptr) { // No left child. Insert node into the tree
					AVLNode* link = new AVLNode(ss, na);
					curr->left = link;
					link->parent = curr;

					// Balance the tree
					while (curr != nullptr) {
						curr = balance(curr);
						curr = curr->parent;
					}
					
					treeSize++;

					return true; // Insertion successful
				} else { // Left child exists
					curr = curr->left; // Go to the left child
				}
			} else if (ss > curr->ssn) { // ss is greater than the current node's key
				if (curr->right == nullptr) { // No right child. Insert node into the tree
					AVLNode* link = new AVLNode(ss, na);
					curr->right = link;
					link->parent = curr;

					// Balance the tree
					while (curr != nullptr) {
						curr = balance(curr);
						curr = curr->parent;
					}

					treeSize++;

					return true; // Insertion successful
				} else { // Right child exists
					curr = curr->right;
				}
			} else { // Duplicate exists. Abort insertion
				return false;
			}
		}
	}
}

// Finds the node with largest value in the subtree
AVLNode* AVLTree::maxOfSubtree(AVLNode* node){
    if (node == nullptr) { // Node argument is null
        return nullptr;
    }

	// Keep going right until the rightmost node has been obtained
    while (node->right != nullptr) {
        node = node->right;
    }

    return node;
}

// Deletes the node with ss and rebalances if necessary
bool AVLTree::deleteNode(string ss){
	// Start at the root
	AVLNode* curr = root;
	AVLNode* prev = nullptr;
	
	// Traverse the tree until the node is found or until there are no nodes left
    while (curr != nullptr) {
		if (ss < curr->ssn) { // Node's key is greater than ss
			// Go to the left child
			prev = curr;
			curr = curr->left;
		} else if (ss > curr->ssn) { // Node's key is less than ss
			// Go to the right child
			prev = curr;
			curr = curr->right;
		} else { // A match has been found
			AVLNode* temp = prev; // Needed for balancing the tree after deleting the node

			// Handles the scenarios of children nodes
			if ((curr->left == nullptr) && (curr->right == nullptr)) { // No child nodes
				// Set null the pointer referring to the current node
				if (root != curr) { // Current node is not the root
					if (prev->left == curr) { // Current node is a left child
						prev->left = nullptr;
					} else if (prev->right == curr) { // Current node is a right child
						prev->right = nullptr;
					}
				} else { // Current node is the root
					root = nullptr;
				}

				delete curr;
			} else if ((curr->left != nullptr) && (curr->right == nullptr)) { // Only left child
				if (prev == nullptr) { // Root case
					root = curr->left;
					root->parent = nullptr;
				} else if (prev->left == curr) { // Current node is a left child
					// Connects the parent node and left child to each other
					prev->left = curr->left;
					curr->left->parent = prev;
				} else { // Current node is a right child
					// Connects the parent node and left child to each other
					prev->right = curr->left;
					curr->left->parent = prev;
				}

				delete curr;
			} else if ((curr->left == nullptr) && (curr->right != nullptr)) { // Only right child
				if (prev == nullptr) { // Root case
					root = curr->right;
					root->parent = nullptr;
				} else if (prev->left == curr) { // Current node is a left child
					// Connects the parent node and right child to each other
					prev->left = curr->right;
					curr->right->parent = prev;
				} else { // Current node is a right child
					// Connects the parent node and right child to each other
					prev->right = curr->right;
					curr->right->parent = prev;
				}

				delete curr;
			} else { // Both child nodes present
				// Get the node with the highest value from the left subtree
				AVLNode* succ = maxOfSubtree(curr->left);

				// Overwrite the current node's values with succ's values
				curr->ssn = succ->ssn;
				curr->name = succ->name;

				// Save the parent node of succ
				prev = succ->parent;
				temp = prev; // Change temp to be succ's parent

				// Connects the parent node to succ's left child
				if (curr->left == succ) { // Only possible if succ is curr's left child
					if (succ->left != nullptr) { // Left child
						// Connects the parent of succ to succ's left child
						curr->left = succ->left;
						succ->left->parent = prev;
					} else { // No left child
						prev->left = nullptr;
					}
				} else { // Current node is NOT curr's left child
					if (succ->left != nullptr) { // Left child
						// Connects the parent of succ to succ's left child
						prev->right = succ->left;
						succ->left->parent = prev;
					} else { // No left child
						prev->right = nullptr;
					}
				}

				delete succ;
			}

			// Balance the tree if necessary as temp traverses to the root
			while (temp != nullptr) {
				temp = balance(temp);
				temp = temp->parent;
			}

			treeSize--;

			return true; // Deletion successful
		}
	}
	return false; // No node was deleted
}

// Prints the key value of the node
// NOTE: Internal function. Do not call it directly
void AVLTree::print(AVLNode* x, int indent){
    if (x != nullptr) { // Continues if x is a node
		// Uses recursion to print the right node(s)
    	if (x->right != nullptr) {
        	print(x->right, indent+4);
    	}

		// Prints whitespace to help visualize the tree and put space between the keys
    	if (indent != 0) {
        	cout << std::setw(indent) << ' ';
    	}

		// Draws the edge which represents a relationship between the nodes
    	if(x->right != nullptr){
        	cout << " /\n" << std::setw(indent) << ' ';
    	}

		// Prints the key of the node
    	cout << x->ssn << endl;

		// Uses recursion to print the left node(s)
    	if (x->left != nullptr) {
        	cout << std::setw(indent) << ' ' <<" \\\n"; // Draws the edge
        	print(x->left, indent+4);
    	}
	}
}

// Prints out the structure of the tree
void AVLTree::print(){
    print(root, 0);
}

// Returns the number of nodes in the tree
int AVLTree::size(){
	return treeSize;
}

// Computes and returns the number of nodes in the tree. Used for debugging
int AVLTree::computeSize(){
	int numNodes = 0; // Tracks the number of nodes in the queue

	// Count the nodes if the tree is not empty
    if (root != nullptr) {
		// Push the root to the queue
		queue<AVLNode*> q;
		q.push(root);

		// Uses level order traversal to count the nodes
		while (q.size() > 0) {
			AVLNode* node = q.front(); // Gets the node at the front of the queue
			numNodes++;

			// If the left child exists, add it to the queue
			if (node->left != nullptr) {
				q.push(node->left);
			}

			// If the right node exists, add it to the queue
			if (node->right != nullptr) {
				q.push(node->right);
			}

			// Remove the node from the queue
			q.pop();
		}
	}
	
	return numNodes;
}
