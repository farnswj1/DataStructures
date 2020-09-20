/* Justin Farnsworth
 * December 7, 2017
 * AVLNode.cpp
 * 
 * This is the implementation of the AVL node.
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
#include "AVLNode.h"
using namespace std;

// AVL Node constructor
AVLNode::AVLNode(string ss, string na){
    ssn = ss; // Key
    name = na;
    height = 0;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}
