#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "item.h"

#include <cstdint>
#include <iostream>


class LinkedList 
{
    
public:
    
    // Constructs the empty linked list object.
    // Creates the head node and sets length to zero.
    LinkedList();
    
    //Deallocates and clears elements
    ~LinkedList();
    
    void freeList();
    
    // Inserts an item at the end of the list.
    void insertItem( Item* newItem );
    
    // Removes an item from the list by item key.
    // Returns true if the operation is successful.
    bool removeItem( std::string itemKey );
    
    // Searches for an item by its key.
    // Returns a reference to first match.
    // Returns a NULL pointer if no match is found.
    Item* getItem( std::string itemKey );
    
    Item* getItemByItemIndex(std::string itemKey,std::int8_t& itemIndex);
    
    // Displays list contents to the console window.
    void printList();
    
    // Returns the length of the list.
    std::int8_t getLength();
        
private:
    //pointer to first element in list
    Item* headItem;
    //length of list
    std::int8_t listLength;
    
        
};

#endif