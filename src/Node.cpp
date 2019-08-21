#include "Node.h"

Node::Node()
{
    //initialize position of node
    std::int16_t x = 0; std::int16_t y = 0;
    Node::setPosition(x,y);
    //initialize collision boxes
    Node::initCollider();
    //initialize pointer to next node
    nextNodePtr = nullptr;
    //initialize pointer to previous node
    previousNodePtr = nullptr;
    //initialize node to face north
    Node::rotateCollider(Node::FaceDirection::NORTH);
    //initialize node as unmarked
    Node::setState(Node::State::EMPTY);
}

Node::~Node()
{
    //initialize pointer to next node
    nextNodePtr = nullptr;
    //initialize pointer to previous node
    previousNodePtr = nullptr;
}

//set pointers to node
void Node::setPointerToNextNode(Node* nextNode){nextNodePtr = nextNode;}
Node* Node::getPointerToNextNode(){return nextNodePtr;}

void Node::setPointerToPreviousNode(Node* prevNode){previousNodePtr = prevNode;}
Node* Node::getPointerToPreviousNode(){return previousNodePtr;}

void calculateDistanceBetweenNodes(Node* node1, Node* node2,std::int16_t* distance)
{
    // sqrt ( (x2-x1)^2 + (y2 - y1)^2 )
    
    std::int16_t node1X = node1->collider.x;
    std::int16_t node2X = node2->collider.x;
    std::int16_t node1Y = node1->collider.y;
    std::int16_t node2Y = node2->collider.y;
    
    //if node 1 is to left of node 2
    if(node1->collider.x < node2->collider.x)
    {
        //node 1 x is right of rectangle
        node1X = node1->collider.x + node1->collider.w;
        //node 2 x is left of rectangle
        node2X = node2->collider.x;
    }
    //if node 1 is to right of node 2
    else if(node1->collider.x > node2->collider.x)
    {
        //node 1 x is left of rectangle
        node1X = node1->collider.x;
        //node 2 x is right of rectangle
        node2X = node2->collider.x + node2->collider.w;
    }
    
    //if node 1 is above node 2
    if(node1->collider.y < node2->collider.y)
    {
        //node 1 y is bottom of rectangle
        node1Y = node1->collider.y + node1->collider.h;
        //node 2 y is top part of rectangle
        node2Y = node2->collider.y;
    }
    //if node 1 is below node 2
    else if(node1->collider.y > node2->collider.y)
    {
        //node 1 y is top of rectangle
        node1Y = node1->collider.y;
        //node 2 y is bottom of rectangle
        node2Y = node2->collider.y + node2->collider.h;
    }
    
    //calculate distance
    *distance = sqrt( 
    pow(node2X - node1X,2) 
    + pow( node2Y - node1Y,2) 
    );
   
}



bool nodeIsInBounds(Node* node, std::int16_t& leftBound,std::int16_t& rightBound, 
                    std::int16_t& topBound, std::int16_t& bottomBound)
{
    //bool inBounds = true;
    
    //check leftmost point isn't to left of left bound
    if(node->collider.x < leftBound)
    {
       return false;
    }
    //check leftmost point isn't to right of right bound
    if(node->collider.x > rightBound)
    {
        return false;
    }
    
    //check rightmost point isn't to right of right bound
    if(node->collider.x + node->collider.w > rightBound)
    {
        return false;
    }
    //check rightmost point isn't to left of left bound
    if(node->collider.x + node->collider.w < leftBound)
    {
        return false;
    }
    
    //check top point isn't above top bound
    if(node->collider.y < topBound)
    {
        return false;
    }
    
    //check bottom point isn't below bottom bound
    if(node->collider.y + node->collider.h > bottomBound)
    {
        return false;
    }
    
    //return inBounds;
}

