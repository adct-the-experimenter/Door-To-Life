#include "item.h"

Item::Item()
{
    //std::cout << "Item " << this << " constructor called! \n";
    Item::setKey("empty constructed");
    Item::setNextItemPointer(nullptr);
    Item::setThisNodeElementPointer(nullptr);
    Item::setItemType(Item::ItemType::NONE);
}

Item::~Item()
{
    Item::setKey("empty destructed");
    Item::setNextItemPointer(nullptr);
    Item::setThisNodeElementPointer(nullptr);
    Item::setItemType(Item::ItemType::NONE);
    
    //std::cout << "Item " << this << " destructor called! \n";
}

void Item::setNextItemPointer(Item* thisItem){ptrToNextItem = thisItem;}
Item* Item::getNextItemPointer(){return ptrToNextItem;}

void Item::setKey(std::string thisKey)
{
    key.clear();
    key.assign(thisKey);
}
std::string Item::getKey(){return key;}
void Item::printKey(){std::cout << Item::getKey();}

void Item::setItemType(Item::ItemType thisType){type = thisType;}
Item::ItemType Item::getItemType(){return type;}

void Item::setThisNodeElementPointer(Node* thisNode){thisNodeElement = thisNode;}
Node* Item::getThisNodeElementPointer(){return thisNodeElement;}
