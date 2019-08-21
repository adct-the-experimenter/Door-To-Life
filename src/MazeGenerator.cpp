#include "MazeGenerator.h"

MazeGenerator::MazeGenerator()
{
    
}

MazeGenerator::~MazeGenerator()
{
    
}

void MazeGenerator::loadResourcesFromNodeGenerator(NodeGenerator* node_gen)
{
    MazeGenerator::loadKeptNodesFromNodeGenerator(node_gen);
    
    MazeGenerator::loadNodesLookUpFromNodeGenerator(node_gen);
    
}

void MazeGenerator::loadKeptNodesFromNodeGenerator(NodeGenerator* node_gen)
{
    //initialize size of maze nodes vector with size of nodes to keep list
    mazeNodesVector.resize(node_gen->nodesToKeepList.size());
    
    //initialize elements of maze nodes vector
    for(size_t i = 0; i < mazeNodesVector.size(); i++)
    {
        mazeNodesVector[i].setNode(*node_gen->nodesToKeepList[i]);
    }
}

void MazeGenerator::loadNodesLookUpFromNodeGenerator(NodeGenerator* node_gen)
{
    gridX = node_gen->gridX;
    gridY = node_gen->gridY;
    gridWidth = node_gen->gridWidth;
    gridHeight = node_gen->gridHeight;
    
    gridNodeWidthDivision = node_gen->gridNodeWidthDivision;
    gridNodeHeightDivision = node_gen->gridNodeHeightDivision;
    
    node_gen->getColsAndRows(numberXNodeColumns,numberYNodeRows);
    
    //initialize size of maze node look up
    maze_node_look_up.resize( numberXNodeColumns );
    
    for(size_t xCol = 0; xCol < maze_node_look_up.size(); xCol++)
    {
        maze_node_look_up [xCol].resize( numberYNodeRows );
    }
    
    std::int16_t posX = 0;
    std::int16_t posY = 0;
    
    std::int16_t mazeNodePosX = 0;
    std::int16_t mazeNodePosY = 0;
    
    //initialize elements of maze node look up
    for(size_t xCol = 0; xCol < numberXNodeColumns; xCol++)
    {
        for(size_t yRow = 0; yRow < numberYNodeRows; yRow++)
        {
            std::int16_t colNode = xCol;
            std::int16_t rowNode = yRow;
            //calculate screen position of node from column and row position
            posX = gridX + ( colNode * gridNodeWidthDivision);
            posY = gridY + (rowNode * gridNodeHeightDivision);
            
            //check if node in maze node vector matches this position
            for(size_t i = 0; i < mazeNodesVector.size(); i++)
            {
                //initialize maze node look up element to point to nullptr
                maze_node_look_up [xCol][yRow] = nullptr;
                
                mazeNodesVector[i].getNode().getPosition(&mazeNodePosX,&mazeNodePosY);
                
                //if match add to maze_node_look_up
                if(posX == mazeNodePosX && posY == mazeNodePosY)
                {
                    maze_node_look_up [xCol][yRow] =  &mazeNodesVector[i];
                    break;
                }
            }
        }
    }
    
}

void MazeGenerator::setup_maze_node_lookup()
{
    
    
}

void MazeGenerator::generateMaze(RNGType& rngSeed)
{
    MazeGenerator::recursiveBackTracking(rngSeed);
}

