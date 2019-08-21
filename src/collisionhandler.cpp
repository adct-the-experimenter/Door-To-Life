#include "collisionhandler.h"


CollisionObject* playerCollisionObject;

Weapon* playerEquippedWeapon;

std::vector <CollisionObject*> collisionObjectsVector;

void addPlayerToCollisionSystem(CollisionObject* thisObject)
{
    //Initialize collision type to none
    thisObject->typeOfCollision = CollisionType::NONE;
    //assign player collision object global pointer to this object
    playerCollisionObject = thisObject;
    
}

void addObjectToCollisionSystem(CollisionObject* thisObject)
{
    //Initialize collision type to none
    thisObject->typeOfCollision = CollisionType::NONE;
    collisionObjectsVector.push_back(thisObject);
}

void addPlayerEquippedWeaponToCollisionSystem(Weapon* thisWeapon)
{
     //Initialize collision type to none
    thisWeapon->getCollisionObjectPtr()->typeOfCollision = CollisionType::NONE;
    playerEquippedWeapon = thisWeapon;
}

void removeObjectFromCollisionSystem(CollisionObject* thisObject)
{
    //Initialize collision type to none
    thisObject->typeOfCollision = CollisionType::NONE;
}

SDL_Rect* cameraCollisionHandler;
void setCameraForCollisionSystem(SDL_Rect* camera)
{
    cameraCollisionHandler = camera;
}

//function to check if object collided with player
static void runPlayerCollisionOperations(CollisionObject& thisObject);

//function to check if object collided with player weapon
static void runPlayerWeaponCollisionOperations(CollisionObject& thisObject);

void run_collision_handler()
{
    //for every collision object element in vector
    for(size_t i = 0; i < collisionObjectsVector.size(); ++i)
    {
        //if collision object pointer not pointing to nullptr
        if(collisionObjectsVector[i] != nullptr)
        {
            //if object is within camera
            if(checkCollision( *collisionObjectsVector.at(i)->ptrToCollisionBox,*cameraCollisionHandler ))
            {
                //check if object hits player
                runPlayerCollisionOperations(*collisionObjectsVector[i]);
                
                //check if object collided with player's equipped weapon
                runPlayerWeaponCollisionOperations(*collisionObjectsVector[i]);
            }
        }
               
    }
}

void runPlayerCollisionOperations(CollisionObject& thisObject)
{
    //if player collision object pointer is not pointing to nullptr
    if(playerCollisionObject != nullptr)
    {
        //if collides with player
        if(checkCollision( *playerCollisionObject->ptrToCollisionBox,
                            *thisObject.ptrToCollisionBox ) )
        {
            //set collision type of enemy collision object to type hit player
            thisObject.typeOfCollision = CollisionType::HIT_PLAYER;
            
            CollisionType typeCollisionToPlayer;
            //set collision type of player collision object based on
            switch(thisObject.ownerType )
            {
                case CollisionBoxOwnerType::COCKROACH :{ typeCollisionToPlayer = CollisionType::HIT_BY_COCKROACH; break;}
                case CollisionBoxOwnerType::HOLE:{ typeCollisionToPlayer = CollisionType::COLLIDING_WITH_HOLE; break;}
                default:{typeCollisionToPlayer = CollisionType::NONE; break;}
            }
            
            playerCollisionObject->typeOfCollision = typeCollisionToPlayer;
        }
        //else set collision type to none
        else{thisObject.typeOfCollision = CollisionType::NONE;}
    }
    
}


void runPlayerWeaponCollisionOperations(CollisionObject& thisObject)
{
    if(playerEquippedWeapon != nullptr)
    {
        //if collides with player weapon
        //if(checkCollision( *playerEquippedWeaponCollisionObject->ptrToCollisionBox,
        //                    *thisObject.ptrToCollisionBox ) )
        if(playerEquippedWeapon->checkCollisionWithWeapon(*thisObject.ptrToCollisionBox))
        {
            
            
            //type of collision to object
            //initialize to previous collision type
            CollisionType typeCollisionToObject = thisObject.typeOfCollision;
            
            //set collision type of enemy collision object 
            //based on owner type of equipped weapon
            switch(playerEquippedWeapon->getCollisionObjectPtr()->ownerType)
            {
                case CollisionBoxOwnerType::SWORD:{typeCollisionToObject = CollisionType::HIT_BY_SWORD; break;}
                case CollisionBoxOwnerType::BULLET:{typeCollisionToObject = CollisionType::HIT_BY_BULLET; break;}
                default:{ break;}
            }
            
            thisObject.typeOfCollision = typeCollisionToObject;
            
            //set direction of collision of object to direction of collision of player's weapon
            thisObject.directionOfCollision = playerEquippedWeapon->getCollisionObjectPtr()->directionOfCollision;
        }
    }
    
}


