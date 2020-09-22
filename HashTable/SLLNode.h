/* Justin Farnsworth
 * December 7, 2017
 * SLLNode.h
 * 
 * This is the implementation of the SLL node.
 */

#include <iostream>
using namespace std;

// SLL node class
template <class T>
struct SLLNode {
  T SSN;
  T name;
  SLLNode<T>* next;
};
