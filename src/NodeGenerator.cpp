#include "NodeGenerator.h"



    
void calculateDistanceBetweenNodes(Node* node1, Node* node2, 
                                              std::int16_t* distance);

bool checkNodeCollision(SDL_Rect& a, SDL_Rect& b );                                              
                                              
bool nodeIsInBounds(Node* node, std::int16_t& leftBound,std::int16_t& rightBound, 
                    std::int16_t& topBound, std::int16_t& bottomBound);   

bool nodeEdgesTouch(Node& node1,Node& node2 );

//function to return a string from converting number to char

std::string setNumberToASCII_string(int number);
                                              
NodeGenerator::NodeGenerator()
{
    NodeGenerator::setGridDimensions(0,0,0,0);
    std::int16_t init_nodes_num = 0;
    NodeGenerator::setNumberOfNodesInLabyrinth(init_nodes_num);
    NodeGenerator::resetBannedDirections();
    NodeGenerator::setConductorsState(NodeGenerator::ConductorState::NONE);
    
    //initialize probabilities for direction arrays
    //N,NE,E,SE,S,SW,W,NW
    nextDirectionNorth = {0.2, 0.1, 0.2, 0.1, 0.2, 0.1, 0.2, 0.1};
    nextDirectionNorthEast = {0.2, 0.2, 0.2, 0.2, 0.4, 0.2, 0.2, 0.2};
    nextDirectionEast = {0.2, 0.3, 0.2, 0.3, 0.2, 0.2, 0.2, 0.2};
    nextDirectionSouthEast = {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2};
    nextDirectionSouth = {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2};
    nextDirectionSouthWest = {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2};
    nextDirectionWest = {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2};
    nextDirectionNorthWest = {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2};
    
}

NodeGenerator::~NodeGenerator()
{
    
}

//Setup functions

void NodeGenerator::setGridDimensions(std::int16_t x, std::int16_t y,std::int16_t w, std::int16_t h)
{
    gridX = x;
    gridY = y;
    gridWidth = w;
    gridHeight = h;
}

void NodeGenerator::setNumberOfNodesInLabyrinth(std::int16_t& numNodes)
{
    numberOfNodes = numNodes + 1;
    initialListNum = numNodes * 2;
}

void NodeGenerator::generateEmptyNodes()
{
    //create empty node conductor
    Node emptyNodeConductor;
    //Start empty node conductor at top left bound of grid
    std::int16_t startX = gridX;
    std::int16_t startY = gridY;
    emptyNodeConductor.setPosition(startX,startY);
    
    //add to empty node list
    emptyNodeList.push_back(emptyNodeConductor);
    
    //set end y
    std::int16_t heightDivision = gridHeight / emptyNodeConductor.getCollider().h;
    gridNodeHeightDivision = (gridHeight / heightDivision);
    std::int16_t endYRow = (gridY + gridHeight) - gridNodeHeightDivision;
    
    //set end for left and right side of x bounds
    std::int16_t widthDivision = gridWidth / emptyNodeConductor.getCollider().w;
    std::int16_t endLeftX = gridX;
    gridNodeWidthDivision = (gridWidth / widthDivision);
    std::int16_t endRightX = (gridX + gridWidth) -  gridNodeWidthDivision;
    
    bool quit = false;
    
    while(!quit)
    {
        //start at top left bound 
        
        
        //move right until node is outside of grid
        for(;;/*emptyNodeConductor.getCollider().x <= endRightX */)
        {
            emptyNodeConductor.moveRight();
            if(emptyNodeConductor.getCollider().x > endRightX){break;}
            //add to empty node list
            emptyNodeList.push_back(emptyNodeConductor);
        }
        
        //move conductor down and to left
        emptyNodeConductor.moveDown();
            
        //move left until node is outside of  grid
        for(;;/*emptyNodeConductor.getCollider().x >= endLeftX */)
        {
            emptyNodeConductor.moveLeft();
            if(emptyNodeConductor.getCollider().x < endLeftX){break;}
        }
        
        if(emptyNodeConductor.getCollider().y > endYRow){quit = true;}
        
    }
    
    //setup node_look_up
    NodeGenerator::setup_node_lookup();
    
}

