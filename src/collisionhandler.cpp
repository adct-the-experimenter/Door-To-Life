#include "collisionhandler.h"


CollisonHandler::CollisonHandler()
{
	repeatPlay = false;
}

CollisonHandler::~CollisonHandler()
{
	
}

void CollisonHandler::addPlayerToCollisionSystem(CollisionObject* thisObject)
{
    //Initialize collision type to none
    thisObject->typeOfCollision = CollisionType::NONE;
    //assign player collision object global pointer to this object
    m_playerCollisionObject_ptr = thisObject;
    
}

void CollisonHandler::addObjectToCollisionSystem(CollisionObject* thisObject)
{
    //Initialize collision type to none
    thisObject->typeOfCollision = CollisionType::NONE;
    collisionObjectsVector.push_back(thisObject);
}

void CollisonHandler::addPlayerEquippedWeaponToCollisionSystem(Weapon* thisWeapon)
{
     //Initialize collision type to none
    thisWeapon->getCollisionObjectPtr()->typeOfCollision = CollisionType::NONE;
    playerEquippedWeapon = thisWeapon;
}

void CollisonHandler::removeObjectFromCollisionSystem(CollisionObject* thisObject)
{
    //Initialize collision type to none
    thisObject->typeOfCollision = CollisionType::NONE;
}


void CollisonHandler::setCameraForCollisionSystem(SDL_Rect* camera)
{
    cameraCollisionHandler = camera;
}


void CollisonHandler::run_collision_handler()
{
	
    //for every collision object element in vector
    for(size_t i = 0; i < collisionObjectsVector.size(); ++i)
    {
        //if collision object pointer not pointing to nullptr
        if(collisionObjectsVector[i] != nullptr)
        {
			if(repeatPlay)
			{
				std::cout << "repeat Play" << std::endl;
			}
			
			if(collisionObjectsVector.at(i)->ownerType != CollisionBoxOwnerType::NONE)
			{
				if(collisionObjectsVector.at(i)->ptrToCollisionBox)
				{	
					//if object is within camera
					if(checkCollision( *collisionObjectsVector.at(i)->ptrToCollisionBox,*cameraCollisionHandler ))
					{
						//check if object hits player
						CollisonHandler::runPlayerCollisionOperations(*collisionObjectsVector[i]);
						
						//check if object collided with player's equipped weapon
						CollisonHandler::runPlayerWeaponCollisionOperations(*collisionObjectsVector[i]);
					}
				}
				else
				{
					std::cout << "Error, i: " << i << " collision pointer is not initialized.\n";
				}
				
			}
			else
			{
				std::cout << "Uninitialized collision object at i=" << i <<" ! \n";
			}
			
            
        }
               
    }
}

//function to check if object collided with player
void CollisonHandler::runPlayerCollisionOperations(CollisionObject& thisObject)
{
    //if player collision object pointer is not pointing to nullptr
    if(m_playerCollisionObject_ptr != nullptr)
    {
        //if collides with player
        if(checkCollision( *m_playerCollisionObject_ptr->ptrToCollisionBox,
                            *thisObject.ptrToCollisionBox ) )
        {
            //set collision type of enemy collision object to type hit player
            thisObject.typeOfCollision = CollisionType::HIT_PLAYER;
            
            CollisionType typeCollisionToPlayer;
            //set collision type of player collision object based on
            switch(thisObject.ownerType )
            {
                case CollisionBoxOwnerType::COCKROACH :{ typeCollisionToPlayer = CollisionType::HIT_BY_COCKROACH; break;}
                case CollisionBoxOwnerType::GREEDY_ZOMBIE :{ typeCollisionToPlayer = CollisionType::HIT_BY_ZOMBIE; break;}
                case CollisionBoxOwnerType::HOLE:{ typeCollisionToPlayer = CollisionType::COLLIDING_WITH_HOLE; break;}
                default:{typeCollisionToPlayer = CollisionType::NONE; break;}
            }
            
            m_playerCollisionObject_ptr->typeOfCollision = typeCollisionToPlayer;
        }
        //else set collision type to none
        else{thisObject.typeOfCollision = CollisionType::NONE;}
    }
    
}

//function to check if object collided with player weapon
void CollisonHandler::runPlayerWeaponCollisionOperations(CollisionObject& thisObject)
{
	
    if(playerEquippedWeapon != nullptr)
    {
		
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

void CollisonHandler::EmptyCollisionObjectVector()
{
	collisionObjectsVector.empty();
}

void CollisonHandler::EmptyPlayerEquippedWeapon()
{
	playerEquippedWeapon = nullptr;
}