void MazeGenerator::recursiveBackTracking(RNGType& rngSeed)
{
    MazeNode* conductor = nullptr;
    MazeNode* source = nullptr;
    
    //variable for direction conductor should take
    std::int8_t nextDirection = 0;
    
    std::cout << "Picking a random point to start in... \n";
    
    //pick a random node in maze nodes vector at wall
    source = MazeGenerator::getRandomWallMazeNode(rngSeed);
    
    //move conductor to source
    conductor = source;
    
    //Setup RNG
    std::array <double,4> probabilities;
    probabilities = {0.2, 0.2, 0.2, 0.2}; 
   
    
    std::cout << "Creating paths and walls... \n";
    
    bool quit = false;
    
    //loop
    while(!quit)
    {
        //set current node conductor is on as visited
        conductor->setState(MazeNode::State::VISITED);
            
        MazeNode* nextNode = nullptr;
        
        //look around in north,east,west,and south of node for
        //nodes that have not been visited
        MazeNode* north = MazeGenerator::getNorthElement(conductor);
        MazeNode* east = MazeGenerator::getEastElement(conductor);
        MazeNode* south = MazeGenerator::getSouthElement(conductor);
        MazeNode* west = MazeGenerator::getWestElement(conductor);
        
        //choose next node randomly
        
        //setup probabilites based on which direction can be taken
        //eliminate direction if it points to nullptr or it is already visited
        //4 probabilites N,E,S,W
        probabilities = {0.2, 0.2, 0.2, 0.2}; 
        if(north == nullptr){probabilities[0] = 0.0;}
        else if(north->getState() == MazeNode::State::VISITED){probabilities[0] = 0.0;}
        if(east == nullptr){probabilities[1] = 0.0;}
        else if(east->getState() == MazeNode::State::VISITED){probabilities[1] = 0.0;}
        if(south == nullptr){probabilities[2] = 0.0;}
        else if(south->getState() == MazeNode::State::VISITED){probabilities[2] = 0.0;}
        if(west == nullptr){probabilities[3] = 0.0;}
        else if(west->getState() == MazeNode::State::VISITED){probabilities[3] = 0.0;}
        
        //if all probabilities are zero no other directions to take
        if(probabilities[0] == 0.0 && probabilities[1] == 0.0 
            && probabilities[2] == 0.0 && probabilities[3] == 0.0)
        {
            
            //quit loop if previous node pointer is nullptr
            if(conductor->getPointerToPreviousMazeNode() != nullptr)
            {
                //go back to previous node
                conductor = conductor->getPointerToPreviousMazeNode();
            }
            else{quit = true;}
        }
        else
        {
             //setup rng with set probablities    
            boost::random::discrete_distribution <int> dist(probabilities);
            boost::random::variate_generator <RNGType&, boost::random::discrete_distribution <> > Die(rngSeed,dist);

            //set next direction randomly
            nextDirection = Die();
            
            //set next node
            switch(nextDirection)
            {
                case 0:{ nextNode = north; break;}
                case 1:{ nextNode = east; break;}
                case 2:{ nextNode = south; break;}
                case 3:{ nextNode = west; break;}
            }
        
            //carve passage from conductor to next node in next direction
            MazeGenerator::carvePassage(conductor,nextNode,
                                        MazeNode::WallDirection(nextDirection));
            
            //move conductor to next node
            conductor = nextNode;
            
            //quit loop if previous node pointer is nullptr
            if(conductor->getPointerToPreviousMazeNode() == nullptr){quit = true;}
        }
        
       
    }
    
}

MazeNode* MazeGenerator::getRandomWallMazeNode(RNGType& rngSeed)
{
    
    MazeNode* pointerToWallNode = nullptr;
    
    //Setup RNG
    std::array <double,2> probabilities;
    
    //2 probabilites 
    probabilities = {0.2, 0.2};
        
    //setup rng with set probablities    
    boost::random::discrete_distribution <int> dist(probabilities);
    boost::random::variate_generator <RNGType&, boost::random::discrete_distribution <> > Die(rngSeed,dist);

    std::int8_t x = 0;
    std::int8_t y = 0;
    
    size_t xCol,yRow;
    
    
    size_t startX = 0;
    size_t endX = numberXNodeColumns - 1;
    
    size_t startY = 0;
    size_t endY = numberYNodeRows - 1;
    
    size_t dx = 0;
    size_t dy = 0;
    
    std::int8_t count = 0;
    
    while(pointerToWallNode == nullptr)
    {
        //roll for top or bottom
        y = Die();
        //roll for left right or neither
        x = Die();
        
        //if top
        if(y == 0){yRow = startY + dy;}
        //if bottom
        else if(y == 1){yRow = endY - dy;}
        
        //if left
        if(x == 0){xCol = startX + dx;}
        //if right
        else if(x == 1){xCol = endX - dx;}
        
        if(xCol <= endX && yRow <= endY)
        {
            pointerToWallNode = maze_node_look_up [xCol] [yRow];
        }

        //increment count
        count++;
        
        //increment dx dy and reset count at certain count intervals
        if(count == 5){ dx++;}
        if(count == 10){dy++;}
        if(count == 30){count = 0;}
        
        //if dx equal to endX 
        if(dx >= endX){dx = 0;}
        if(dy >= endY){dy = 0;}
    }
    
    return pointerToWallNode;
}


MazeNode* MazeGenerator::getNorthElement(MazeNode* conductor)
{
    //get screen position of conductor
    std::int16_t conductorScreenX = 0;
    std::int16_t conductorScreenY = 0;
    conductor->getNode().getPosition(&conductorScreenX,&conductorScreenY);
    
    //calculate position of conductor relative to column and row of nodes
    size_t conductorColumn = ( conductorScreenX - gridX ) / gridNodeWidthDivision;
    size_t conductorRow = ( conductorScreenY - gridY   ) / gridNodeHeightDivision;
    
    size_t northColumn = conductorColumn;
    size_t northRow = conductorRow - 1;
    
    //bounds check
    if( northRow >= numberYNodeRows){return nullptr;}
    else{return maze_node_look_up [northColumn] [northRow];}
}

