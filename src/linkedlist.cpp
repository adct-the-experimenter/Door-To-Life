#include "linkedlist.h"


// Constructs the empty linked list object.
// Creates the head node and sets length to zero.
LinkedList::LinkedList()
{
    //set head item to point to nullptr 
    headItem = nullptr;
    //initialize list length to zero
    listLength = 0;
}

// De-allocates list memory when the program terminates.
LinkedList::~LinkedList()
{
    //LinkedList::freeList();
    //std::cout << "Linked list destructor called! \n";
}

void LinkedList::freeList()
{
    //std::cout << "Linked list free list called! \n";
    //if headItem is not pointing to nullptr
    if(headItem != nullptr)
    {
        //if headItem next pointer is not nullptr
        if(headItem->getNextItemPointer() != nullptr)
        {
            //go down list and set all to nullptr
            
            Item * current = headItem->getNextItemPointer();
            Item * previous = headItem;
            
            //while current is not nullptr
            //set previous to nullptr
            //set current to point to next of current item
            //repeat
            while (current != nullptr)
            {
                //delete previous;
                previous = nullptr;
                
                current = current->getNextItemPointer();
                previous = current;
            }
            
            headItem = nullptr;
        }
        else{headItem = nullptr;}
    }
    //else do nothing
    listLength = 0;
}

// Inserts an item at the end of the list.
void LinkedList::insertItem( Item* newItem )
{
    //std::cout << "Node address " << newItem->getThisNodeElementPointer() << "in insertItem!"
    //<< "Key: " << newItem->getKey() << "\n";
    
    //if head item pointer is pointing to nullptr
    if(headItem == nullptr)
    {
        headItem = newItem;
        listLength += 1;
    }
    //if head item next pointer is pointing to nullptr
    else if (headItem->getNextItemPointer() == nullptr)
    {
        //set its next pointer to point to newItem
        //headItem->ptrToNextItem = newItem;
        headItem->setNextItemPointer(newItem);
        //increment listLength by 1
        listLength += 1;
    }
    //else if head item next pointer is not pointing to nullptr
    //means there is already an item in list
    else
    {
        Item * current = headItem;
        Item * next = headItem;
        
        //keep going down list until find an item without next pointer
        while(next != nullptr)
        {
            current = next;
            if(current->getNextItemPointer() == nullptr){break;}
            next = current->getNextItemPointer();
        }
        
        //after reached item that doesn't point to next item
        //current->ptrToNextItem = newItem;
        //newItem->ptrToNextItem = nullptr;
        current->setNextItemPointer(newItem);
        newItem->setNextItemPointer(nullptr);
        //increment list length by 1
        listLength += 1;
    }
    
    
}

// Removes an item from the list by item key.
// Returns true if the operation is successful.
bool LinkedList::removeItem( std::string itemKey )
{
    //if no other item in list
    if (headItem->getNextItemPointer() == nullptr ){return false;}
    //else if other items in list
    else
    {
        Item * current = headItem;
        Item * next = headItem;

        // go through list of items
        while (next != nullptr)
        {
            //if next item has key that matches 
            if (next->getKey() == itemKey)
            {
                //make curent's next pointer point to next's next pointer
                //removes the pointer in between current and next item after next 
                current->setNextItemPointer(next->getNextItemPointer());
                //delete q;
                //decrement list length by 1
                listLength -= 1;
                return true;
            }
            current = next;
            next = current->getNextItemPointer();
        }
        return false;
    }
    
}

// Searches for an item by its key.
// Returns a reference to first match.
// Returns a NULL pointer if no match is found.
Item* LinkedList::getItem( std::string itemKey )
{
    Item * current = headItem;
    Item * next = headItem;
    //go through list
    while (next != nullptr)
    {
        
        //if current is not head item 
        //and current key matches item key
        //return current
        if ( /*current != headItem &&*/ (*current).getKey() == itemKey){return current;}
        else
        {
           //move current to next
            current = next;
            //move next to next item for current
            if(current != nullptr){next = current->getNextItemPointer(); }
            //else{break;}
        }
        
    }
    
    return nullptr;
}

Item* LinkedList::getItemByItemIndex(std::string itemKey, std::int8_t& itemIndex)
{
    Item * current = headItem;
    Item * next = headItem;
    
    std::int8_t count = 0;
    
    if(itemIndex >= listLength)
    {
        std::cout << "Invalid item index! \n";
        return nullptr;
    }
    
    //go through list
    while (next != nullptr)
    {
        
        //if current is not head item 
        //and current key matches item key
        //return current
        if ( /*current != headItem &&*/  
        (*current).getKey() == itemKey)
        {
            if(itemIndex == 0){return current;}
            else
            {
                //move to next item until count is equal to itemIndex 
                //+ 1 is for accounting for head item 
                while(count < itemIndex + 1)
                {
                    //move current to next
                    current = next;
                    //move next to next item for current
                    if(current != nullptr){next = current->getNextItemPointer(); }
                    
                    //else{break;}
                    //increment count
                    count++;
                }
                
                return current;
            }
            
        }
        
        
    }
    
    return nullptr;
}

// Displays list contents to the console window.
void LinkedList::printList()
{
    //if list length is zero
    if (listLength == 0)
    {
        std::cout << "\n{NA}\n";
        
    }
    else
    {
        Item * current = headItem;
        Item * next = headItem;
        std::cout << "\n{ Key:";
        while (next != nullptr)
        {
            //move current to next item
            current = next;
            //if (current != headItem)
            //{
                //std::cout << current->getKey();
                current->printKey();
                if (current->getNextItemPointer()){ std::cout << ", ";}
                else{ std::cout << " ";}
            //}
            
            //move next to next item
            //next = current->ptrToNextItem;
            next = current->getNextItemPointer();
        }
        std::cout << "}\n";
    }
    
    
}

// Returns the length of the list.
std::int8_t LinkedList::getLength()
{
    return listLength;
}

