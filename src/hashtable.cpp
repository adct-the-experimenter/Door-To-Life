#include "hashtable.h"

//function to return a string from converting number to char

std::string setNumberToASCII_string(int number)
{
    std::ostringstream os;
	os << number;
	std::string returnKey = os.str() ;
    //std::string returnKey = std::to_string(number);
    //std::cout << "Number " << number << "is " << returnKey << "in string. \n";  
    return returnKey;
}



// Constructs the empty Hash Table object.
// Array length is set to 13 by default.
HashTable::HashTable( std::int8_t tableLength )
{
    if (tableLength <= 0){ tableLength = 10;}
    //linkedListArray = new LinkedList[ tableLength ];
    linkedListArray.resize(tableLength);
    tableSize = tableLength;
}

// De-allocates all memory used for the Hash Table.
HashTable::~HashTable()
{
    //HashTable::freeEntireTable();
}

void HashTable::freeEntireTable()
{
    //std::cout << "Hash table free entire table called! \n";
    //delete [] linkedListArray;
    for(size_t i=0; i < linkedListArray.size(); i++)
    {
        linkedListArray[i].freeList();
    }

}

// Returns an array location for a given item key.
int HashTable::hash(  std::string itemKey )
{
    int value = 0;
    for ( int i = 0; i < itemKey.length(); i++ ){value += itemKey[i];}
    return (value * itemKey.length() ) % tableSize;
}


// Adds an item to the Hash Table.
void HashTable::insertItem( Item * newItem )
{
    int index = hash( newItem->getKey());
    linkedListArray[ index ].insertItem( newItem );
}

// Deletes an Item by key from the Hash Table.
// Returns true if the operation is successful.
bool HashTable::removeItem(  std::string itemKey )
{
    int index = hash( itemKey );
    return linkedListArray[ index ].removeItem( itemKey );
}

// Returns an item from the Hash Table by key.
// If the item isn't found, a null pointer is returned.
Item * HashTable::getItemByKey( std::string itemKey )
{
    int index = hash( itemKey );
    return linkedListArray[ index ].getItem( itemKey );
}

Item* HashTable::getItemByKeyAndIndex(std::string itemKey,std::int8_t& itemIndex)
{
    int index = hash( itemKey );
    return linkedListArray[ index ].getItemByItemIndex( itemKey, itemIndex );
}

// Display the contents of the Hash Table to console window.
void HashTable::printTable()
{
    std::cout << "\n Hash Table:\n";
    for ( int i = 0; i < tableSize; i++ )
    {
        std::cout << "Bucket " << i + 1 << ": ";
        linkedListArray[i].printList();
    }
}

// Prints a histogram illustrating the Item distribution.
void HashTable::printHistogram()
{
    std::cout << "\n\nHash Table Contains ";
    std::cout << getNumberOfItems() << " Items total\n";
    for ( int i = 0; i < tableSize; i++ )
    {
        std::cout << i + 1 << ":\t";
        for ( int j = 0; j < linkedListArray[i].getLength(); j++ )
        {
            std::cout << " X";
            std::cout << "\n";
        }
    }
}


// Returns the number of locations in the Hash Table.
int HashTable::getLength()
{
    return tableSize;
}

// Returns the number of Items in the Hash Table.
int HashTable::getNumberOfItems()
{
    int itemCount = 0;
    for ( int i = 0; i < tableSize; i++ )
    {
        itemCount += linkedListArray[i].getLength();
    }
    return itemCount;
}

