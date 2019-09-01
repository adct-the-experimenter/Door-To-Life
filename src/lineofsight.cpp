#include "lineofsight.h"

LineOfSight::LineOfSight()
{
    //make collider object point to line of sight collision box
    LOS_ColliderObject.ptrToCollisionBox = &LOS_collisionBox;
    //make collider object owner type line of sight
    LOS_ColliderObject.ownerType = CollisionBoxOwnerType::LINE_OF_SIGHT;
    
    //initialize enemy box pointer
    enemyBox = nullptr;
}

LineOfSight::~LineOfSight()
{
    
}

void LineOfSight::addLineOfSightToCollisionHandler()
{
    //addObjectToCollisionSystem(&LOS_ColliderObject);
}

void LineOfSight::removeLineOfSightFromCollisionHandler()
{
    //removeObjectFromCollisionSystem(&LOS_ColliderObject);
}


void LineOfSight::setLineWidth(std::int16_t& width){ lineWidth = width;}

void LineOfSight::setLineHeight(std::int16_t& height){lineHeight = height;}

void LineOfSight::setLineLocation(std::int16_t& x, std::int16_t& y)
{
    xPos = x;
    yPos = y;
}

void LineOfSight::attachLineOfSightToEnemyBox(SDL_Rect* box)
{
    enemyBox = box;
}
    
void LineOfSight::moveLineOfSightWithEnemy()
{
    if(enemyBox != nullptr)
    {
        xPos = enemyBox->x;
        yPos = enemyBox->y;
        enemyWidth = enemyBox->w;
        enemyHeight = enemyBox->h;
    }
}

void LineOfSight::faceUp()
{
    //keep at same x position
    LOS_collisionBox.x = xPos;
    //move up collision box by lineHeight
    LOS_collisionBox.y = yPos - lineHeight;
    
    //width and height of collision box when facing up
    LOS_collisionBox.h = lineHeight;
    LOS_collisionBox.w = lineWidth;
}

void LineOfSight::faceDown()
{
    //keep x position of enemy
    LOS_collisionBox.x = xPos;
    //move down collision box by line height and enemy height
    LOS_collisionBox.y = yPos + enemyHeight;
    
    //width and height of collision box when facing down
    LOS_collisionBox.h = lineHeight;
    LOS_collisionBox.w = lineWidth;
}

void LineOfSight::faceLeft()
{
    //keep at same y position
    LOS_collisionBox.y = yPos;
    //move collision box to the left by height of collision box
    LOS_collisionBox.x = xPos - lineHeight;
    
    //width and height of collision box when facing left
    //long side horizontal
    LOS_collisionBox.h = lineWidth;
    LOS_collisionBox.w = lineHeight;
}

void LineOfSight::faceRight()
{
    //keep at same y position
    LOS_collisionBox.y = yPos;
    //move collision box to the right by height of collision box and enemy width
    LOS_collisionBox.x = xPos + enemyWidth;
    //width and height of collision box when facing right
    //long side horizontal
    LOS_collisionBox.h = lineWidth;
    LOS_collisionBox.w = lineHeight;
}

void LineOfSight::faceUpLeft()
{
    //move collision box to the left by 1/2 width of collision box
    LOS_collisionBox.x = xPos - ( LOS_collisionBox.w / 2);
    //move up collision box by height of collision box
    LOS_collisionBox.y = yPos - LOS_collisionBox.h;
    
}

void LineOfSight::faceUpRight()
{
    //move collision box to the right by 1/2 width of collision box
    LOS_collisionBox.x = xPos + ( LOS_collisionBox.w / 2);
    //move up collision box by height of collision box
    LOS_collisionBox.y = yPos - LOS_collisionBox.h;
}

void LineOfSight::faceDownLeft()
{
    //move collision box to the left by 1/2 width of collision box
    LOS_collisionBox.x = xPos - ( LOS_collisionBox.w / 2);
    //move down collision box by height of collision box
    LOS_collisionBox.y = yPos + LOS_collisionBox.h;
}

void LineOfSight::faceDownRight()
{
    //move collision box to the right by 1/2 width of collision box
    LOS_collisionBox.x = xPos + ( LOS_collisionBox.w / 2);
    //move down collision box by height of collision box
    LOS_collisionBox.y = yPos + LOS_collisionBox.h;
}

bool LineOfSight::getBool_LineOfSightHitHero()
{
    //if line of sight collision object hit player
    if(LOS_ColliderObject.typeOfCollision == CollisionType::HIT_PLAYER)
    {
        return true;
    }
    else{return false;}
}

void LineOfSight::renderLineSight(SDL_Rect& camera, SDL_Renderer* gRenderer)
{
    SDL_SetRenderDrawColor(gRenderer,
                           200,
                           0,
                           0,
                           50);
    /*
    std::cout << "Enemy LOS box :" << "x: " << LOS_collisionBox.x << " " 
                                << "y: " << LOS_collisionBox.y << " "
                                << "w: " << LOS_collisionBox.w << " "
                                << "h: " << LOS_collisionBox.h << std::endl;
    
    */
    SDL_Rect renderRect = {LOS_collisionBox.x - camera.x, LOS_collisionBox.y - camera.y, 
                            LOS_collisionBox.w, LOS_collisionBox.h};
                            
    SDL_RenderDrawRect(gRenderer,&renderRect);
    
}

CollisionObject* LineOfSight::GetLineOfSightCollisionObject()
{
	return &LOS_ColliderObject;
}
