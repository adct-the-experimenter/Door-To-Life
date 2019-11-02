#include "enemy.h"


//constructor
Enemy::Enemy(int x,int y,int width,int height) : Sprite(x,y,width,height)
{
    std::int16_t initialHealth = 50;
    Enemy::setHealth(initialHealth);
    
    Enemy::resetLoopCount();
    
    Enemy::resetCountPushBack();
    
    //std::cout << "\n Enemy constructor called! \n";
}

Enemy::~Enemy()
{
    //std::cout << "\n Enemy destructor called! \n";
}

void Enemy::setSpeed(float& speed){Sprite::setSpeed(speed);}

void Enemy::setPosX(float& x){Sprite::setPosX(x);}

void Enemy::setPosY(float& y){Sprite::setPosY(y);}

void Enemy::setVelX(float& dx){Sprite::setVelX(dx);}

void Enemy::setVelY(float& dy){Sprite::setVelY(dy);}

bool Enemy::loadMedia(LTexture* thisTex, std::string path,SDL_Renderer* gRenderer)
{
    return Sprite::loadMedia(thisTex,path,gRenderer);
}
void Enemy::setPointerToTexture(LTexture* thisTex){Sprite::setPointerToTexture(thisTex);}

void Enemy::setSpriteClips(std::vector <SDL_Rect> *this_clips){Sprite::setSpriteClips(this_clips);}

std::vector <SDL_Rect> *Enemy::getSpriteClips(){return Sprite::getSpriteClips();}

void Enemy::handleEvent(Event& thisEvent){Sprite::handleEvent(thisEvent);}

void Enemy::handleEvent_EnemyAI(RNGType& rngSeed){}

void Enemy::setPlace(std::int16_t& screenWidth, std::int16_t& screenHeight)
{
    Sprite::setPlace(screenWidth,screenHeight);
}

void Enemy::setCamera( SDL_Rect& camera  ) //set camera relative to dot and intialize screen and level dimensions
{
	Sprite::setCamera(camera);
}

void Enemy::move(float& timeStep){Sprite::move(timeStep);}

bool Enemy::moveOnTiles(float& timeStep, 
                        std::vector<DungeonTile*> &dungeonTiles)
{
    return Sprite::moveOnTiles(timeStep, dungeonTiles);
}

DungeonTile::TileType Enemy::moveOnTiles_TileType(float& timeStep, std::vector<DungeonTile*> &dungeonTiles)
{
    //return tile type dot touches
    DungeonTile::TileType tileType =  Sprite::moveOnTiles_TileType(timeStep,dungeonTiles);
    
    //if tile type is one of wall tiles, tile that has door 
    if(tileType == DungeonTile::TileType::TOP_LEFT || tileType == DungeonTile::TileType::LEFT 
        || tileType == DungeonTile::TileType::BOTTOM_LEFT || tileType == DungeonTile::TileType::TOP || 
        tileType == DungeonTile::TileType::CENTER || tileType == DungeonTile::TileType::BOTTOM ||
        tileType == DungeonTile::TileType::TOP_RIGHT || tileType == DungeonTile::TileType::RIGHT || 
        tileType == DungeonTile::TileType::BOTTOM_RIGHT ||
        
        //door
        tileType == DungeonTile::TileType::DOOR ||
        // center hole
        tileType == DungeonTile::TileType::CENTER
        )
    {
        Enemy::setEnemyState(Enemy::EnemyState::COLLIDE_WITH_WALL);
    }
    else{Enemy::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER); }
    
    return tileType;
}

void Enemy::moveBack(float& timeStep){Sprite::moveBack(timeStep);}

//Frame animation 
void Enemy::setDirection(){Sprite::setDirection();}
void Enemy::setMoveClip(){Sprite::setMoveClip();}
//function to determine which frame to use
void Enemy::setFrame(){Sprite::setFrame();}

void Enemy::incrementFrameCount(){Sprite::incrementFrameCount();}
std::int8_t Enemy::getFrameCount(){return Sprite::getFrameCount();}
void Enemy::resetFrameCount(){Sprite::resetFrameCount();}

void Enemy::setFrameOffset(std::int8_t& thisOffset){Sprite::setFrameOffset(thisOffset);}
std::int8_t Enemy::getFrameOffset(){return Sprite::getFrameOffset();}

void Enemy::setNumberOfAnimationFrames(std::int8_t& numFrames){Sprite::setNumberOfAnimationFrames(numFrames);}
std::int8_t Enemy::getNumberOfFramesOfAnimation(){return Sprite::getNumberOfFramesOfAnimation();}

