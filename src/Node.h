#ifndef NODE_H
#define NODE_H

#include "globalvariables.h" //for SDL_Rect
#include <cstdint>
#include <vector>
#include <cmath>


class Node
{
public:
    
    Node();
    ~Node();
    
    //next node
    void setPointerToNextNode(Node* nextNode);
    Node* getPointerToNextNode();
    
    //previous node
    void setPointerToPreviousNode(Node* prevNode);
    Node* getPointerToPreviousNode();
    
    //distance between node border points
    friend void calculateDistanceBetweenNodes(Node* node1, Node* node2,std::int16_t* distance);
                                              
                              
    //function to check if a node is in bounds of an area
    friend bool nodeIsInBounds(Node* node, std::int16_t& leftBound,std::int16_t& rightBound, 
                    std::int16_t& topBound, std::int16_t& bottomBound);
    
    //function to check if a node is touching another node's edge
    friend bool nodeEdgesTouch(Node& node1,Node& node2 );
    
    //function to set position of node
    void setPosition(std::int16_t& x, std::int16_t& y);
    //function to return position of node
    void getPosition(std::int16_t* x,std::int16_t* y);
   
    
    enum class FaceDirection : std::int8_t {NORTH = 0,
                                            NORTHEAST,EAST,SOUTHEAST,
                                            SOUTH,
                                            SOUTHWEST, WEST, NORTHWEST}; 
    
    Node::FaceDirection getFaceDirection();
    
    //function to rotate collider in certain direction
    void rotateCollider(Node::FaceDirection direction);
    
    //functions to move a node up or down by its height 
    //or left or right by its width
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    
    
    //function to check collision between nodes
    friend bool checkNodeCollision(SDL_Rect& a, SDL_Rect& b );
    
    //function to return address of collider variable
    SDL_Rect& getCollider();
    
    //for rendering node
    void render(SDL_Renderer* gRenderer,unsigned int r, unsigned int g, unsigned int b);
    
    //scale factor for node width and height
    std::int8_t scale = 2;
    
    std::int8_t NODE_WIDTH = 10;
    std::int8_t NODE_HEIGHT = 10;
    
    //set width and height of rectangle node
    void initCollider();
    
    //State of Node
    enum class State : std::int8_t {EMPTY=0,MARKED_TEMP,MARKED_KEEP};
    
    void setState(Node::State state);
    Node::State getState();
    
    bool getMarkedKeepStatus();
    
private:
    //pointer to previous node
    Node* previousNodePtr;
    
    
    //pointer to next node
    Node* nextNodePtr;
    
    
    //what direction rectangle is facing
    Node::FaceDirection faceDirection;
    
    //collision box for rectangular node
    SDL_Rect collider;
    
    //bit set to hold info on wall
    //bit set walls;
    
    //state of bool
    Node::State nodeState;
};

#endif