/* Justin Farnsworth
 * December 7, 2017
 * AVLTree.h
 * 
 * This is the header file of the AVL tree.
 */

#include <iostream>
#include <string>
#include "AVLNode.h"
using namespace std;

// AVL Tree class
class AVLTree{
    AVLNode* root;
    int treeSize;
    
    public:
    AVLTree();                            // Constructor
    ~AVLTree();                           // Destructor
    AVLNode* getRoot();                   // Returns the root
    AVLNode* rotateRight(AVLNode* node);  // Rotates right the subtree rooted at the node
    AVLNode* rotateLeft(AVLNode* node);   // Rotates left the subtree rooted at the node
    AVLNode* balance(AVLNode* node);      // Balances the tree
    AVLNode* maxOfSubtree(AVLNode* node); // Finds the node with largest value in the subtree
    AVLNode* find(string ss);             // Searches ss value in the AVL tree
    bool insert(string ss, string na);    // Inserts data to the tree and rebalances if necessary
    bool deleteNode(string ss);           // Deletes the node with ss and rebalances if necessary
    int height(AVLNode* node);            // Returns the height of the subtree rooted at node
    int balanceFactor(AVLNode* node);     // Returns the balance factor of the node
    int size();                           // Returns the number of nodes in the tree
    int computeSize();                    // Computes the number of nodes in the tree
    void updateHeight(AVLNode* node);     // Updates the height value of a given node
    void print(AVLNode* x, int indent);   // Prints the key value of the node
    void print();                         // Prints out the structure of the tree
};
