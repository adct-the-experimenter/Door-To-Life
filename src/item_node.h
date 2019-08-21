#ifndef ITEM_NODE_H
#define ITEM_NODE_H

#include "item.h"
#include "Node.h"

class ItemNode : public Item
{
public:
    Item();
    ~Item();
    
    virtual void setKey(std::string thisKey);
    virtual std::string getKey();
    
    virtual void setCurrentPtr(Node* thisItem);
    virtual void getCurrentPtr(Node* thisItem) = 0;
    
    virtual void setNextPtr(Node* thisItem) = 0;
    virtual void getNextPtr(Node* thisItem) = 0;
    
private:
    

};

#endif