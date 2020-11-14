#include "player.h"

#include <iostream>

//constructor
Player::Player(int x,int y,int width,int height) : Sprite(x,y,width,height)
{
    std::int16_t initialHealth = 100;
    
    Player::setHealth(initialHealth);
    
    Player::setPlayerState(Player::PlayerState::NORMAL);
    Player::setupPlayerCollisionObject();
    
    Player::resetLoopCount();
    clipPlayer.w = 35; clipPlayer.h = 30;
    
    //set where head is facing
    //initially set facing south
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_X] = 0.0f; //forward vector x value
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_Y] = 0.0f; //forward vector y value
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_Z] = 1.0f; //forward vector z value
	//set direction of top of head surface vector
	listener_orientation_vector[ORIENTATION_INDEX::UP_X] = 0.0f; //up vector x value
	listener_orientation_vector[ORIENTATION_INDEX::UP_Y] = 1.0f; //up vector y value
	listener_orientation_vector[ORIENTATION_INDEX::UP_Z] = 0.0f; //up vector z value
	
	//set current listener orientation
	alListenerfv(AL_ORIENTATION, listener_orientation_vector.data());
	
	//Initialize Listener speed
	alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);//is not moving in 3d space
	
	equippedPlayerWeapon = nullptr;
	
	m_player_num = 0;
}

Player::~Player()
{
    //std::cout << "\n Player destructor called! \n";
}

void Player::setPlayerState(Player::PlayerState thisState){playerState = thisState;}
Player::PlayerState Player::getPlayerState(){return playerState;}

void Player::setupPlayerCollisionObject()
{
    CollisionBoxOwnerType type = CollisionBoxOwnerType::PLAYER;
    Player::setOwnerTypeOfCollisionObject(type);
}


bool Player::loadMedia(LTexture* thisTex, std::string path,SDL_Renderer* gRenderer)
{
    return Sprite::loadMedia(&playerTexture,path,gRenderer);
}

void Player::setPointerToTexture(LTexture* thisTex){Sprite::setPointerToTexture(thisTex);}

LTexture* Player::getPointerToTexture(){return Sprite::getPointerToTexture();}

