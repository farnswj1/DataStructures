/* Justin Farnsworth
 * December 7, 2017
 * SLLNode.h
 * 
 * This is the implementation of the node, which is used to store the data.
 */

#include <iostream>
using namespace std;

// Node class
template <class T>
struct SLLNode {
  T SSN;
  T name;
  SLLNode<T>* next;
};