void NodeGenerator::setup_node_lookup()
{
    
    //x is the horizontal division number
    //zero x division, 1st x division
    //y is the vertical division number
    //zero y division, 1st y division
   numXNodeColumns = gridWidth / gridNodeWidthDivision;
   numYNodeRows = gridHeight / gridNodeHeightDivision;
   
   //resize node look up vector
   
    //resize node look up x divisions columns
    node_look_up.resize(numXNodeColumns);
    
    for(size_t xCol=0; xCol < numXNodeColumns; xCol++)
    {
        node_look_up[xCol].resize(numYNodeRows);
    }
    
    
    size_t i = 0;
    size_t xCol = 0;
    size_t yRow = 0;
    //fill with each element address from empty node list
 
    bool quit = false;
    while(!quit)
    {
        node_look_up [xCol][yRow] = &emptyNodeList[i];
        
        //increment xCol
        xCol++;
        //if at end of x row, reset x increment y
        if(xCol == numXNodeColumns){xCol = 0; yRow++;}
        
        //increment i
        i++;
        
        //break loop when i has already reached last element
        if(i == emptyNodeList.size()){break;}
    }
}

std::int16_t NodeGenerator::getNumberOfNodesInLabyrinth(){return numberOfNodes;}

std::int16_t NodeGenerator::getInitialListNum(){return initialListNum;}

//Generation Functions



//function to generate different node options to take
void NodeGenerator::generateNodes(RNGType& rngSeed)
{
    NodeGenerator::generateEmptyNodes();
    
    std::int8_t root_gen_limit = initialListNum / 4;
    std::int8_t end_gen_limit = root_gen_limit;
    std::int8_t thisNode_gen_limit = root_gen_limit;
    NodeGenerator::genNodesFromRoot(rngSeed,root_gen_limit);
    NodeGenerator::genNodesFromEnd(rngSeed,end_gen_limit);
    
    //generate nodes from last element in temp node list
    NodeGenerator::genNodesFromThisNode(tempNodeList.back(),rngSeed,thisNode_gen_limit);
    //generate nodes from first element in temp node list
    NodeGenerator::genNodesFromThisNode(tempNodeList.front(),rngSeed,thisNode_gen_limit);
    
}

void NodeGenerator::genNodesFromRoot(RNGType& rngSeed,std::int8_t& limit)
{
    
    //start at center
    Node* rootCenterNode = node_look_up [(numXNodeColumns / 2) -1 ] [(numYNodeRows / 2) - 1];
    tempNodeList.push_back(rootCenterNode);
    rootCenterNode->setState(Node::State::MARKED_TEMP);
    
    NodeGenerator::genNodesFromThisNode(rootCenterNode,rngSeed,limit);
}


void NodeGenerator::genNodesFromEnd(RNGType& rngSeed,std::int8_t& limit)
{
    
//start from the last element of temp node list
    Node* lastNode = tempNodeList.back();
    Node::FaceDirection randFDir =  Node::FaceDirection(genDirection(rngSeed));
    lastNode->rotateCollider(randFDir);

    //generate nodes
    NodeGenerator::genNodesFromThisNode(lastNode,rngSeed,limit);
}


void NodeGenerator::genNodesFromThisNode(Node* thisNode,RNGType& rngSeed,std::int8_t& limit)
{
    //set conductor state to generating nodes
    NodeGenerator::setConductorsState(NodeGenerator::ConductorState::GENERATING_NODES);
    
    //Conductor node
    Node* conductorNode;
    //start conductor at node input
    conductorNode = thisNode;
    
//Move outward from parent node
//randomly choose direction

    
    std::int16_t count = 1;
    
    //bitset to represent which cardinal directions have been banned
    //will be used to see if node gen conductor is stuck
    NodeGenerator::resetBannedDirections();
    std::int16_t nodeRepeated = limit + 1;
    
    //while loop,
    while(count < limit)
    {
        
        NodeGenerator::moveConductorNodeRandomly_Generation(&conductorNode,rngSeed);
        
        NodeGenerator::runNodeGenChecks(conductorNode,tempNodeList);
        
        if(NodeGenerator::getConductorsState() == 
            NodeGenerator::ConductorState::PASSED_NODE_GEN_CHECKS)
        {
            //if node is empty
            if(conductorNode->getState() == Node::State::EMPTY)
            {
                //add node to list
                tempNodeList.push_back(conductorNode);
                conductorNode->setState(Node::State::MARKED_TEMP);
                //increment count
                count++;
                
                //reset bitset directions
                NodeGenerator::resetBannedDirections();
            }
        }
        else
        {
            //if node repeated already equal to count
            //means node is being repeated multiple times
            if(nodeRepeated == count)
            {
                //set bitset according to banned direction
                NodeGenerator::banDirection(conductorNode->getFaceDirection());
                //break loop if all directions are banned
                if(directionsBanned.all())
                {
                    //std::cout << "Hit a wall of nodes in genNodeRoot!Stop! \n";
                    
                    //reset bitset
                    NodeGenerator::resetBannedDirections();
                    break;
                }
            }
            else
            {
                //reset bitset directions
                NodeGenerator::resetBannedDirections();
            }
            
            nodeRepeated = count;
        }
    }
}