void Player::handleEvent(Event& thisEvent)
{
	   
    float mVelX = Dot::getVelX();
    float mVelY = Dot::getVelY();
    
    //if first or single player
    if(m_player_num == 1 || m_player_num == 0)
    {
		//if equipped weapon is not pointing to nullptr
		if(equippedPlayerWeapon != nullptr)
		{
			switch(thisEvent)
			{
				case Event::SPACE:{ equippedPlayerWeapon->setWeaponState(Weapon::WeaponState::STAND_WITH_HANDLER_ACTIVATED); break;}
				case Event::SPACE_REPEAT:{ equippedPlayerWeapon->setWeaponState(Weapon::WeaponState::STAND_WITH_HANDLER_NO_ACTION); break;}
				case Event::SPACE_RELEASE:{ equippedPlayerWeapon->setWeaponState(Weapon::WeaponState::STAND_WITH_HANDLER_NO_ACTION); break;}
				default:{  break;}
			}
		}
		
		switch(thisEvent)
		{
			case Event::UP_ARROW:{ mVelY -= DOT_VEL; Sprite::setSpriteState(Sprite::State::WALK); break;}
			case Event::DOWN_ARROW:{ mVelY += DOT_VEL; Sprite::setSpriteState(Sprite::State::WALK); break;}
			case Event::LEFT_ARROW:{ mVelX -= DOT_VEL; Sprite::setSpriteState(Sprite::State::WALK); break;}
			case Event::RIGHT_ARROW:{ mVelX += DOT_VEL; Sprite::setSpriteState(Sprite::State::WALK); break;}
			
			//if repeating, keep at same velocity
			case Event::UP_ARROW_REPEAT:{ Sprite::setSpriteState(Sprite::State::WALK); break;}
			case Event::DOWN_ARROW_REPEAT:{ Sprite::setSpriteState(Sprite::State::WALK); break;}
			case Event::LEFT_ARROW_REPEAT:{ Sprite::setSpriteState(Sprite::State::WALK); break;}
			case Event::RIGHT_ARROW_REPEAT:{ Sprite::setSpriteState(Sprite::State::WALK); break;}
			
			//if released, stop
			case Event::UP_ARROW_RELEASE:{ mVelY = 0; Sprite::setSpriteState(Sprite::State::STAND); break;}
			case Event::DOWN_ARROW_RELEASE:{  mVelY = 0; Sprite::setSpriteState(Sprite::State::STAND); break;}
			case Event::LEFT_ARROW_RELEASE:{ mVelX = 0; Sprite::setSpriteState(Sprite::State::STAND); break;}
			case Event::RIGHT_ARROW_RELEASE:{ mVelX = 0; Sprite::setSpriteState(Sprite::State::STAND); break;}
			
			
			case Event::NONE:{ Sprite::setSpriteState(Sprite::State::STAND); break;}
			
			default:{ mVelX = 0; mVelY = 0; Sprite::setSpriteState(Sprite::State::STAND); break;}
		}
		
		
	}
	
	//if second player
	else if(m_player_num == 2)
	{
		float speed_factor = 0.8;
		
		switch(thisEvent)
		{
			case Event::JOYSTICK_0_HAT_UP:{ mVelY -= speed_factor*DOT_VEL; Sprite::setSpriteState(Sprite::State::WALK); break;}
			case Event::JOYSTICK_0_HAT_DOWN:{ mVelY += speed_factor*DOT_VEL; Sprite::setSpriteState(Sprite::State::WALK); break;}
			case Event::JOYSTICK_0_HAT_LEFT:{ mVelX -= speed_factor*DOT_VEL; Sprite::setSpriteState(Sprite::State::WALK); break;}
			case Event::JOYSTICK_0_HAT_RIGHT:{ mVelX += speed_factor*DOT_VEL; Sprite::setSpriteState(Sprite::State::WALK); break;}
			case Event::JOYSTICK_0_HAT_UP_RIGHT:{ mVelX += 0.5*speed_factor*DOT_VEL; mVelY -= 0.5*speed_factor*DOT_VEL; Sprite::setSpriteState(Sprite::State::WALK); break;}
			case Event::JOYSTICK_0_HAT_UP_LEFT:{ mVelX -= 0.5*speed_factor*DOT_VEL; mVelY -= 0.5*speed_factor*DOT_VEL; Sprite::setSpriteState(Sprite::State::WALK); break;}
			case Event::JOYSTICK_0_HAT_DOWN_RIGHT:{ mVelX += 0.5*speed_factor*DOT_VEL; mVelY += 0.5*speed_factor*DOT_VEL; Sprite::setSpriteState(Sprite::State::WALK); break;}
			case Event::JOYSTICK_0_HAT_DOWN_LEFT:{ mVelX -= 0.5*speed_factor*DOT_VEL; mVelY += 0.5*speed_factor*DOT_VEL; Sprite::setSpriteState(Sprite::State::WALK); break;}
			
			case Event::JOYSTICK_0_BUTTON_DOWN_PRESSED:{ std::cout << "button up pressed!\n"; equippedPlayerWeapon->setWeaponState(Weapon::WeaponState::STAND_WITH_HANDLER_ACTIVATED); break;}
			case Event::JOYSTICK_0_BUTTON_DOWN_RELEASED:{ equippedPlayerWeapon->setWeaponState(Weapon::WeaponState::STAND_WITH_HANDLER_NO_ACTION); break;}
			
			case Event::JOYSTICK_0_BUTTON_UP_PRESSED:{ std::cout << "button up pressed!\n"; equippedPlayerWeapon->setWeaponState(Weapon::WeaponState::STAND_WITH_HANDLER_ACTIVATED); break;}
			case Event::JOYSTICK_0_BUTTON_UP_RELEASED:{ equippedPlayerWeapon->setWeaponState(Weapon::WeaponState::STAND_WITH_HANDLER_NO_ACTION); break;}
			
			//if released, stop
			case Event::JOYSTICK_0_HAT_NULL:{ mVelX = 0; mVelY = 0; Sprite::setSpriteState(Sprite::State::STAND); break;}
			
			case Event::NONE:{ Sprite::setSpriteState(Sprite::State::STAND); break;}
			
			default:{ mVelX = 0; mVelY = 0; Sprite::setSpriteState(Sprite::State::STAND); break;}
		}
	}
    
    
    Dot::setVelX(mVelX);
    Dot::setVelY(mVelY);
}

