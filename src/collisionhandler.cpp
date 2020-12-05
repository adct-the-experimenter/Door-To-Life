#include "collisionhandler.h"


CollisonHandler::CollisonHandler()
{
	repeatPlay = false;
	
	playerEquippedWeapon = nullptr;
	playerEquippedWeapon2 = nullptr;
	playerEquippedWeapon3 = nullptr;
	playerEquippedWeapon4 = nullptr;
	
	m_player1CollisionObject_ptr = nullptr;
	m_player2CollisionObject_ptr = nullptr;
	m_player3CollisionObject_ptr = nullptr;
	m_player4CollisionObject_ptr = nullptr;
}

CollisonHandler::~CollisonHandler()
{
	
}

void CollisonHandler::addPlayerToCollisionSystem(CollisionObject* thisObject)
{
    //Initialize collision type to none
    thisObject->typeOfCollision = CollisionType::NONE;
    //assign player collision object global pointer to this object
    m_player1CollisionObject_ptr = thisObject;
    
}

void CollisonHandler::addPlayersToCollisionSystem(CollisionObject* p1,CollisionObject* p2,CollisionObject* p3,CollisionObject* p4)
{
    
    //assign player collision object global pointer to this object
    m_player1CollisionObject_ptr = p1;
    m_player2CollisionObject_ptr = p2;
    m_player3CollisionObject_ptr = p3;
    m_player4CollisionObject_ptr = p4;
    
    //Initialize collision type to none
    if(p1){p1->typeOfCollision = CollisionType::NONE;}
    if(p2){p2->typeOfCollision = CollisionType::NONE;}
    if(p3){p3->typeOfCollision = CollisionType::NONE;}
    if(p4){p4->typeOfCollision = CollisionType::NONE;}
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

void CollisonHandler::addPlayerEquippedWeaponsToCollisionSystem(Weapon* thisWeapon1,Weapon* thisWeapon2,Weapon* thisWeapon3,Weapon* thisWeapon4)
{
	if(thisWeapon1)
	{
		thisWeapon1->getCollisionObjectPtr()->typeOfCollision = CollisionType::NONE;
		playerEquippedWeapon = thisWeapon1;
	}
	
	if(thisWeapon2)
	{
		thisWeapon2->getCollisionObjectPtr()->typeOfCollision = CollisionType::NONE;
		playerEquippedWeapon2 = thisWeapon2;
	}
	
	if(thisWeapon3)
	{
		thisWeapon3->getCollisionObjectPtr()->typeOfCollision = CollisionType::NONE;
		playerEquippedWeapon3 = thisWeapon3;
	}
	
	if(thisWeapon4)
	{
		thisWeapon4->getCollisionObjectPtr()->typeOfCollision = CollisionType::NONE;
		playerEquippedWeapon4 = thisWeapon4;
	}
	
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

void CollisonHandler::SetCamerasForCollisionSystem(SDL_Rect* camera1,SDL_Rect* camera2,SDL_Rect* camera3,SDL_Rect* camera4)
{
	cameraCollisionHandler = camera1;
	cameraCollisionHandler2 = camera2;
	cameraCollisionHandler3 = camera3;
	cameraCollisionHandler4 = camera4;
}

void CollisonHandler::run_collision_handler(PlayerManager& playerManager,PlayerManager::PlayerLocation& location)
{
	int num_players = playerManager.GetNumberOfPlayers();
	
	PlayerManager::PlayerLocation p1_loc, p2_loc, p3_loc, p4_loc;
	playerManager.GetLocationEnumOfPlayers(&p1_loc,&p2_loc,&p3_loc,&p4_loc);
							
	
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
					if(p1_loc == location && 
						checkCollision( *collisionObjectsVector.at(i)->ptrToCollisionBox,*cameraCollisionHandler ))
					{
						//check if object hits player
						CollisonHandler::runPlayer1CollisionOperations(*collisionObjectsVector[i]);
						
						//check if object collided with player's equipped weapon
						CollisonHandler::runPlayer1WeaponCollisionOperations(*collisionObjectsVector[i]);
					}
					if(p2_loc == location && num_players > 1 && cameraCollisionHandler2)
					{
						if(checkCollision( *collisionObjectsVector.at(i)->ptrToCollisionBox,*cameraCollisionHandler2 ))
						{
							//check if object hits player
							CollisonHandler::runPlayer2CollisionOperations(*collisionObjectsVector[i]);
							
							//check if object collided with player's equipped weapon
							CollisonHandler::runPlayer2WeaponCollisionOperations(*collisionObjectsVector[i]);
							
						}
						
					}
					if(p3_loc == location && num_players > 2 && cameraCollisionHandler3)
					{
						if(checkCollision( *collisionObjectsVector.at(i)->ptrToCollisionBox,*cameraCollisionHandler3 ))
						{
							//check if object hits player
							CollisonHandler::runPlayer3CollisionOperations(*collisionObjectsVector[i]);
							
							//check if object collided with player's equipped weapon
							CollisonHandler::runPlayer3WeaponCollisionOperations(*collisionObjectsVector[i]);
						}
						
					}
					if(p4_loc == location && num_players > 3 && cameraCollisionHandler4)
					{
						if(checkCollision( *collisionObjectsVector.at(i)->ptrToCollisionBox,*cameraCollisionHandler4 ))
						{
							//check if object hits player
							CollisonHandler::runPlayer4CollisionOperations(*collisionObjectsVector[i]);
							
							//check if object collided with player's equipped weapon
							CollisonHandler::runPlayer4WeaponCollisionOperations(*collisionObjectsVector[i]);
						}
						
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
    
    CollisonHandler::runPlayerToPlayerCollisionOperations(playerManager,location);
}

void CollisonHandler::runPlayerToPlayerCollisionOperations(PlayerManager& playerManager,PlayerManager::PlayerLocation& location)
{
	
	int num_players = playerManager.GetNumberOfPlayers();
	
	PlayerManager::PlayerLocation p1_loc, p2_loc, p3_loc, p4_loc;
	playerManager.GetLocationEnumOfPlayers(&p1_loc,&p2_loc,&p3_loc,&p4_loc);
	
	//for at least 2 player game
	if(num_players > 1 && m_player2CollisionObject_ptr && m_player1CollisionObject_ptr)
	{
		if(p1_loc == location && p2_loc == p1_loc)
		{
			//check if player 1 collides with player 2
			CollisonHandler::runPlayer1WeaponCollisionOperations(*m_player2CollisionObject_ptr);
			CollisonHandler::runPlayer2WeaponCollisionOperations(*m_player1CollisionObject_ptr);
		}
	}
	
	//for at least 3 player game
	if(num_players > 2 && m_player3CollisionObject_ptr 
		&& m_player2CollisionObject_ptr 
		&& m_player1CollisionObject_ptr)
	{
		if(p1_loc == location && p3_loc == p1_loc)
		{
			
			//check if player 1 and player 3 collide
			CollisonHandler::runPlayer1WeaponCollisionOperations(*m_player3CollisionObject_ptr);
			CollisonHandler::runPlayer3WeaponCollisionOperations(*m_player1CollisionObject_ptr);
						
		}
		
		if(p2_loc == location && p3_loc == p2_loc)
		{
						
			//check if player 2 and player 3 collide
			CollisonHandler::runPlayer2WeaponCollisionOperations(*m_player3CollisionObject_ptr);
			CollisonHandler::runPlayer3WeaponCollisionOperations(*m_player2CollisionObject_ptr);
			
		}
	}
	
	//for at least 4 player game
	if(num_players > 3 && m_player4CollisionObject_ptr
		&& m_player3CollisionObject_ptr 
		&& m_player2CollisionObject_ptr 
		&& m_player1CollisionObject_ptr)
	{
		if(p1_loc == location && p4_loc == p1_loc)
		{
			
			//check if player 1 and player 4 collide
			CollisonHandler::runPlayer4WeaponCollisionOperations(*m_player1CollisionObject_ptr);
			CollisonHandler::runPlayer1WeaponCollisionOperations(*m_player4CollisionObject_ptr);
			
		}
		
		if(p2_loc == location && p4_loc == p2_loc)
		{
					
			//check if player 2 and player 4 collide
			CollisonHandler::runPlayer2WeaponCollisionOperations(*m_player4CollisionObject_ptr);
			CollisonHandler::runPlayer4WeaponCollisionOperations(*m_player2CollisionObject_ptr);
			
		}
		
		if(p3_loc == location && p4_loc == p3_loc)
		{
			//check if player 3 and player 4 collide
			CollisonHandler::runPlayer3WeaponCollisionOperations(*m_player4CollisionObject_ptr);
			CollisonHandler::runPlayer4WeaponCollisionOperations(*m_player3CollisionObject_ptr);
			
		}
	}
}


//function to check if object collided with player
void CollisonHandler::runPlayer1CollisionOperations(CollisionObject& thisObject)
{
    //if player collision object pointer is not pointing to nullptr
    if(m_player1CollisionObject_ptr != nullptr)
    {
        //if collides with player
        if(checkCollision( *m_player1CollisionObject_ptr->ptrToCollisionBox,
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
                case CollisionBoxOwnerType::SWORD:{ typeCollisionToPlayer = CollisionType::HIT_BY_SWORD; break;}
                case CollisionBoxOwnerType::BULLET:{ typeCollisionToPlayer = CollisionType::HIT_BY_BULLET; break;}
                default:{typeCollisionToPlayer = CollisionType::NONE; break;}
            }
            
            m_player1CollisionObject_ptr->typeOfCollision = typeCollisionToPlayer;
        }
        //else set collision type to none
        else{thisObject.typeOfCollision = CollisionType::NONE;}
    }
   
   
    
    
}

void CollisonHandler::runPlayer2CollisionOperations(CollisionObject& thisObject)
{
	 //if player collision object pointer is not pointing to nullptr
    if(m_player2CollisionObject_ptr != nullptr)
    {
        //if collides with player
        if(checkCollision( *m_player2CollisionObject_ptr->ptrToCollisionBox,
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
                case CollisionBoxOwnerType::SWORD:{ typeCollisionToPlayer = CollisionType::HIT_BY_SWORD; break;}
                case CollisionBoxOwnerType::BULLET:{ typeCollisionToPlayer = CollisionType::HIT_BY_BULLET; break;}
                default:{typeCollisionToPlayer = CollisionType::NONE; break;}
            }
            
            m_player2CollisionObject_ptr->typeOfCollision = typeCollisionToPlayer;
        }
        //else set collision type to none
        else{thisObject.typeOfCollision = CollisionType::NONE;}
    }
}

void CollisonHandler::runPlayer3CollisionOperations(CollisionObject& thisObject)
{
	 //if player collision object pointer is not pointing to nullptr
    if(m_player3CollisionObject_ptr != nullptr)
    {
        //if collides with player
        if(checkCollision( *m_player3CollisionObject_ptr->ptrToCollisionBox,
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
                case CollisionBoxOwnerType::SWORD:{ typeCollisionToPlayer = CollisionType::HIT_BY_SWORD; break;}
                case CollisionBoxOwnerType::BULLET:{ typeCollisionToPlayer = CollisionType::HIT_BY_BULLET; break;}
                default:{typeCollisionToPlayer = CollisionType::NONE; break;}
            }
            
            m_player3CollisionObject_ptr->typeOfCollision = typeCollisionToPlayer;
        }
        //else set collision type to none
        else{thisObject.typeOfCollision = CollisionType::NONE;}
    }
}

void CollisonHandler::runPlayer4CollisionOperations(CollisionObject& thisObject)
{
	//if player collision object pointer is not pointing to nullptr
    if(m_player4CollisionObject_ptr != nullptr)
    {
        //if collides with player
        if(checkCollision( *m_player4CollisionObject_ptr->ptrToCollisionBox,
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
                case CollisionBoxOwnerType::SWORD:{ typeCollisionToPlayer = CollisionType::HIT_BY_SWORD; break;}
                case CollisionBoxOwnerType::BULLET:{ typeCollisionToPlayer = CollisionType::HIT_BY_BULLET; break;}
                default:{typeCollisionToPlayer = CollisionType::NONE; break;}
            }
            
            m_player4CollisionObject_ptr->typeOfCollision = typeCollisionToPlayer;
        }
        //else set collision type to none
        else{thisObject.typeOfCollision = CollisionType::NONE;}
    }
}

//function to check if object collided with player weapon
void CollisonHandler::runPlayer1WeaponCollisionOperations(CollisionObject& thisObject)
{
	
    if(playerEquippedWeapon != nullptr && thisObject.ptrToCollisionBox)
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

void CollisonHandler::runPlayer2WeaponCollisionOperations(CollisionObject& thisObject)
{
	
    if(playerEquippedWeapon2 != nullptr)
    {
		
        if(playerEquippedWeapon2->checkCollisionWithWeapon(*thisObject.ptrToCollisionBox))
        {
            
            //type of collision to object
            //initialize to previous collision type
            CollisionType typeCollisionToObject = thisObject.typeOfCollision;
            
            //set collision type of enemy collision object 
            //based on owner type of equipped weapon
            switch(playerEquippedWeapon2->getCollisionObjectPtr()->ownerType)
            {
                case CollisionBoxOwnerType::SWORD:{typeCollisionToObject = CollisionType::HIT_BY_SWORD; break;}
                case CollisionBoxOwnerType::BULLET:{typeCollisionToObject = CollisionType::HIT_BY_BULLET; break;}
                default:{ break;}
            }
            
            thisObject.typeOfCollision = typeCollisionToObject;
            
            //set direction of collision of object to direction of collision of player's weapon
            thisObject.directionOfCollision = playerEquippedWeapon2->getCollisionObjectPtr()->directionOfCollision;
        }
    }
    
}

void CollisonHandler::runPlayer3WeaponCollisionOperations(CollisionObject& thisObject)
{
	
    if(playerEquippedWeapon3 != nullptr)
    {
		
        if(playerEquippedWeapon3->checkCollisionWithWeapon(*thisObject.ptrToCollisionBox))
        {
            
            //type of collision to object
            //initialize to previous collision type
            CollisionType typeCollisionToObject = thisObject.typeOfCollision;
            
            //set collision type of enemy collision object 
            //based on owner type of equipped weapon
            switch(playerEquippedWeapon3->getCollisionObjectPtr()->ownerType)
            {
                case CollisionBoxOwnerType::SWORD:{typeCollisionToObject = CollisionType::HIT_BY_SWORD; break;}
                case CollisionBoxOwnerType::BULLET:{typeCollisionToObject = CollisionType::HIT_BY_BULLET; break;}
                default:{ break;}
            }
            
            thisObject.typeOfCollision = typeCollisionToObject;
            
            //set direction of collision of object to direction of collision of player's weapon
            thisObject.directionOfCollision = playerEquippedWeapon3->getCollisionObjectPtr()->directionOfCollision;
        }
    }
    
}

void CollisonHandler::runPlayer4WeaponCollisionOperations(CollisionObject& thisObject)
{
	
    if(playerEquippedWeapon4 != nullptr)
    {
		
        if(playerEquippedWeapon4->checkCollisionWithWeapon(*thisObject.ptrToCollisionBox))
        {
            
            //type of collision to object
            //initialize to previous collision type
            CollisionType typeCollisionToObject = thisObject.typeOfCollision;
            
            //set collision type of enemy collision object 
            //based on owner type of equipped weapon
            switch(playerEquippedWeapon4->getCollisionObjectPtr()->ownerType)
            {
                case CollisionBoxOwnerType::SWORD:{typeCollisionToObject = CollisionType::HIT_BY_SWORD; break;}
                case CollisionBoxOwnerType::BULLET:{typeCollisionToObject = CollisionType::HIT_BY_BULLET; break;}
                default:{ break;}
            }
            
            thisObject.typeOfCollision = typeCollisionToObject;
            
            //set direction of collision of object to direction of collision of player's weapon
            thisObject.directionOfCollision = playerEquippedWeapon4->getCollisionObjectPtr()->directionOfCollision;
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