//Node Keep

//function to choose node options
bool NodeGenerator::chooseNodesRandomly(RNGType& rngSeed)
{
    bool success = true;
    
    bool quit_Pass1 = false;
    
    std::int16_t count = 0;
    
    while(!quit_Pass1)
    {
        //if failed
        if(!NodeGenerator::nodeKeep_Pass1(rngSeed))
        {
            //if list of nodes is not empty
            if(!nodesToKeepList.empty() )
            {
                //clear vector
                nodesToKeepList.clear();
            }
            
            //if list of nodes is not empty
            if(!tempNodeList.empty() )
            {
                //clear vector
                tempNodeList.clear();
            }
            
            std::cout << "Pass 1 failed! Lists cleared! \n";
            success = false; 
            std::cout << "Failed to generate any nodes! \n"; 
            break;
        }
        else{quit_Pass1 = true; success = true;}
    }
    
    return success;
}

bool NodeGenerator::nodeKeep_Pass1(RNGType& rngSeed)
{
    bool success = true;
    
    //Conductor node, points to a node in vector of nodes
    Node* conductor = nullptr;
    //Root Node, points to first node in list
    Node* root = tempNodeList[0];
    //Node* root = &tempNodeList.back(); //points to last node in list
    NodeGenerator::addNodeToKeepList(root);
    
    //set conductor to point to root node
    conductor = root;
    
    std::int16_t numWanted =  NodeGenerator::getNumberOfNodesInLabyrinth() ;
    
    std::int16_t countInLoop = 0;
    size_t iterator_keep_list = 0;
    std::int8_t genNodeLimit = 2;
    
    std::int8_t restartCount = 0;
    std::int8_t restartLimit = 10;
    
    while(nodesToKeepList.size() < numWanted)
    {
        //std::cout << "Count in pass 1: " << countInLoop << std::endl;
        NodeGenerator::nodeKeepProcess_AddNodes(conductor,root,rngSeed);
        if(nodesToKeepList.size() == 0 ){std::cout << "Unable to choose nodes at all! Something went really wrong! \n";break;}
        
        //if unable to add sufficient nodes to keep list
        
        //generate new nodes from current value of keep list iterator 
        //std::cout << "Failed to generate enough suitable nodes! Generating new nodes... \n";
        
        //node to use as conductor for generation
        Node* genConductor;
        
         //set gen conductor equal to node in current iterator of node keep list
        if( iterator_keep_list < nodesToKeepList.size() ){genConductor = nodesToKeepList[iterator_keep_list];}
        else
        {
            //get last element conductor was on
            size_t conductor_last_node = iterator_keep_list - 1;
            
            //reset iterator keep list
            iterator_keep_list = 0;
            //if reached restart limit, break loop
            if(restartCount == restartLimit){break;}
            
            genConductor = (nodesToKeepList[conductor_last_node]);
            
            //increment failed process count
            restartCount++;
        }
        
        genConductor->initCollider();
            
        //generate nodes from conductor 
        NodeGenerator::genNodesFromThisNode(genConductor,rngSeed,genNodeLimit);
        
        //increment iterator
        iterator_keep_list++;
        
        //increment count in loop
        countInLoop++;
    }
    
    //if process ended with less than intended nodes 
    if(nodesToKeepList.size() < numWanted){success = false;}
    
    return success;
}

void NodeGenerator::nodeKeepProcess_AddNodes(Node* conductor,Node* root,RNGType& rngSeed)
{
    size_t limit = NodeGenerator::getNumberOfNodesInLabyrinth();
    //while  num node keep list is less than number of nodes wanted
    while(nodesToKeepList.size() < limit )
    {
       NodeGenerator::conductorKeepNodeProcess(&conductor,rngSeed);
        //if conductor ends up going all the way back to root
        if(conductor == nullptr)
        {
            conductor = root;
            ///std::cout << " \n Conductor ended up back to root. \n";
            break;
        }
    }
}


