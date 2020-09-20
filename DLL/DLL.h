/* Justin Farnsworth
 * November 5, 2017
 * DLL.h
 * 
 * This is the header file of the doubly-linked list.
 */ 

#include <string>
#include "DLLNode.h"
using namespace std;

// Doubly-linked list class
class DLL{
    private:
    DLLNode* headPtr;
    DLLNode* tailPtr;
    int listSize;
    
    public:
    DLL();                               // Constructor
    DLL(DLL& n);                         // Deepcopy constructor
    virtual ~DLL();                      // Destructor
    DLLNode* getHeadPtr();               // Returns the head pointer of the list
    DLLNode* getTailPtr();               // Returns the tail pointer of the list
    DLLNode* search(string ss) const;    // Searches for the node with key value ss
    bool insert(string ss, string name); // Inserts data to the list
    bool remove(string ss);              // Deletes data from the list
    int getIndex(string ss) const;       // Returns the index of the node with key value ss
    int size();                          // Prints out the key and memory address of each node
    void display();                      // Prints the contents of the list
};