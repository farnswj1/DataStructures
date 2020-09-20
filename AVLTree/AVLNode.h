/* Justin Farnsworth
 * December 7, 2017
 * AVLNode.h
 * 
 * This is the header file of the AVL node.
 */

#include <iostream>
#include <string>
using namespace std;

// AVL Tree class
struct AVLNode{
  string ssn; // Key
  string name;
  AVLNode* left;
  AVLNode* right;
  AVLNode* parent;
  int height;
  
  // Constructor
  AVLNode(string ss, string na);
};