//function to remove nodes not chosen
void NodeGenerator::removeExtraNodes()
{
     
}

 //add node to keep list
void NodeGenerator::addNodeToKeepList(Node* thisNode)
{
    
     //add current node conductor to list of nodes to keep
    nodesToKeepList.push_back(thisNode);
    //mark node to be added to keep list
    thisNode->setState(Node::State::MARKED_KEEP);
}

//Condition Functions





void NodeGenerator::conductorKeepNodeProcess(Node** conductorNode, RNGType& rngSeed)
{
    Node* conductor = *conductorNode;
//make options for conductor to choose based on how close a node is to conductor
    //Example Closest node is 1st option, farthest node is last option
    //Make conductor node as previous node for these nodes
    NodeGenerator::makeNodeOptionsBasedOnProximity(conductor,tempNodeList);
    
    //std::cout << "\n Conductor Node "<< conductor <<" Hash Table is ";
    //conductorsTable.printTable(); conductorsTable.printHistogram();
    
    //if there are node options available
    if(conductorsTable.getNumberOfItems() > 0)
    {
        NodeGenerator::makeConductorChooseCloseAvailableNodeRandomly(conductor,rngSeed);
        
        //if unable to set next node pointer for conductor
        //in make conductor choose close available node function
        if(conductor->getPointerToNextNode() == nullptr)
        {
            
            //add current node conductor is on to keep list
             //if conductor is not marked as on keep list
            if(!conductor->getMarkedKeepStatus() )
            {
                
                NodeGenerator::addNodeToKeepList(conductor);
                std::cout << "\n Node:" << conductor << " added to keep list!\n";
            }
        
            std::cout << "\n Conductor going back to previous node "
            << " b/c unable to find next node in makeConductorChooseCloseAvailableNodeRandomly! \n";
            //make conductor go back to previous node
            *conductorNode = conductor->getPointerToPreviousNode();
             //clear vector of pointers to nodes conductor should move to
            NodeGenerator::clearConductorsTable();
        }
        //if conductor node previous pointer is same as next pointer
        else if( conductor->getPointerToNextNode() == conductor->getPointerToPreviousNode())
        {
            std::cout << "\n Something is very wrong. Conductor's previous node is conductor's next node! \n";
            //go all the way back to previous node of previous node
            Node* previousNodeToGoTo = conductor->getPointerToPreviousNode()
            ->getPointerToPreviousNode();
            //set node conductor is on to nullptr
            conductor->setPointerToPreviousNode(nullptr);
            conductor->setPointerToNextNode(nullptr);
            
            if(conductor->getPointerToPreviousNode() != nullptr){conductor = previousNodeToGoTo;}
        }
        //if conductor next pointer is not nullptr
        else if(conductor->getPointerToNextNode() != nullptr)
        {
            //if conductor's next node is not marked
            //means it is not on keep list
            if(!conductor->getPointerToNextNode()->getMarkedKeepStatus() )
            {
                //if conductor is not marked as on keep list
                if(!conductor->getMarkedKeepStatus() )
                {
                    NodeGenerator::addNodeToKeepList(conductor);
                    //std::cout << "\n Node:" << conductor << " added to keep list!\n";
                }
                
                //std::cout << "\n Moving to Node " << conductor->getPointerToNextNode() << std::endl;
                //set node that is pointed to as conductor's next node 
                //as current node conductor should be on
                *conductorNode = conductor->getPointerToNextNode();
            
            }
            //if node conductor's next node is marked
            else
            {
                //Move to previous node
                
                 std::cout << "\n Next Node is Marked! Moving to previous Node " 
                << conductor->getPointerToNextNode() << std::endl;
                *conductorNode = conductor->getPointerToPreviousNode();
                
            }
            
            //clear vector of pointers to nodes conductor should move to
            NodeGenerator::clearConductorsTable();
        }
    }
    //else if there aren't node options available
    else
    {
        //add current node conductor is on to keep list
         //if conductor is not marked as on keep list
        if(!conductor->getMarkedKeepStatus() )
        {
            NodeGenerator::addNodeToKeepList(conductor);
            //std::cout << "\n Node:" << conductor << " added to keep list!\n";
        }
        //std::cout << "Unable to generate close node options! Going back to previous node... \n";
        //make conductor go back to previous node
        //leave node conductor is on with a nullptr for next node pointer
        *conductorNode = conductor->getPointerToPreviousNode();
         //clear vector of pointers to nodes conductor should move to
         NodeGenerator::clearConductorsTable();
        
    }
    
    //if run out of options
    //go back to previous node  and check its options 
    //by seeing if current conductor node is the previous node of other nodes and these other nodes don't have a
    //next node pointer pointing to something
}
    