bool nodeEdgesTouch(Node& node1,Node& node2 )
{
    bool edgesTouch = false;
    
    std::int16_t node1X = node1.collider.x;
    std::int16_t node2X = node2.collider.x;
    std::int16_t node1Y = node1.collider.y;
    std::int16_t node2Y = node2.collider.y;
    
    std::int8_t bounds_width = 1;
    std::int8_t bounds_height = 1;
    
    //bounds rectangle width and height
    std::int16_t leftBound,rightBound,topBound,bottomBound;
    
    //if node 1 is to left of node 2
    if(node1.collider.x < node2.collider.x)
    {
        /*
         *  |1||2| 
         * 
         * 
         * 
        */
        //node 1 x is right of rectangle
        leftBound = node1.collider.x + node1.collider.w;
        //node 2 x is left of rectangle
        rightBound = node2.collider.x;
        
        //if x distance between bounds is equal to bounds width
        if(rightBound - leftBound <= bounds_width)
        {
            //if node 1 and node 2 y coordinates are the same
            if(node1Y == node2Y){edgesTouch = true;}
        }
    }
    //if node 1 is to right of node 2
    else if(node1.collider.x > node2.collider.x)
    {
        /*
         *  |2||1| 
         * 
         * 
         * 
        */
        
        //node 1 x is left of rectangle
        rightBound = node1.collider.x;
        //node 2 x is right of rectangle
        leftBound = node2.collider.x + node2.collider.w;
        
        //if x distance between bounds of rectangle
        if(rightBound - leftBound <= bounds_width)
        {
            //if node 1 and node 2 y coordinates are the same
            if(node1Y == node2Y){edgesTouch = true;}
        }
    }
    
    //if node 1 is above node 2
    if(node1.collider.y < node2.collider.y)
    {
        /*
         *  |1|
         *  |2| 
         * 
         * 
        */
        //node 1 y is bottom of rectangle
        topBound = node1.collider.y + node1.collider.h;
        //node 2 y is top part of rectangle
        bottomBound = node2.collider.y;
        
        //if y distance between node 1y and node 2y is less than
        //or equal to height of bounds rectangle
        if(bottomBound - topBound <= bounds_height)
        {
            //if node 1 and node 2 x coordinates are the same
            if(node1X == node2X){edgesTouch = true;}
        }
    }
    //if node 1 is below node 2
    else if(node1.collider.y > node2.collider.y)
    {
        /*
         *  
         *  |2| 
         *  |1|
         * 
        */
        
        //node 1 y is top of rectangle
        bottomBound = node1.collider.y;
        //node 2 y is bottom of rectangle
        topBound = node2.collider.y + node2.collider.h;
        
        //if y distance between node 1y and node 2y is less than
        //or equal to height of bounds rectangle
        if(bottomBound - topBound <= bounds_height)
        {
            //if node 1 and node 2 x coordinates are the same
            if(node1X == node2X){edgesTouch = true;}
        }
    }
    
    
    return edgesTouch;
}

void Node::setPosition(std::int16_t& x, std::int16_t& y)
{
    collider.x = x; collider.y = y;
}

void Node::getPosition(std::int16_t* x,std::int16_t* y)
{
    *x = collider.x; *y = collider.y;
}

Node::FaceDirection Node::getFaceDirection(){return faceDirection;}

//functions to move node by width or height
void Node::moveUp()
{
    //move up by collider's height
    std::int16_t newY = collider.y - collider.h;
    std::int16_t posX = collider.x;
    Node::setPosition(posX,newY);
}

void Node::moveDown()
{
    //move down by collider's height
    std::int16_t newY = collider.y + collider.h;
    std::int16_t posX = collider.x;
    Node::setPosition(posX,newY);
}

void Node::moveLeft()
{
    //move left by collider's width
    std::int16_t newX = collider.x - collider.w;
    std::int16_t posY = collider.y;
    Node::setPosition(newX,posY);
}

void Node::moveRight()
{
    //move right by collider's width
    std::int16_t newX = collider.x + collider.w;
    std::int16_t posY = collider.y;
    Node::setPosition(newX,posY);
}

void Node::rotateCollider(Node::FaceDirection direction){faceDirection = direction;}

void Node::initCollider()
{
    NODE_WIDTH = scale * 10; 
    NODE_HEIGHT = scale * 10;
    
    collider.w = NODE_WIDTH;
    collider.h = NODE_HEIGHT;
}