MazeNode* MazeGenerator::getEastElement(MazeNode* conductor)
{
    //get screen position of conductor
    std::int16_t conductorScreenX, conductorScreenY;
    conductor->getNode().getPosition(&conductorScreenX,&conductorScreenY);
    
    //calculate position of conductor relative to column and row of nodes
    size_t conductorColumn = ( conductorScreenX - gridX ) / gridNodeWidthDivision;
    size_t conductorRow = ( conductorScreenY - gridY   ) / gridNodeHeightDivision;
    
    size_t eastColumn = conductorColumn + 1;
    size_t eastRow = conductorRow;
    
    //bounds check
    if(eastColumn >= numberXNodeColumns){return nullptr;}
    else{return maze_node_look_up [eastColumn] [eastRow];}
}

MazeNode* MazeGenerator::getSouthElement(MazeNode* conductor)
{
    //get screen position of conductor
    std::int16_t conductorScreenX, conductorScreenY;
    conductor->getNode().getPosition(&conductorScreenX,&conductorScreenY);
    
    //calculate position of conductor relative to column and row of nodes
    size_t conductorColumn = ( conductorScreenX - gridX ) / gridNodeWidthDivision;
    size_t conductorRow = ( conductorScreenY - gridY   ) / gridNodeHeightDivision;
    
    size_t southColumn = conductorColumn;
    size_t southRow = conductorRow + 1;
    
    //bounds check
    if(southRow >= numberYNodeRows){return nullptr;}
    else{return maze_node_look_up [southColumn] [southRow];}
}

MazeNode* MazeGenerator::getWestElement(MazeNode* conductor)
{
    //get screen position of conductor
    std::int16_t conductorScreenX, conductorScreenY;
    conductor->getNode().getPosition(&conductorScreenX,&conductorScreenY);
    
    //calculate position of conductor relative to column and row of nodes
    size_t conductorColumn = ( conductorScreenX - gridX ) / gridNodeWidthDivision;
    size_t conductorRow = ( conductorScreenY - gridY   ) / gridNodeHeightDivision;
    
    size_t westColumn = conductorColumn - 1;
    size_t westRow = conductorRow;
    
    //bounds check
    //size type can't be negative it just goes big
    if(westColumn >= numberXNodeColumns){return nullptr;}
    else{return maze_node_look_up [westColumn] [westRow];}
}

void MazeGenerator::carvePassage(
    MazeNode* someNode,
    MazeNode* nodeToBeConnected,
    MazeNode::WallDirection directionToConnectNode)
{
    //if some node connecting to node north of it
    if(directionToConnectNode == MazeNode::WallDirection::NORTH)
    {
        //destroy walls
        someNode->setWall(MazeNode::WallDirection::NORTH, false);
        nodeToBeConnected->setWall(MazeNode::WallDirection::SOUTH,false);
        
        //connect nodes through previous and next node pointers
        someNode->setPointerToNextMazeNodeNorth(nodeToBeConnected);
        nodeToBeConnected->setPointerToPreviousMazeNode(someNode);
    }
    //if some node connecting to node east of it
    else if(directionToConnectNode == MazeNode::WallDirection::EAST)
    {
        //destroy walls
        someNode->setWall(MazeNode::WallDirection::EAST, false);
        nodeToBeConnected->setWall(MazeNode::WallDirection::WEST,false);
        
        //connect nodes through previous and next node pointers
        someNode->setPointerToNextMazeNodeEast(nodeToBeConnected);
        nodeToBeConnected->setPointerToPreviousMazeNode(someNode);
    }
    //if some node connecting to node south of it
    else if(directionToConnectNode == MazeNode::WallDirection::SOUTH)
    {
        //destroy walls
        someNode->setWall(MazeNode::WallDirection::SOUTH, false);
        nodeToBeConnected->setWall(MazeNode::WallDirection::NORTH,false);
        
        //connect nodes through previous and next node pointers
        someNode->setPointerToNextMazeNodeSouth(nodeToBeConnected);
        nodeToBeConnected->setPointerToPreviousMazeNode(someNode);
    }
    //if some node connecting to node west of it
     //if some node connecting to node south of it
    else if(directionToConnectNode == MazeNode::WallDirection::WEST)
    {
        //destroy walls
        someNode->setWall(MazeNode::WallDirection::WEST, false);
        nodeToBeConnected->setWall(MazeNode::WallDirection::EAST,false);
        
        //connect nodes through previous and next node pointers
        someNode->setPointerToNextMazeNodeWest(nodeToBeConnected);
        nodeToBeConnected->setPointerToPreviousMazeNode(someNode);
    }
}

void MazeGenerator::render(SDL_Renderer* gRenderer)
{
    unsigned int r = 100; unsigned int g = 0; unsigned int b = 204;
    for(size_t i = 0; i < mazeNodesVector.size(); i++)
    {
        mazeNodesVector[i].render(gRenderer,r,g,b);
    }
}

void MazeGenerator::renderSquareInMazeNode(SDL_Renderer* gRenderer,size_t& xCol, size_t& yRow, unsigned int &  r, unsigned int &  g, unsigned int &  b)
{
    maze_node_look_up [xCol][yRow]->renderCenterDot(gRenderer, r,g,b);
}