void Enemy::setClipToShow(SDL_Rect* clip){ Sprite::setClipToShow(clip);}
SDL_Rect* Enemy::getClipToShow(){return Sprite::getClipToShow();}

void Enemy::faceNorth(){Sprite::faceNorth();}

void Enemy::faceSouth(){Sprite::faceSouth();}

void Enemy::faceWest(){Sprite::faceWest();}

void Enemy::faceEast(){Sprite::faceEast();}

void Enemy::setSpriteState(Sprite::State state){Sprite::setSpriteState(state);}
Sprite::State Enemy::getSpriteState(){return Sprite::getSpriteState();}

LTexture* Enemy::getPointerToTexture(){return Sprite::getPointerToTexture();}

void Enemy::render(SDL_Rect& camera, SDL_Renderer* gRenderer, SDL_Rect* clip)
{
   Sprite::render(camera,gRenderer,clip);
}

float Enemy::getPosX(){return Sprite::getPosX();}

float Enemy::getPosY(){return Sprite::getPosY();}

int Enemy::getHeight(){return Sprite::getHeight();}

int Enemy::getWidth(){return Sprite::getWidth();}

float Enemy::getVelX(){return Sprite::getVelX();}

float Enemy::getVelY(){return Sprite::getVelY();}

float Enemy::getSpeed(){return Sprite::getSpeed();}

void Enemy::placeChar(int x, int y){Sprite::placeChar(x,y);}

void Enemy::setCollisionBox(SDL_Rect& box){Sprite::setCollisionBox(box);}

SDL_Rect& Enemy::getCollisionBox(){return Sprite::getCollisionBox();}

SDL_Rect& Enemy::getSpaceBox(){return Sprite::getSpaceBox();}

//Collision object Functions
void Enemy::setOwnerTypeOfCollisionObject(CollisionBoxOwnerType& oType)
{
    Sprite::setOwnerTypeOfCollisionObject(oType);
}

CollisionType Enemy::getCollisionType(){return Sprite::getCollisionType();}
void Enemy::resetCollisionType(){Sprite::resetCollisionType();}
CollisionObject* Enemy::getCollisionObjectPtr(){return Sprite::getCollisionObjectPtr();}

void Enemy::pushBackEnemy(float& timeStep,std::int16_t& pushBackDist,CollisionDirection dir)
{
	float newPosX,newPosY;
	float velX = Enemy::getVelX();
	float velY = Enemy::getVelY();
	
	switch(dir)
	{
		//move up
		case CollisionDirection::NORTH:
		{
			newPosX = Enemy::getPosX(); 
			newPosY = Enemy::getPosY() - pushBackDist - (velY * timeStep); 
			break;
		}
		//move eight and up
		case CollisionDirection::NORTHEAST:
		{
			newPosX = Enemy::getPosX() + pushBackDist - (velX * timeStep); 
			newPosY = Enemy::getPosY() - pushBackDist - (velY * timeStep); 
			break;
		}
		//move right
		case CollisionDirection::EAST:
		{
			newPosX = Enemy::getPosX() + pushBackDist - (velX * timeStep); 
			newPosY = Enemy::getPosY(); 
			break;
		}
		// move right and down
		case CollisionDirection::SOUTHEAST:
		{
			newPosX = Enemy::getPosX() + pushBackDist - (velX * timeStep); 
			newPosY = Enemy::getPosY() + pushBackDist - (velY * timeStep); 
			break;
		}
		//move down 
		case CollisionDirection::SOUTH:
		{
			newPosX = Enemy::getPosX(); 
			newPosY = Enemy::getPosY() + pushBackDist - (velY * timeStep); 
			break;
		}
		//move left and down
		case CollisionDirection::SOUTHWEST:
		{
			newPosX = Enemy::getPosX() - pushBackDist - (velX * timeStep);
			newPosY = Enemy::getPosY() + pushBackDist - (velY * timeStep); 
			break;
		}
		//move left
		case CollisionDirection::WEST:
		{
			newPosX = Enemy::getPosX() - pushBackDist - (velX * timeStep); 
			newPosY = Enemy::getPosY();
			break;
		}
		//move left and up
		case CollisionDirection::NORTHWEST:
		{
			newPosX = Enemy::getPosX() - pushBackDist - (velX * timeStep); 
			newPosY = Enemy::getPosY() - pushBackDist - (velY * timeStep); 
			break;
		}
		//push back in opposite direction of velocity
		case CollisionDirection::WALL:
		{
			//if x velocity is positive - going right, push left
			if(velX > 0){newPosX = Enemy::getPosX() - pushBackDist - (velX * timeStep);}
			//else if x velocity is negative - going left, push right
			else if(velX < 0){newPosX = Enemy::getPosX() + pushBackDist - (velX * timeStep);}
			else if(velX == 0){newPosX = Enemy::getPosX();}
			
			//if y velocity is positive - going down, push up 
			if(velY > 0){newPosY = Enemy::getPosY() - pushBackDist - (velY * timeStep);}
			//else if y velocity is negative - going up, push down
			else if(velY < 0){newPosY = Enemy::getPosY() + pushBackDist - (velY * timeStep);}
			else if(velY == 0){newPosY = Enemy::getPosY();}
    
			break;
		}
		default:{break;}
	}

    Enemy::setPosX(newPosX);
    Enemy::setPosY(newPosY);
}