void NodeGenerator::makeNodeOptionsBasedOnProximity(Node* conductorNode, std::vector <Node*> &thisList)
{
    //distance between nodes
    std::int16_t distance;
    //max distance is 10 pixels
    std::int16_t maxDistance = 2;

    //go through whole vector of nodes
    for(size_t i=0; i < thisList.size(); i++)
    {
        //if node in vector isn't node input
        if(conductorNode != thisList[i])
        {
            //if it doesn't have a pointer to next node
            if(thisList[i]->getPointerToNextNode() == nullptr)
            {
                //if node doesn't have a pointer to a previous node
                if(thisList[i]->getPointerToPreviousNode() == nullptr )
                {
                    //if edges touch
                    if(nodeEdgesTouch(*conductorNode, *thisList[i]))
                    {
                        //make previous node pointer of node in vector point to conductor
                        thisList[i]->setPointerToPreviousNode(conductorNode);
                        
                        //calculate distance between current node in list and conductor node
                        calculateDistanceBetweenNodes(conductorNode, thisList[i],&distance);
                        
                        //if distance is less than max distance
                        if(distance < maxDistance && distance >= 0)
                        {
                            //and node isn't marked
                            if( thisList[i]->getState() == Node::State::MARKED_TEMP )
                            {
                                //insert item
                                NodeGenerator::insertItemWithNode_IntoConductorsTable(thisList[i],distance);
                            }
                            else
                            {
                                //set pointer to previous node back to nullptr
                                thisList[i]->setPointerToPreviousNode(nullptr);
                            }
                        }
                        else
                        {
                            //set pointer to previous node back to nullptr
                            thisList[i]->setPointerToPreviousNode(nullptr);
                        }
                    }
                    
                    //else if node edges don't touch
                    else
                    {
                        //set pointer to previous node back to nullptr
                        thisList[i]->setPointerToPreviousNode(nullptr);
                    }
                }
                //if node does have a pointer to previous node
                else
                {
                    //if edges touch
                    if(nodeEdgesTouch(*conductorNode, *thisList[i]))
                    {
                        //means conductor has evaluated this node but didn't go through it
                        //make previous node pointer of node in vector point to conductor
                        thisList[i]->setPointerToPreviousNode(conductorNode);
                        //calculate distance between current node in list and conductor node
                        calculateDistanceBetweenNodes(conductorNode, thisList[i],&distance);
                        
                        //if distance is less than max distance
                        if(distance < maxDistance && distance >= 0)
                        {
                             if( thisList[i]->getState() == Node::State::MARKED_TEMP  )
                            {
                                //insert item
                                NodeGenerator::insertItemWithNode_IntoConductorsTable(thisList[i],distance);
                            }
                            
                        }
                        //else if distance is more than max distance
                        else
                        {
                            //set pointer to previous node back to nullptr
                            thisList[i]->setPointerToPreviousNode(nullptr);
                        }
                    }
                    else
                    {
                        //set pointer to previous node back to nullptr
                        thisList[i]->setPointerToPreviousNode(nullptr);
                    }                    
                }
            }
        }
    }
}

void NodeGenerator::insertItemWithNode_IntoConductorsTable(Node* thisNode, std::int16_t& distance)
{
    //create item
    //Item* nodeItem = new Item();
    std::unique_ptr <Item> nodeItem (new Item);
    nodeItem.get()->setThisNodeElementPointer(thisNode);
    
    std::string key = setNumberToASCII_string(distance);
    nodeItem.get()->setKey(key);
    
    Item* itemToInsert = nullptr;
    //release responsibility of deleting object from unique pointer nodeItem 
    //give it to itemToInsert
    itemToInsert = nodeItem.release();
    
    if(itemToInsert->getThisNodeElementPointer()->getMarkedKeepStatus())
    {
        std::cout << " \n Node " << itemToInsert->getThisNodeElementPointer()
        << "in Item " << itemToInsert << " is marked! \n";
    } 
    
    //std::cout << "Item " << itemToInsert << " passed to tempItemContainer vector. "
    //<< "Contains node address " << itemToInsert->getThisNodeElementPointer() <<
    //". Has key " << itemToInsert->getKey() << std::endl;
    //std::cout << "Node address passed to vector " << itemToInsert->getThisNodeElementPointer() << "\n";
    tempItemContainer.push_back(itemToInsert);
    
    conductorsTable.insertItem(tempItemContainer.back());
    
   // std::cout << "Node address in vector "<< tempItemContainer.back()->getThisNodeElementPointer() << " inserted. key is: " 
   // << tempItemContainer.back()->getKey() << std::endl;
}

