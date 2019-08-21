#ifndef NODE_GENERATOR_H
#define NODE_GENERATOR_H

#include "hashtable.h"
#include "item.h"
#include "Node.h"
#include <vector>
#include <array>
#include <cstdint>
#include <cstdlib>

//boost random meresenne twister with probablities
#include <ctime>
#include "globalvariables.h" //random generation


#include <bitset> //for std::bitset




/*
 * 
 *                                     [Root Node]
 *                      /
 * 
 *              [Node 1-0]               [Node 2-0]                 [Node 3-0]         
 * 
 *                  \   
 * [Node 1-0-1]  [Node 1-0-2]   [Node 2-0-1] [Node 2-0-2]  [Node 3-0-1] [Node 3-0-2]
 * 
 * 
 * 
 *  Workflow: 
 *  Generate node options randomly   
 *  Add options to list
 *  As conductor moves along, present it with options to which node to go to based on 
 *  what node is closest.
 *  With conductor node go through options, evaluate according to conditions, remove from list
 *   
 * 
 */



class NodeGenerator
{
public:
    NodeGenerator();
    ~NodeGenerator();

//Setup functions    
    //function to set grid dimensions
    void setGridDimensions(std::int16_t x, std::int16_t y,std::int16_t w, std::int16_t h);
    //function to set number of nodes to put in labyrinth
    void setNumberOfNodesInLabyrinth(std::int16_t& numNodes);
    //function to return number of nodes in labyrinth
    std::int16_t getNumberOfNodesInLabyrinth();
    
//Generation functions
    //function to generate different node options to take
    void generateNodes(RNGType& rngSeed);
    
    //function to choose node options
    bool chooseNodesRandomly(RNGType& rngSeed);
    
    
    
    
    //function to remove nodes not chosen
    void removeExtraNodes();
    

    
    
    //render nodes
    void render(SDL_Renderer* gRenderer);
    
    //function to render grid of empty nodes
    void renderEmptyGrid(SDL_Renderer* gRenderer);
    //function to render nodes that were chosen as temp
    void renderTempNodes(SDL_Renderer* gRenderer);
    //function to render kept nodes
    void renderKeptNodes(SDL_Renderer* gRenderer);
    
    enum class ConductorState : std::int8_t {NONE=0, GENERATING_NODES,
                                            HIT_NODE_IN_GENERATING_NODES,
                                            HIT_WALL_IN_GENERATING_NODES,
                                            PASSED_NODE_GEN_CHECKS,
                                            CONDUCTING_TO_NEXT_NODE,
                                            CONDUCTING_TO_PREV_NODE};
                                            
    void setConductorsState(NodeGenerator::ConductorState state);
    NodeGenerator::ConductorState getConductorsState();
    
    //function to return vector of nodes in nodes to keep list
    std::vector <Node> getNodesKept();
    
    friend class MazeGenerator;
    
private:
    
    //container that allows pop back and push back and insertion
    
    
    //2D vector that conatains address of nodes in empty node list
    std::vector < std::vector <Node*> > node_look_up;
    void setup_node_lookup();
    
    size_t numXNodeColumns;
    size_t numYNodeRows;
    
    void getColsAndRows(size_t& xCols,size_t& yRows);
    
    //list of nodes to keep
    std::vector <Node*> nodesToKeepList;
    //list of temporary node generated
    std::vector <Node*> tempNodeList;
    //list of empty nodes
    std::vector <Node> emptyNodeList;
    
   
    
    //vector to temporarily hold items in memory
    std::vector <Item*> tempItemContainer;
    
    std::int16_t numberOfNodes;
    std::int16_t initialListNum;
    
    std::int16_t getInitialListNum();
    
    //grid boundaries
    std::int16_t gridX;
    std::int16_t gridY;
    std::int16_t gridWidth;
    std::int16_t gridHeight;
    
    std::int16_t gridNodeHeightDivision;
    std::int16_t gridNodeWidthDivision;
    
    //state of conductor
    ConductorState conductors_state;
    
//Empty Nodes
    void generateEmptyNodes();
    
//Node Generation
    // probabilites for cardinal directions N,NE,E,SE,S,SW,W,NW
    std::array <double,8> nextDirectionNorth;// = {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2};
    std::array <double,8> nextDirectionNorthEast;// = {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2};
    std::array <double,8> nextDirectionEast;// = {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2};
    std::array <double,8> nextDirectionSouthEast;// = {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2};
    std::array <double,8> nextDirectionSouth;// = {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2};
    std::array <double,8> nextDirectionSouthWest;// = {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2};
    std::array <double,8> nextDirectionWest;// = {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2};
    std::array <double,8> nextDirectionNorthWest;// = {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2};
    
    //conductor reaction processes
    void moveConductorNodeRandomly_Generation(Node** conductorNodePtr,RNGType& rngSeed);
    
    void genNodesFromRoot(RNGType& rngSeed,std::int8_t& limit);
    void genNodesFromEnd(RNGType& rngSeed,std::int8_t& limit);
    void genNodesFromThisNode(Node* thisNode,RNGType& rngSeed,std::int8_t& limit);
    
    
//Node Keep Process

    //function to run pass 1 of node and return a bool if successful
    bool nodeKeep_Pass1(RNGType& rngSeed);

    //function to run process for chossing nodes and generating new ones if run out
    void nodeKeepProcess_AddNodes(Node* conductor,Node* root,RNGType& rngSeed);
    
 //hash table for next nodes for conductor
    //used to organize nodes by distance
    HashTable conductorsTable;
    
    //function to insert item that has Node pointer pointing to something 
    //into condcutor's table
    void insertItemWithNode_IntoConductorsTable(Node* thisNode, std::int16_t& distance);
    
    //function to clear hash table for conductor
    void clearConductorsTable();
    
    //function to make nodes close to conductor point to conductor as a previous node
    void makeNodeOptionsBasedOnProximity(Node* conductorNode, std::vector <Node*> &thisList);
    //function to make conductor choose to go to node closest to it
    void makeConductorChooseCloseAvailableNodeRandomly(Node* conductorNode,RNGType& rngSeed );
    
    //function to run process for chosing node to keep
    void conductorKeepNodeProcess(Node** conductor,RNGType& rngSeed);
    

    void runNodeGenChecks(Node* conductorNode,std::vector <Node*> &tempList);
    //Condition functions    
    //function to check if a node collides with another node
    bool checkNodeToNodeCollision(Node* thisNode, std::vector <Node*> &thisList);
    
    //function to check if node collides with grid
    bool checkNodeIsInGrid(Node* node);
    
    //variable to tell which direction conductor node should not go to.                                        
    std::bitset <8> directionsBanned;//initialized to 9 so that no directions are banned at start
    void banDirection(Node::FaceDirection thisDirection);
    
    void resetBannedDirections();
    
    //function to generate random direction
    std::int8_t genDirection(RNGType& rngSeed);
    
    //add node to keep list
    void addNodeToKeepList(Node* thisNode);
    
};

#endif