void Enemy::setNumTimesEnemyPushBack(std::int8_t& num){numTimes_pushBackEnemy = num;}
std::int8_t Enemy::getNumTimesEnemyPushBack(){return numTimes_pushBackEnemy;}
std::int8_t Enemy::getCountPushBack(){return countPushBackEnemy;}
void Enemy::incrementCountPushBack(){countPushBackEnemy += 1;}
void Enemy::resetCountPushBack(){countPushBackEnemy = 0;}
void Enemy::setPushBackDirection(CollisionDirection dir){pushBackDirection = dir;}
CollisionDirection Enemy::getPushBackDirection(){return pushBackDirection;}
void Enemy::resetPushBackDirection(){pushBackDirection = CollisionDirection::NONE;}
void Enemy::resetPushBackVariables(){countPushBackEnemy = 0; numTimes_pushBackEnemy = 0; pushBackDirection = CollisionDirection::NONE;}
//Health

void Enemy::setHealth(std::int16_t& thisHP){health = thisHP;}
std::int16_t Enemy::getHealth(){return health;}
std::int16_t& Enemy::getHealthAddress(){return health;}
void Enemy::incrementHealth(std::int16_t& amount){health += amount;}
void Enemy::decrementHealth(std::int16_t& amount){health -= amount;}

void Enemy::setEnemyState(Enemy::EnemyState state){enemy_state = state;}
Enemy::EnemyState Enemy::getEnemyState(){return enemy_state;}

void Enemy::setRandNumber(std::int8_t& thisNum){randNumber = thisNum;}
std::int8_t Enemy::getRandNumber(){return randNumber;}

void Enemy::incrementLoopCount(){loopCount++;}
std::int8_t Enemy::getLoopCount(){return loopCount;}
void Enemy::resetLoopCount(){loopCount = 0;}

//functions for movement
void Enemy::moveUp(float& timeStep)
{
    //set y velocity negative
    //mVelY -= DOT_VEL;
    float newVelY = Enemy::getVelY() - Enemy::getSpeed();
    Enemy::setVelY(newVelY);
    float newVelX = 0;
    Enemy::setVelX(newVelX);
    //Move the dot up or down
    //float newPosY = Enemy::getPosY() + newVelY * timeStep;
    //Enemy::setPosY(newPosY);
    Sprite::move(timeStep);
}

void Enemy::moveDown(float& timeStep)
{
    //set y velocity positive
    //mVelY += DOT_VEL;
    float newVelY = Enemy::getVelY() + Enemy::getSpeed();
    Enemy::setVelY(newVelY);
    float newVelX = 0;
    Enemy::setVelX(newVelX);
    //Move the dot up or down
    //float newPosY = Enemy::getPosY() + newVelY * timeStep;
    //Enemy::setPosY(newPosY);
    Sprite::move(timeStep);
}

void Enemy::moveLeft(float& timeStep)
{
    //set x velocity negative
    //mVelX -= DOT_VEL;
    float newVelX = Enemy::getVelX() - Enemy::getSpeed();
    Enemy::setVelX(newVelX);
    float newVelY = 0;
    Enemy::setVelY(newVelY);
    //Move the dot left or right
    //float newPosX = Enemy::getPosX() + newVelX * timeStep;
    //Enemy::setPosX(newPosX);
    Sprite::move(timeStep);
}