void NodeGenerator::makeConductorChooseCloseAvailableNodeRandomly(Node* conductorNode,RNGType& rngSeed )
{
    std::int8_t numNodesForConductor = conductorsTable.getNumberOfItems();
    //if vector of nodes for conductor to move to is not empty
    if(numNodesForConductor != 0)
    {
        std::int8_t elementRandom;
        //std::int8_t numNodesForConductor = conductorsNextNodes.size();
        
        std::array <double,2> probabilities;
        
        //fill probabilities array with 0.1
        probabilities[0] = 0.1;
        probabilities[1] = 0.1;
        //setup rng with set probablities    
        boost::random::discrete_distribution <int> dist(probabilities);
        boost::random::variate_generator <RNGType&, boost::random::discrete_distribution <> > Die(rngSeed,dist);

        std::int8_t count = 0;
        bool quit = false;
        //while conductor next node pointer is pointing to nullptr 
        while(!quit)
        {
            //if more than 1 node in conductor next node vector
            if(numNodesForConductor > 1)
            {
                
                //roll a 1 or 0
                std::int8_t index = Die();
                
                //check all elements in conductor's next nodes vector
                //for shortest distance
                
                //for now just choose first node
                Item* closestItem = nullptr;
                int distance = 0;
                
                closestItem = conductorsTable.getItemByKeyAndIndex(setNumberToASCII_string(distance),index);
                
                if(closestItem != nullptr)
                {
                    if(closestItem->getThisNodeElementPointer() != nullptr )
                    {
                        conductorNode->setPointerToNextNode(closestItem->getThisNodeElementPointer() );
                        quit = true;
                        break;
                    }
                    else
                    {
                        std::cout << "Invalid node tried to be passed to conductor! \n";
                        quit = true;
                        break;
                    }
                    
                }
            }
            //else if 1
            else if(numNodesForConductor == 1)
            {  
                //set conductor's pointer to next node as node element in vector
                //conductorNode->setPointerToNextNode(conductorsNextNodes[0].nextNodePtr);
                Item* closestItem = nullptr;
                int distance = 0;
                
                closestItem = conductorsTable.getItemByKey(setNumberToASCII_string(distance));
                if(closestItem != nullptr)
                {
                    conductorNode->setPointerToNextNode(closestItem->getThisNodeElementPointer() );
                    quit = true;
                }
            }
        }
    }
}

void NodeGenerator::clearConductorsTable()
{
    conductorsTable.freeEntireTable();
    
    for(size_t i=0; i < tempItemContainer.size(); i++)
    {
        delete tempItemContainer[i];
        tempItemContainer[i] = nullptr;
    }
    
    tempItemContainer.clear();
}

void NodeGenerator::render(SDL_Renderer* gRenderer)
{
    //render grid
    for(size_t i=0; i < emptyNodeList.size(); i++)
    {
        //render node in gray color
        if(emptyNodeList[i].getState() == Node::State::EMPTY)
        {
            emptyNodeList[i].render(gRenderer,160,160,160);
        }
    }

    //render nodes in temp list
    for(size_t i=0; i < tempNodeList.size(); i++)
    {
        //render in green color
        tempNodeList[i]->render(gRenderer,0,204,0);
    }
  
    //render nodes in keep list
    for(size_t i=0; i < nodesToKeepList.size(); i++)
    {
        //render in blue color
        nodesToKeepList[i]->render(gRenderer,0,0,204);
    }
}

void NodeGenerator::renderEmptyGrid(SDL_Renderer* gRenderer)
{
    for(size_t i=0; i < emptyNodeList.size(); i++)
    {
        //render all nodes in gray color
        emptyNodeList[i].render(gRenderer,160,160,160);
    }
}

void NodeGenerator::renderTempNodes(SDL_Renderer* gRenderer)
{
    for(size_t i=0; i < emptyNodeList.size(); i++)
    {
        //render nodes chosen as temp at one point as green
        //including nodes kept
        if( emptyNodeList[i].getState() != Node::State::EMPTY )
        {
            //render in green
            emptyNodeList[i].render(gRenderer,0,204,0); 
        }
        //else render as empty node in gray color
        else{emptyNodeList[i].render(gRenderer,160,160,160);}
    }
}

