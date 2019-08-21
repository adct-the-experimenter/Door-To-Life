#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "linkedlist.h"

#include <string>
#include <sstream>

//function to return a string from converting number to char
std::string setNumberToASCII_string(int number);

class HashTable
{

public:

     // Constructs the empty Hash Table object.
    // Array length is set to 10 by default.
    HashTable( std::int8_t tableLength = 10 );
    ~HashTable();
    
    // Adds an item to the Hash Table.
    void insertItem( Item* newItem );
    
    // Deletes an Item by key from the Hash Table.
    // Returns true if the operation is successful.
    bool removeItem(  std::string itemKey );
    
    // Returns an item from the Hash Table by key.
    // If the item isn't found, a null pointer is returned.
    Item* getItemByKey(  std::string itemKey );
    
    Item* getItemByKeyAndIndex(std::string itemKey,std::int8_t& itemIndex);
    
    // Display the contents of the Hash Table to console window.
    void printTable();
    
    // Prints a histogram illustrating the Item distribution.
    void printHistogram();
    
    // Returns the number of locations in the Hash Table.
    int getLength();
    
    // Returns the number of Items in the Hash Table.
    int getNumberOfItems();
    
    void freeEntireTable();
    
    //options to choose hash method
    //enum class HashMethod : std::int8_t {HASH_BY_NAME=0, HASH_BY_NUM_LTG };

private:
    
    // Array is a reference to an array of Linked Lists.
    //LinkedList* linkedListArray;
    std::vector <LinkedList> linkedListArray;
    
    // Length is the size of the Hash Table array.
    std::int8_t tableSize;
    
    // Returns an array location for a given item key.
    int hash( std::string itemKey );
    
};

#endif