void Enemy::moveRight(float& timeStep)
{
    //set x velocity positive
    //mVelX += DOT_VEL;
    float newVelX = Enemy::getVelX() + Enemy::getSpeed();
    Enemy::setVelX(newVelX);
    //Move the dot left or right
    //float newPosX = Enemy::getPosX() - Dot::xClipPosOffset + newVelX * timeStep;
    //Enemy::setPosX(newPosX);
    
    Sprite::move(timeStep);
}

void Enemy::pause(float& timeStep){}

void Enemy::setFaceDirection(Sprite::FaceDirection dir){Sprite::setFaceDirection(dir);}
Sprite::FaceDirection Enemy::getFaceDirection(){return Sprite::getFaceDirection();}

void Enemy::setEnemyView(Enemy::EnemyViewOption option)
{
    enemy_view = option;
    
    //add collision object of view to collision handler
    switch(option)
    {
        case Enemy::EnemyViewOption::NONE:{break;}
        case Enemy::EnemyViewOption::LINE_OF_SIGHT:{enemy_lineofsight.addLineOfSightToCollisionHandler(); break;}
        case Enemy::EnemyViewOption::FIELD_OF_VIEW:{ break;}
    }
}

void Enemy::setLineOfSightDimensions(std::int16_t& w, std::int16_t& h)
{
    enemy_lineofsight.setLineWidth(w);
    enemy_lineofsight.setLineHeight(h);
}

void Enemy::setLineOfSightToEnemyBox()
{
    SDL_Rect* enemyBoxPtr = Enemy::getCollisionObjectPtr()->ptrToCollisionBox;
    enemy_lineofsight.attachLineOfSightToEnemyBox(enemyBoxPtr);
}

void Enemy::checkViewForPlayer()
{
    bool playerSeen = false;
    
    switch(enemy_view)
    {
        case Enemy::EnemyViewOption::NONE:{ break;}
        case Enemy::EnemyViewOption::LINE_OF_SIGHT:
        {
            //update location of line of sight based on location
            //std::int16_t x = Enemy::getCollisionBox().x /*+ Enemy::getCollisionBox().w*/;
            //std::int16_t y = Enemy::getCollisionBox().y /*+ Enemy::getCollisionBox().h */;
            //enemy_lineofsight.setLineLocation(x,y);
            
            enemy_lineofsight.moveLineOfSightWithEnemy();
            
            //set direction of line of sight based on enemy face direction
            switch(Enemy::getFaceDirection())
            {
                case Sprite::FaceDirection::NORTH:
                {
                    enemy_lineofsight.faceUp(); 
                    break;
                }
                case Sprite::FaceDirection::NORTHEAST:
                {
                    enemy_lineofsight.faceUpRight(); 
                    break;
                }
                case Sprite::FaceDirection::EAST:
                {
                    enemy_lineofsight.faceRight();  
                    break;
                }
                case Sprite::FaceDirection::SOUTHEAST:
                {
                    enemy_lineofsight.faceDownRight(); 
                    break;
                }
                case Sprite::FaceDirection::SOUTH:
                {
                    enemy_lineofsight.faceDown(); 
                    break;
                }
                case Sprite::FaceDirection::SOUTHWEST:
                {
                    enemy_lineofsight.faceDownLeft();  
                    break;
                }
                case Sprite::FaceDirection::WEST:
                {
                    enemy_lineofsight.faceLeft(); 
                    break;
                }
                case Sprite::FaceDirection::NORTHWEST:
                {
                    enemy_lineofsight.faceUpLeft();  
                    break;
                }
                default:{break;}
            }
            //check if line of sight collision box hit hero
            playerSeen = enemy_lineofsight.getBool_LineOfSightHitHero();
            
            break;
        } 
        case Enemy::EnemyViewOption::FIELD_OF_VIEW:{ break;}
    }
    
    //set enemy state to see player if playerFound is true
    if(playerSeen){Enemy::setEnemyState(Enemy::EnemyState::MOVING_SEE_PLAYER);}
    else{Enemy::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER);}

}

void Enemy::renderEnemyView(SDL_Rect& camera, SDL_Renderer* gRenderer)
{
    switch(enemy_view)
    {
        case Enemy::EnemyViewOption::NONE:{ break;}
        case Enemy::EnemyViewOption::LINE_OF_SIGHT:
        {
            enemy_lineofsight.renderLineSight(camera,gRenderer);
            break;
        } 
        case Enemy::EnemyViewOption::FIELD_OF_VIEW:{ break;}
    }
    
}

CollisionObject* Enemy::GetLineOfSightCollisionObject()
{
	return enemy_lineofsight.GetLineOfSightCollisionObject();
}
