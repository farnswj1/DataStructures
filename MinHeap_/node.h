/* Justin Farnsworth
 * September 21, 2020
 * node.h
 * 
 * This is the implementation of the node.
 */

#include <iostream>
#include <string>
using namespace std;

// Node class
template <class T>
struct Node {
	T SSN; // Key
	T name;
};