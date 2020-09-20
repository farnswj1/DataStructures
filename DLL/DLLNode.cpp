/* Justin Farnsworth
 * November 5, 2017
 * DLLNode.cpp
 * 
 * This is the implementation of the DLL node.
 * 
 * Compile Command:
 * g++ test.cpp DLL.cpp DLLNode.cpp -o test
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
#include "DLLNode.h"
using namespace std;

// DLL Node constructor
DLLNode::DLLNode(string ss, string na){
    ssn = ss; // Key
    name = na;
    succ = nullptr;
    pred = nullptr;
}