#ifndef MAZE_NODE_H
#define MAZE_NODE_H

#include "Node.h"
#include <bitset>

class MazeNode
{
public:

    MazeNode();
    ~MazeNode();
    
    //functions to set and get Node member
    void setNode(Node& thisNode);
    Node& getNode();
    
    //enum for wall directions
    enum class WallDirection : std::int8_t {NORTH=0,EAST,SOUTH,WEST};
    
    void setWall(MazeNode::WallDirection direction,bool state);
    bool getWallInThisDirection(MazeNode::WallDirection direction);

    void setPointerToPreviousMazeNode(MazeNode* thisNode);
    MazeNode* getPointerToPreviousMazeNode();
    
    void setPointerToNextMazeNodeNorth(MazeNode* thisNode);
    MazeNode* getPointerToNextMazeNodeNorth();
    
    void setPointerToNextMazeNodeEast(MazeNode* thisNode);
    MazeNode* getPointerToNextMazeNodeEast();
    
    void setPointerToNextMazeNodeSouth(MazeNode* thisNode);
    MazeNode* getPointerToNextMazeNodeSouth();
    
    void setPointerToNextMazeNodeWest(MazeNode* thisNode);
    MazeNode* getPointerToNextMazeNodeWest();
    
    //State of maze node
    enum class State : std::int8_t {NOT_VISITED = 0, VISITED};
    void setState(MazeNode::State state);
    MazeNode::State getState();
    
    //function to render maze node with walls
    void render(SDL_Renderer* gRenderer, unsigned int&   r, unsigned int&   g, unsigned int&   b);
    
    //function to render dot in middle of node
    void renderCenterDot(SDL_Renderer* gRenderer, unsigned int&   r, unsigned int&   g, unsigned int&   b);
    
private:
    Node maze_node;
    std::bitset <4> directions_walled;
    
    MazeNode* previousMazeNode;
    //pointers to next nodes for a direction
    MazeNode* nextMazeNodeNorth;
    MazeNode* nextMazeNodeEast;
    MazeNode* nextMazeNodeSouth;
    MazeNode* nextMazeNodeWest;
    
    MazeNode::State mazeNodeState;
};

#endif