void Player::handleEvent(SDL_Joystick* joystick_controller)
{
	
	float mVelX = Dot::getVelX();
    float mVelY = Dot::getVelY();
    
    int hat_dir = SDL_HAT_CENTERED;
    
    SDL_JoystickGetHat(joystick_controller,hat_dir);
	std::cout << "hat:" << hat_dir << std::endl;
	
	switch(hat_dir)
	{
		case SDL_HAT_CENTERED:{ mVelX = 0; mVelY = 0; break;}
		case SDL_HAT_UP:{ mVelY -= DOT_VEL; break;}
		case SDL_HAT_RIGHT:{mVelX += DOT_VEL; break;}
		case SDL_HAT_DOWN:{ mVelY += DOT_VEL; break;}
		case SDL_HAT_LEFT:{mVelX -= DOT_VEL; break;}
		case SDL_HAT_RIGHTUP:{mVelY -= DOT_VEL; mVelX += DOT_VEL; break;}
		case SDL_HAT_RIGHTDOWN:{ mVelX -= DOT_VEL; mVelX += DOT_VEL; break;}
		case SDL_HAT_LEFTUP:{mVelY -= DOT_VEL; mVelX -= DOT_VEL; break;}
		case SDL_HAT_LEFTDOWN:{mVelY += DOT_VEL; mVelX -= DOT_VEL; break;}
	}
    
    
	Dot::setVelX(mVelX);
    Dot::setVelY(mVelY);
}


void Player::move(float& timeStep){Sprite::move(timeStep); }

bool Player::moveOnTiles(float& timeStep, std::vector<DungeonTile*> &dungeonTiles)
{
	
    //if sprite is not moving on tiles and is colliding with wall
    if(!Sprite::moveOnTiles(timeStep, dungeonTiles))
    {
        Player::setPlayerState(Player::PlayerState::COLLIDING_CONTRA_WALL);
        return false;
    }
    else{return true;}
}

DungeonTile::TileType Player::moveOnTiles_TileType(float& timeStep, std::vector<DungeonTile*> &dungeonTiles)
{
    //return tile type dot touches
    DungeonTile::TileType tileType =  Sprite::moveOnTiles_TileType(timeStep,dungeonTiles);
    
    if(tileType == DungeonTile::TileType::TOP_LEFT || tileType == DungeonTile::TileType::LEFT 
        || tileType == DungeonTile::TileType::BOTTOM_LEFT || tileType == DungeonTile::TileType::TOP || 
        tileType == DungeonTile::TileType::BOTTOM ||
        tileType == DungeonTile::TileType::TOP_RIGHT || tileType == DungeonTile::TileType::RIGHT || 
        tileType == DungeonTile::TileType::BOTTOM_RIGHT 
        || tileType == DungeonTile::TileType::INVISIBLE_WALL)
    {
        Player::setPlayerState(Player::PlayerState::COLLIDING_CONTRA_WALL);
    }
    
    if(tileType == DungeonTile::TileType::CENTER)
    {
		Player::setPlayerState(Player::PlayerState::FALLING_IN_HOLE);
	}
    
    return tileType;
}


void Player::render(SDL_Rect& camera, SDL_Renderer* gRenderer, SDL_Rect* clip)
{
    
    if(Player::getPlayerState() != PlayerState::FALLING_IN_HOLE){Sprite::render(camera,gRenderer,clip); }
    else{Sprite::render(camera,gRenderer,&clipPlayer);}
    
    
    //render collision box of player
    //Player::renderPlayerCollisionBox(camera,gRenderer);
    
    Player::renderEquippedWeapon(camera,gRenderer);
}


void Player::renderPlayerCollisionBox(SDL_Rect& camera,SDL_Renderer* gRenderer)
{
	SDL_SetRenderDrawColor(gRenderer,
                           200,
                           0,
                           0,
                           50);
    
    SDL_Rect pBox = {  Player::getCollisionBox().x - camera.x ,
                         Player::getCollisionBox().y - camera.y ,
                        Player::getCollisionBox().w,
                        Player::getCollisionBox().h };
    SDL_RenderDrawRect(gRenderer,&pBox);
}


//Health

void Player::setHealth(std::int16_t& thisHP){health = thisHP;}
std::int16_t Player::getHealth(){return health;}
std::int16_t& Player::getHealthAddress(){return health;}
void Player::incrementHealth(std::int16_t& amount){health += amount;}
void Player::decrementHealth(std::int16_t& amount){health -= amount;}

//Weapon

void Player::renderEquippedWeapon(SDL_Rect& camera, SDL_Renderer* gRenderer)
{
    if(equippedPlayerWeapon != nullptr)
    {
        equippedPlayerWeapon->render(camera, gRenderer, nullptr);
    }
}