bool checkNodeCollision( SDL_Rect& a, SDL_Rect& b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA; int topB;
    int bottomA; int bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

SDL_Rect& Node::getCollider(){return collider;}

void Node::render(SDL_Renderer* gRenderer,unsigned int r, unsigned int g, unsigned int b)
{
    //render collider rectangle of node
        SDL_SetRenderDrawColor(gRenderer,
                           r,
                           g,
                           b,
                           50);

        SDL_RenderDrawRect(gRenderer,&collider);
    
}

void Node::setState(Node::State state){nodeState = state;}
Node::State Node::getState(){return nodeState;}

bool Node::getMarkedKeepStatus()
{
    if(Node::getState() == Node::State::MARKED_KEEP){return true;}
    
    return false;
}

/*
    Shift colliders and rotate colliders test
 * //north node
    Node node1;
    node1.setPosition(320,320);
    //south node
    Node node2;
    node2.setPosition(200,300);
    node2.rotateColliders(Node::FaceDirection::SOUTH);
    //north east node
    Node node3;
    node3.setPosition(340,100);
    node3.rotateColliders(Node::FaceDirection::NORTHEAST);
    //north west node
    Node node4;
    node4.setPosition(200,100);
    node4.rotateColliders(Node::FaceDirection::NORTHWEST);
    //east node
    Node node5;
    node5.setPosition(320,200);
    node5.rotateColliders(Node::FaceDirection::EAST);
    //west node
    Node node6;
    node6.setPosition(200,200);
    node6.rotateColliders(Node::FaceDirection::WEST);
    //south east node
    Node node7;
    node7.setPosition(100,100);
    node7.rotateColliders(Node::FaceDirection::SOUTHEAST);
    //south west node
    Node node8;
    node8.setPosition(400,100);
    node8.rotateColliders(Node::FaceDirection::SOUTHWEST);
    
    bool collision = checkCollision(node3.getColliders(),node4.getColliders());
    
    //Rendering
    SDL_RenderClear(gRenderer);
    
    node1.render(gRenderer);
    node2.render(gRenderer);
    node3.render(gRenderer);
    node4.render(gRenderer);
    node5.render(gRenderer);
    node6.render(gRenderer);
    node7.render(gRenderer);
    node8.render(gRenderer);
    
    SDL_RenderPresent(gRenderer);

*/

/*
 bool node edges touch test
 //center Node 
    Node centerNode; 
    std::int16_t x = 320; std::int16_t y = 240;
    centerNode.setPosition(x,y);
    centerNode.initCollider();
    
    //left node
    Node leftNode = centerNode;
    leftNode.moveLeft();
    
    //right node
    Node rightNode = centerNode;
    rightNode.moveRight();
    
    //top node
    Node topNode = centerNode;
    topNode.moveUp();
    
    //bottom node
    Node bottomNode = centerNode;
    bottomNode.moveDown();
    
    //top left node
    Node topLeftNode = centerNode;
    topLeftNode.moveLeft();topLeftNode.moveUp();
    
    if(!nodeEdgesTouch(centerNode,leftNode)){std::cout << "False center & left! \n";}
    if(!nodeEdgesTouch(leftNode,centerNode)){std::cout << "False left & center! \n";}
    if(!nodeEdgesTouch(centerNode,rightNode)){std::cout << "False center & right! \n";}
    if(!nodeEdgesTouch(rightNode,centerNode)){std::cout << "False right & center! \n";}
    if(!nodeEdgesTouch(centerNode,topNode)){std::cout << "False center & top! \n";}
    if(!nodeEdgesTouch(topNode,centerNode)){std::cout << "False top & center! \n";}
    if(!nodeEdgesTouch(centerNode,bottomNode)){std::cout << "False center & bottom! \n";}
    if(!nodeEdgesTouch(bottomNode,centerNode)){std::cout << "False bottom & center! \n";}
    if(!nodeEdgesTouch(leftNode,topLeftNode)){std::cout << "False left & top left! \n";}
    if(!nodeEdgesTouch(topLeftNode,leftNode)){std::cout << "False topleft &  left! \n";}
    if(!nodeEdgesTouch(centerNode,topLeftNode)){std::cout << "False center & top left! \n";}
    if(!nodeEdgesTouch(topLeftNode,centerNode)){std::cout << "False  top left and center! \n";}
     * 
     * //render
     * centerNode.render(gRenderer,204,0,0);
        leftNode.render(gRenderer,204,0,0);
        topNode.render(gRenderer,204,0,0);
        bottomNode.render(gRenderer,204,0,0);
        topLeftNode.render(gRenderer,204,0,0);
  
*/