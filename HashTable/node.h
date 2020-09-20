/* Justin Farnsworth
 * December 7, 2017
 * node.h
 * 
 * This is the implementation of the node, which is used to store the data.
 */

#include <iostream>
using namespace std;

// Node class
template <class T>
struct Node{
  T SSN;
  T name;
  Node<T>*  next;
};