void Player::logic(float& timeStep)
{
	//listener change orientation logic
	
	
	//collsion logic
	Player::reactToCollision(timeStep);
	
    switch(Player::getPlayerState())
    {
        case Player::PlayerState::COLLIDING_CONTRA_WALL:{Player::runLogicState_CollideWithWall(timeStep); break;}
        case Player::PlayerState::NORMAL:{Player::runLogicState_Normal(timeStep); break;}
        case Player::PlayerState::PUSHED_BACKED_BY_ENEMY:{Player::runLogicState_PushedBack(timeStep); break;}
        case Player::PlayerState::FALLING_IN_HOLE:{Player::decrementHealth(cockroachDamage); break;}
    }
    
    //increment loop count
    Player::incrementLoopCount();
    if(Player::getLoopCount() > 20){Player::resetLoopCount();}
}

void Player::runLogicState_CollideWithWall(float& timeStep)
{
    float zeroVelocity = 0;
    
    Player::moveBack(timeStep);
    Player::setVelX(zeroVelocity); Player::setVelY(zeroVelocity);
    //set player state back to normal
    Player::setPlayerState(PlayerState::NORMAL);
}

void Player::runLogicState_Normal(float& timeStep)
{
    //if equipped weapon is not pointing to nullptr
    if(equippedPlayerWeapon != nullptr)
    {
        Player::runEquippedWeaponLogic(timeStep);
    }
}

void Player::runLogicState_PushedBack(float& timeStep)
{
    //if count of times player has been pushed back is less than number of times 
    //player has to be pushed back
    if( Player::getCountPushBack() < Player::getNumTimesPushBackPlayer())
    {
        Player::pushBackPlayer(timeStep,onePushBack); //get pushed back
        Player::incrementCountPushBack();
    }
    //else set player state back to normal and reset count
    else
    {
        Player::setPlayerState(PlayerState::NORMAL); 
        Player::resetCountPushBack();
    }
}

void Player::runEquippedWeaponLogic(float& timeStep)
{
    bool weaponActivated = false;
    
    //if weapon is not in state where weapon is activated
    if(equippedPlayerWeapon->getWeaponState() != Weapon::WeaponState::STAND_WITH_HANDLER_ACTIVATED)
    {
        //set weapon state based on sprite state
        switch(Player::getSpriteState())
        {
            case Sprite::State::STAND:{ equippedPlayerWeapon->setWeaponState(Weapon::WeaponState::STAND_WITH_HANDLER_NO_ACTION); break;}
            case Sprite::State::WALK:{ equippedPlayerWeapon->setWeaponState(Weapon::WeaponState::MOVING_WITH_HANDLER_NO_ACTION); break;}
            default:{ break;}
        }
        
        weaponActivated = true;
    }
    
    
    //set direction weapon is facing to direction player is facing
    switch(Player::getFaceDirection())
    {
        case Player::FaceDirection::NORTH:
        {
            equippedPlayerWeapon->faceWeaponNorth(); break;
        }
        case Player::FaceDirection::NORTHEAST:
        {
            equippedPlayerWeapon->faceWeaponNorthEast(); break;
        }
        case Player::FaceDirection::EAST:
        {
            equippedPlayerWeapon->faceWeaponEast(); break;
        }
        case Player::FaceDirection::SOUTHEAST:
        {
            equippedPlayerWeapon->faceWeaponSouthEast(); break;
        }
        case Player::FaceDirection::SOUTH:
        {
            equippedPlayerWeapon->faceWeaponSouth(); break;
        }
        case Player::FaceDirection::SOUTHWEST:
        {
            equippedPlayerWeapon->faceWeaponSouthWest(); break;
        }
        case Player::FaceDirection::WEST:
        {
            equippedPlayerWeapon->faceWeaponWest(); break;
        }
        case Player::FaceDirection::NORTHWEST:
        {
            equippedPlayerWeapon->faceWeaponNorthWest(); break;
        }
    }
    
    equippedPlayerWeapon->logic(timeStep);
}

