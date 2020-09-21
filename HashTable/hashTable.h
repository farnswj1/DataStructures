/* Justin Farnsworth
 * December 7, 2017
 * hashTable.h
 * 
 * This is the implementation of the hash table.
 * Note the singly-linked lists are used in this hash table for chaining.
 */

#include <iostream>
#include "SLL.h"
using namespace std;

// Hash table class (uses chaining to handle collisions)
template <class V>
class HashTable {
    int tableSize; // Table size
    SLL<V>* table;

    public:
    // Default constructor which uses default table size 3
    HashTable(){
        tableSize = 3;
        table = new SLL<V>[tableSize];
    }

    // Constructor with customizable table size
    HashTable(int size){
		tableSize = size;
        table = new SLL<V>[tableSize];
    }

    // Destructor
    ~HashTable(){
        delete table;
    }

    // Searches for the item in the table.
    // If found, it returns true. Otherwise, it returns false
    SLLNode<V>* find(V item){
        return table[stoi(item) % tableSize].search(item);
    }

    // Inserts (item1, item2) to the table, where item1 is the key.
    // If inserted, it returns true. Otherwise, it returns false
    bool insert(V item1, V item2){
        return table[stoi(item1) % tableSize].insert(item1, item2);
    }

    // Deletes the node containing the specified value
    // If deleted, it returns true. Otherwise, it returns false
    bool erase(V item){
        return table[stoi(item) % tableSize].remove(item);
    }

    // Returns the total number of nodes in the hash table
    int size(){
        int numNodes = 0;
        for (int i = 0; i < tableSize; i++) {
            numNodes = numNodes + table[i].size();
        }
        return numNodes;
    }
};
