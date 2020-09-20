/* Justin Farnsworth
 * November 5, 2017
 * DLLNode.h
 * 
 * This is the header file of the DLL node.
 */

#include <iostream>
#include <string>
using namespace std;

// DLL Tree class
struct DLLNode{
  string ssn; // Key
  string name;
  DLLNode* succ;
  DLLNode* pred;
  
  // Constructor
  DLLNode(string ss, string na);
};