void Player::reactToCollision(float& timeStep)
{
    //reset count push back
    //count_PushBackPlayer = 0;
    switch(Player::getCollisionType())
    {
        
        case CollisionType::NONE:{ break;} // Do Nothing
        
        case CollisionType::HIT_BY_COCKROACH:
        {
			//std::cout << "Collision with cockroach! \n" << std::endl;
            Player::decrementHealth(cockroachDamage); //decrease health
            
            //put in state of push back
            Player::setPlayerState(Player::PlayerState::PUSHED_BACKED_BY_ENEMY);
            std::int8_t numTimes = cockroach_PushBackHero / onePushBack; 
            Player::setNumTimesPushBackPlayer(numTimes);
            
            break;
        }
        case CollisionType::HIT_BY_ZOMBIE:
        {
			//std::cout << "Collision with cockroach! \n" << std::endl;
            Player::decrementHealth(greedZombieDamage); //decrease health
            
            //put in state of push back
            Player::setPlayerState(Player::PlayerState::PUSHED_BACKED_BY_ENEMY);
            std::int8_t numTimes = cockroach_PushBackHero / onePushBack; 
            Player::setNumTimesPushBackPlayer(numTimes);
            
            break;
        }
        case CollisionType::COLLIDING_WITH_HOLE:
        {
            Player::decrementHealth(cockroachDamage);
            Player::setPlayerState( PlayerState::FALLING_IN_HOLE);
            break;
        }
        case CollisionType::HIT_BY_BULLET:
        {
			Player::decrementHealth(greedZombieDamage); //decrease health
            
            //put in state of push back
            Player::setPlayerState(Player::PlayerState::PUSHED_BACKED_BY_ENEMY);
            std::int8_t numTimes = cockroach_PushBackHero / onePushBack; 
            Player::setNumTimesPushBackPlayer(numTimes);
            break;
		}
		case CollisionType::HIT_BY_SWORD:
        {
			Player::decrementHealth(greedZombieDamage); //decrease health
            
            //put in state of push back
            Player::setPlayerState(Player::PlayerState::PUSHED_BACKED_BY_ENEMY);
            std::int8_t numTimes = cockroach_PushBackHero / onePushBack; 
            Player::setNumTimesPushBackPlayer(numTimes);
            break;
		}
        
       
        default:{break;}
    }
    
    if(equippedPlayerWeapon != nullptr)
    {
		if(equippedPlayerWeapon->getCollisionObjectPtr())
		{
			if(equippedPlayerWeapon->getCollisionObjectPtr()->typeOfCollision == CollisionType::HIT_BY_COCKROACH)
			{
				if(equippedPlayerWeapon->getWeaponState() == Weapon::WeaponState::STAND_WITH_HANDLER_NO_ACTION
				 || equippedPlayerWeapon->getWeaponState() == Weapon::WeaponState::MOVING_WITH_HANDLER_NO_ACTION)
				 {
					Player::decrementHealth(cockroachDamage); //decrease health

					//put in state of push back
					Player::setPlayerState(Player::PlayerState::PUSHED_BACKED_BY_ENEMY);
					std::int8_t numTimes = cockroach_PushBackHero / onePushBack; 
					Player::setNumTimesPushBackPlayer(numTimes);
				 }
			}
			
		}
		
	}
    
    Player::resetCollisionType();
}

void Player::pushBackPlayer(float& timeStep,std::int16_t& pushBackDist)
{
    float velX = Player::getVelX();
    float velY = Player::getVelY();
    
    float newPosX, newPosY;
    //if going right, push left
    if(velX > 0){newPosX = Player::getPosX() - pushBackDist - (velX * timeStep);}
    //else if going left, push right
    else if(velX < 0){newPosX = Player::getPosX() + pushBackDist - (velX * timeStep);}
    else if(velX == 0){newPosX = Player::getPosX() + pushBackDist;}
    
    Player::setPosX(newPosX);
    
    //if going down, push up
    if(velY > 0){newPosY = Player::getPosY() - pushBackDist - (velY * timeStep);}
    //else if going up, push down
    else if(velY < 0){newPosY = Player::getPosY() + pushBackDist - (velY * timeStep);}
    else if(velY == 0){newPosY = Player::getPosY() + pushBackDist; }

    Player::setPosY(newPosY);
}

void Player::setNumTimesPushBackPlayer(std::int8_t& thisNum){numTimes_pushBackPlayer = thisNum;}
std::int8_t Player::getNumTimesPushBackPlayer(){return numTimes_pushBackPlayer;}
void Player::resetNumTimesPushBackPlayer(){numTimes_pushBackPlayer = 0;}

void Player::incrementCountPushBack(){countPushBack += 1;}
std::int8_t Player::getCountPushBack(){return countPushBack;}
void Player::resetCountPushBack(){countPushBack = 0;}

void Player::incrementLoopCount(){loopCount++;}
std::int8_t Player::getLoopCount(){return loopCount;}
void Player::resetLoopCount(){loopCount = 0;}

