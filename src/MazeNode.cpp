#include "MazeNode.h"

MazeNode::MazeNode()
{
    //initialize state
    MazeNode::setState(MazeNode::State::NOT_VISITED);
    
    //initialize bitset, set as all walled
    MazeNode::setWall(MazeNode::WallDirection::NORTH , true);
    MazeNode::setWall(MazeNode::WallDirection::EAST , true);
    MazeNode::setWall(MazeNode::WallDirection::SOUTH , true);
    MazeNode::setWall(MazeNode::WallDirection::WEST , true);
    
    MazeNode::setPointerToPreviousMazeNode(nullptr);
    MazeNode::setPointerToNextMazeNodeNorth(nullptr);
    MazeNode::setPointerToNextMazeNodeEast(nullptr);
    MazeNode::setPointerToNextMazeNodeSouth(nullptr);
    MazeNode::setPointerToNextMazeNodeWest(nullptr);
}

MazeNode::~MazeNode()
{
    //reset state
    MazeNode::setState(MazeNode::State::NOT_VISITED);
    
    //reset bitset
    directions_walled.reset();
}
    
//functions to set and get Node member
void MazeNode::setNode(Node& thisNode){ maze_node = thisNode;}
Node& MazeNode::getNode(){return maze_node;}

void MazeNode::setWall(MazeNode::WallDirection direction, bool state)
{
    //set to 1 if true
    if(state){directions_walled.set(size_t(direction),1);}
    //else set to zero if false
    else{directions_walled.set(size_t(direction),0);}
}

bool MazeNode::getWallInThisDirection(MazeNode::WallDirection direction){return directions_walled.test( size_t(direction) );}

void MazeNode::setPointerToPreviousMazeNode(MazeNode* thisNode){previousMazeNode = thisNode;}
MazeNode* MazeNode::getPointerToPreviousMazeNode(){return previousMazeNode;}

void MazeNode::setPointerToNextMazeNodeNorth(MazeNode* thisNode){nextMazeNodeNorth = thisNode;}
MazeNode* MazeNode::getPointerToNextMazeNodeNorth(){return nextMazeNodeNorth;}

void MazeNode::setPointerToNextMazeNodeEast(MazeNode* thisNode){nextMazeNodeEast = thisNode;}
MazeNode* MazeNode::getPointerToNextMazeNodeEast(){return nextMazeNodeEast;}

void MazeNode::setPointerToNextMazeNodeSouth(MazeNode* thisNode){nextMazeNodeSouth = thisNode;}
MazeNode* MazeNode::getPointerToNextMazeNodeSouth(){return nextMazeNodeSouth;}

void MazeNode::setPointerToNextMazeNodeWest(MazeNode* thisNode){nextMazeNodeWest = thisNode;}
MazeNode* MazeNode::getPointerToNextMazeNodeWest(){return nextMazeNodeWest;}

void MazeNode::setState(MazeNode::State state){mazeNodeState = state;}
MazeNode::State MazeNode::getState(){return mazeNodeState;}

void MazeNode::render(SDL_Renderer* gRenderer, unsigned int &  r, unsigned int &  g, unsigned int &  b)
{
    /*
    SDL_RenderDrawLine(SDL_Renderer* renderer,
                       int           x1,
                       int           y1,
                       int           x2,
                       int           y2)
    */
    
    SDL_SetRenderDrawColor(gRenderer,
                           r,
                           g,
                           b,
                           50);
    
    std::int16_t xPosLeft = maze_node.getCollider().x; 
    std::int16_t xPosRight =  maze_node.getCollider().x + maze_node.getCollider().w;
    std::int16_t yPosTop = maze_node.getCollider().y;
    std::int16_t yPosBottom = maze_node.getCollider().y + maze_node.getCollider().h;
    
    //if there is a wall on north
    if( MazeNode::getWallInThisDirection(MazeNode::WallDirection::NORTH) )
    {
        SDL_RenderDrawLine(gRenderer,xPosLeft,yPosTop,xPosRight,yPosTop);
    }
    //if there is a wall on east
    if( MazeNode::getWallInThisDirection(MazeNode::WallDirection::EAST) )
    {
        SDL_RenderDrawLine(gRenderer,xPosRight,yPosTop,xPosRight,yPosBottom);
    }
    //if there is a wall on south
    if( MazeNode::getWallInThisDirection(MazeNode::WallDirection::SOUTH) )
    {
        SDL_RenderDrawLine(gRenderer,xPosLeft,yPosBottom,xPosRight,yPosBottom);
    }
    //if there is a wall on west
    if( MazeNode::getWallInThisDirection(MazeNode::WallDirection::WEST) )
    {
        SDL_RenderDrawLine(gRenderer,xPosLeft,yPosTop,xPosLeft,yPosBottom);
    }
}

void MazeNode::renderCenterDot(SDL_Renderer* gRenderer, unsigned int &  r, unsigned int &  g, unsigned int &  b)
{
    SDL_SetRenderDrawColor(gRenderer,
                           r,g,b,
                           50);
    SDL_Rect dot_rect;
    dot_rect.x = maze_node.getCollider().x;
    dot_rect.y = maze_node.getCollider().y + ( maze_node.getCollider().h / 2) ;
    dot_rect.w = 10; dot_rect.h = 10;
    
    SDL_RenderDrawRect(gRenderer,&dot_rect);
}