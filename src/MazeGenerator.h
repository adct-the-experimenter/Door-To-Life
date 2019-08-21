#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

#include "MazeNode.h"
#include "NodeGenerator.h"

class MazeGenerator
{
public:
    MazeGenerator();
    ~MazeGenerator();
    
    void loadResourcesFromNodeGenerator(NodeGenerator* node_gen);
    
    //function to carry out process of generating maze
    void generateMaze(RNGType& rngSeed);
    
    //function to render nodes in maze 
    void render(SDL_Renderer* gRenderer);
    
    //function to render dot in maze based on location
    void renderSquareInMazeNode(SDL_Renderer* gRenderer, size_t& xCol, size_t& yRow, unsigned int&   r, unsigned int&   g, unsigned int&   b);
    
    friend class Labyrinth;
    
private:

    std::vector <MazeNode> mazeNodesVector;
    
    std::vector <std::vector <MazeNode*> > maze_node_look_up;
    //function to load node look up from node generator into maze nodes look up
    void setup_maze_node_lookup();
    
    //recursive backtracking function
    void recursiveBackTracking(RNGType& rngSeed);
    
    //function to return pointer to random wall maze node
    MazeNode* getRandomWallMazeNode(RNGType& rngSeed);
    
    //function to return maze node pointer north of conductor
    MazeNode* getNorthElement(MazeNode* conductor);
    MazeNode* getEastElement(MazeNode* conductor);
    MazeNode* getSouthElement(MazeNode* conductor);
    MazeNode* getWestElement(MazeNode* conductor);
    
    //function to make a passage from 1 MazeNode to another MazeNode
    void carvePassage(MazeNode* someNode,MazeNode* NodeToBeConnected,
    MazeNode::WallDirection directionToConnectNode);
    
    //function to load nodes from node generator into mazeNodesVector
    void loadKeptNodesFromNodeGenerator(NodeGenerator* node_gen);
    //function to load node look up from node generator into maze_node_look_up
    void loadNodesLookUpFromNodeGenerator(NodeGenerator* node_gen);
    
    size_t numberXNodeColumns;
    size_t numberYNodeRows;
    std::int16_t gridNodeHeightDivision;
    std::int16_t gridNodeWidthDivision;
    
    std::int16_t gridX;
    std::int16_t gridY;
    std::int16_t gridWidth;
    std::int16_t gridHeight;
};

#endif