void Player::sound(AudioRenderer* gAudioRenderer)
{
	Player::MoveListener(gAudioRenderer);
}

void Player::MoveListener(AudioRenderer* gAudioRenderer)
{
	Player::SetListenerDirection();
    
	//set velocity based on direciton of movement
	alListener3f(AL_VELOCITY, Player::getVelX(), 0.0f, Player::getVelY());
	
	//set listener position
	alListener3f(AL_POSITION,0, 0, 0);
}

void Player::SetListenerDirection()
{
	switch(Player::getFaceDirection())
    {
        case Player::FaceDirection::NORTH:
        {
            Player::FaceListenerNorth(); break;
        }
        case Player::FaceDirection::NORTHEAST:
        {
            Player::FaceListenerNorthEast(); break;
        }
        case Player::FaceDirection::EAST:
        {
            Player::FaceListenerEast(); break;
        }
        case Player::FaceDirection::SOUTHEAST:
        {
            Player::FaceListenerSouthEast(); break;
        }
        case Player::FaceDirection::SOUTH:
        {
            Player::FaceListenerSouth(); break;
        }
        case Player::FaceDirection::SOUTHWEST:
        {
            Player::FaceListenerSouthWest(); break;
        }
        case Player::FaceDirection::WEST:
        {
            Player::FaceListenerWest(); break;
        }
        case Player::FaceDirection::NORTHWEST:
        {
            Player::FaceListenerNorthWest(); break;
        }
    }
}

void Player::FaceListenerNorth()
{
	//set facing north
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_X] = 0.0f; //forward vector x value
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_Y] = 0.0f; //forward vector y value
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_Z] = -1.0f; //forward vector z value
	
	
	//set current listener orientation
	alListenerfv(AL_ORIENTATION, listener_orientation_vector.data());
}

void Player::FaceListenerNorthEast()
{
	//set facing north east
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_X] = 1.0f; //forward vector x value
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_Y] = 0.0f; //forward vector y value
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_Z] = -1.0f; //forward vector z value
	
	//set current listener orientation
	alListenerfv(AL_ORIENTATION, listener_orientation_vector.data());
}

void Player::FaceListenerEast()
{
	//set facing east
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_X] = 1.0f; //forward vector x value
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_Y] = 0.0f; //forward vector y value
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_Z] = 0.0f; //forward vector z value
	
	//set current listener orientation
	alListenerfv(AL_ORIENTATION, listener_orientation_vector.data());
}

void Player::FaceListenerSouthEast()
{
	//set facing south east
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_X] = 1.0f; //forward vector x value
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_Y] = 0.0f; //forward vector y value
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_Z] = 1.0f; //forward vector z value
	
	//set current listener orientation
	alListenerfv(AL_ORIENTATION, listener_orientation_vector.data());
}

void Player::FaceListenerSouth()
{
	//set facing south
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_X] = 0.0f; //forward vector x value
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_Y] = 0.0f; //forward vector y value
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_Z] = 1.0f; //forward vector z value
	
	//set current listener orientation
	alListenerfv(AL_ORIENTATION, listener_orientation_vector.data());
}

void Player::FaceListenerSouthWest()
{
	//set facing south
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_X] = -1.0f; //forward vector x value
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_Y] = 0.0f; //forward vector y value
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_Z] = 1.0f; //forward vector z value
	
	//set current listener orientation
	alListenerfv(AL_ORIENTATION, listener_orientation_vector.data());
}

void Player::FaceListenerWest()
{
	//set facing south
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_X] = -1.0f; //forward vector x value
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_Y] = 0.0f; //forward vector y value
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_Z] = 0.0f; //forward vector z value
	
	//set current listener orientation
	alListenerfv(AL_ORIENTATION, listener_orientation_vector.data());
}

void Player::FaceListenerNorthWest()
{
	//set facing south
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_X] = -1.0f; //forward vector x value
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_Y] = 0.0f; //forward vector y value
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_Z] = -1.0f; //forward vector z value
	
	//set current listener orientation
	alListenerfv(AL_ORIENTATION, listener_orientation_vector.data());
}

int Player::getPlayerHeight(){return Sprite::getHeight();}

void Player::SetPlayerNumber(int num){m_player_num = num;}

int Player::GetPlayerNumber(){return m_player_num;}

Weapon* Player::getPointerToEquippedPlayerWeapon(){return equippedPlayerWeapon;}