void NodeGenerator::renderKeptNodes(SDL_Renderer* gRenderer)
{
    //render nodes in keep list
    for(size_t i=0; i < emptyNodeList.size(); i++)
    {
        //render nodes chosen to be kept
        if( emptyNodeList[i].getState() == Node::State::MARKED_KEEP )
        {
            //render in blue
            emptyNodeList[i].render(gRenderer,0,0,204); 
        }
        //else if render temp nodes as green
        else if( emptyNodeList[i].getState() == Node::State::MARKED_TEMP)
        {
            //render in green
            emptyNodeList[i].render(gRenderer,0,204,0);
        }
        //else render empty nodes in gray color
        else
        {
            emptyNodeList[i].render(gRenderer,160,160,160);
        }
    }
}

void NodeGenerator::setConductorsState(NodeGenerator::ConductorState state){conductors_state = state;}
NodeGenerator::ConductorState NodeGenerator::getConductorsState(){return conductors_state;}

void NodeGenerator::moveConductorNodeRandomly_Generation(Node** conductorNodePtr,RNGType& rngSeed)
{
    std::int8_t moveDirection;
    
    Node* conductorNode = *conductorNodePtr;
    
    //Setup RNG
    std::array <double,8> probabilitiesDirection;
     
    //determine which direction conductor node should take randomly based on face direction
    switch(conductorNode->getFaceDirection())
    {
        
        case Node::FaceDirection::NORTH:{probabilitiesDirection = nextDirectionNorth; break;}
        case Node::FaceDirection::NORTHEAST:{probabilitiesDirection = nextDirectionNorthEast; break;}
        case Node::FaceDirection::EAST:{probabilitiesDirection = nextDirectionEast; break;}
        case Node::FaceDirection::SOUTHEAST:{probabilitiesDirection = nextDirectionSouthEast; break;}
        case Node::FaceDirection::SOUTH:{probabilitiesDirection = nextDirectionSouth; break;}
        case Node::FaceDirection::SOUTHWEST:{probabilitiesDirection = nextDirectionSouthWest; break;}
        case Node::FaceDirection::WEST:{probabilitiesDirection = nextDirectionWest; break;}
        case Node::FaceDirection::NORTHWEST:{probabilitiesDirection = nextDirectionNorthWest; break;}
    }
       
    //change probabilities direction by setting banned directions to zero
    for(size_t i = 0; i < 8; i++)
    {
        //if direction is true, it is banned, set to zero in probabilites direction
        if(directionsBanned.test(i)){probabilitiesDirection[i] = 0.0;}
    }
    
        
    //setup rng with set probablities    
    boost::random::discrete_distribution <int> distDirection(probabilitiesDirection);
    boost::random::variate_generator <RNGType&, boost::random::discrete_distribution <> > DirectionDie(rngSeed,distDirection);

    moveDirection = DirectionDie();

    //Don't move in direction generated if it is banned
        //rotate in direction and move in that direction
        switch(moveDirection)
        {
            case 0:{ conductorNode->rotateCollider(Node::FaceDirection::NORTH); break;}
            case 1:{ conductorNode->rotateCollider(Node::FaceDirection::NORTHEAST); break;}
            case 2:{ conductorNode->rotateCollider(Node::FaceDirection::EAST); break;}
            case 3:{ conductorNode->rotateCollider(Node::FaceDirection::SOUTHEAST); break;}
            case 4:{ conductorNode->rotateCollider(Node::FaceDirection::SOUTH); break;}
            case 5:{ conductorNode->rotateCollider(Node::FaceDirection::SOUTHWEST); break;}
            case 6:{ conductorNode->rotateCollider(Node::FaceDirection::WEST); break;}
            case 7:{ conductorNode->rotateCollider(Node::FaceDirection::NORTHWEST); break;}
        }

        //calculate current position of conductor node relative to column and row in grid
        std::int16_t conductorScreenX = 0;
        std::int16_t conductorScreenY = 0;
        conductorNode->getPosition(&conductorScreenX,&conductorScreenY); 
        
        size_t conductorColumn = ( conductorScreenX - gridX ) / gridNodeWidthDivision;
        size_t conductorRow = ( conductorScreenY - gridY   ) / gridNodeHeightDivision;
        //initialize variables for new column and row
        size_t newColumn = 0;
        size_t newRow = 0;
        
        switch(moveDirection)
        {
            //move north
            case 0:{ newColumn = conductorColumn; newRow = conductorRow - 1; break;}
            //move north east
            case 1:{ newColumn = conductorColumn + 1; newRow = conductorRow - 1; break;}
            //move east
            case 2:{ newColumn = conductorColumn + 1; newRow = conductorRow; break;}
            //move south east
            case 3:{ newColumn = conductorColumn + 1; newRow = conductorRow + 1; break;}
            //move south
            case 4:{ newColumn = conductorColumn; newRow = conductorRow + 1; break;}
            //move south west
            case 5:{ newColumn = conductorColumn - 1; newRow = conductorRow + 1; break;}
            //move west
            case 6:{ newColumn = conductorColumn - 1; newRow = conductorRow; break;}
            //move north west
            case 7:{ newColumn = conductorColumn - 1; newRow = conductorRow - 1; break;}
        }
        
        //grid bounds check
        if(newColumn < numXNodeColumns && newColumn >= 0
            && newRow < numYNodeRows && newRow >= 0)
        {
            //look up node and assign conductor to it
            conductorNode = node_look_up [newColumn][newRow];
            *conductorNodePtr = conductorNode;
        }
        
    
}




