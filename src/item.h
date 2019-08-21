#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <cstdint>
#include <iostream>
#include <memory> //for unique pointers that item can be assigned to outside of item class
#include "Node.h"

class Item
{
public:
    Item();
    ~Item();
    
    //for what type of item it is
    enum class ItemType : std::int8_t {NONE=0,NODE};
    
//Outside Item Members
    void setNextItemPointer(Item* thisItem);
    Item* getNextItemPointer();
    
    void setKey(std::string thisKey);
    std::string getKey();
    
    void printKey();
    
//Inside Item Members
    //Item Type
    void setItemType(Item::ItemType thisType);
    Item::ItemType getItemType();

//Node Functions
    void setThisNodeElementPointer(Node* thisNode);
    Node* getThisNodeElementPointer();
    
    
private:

//Outside Item Members
    //Item pointer
    Item* ptrToNextItem;
    //key to identify item by
    std::string key;
    
//Inside Item Members
    //type of item
    ItemType type;
//Node
    //Pointer holds node element
    Node* thisNodeElement;
    
};

#endif