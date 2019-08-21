
#include "collisionhandler.h"

class LineOfSight
{
public:

    LineOfSight();
    ~LineOfSight();
    
    //function to add collision object of line of sight to collision handler system
    //good in case want enemy to use line of sight or other options 
    void addLineOfSightToCollisionHandler();
    //function to remove collision object of line of sight from collision handler system
    void removeLineOfSightFromCollisionHandler();
    
    //function to set the width of the line
    //assuming it is the short side
    void setLineWidth(std::int16_t& width);
    //function to set the height of the line
    //assuming it is the long side
    void setLineHeight(std::int16_t& height);
    
    //function to change location of the line
    void setLineLocation(std::int16_t& x, std::int16_t& y);
    
    //function to assign SDL_Rect pointer to address enemy collision box
    void attachLineOfSightToEnemyBox(SDL_Rect* box);
    
    //function to set location of line of sight based on location of enemy box
    void moveLineOfSightWithEnemy();
    
    //functions to change direction line of sight is facing
    void faceUp();
    void faceDown();
    void faceLeft();
    void faceRight();
    
    
    void faceUpLeft();
    void faceUpRight();
    void faceDownLeft();
    void faceDownRight();
    
    //function to return if hero hit line of sight
    bool getBool_LineOfSightHitHero();
    
    //function to render line of sight
    void renderLineSight(SDL_Rect& camera,SDL_Renderer* gRenderer);
    
private:
    
    //position of enemy
    std::int16_t xPos;
    std::int16_t yPos;
    
    //dimensions of enemy
    std::int16_t enemyWidth;
    std::int16_t enemyHeight;
    
    SDL_Rect* enemyBox;
    
    //dimensions of enemy LOS box
    std::int16_t lineWidth;
    std::int16_t lineHeight;
    
    SDL_Rect LOS_collisionBox;
    
    //Collision Object member
    CollisionObject LOS_ColliderObject;
};