void NodeGenerator::banDirection(Node::FaceDirection thisDirection)
{
    directionsBanned.set(size_t(thisDirection),1);
}


void NodeGenerator::resetBannedDirections(){directionsBanned.reset();}

void NodeGenerator::runNodeGenChecks(Node* conductorNode,std::vector <Node*> &thisList)
{
     //reset state to generating nodes
     NodeGenerator::setConductorsState(NodeGenerator::ConductorState::GENERATING_NODES);
     
     //check if node address is already in tempNodeList
     
     for(size_t i=0; i < thisList.size(); i++)
     {
         if(thisList[i] == conductorNode)
         { 
             NodeGenerator::setConductorsState(NodeGenerator::ConductorState::HIT_NODE_IN_GENERATING_NODES);
             NodeGenerator::banDirection(conductorNode->getFaceDirection());
             break; 
         }
     }
     
     if(NodeGenerator::getConductorsState() != NodeGenerator::ConductorState::HIT_NODE_IN_GENERATING_NODES)
     {
         NodeGenerator::setConductorsState(NodeGenerator::ConductorState::PASSED_NODE_GEN_CHECKS);
     }
}

//function to check if a node collides with another node
bool NodeGenerator::checkNodeToNodeCollision(Node* thisNode, std::vector <Node*> &thisList)
{
    bool collision = false;
    
    for(size_t i=0; i < thisList.size(); i++)
    {
        if( checkNodeCollision(thisNode->getCollider(),thisList[i]->getCollider() ) )
        { 
            collision = true; 
            break;
        }
    }
    
    return collision;
}
    
//function to check if node collides with grid
bool NodeGenerator::checkNodeIsInGrid(Node* node)
{
    bool inside = true;
    
    std::int16_t* leftBound = &gridX;
    std::int16_t rightBound = gridX + gridWidth;
    std::int16_t* topBound = &gridY;
    std::int16_t bottomBound = gridY + gridHeight;
    
    inside = nodeIsInBounds(node,*leftBound,rightBound, 
                    *topBound, bottomBound);
    
    return inside;
}


std::int8_t NodeGenerator::genDirection(RNGType& rngSeed)
{
    std::int8_t direction;
    
    //Setup RNG
    std::array <double,8> probabilitiesDirection;
     
    probabilitiesDirection= {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2};
        
    //setup rng with set probablities    
    boost::random::discrete_distribution <int> distDirection(probabilitiesDirection);
    boost::random::variate_generator <RNGType&, boost::random::discrete_distribution <> > DirectionDie(rngSeed,distDirection);

    direction = DirectionDie();
    
    return direction;
}

std::vector <Node> NodeGenerator::getNodesKept()
{
    std::vector <Node> vectorToReturn;
    vectorToReturn.resize(nodesToKeepList.size());
    
    for(size_t i=0; i < vectorToReturn.size(); i++)
    {
        vectorToReturn[i] = *nodesToKeepList[i];
    }
    
    return vectorToReturn;
}

void NodeGenerator::getColsAndRows(size_t& xCols,size_t& yRows)
{
    xCols = numXNodeColumns;
    yRows = numYNodeRows ;
}
