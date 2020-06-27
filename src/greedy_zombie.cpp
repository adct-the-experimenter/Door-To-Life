#include "greedy_zombie.h"

//constructor
GreedyZombie::GreedyZombie(int x,int y,int width,int height) : Enemy(x,y,width,height)
{
    //std::int16_t initialHealth = 50;
    GreedyZombie::setHealth(cockroachHealth);
    GreedyZombie::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER);
    GreedyZombie::pushState(GreedyZombie::GreedyZombieState::DETERMINE_DIRECTION);
    
    //initialize speed
    float speed = 10;
    GreedyZombie::setSpeed(speed);
    
    probabilitiesDirection = {0.2, 0.2,0.2,0.2,0.3};
    
    //setup collision object for cockroach
    GreedyZombie::setupGreedyZombieCollisionObject();
    
    //set view of cockroach
    GreedyZombie::setEnemyView(Enemy::EnemyViewOption::LINE_OF_SIGHT);
    
    std::int16_t lineWidth = width; std::int16_t lineHeight = height * 2.5;
    GreedyZombie::setLineOfSightDimensions(lineWidth,lineHeight);
    GreedyZombie::setLineOfSightToEnemyBox();
    
    GreedyZombie::resetPushBackVariables();
    
    //std::cout << "\n GreedyZombie constructor called! \n";
}

GreedyZombie::~GreedyZombie()
{
    //std::cout << "\n GreedyZombie destructor called! \n";
    probabilitiesDirection = {0.3, 0.4,0.2,0.4};
}

void GreedyZombie::setupGreedyZombieCollisionObject()
{
    CollisionBoxOwnerType type = CollisionBoxOwnerType::GREEDY_ZOMBIE;
    GreedyZombie::setOwnerTypeOfCollisionObject(type);
}

bool loadGreedyZombieMedia(LTexture* cTexture,
                        std::vector <SDL_Rect> &walk_clips,
                        SDL_Renderer* gRenderer )
{
    bool success = true;
    
    std::string cTexFilePath = DATADIR_STR + std::string("/Graphics/greedy-zombie.png");
    //initialize greedy zombie image
    if(!cTexture->loadFromFile(cTexFilePath.c_str(),gRenderer) )
    {
        success = false;
        std::cout << "greedy zombie image loading failed! \n";
    }
    else
    {
        walk_clips.resize(32);
    
        std::int8_t width = 51;
        std::int8_t height = 65;
        
        walk_clips[Sprite::UP_1] = {15,196,width,height};
		walk_clips[Sprite::UP_2] = {80,196,width,height}; 
		walk_clips[Sprite::UP_3] = {143,196,width,height}; 
		walk_clips[Sprite::UP_4] = {207,196,width,height};
		
		walk_clips[Sprite::LEFT_1] = {15,64,width,height};
		walk_clips[Sprite::LEFT_2] = {80,64,width,height};
		walk_clips[Sprite::LEFT_3] = {143,64,width,height};
		walk_clips[Sprite::LEFT_4] = {207,64,width,height};
		
		walk_clips[Sprite::DOWN_1] = {16,1,width,height};
		walk_clips[Sprite::DOWN_2] = {80,1,width,height};
		walk_clips[Sprite::DOWN_3] = {143,1,width,height};
		walk_clips[Sprite::DOWN_4] = {207,1,width,height};
		
		walk_clips[Sprite::RIGHT_1] = {15,128,width,height};
		walk_clips[Sprite::RIGHT_2] = {80,128,width,height};
		walk_clips[Sprite::RIGHT_3] = {143,128,width,height};
		walk_clips[Sprite::RIGHT_4] = {207,128,width,height};
		
		walk_clips[Sprite::DOWN_RIGHT_1] = {12,257,width,height};
		walk_clips[Sprite::DOWN_RIGHT_2] = {76,258,width,height};
		walk_clips[Sprite::DOWN_RIGHT_3] = {140,258,width,height};
		walk_clips[Sprite::DOWN_RIGHT_4] = {204,258,width,height};
		
		walk_clips[Sprite::DOWN_LEFT_1] = {17,321,width,height};
		walk_clips[Sprite::DOWN_LEFT_2] = {81,321,width,height};
		walk_clips[Sprite::DOWN_LEFT_3] = {145,321,width,height};
		walk_clips[Sprite::DOWN_LEFT_4] = {209,321,width,height};
		
		walk_clips[Sprite::UP_LEFT_1] = {17,385,width,height};
		walk_clips[Sprite::UP_LEFT_2] = {81,385,width,height};
		walk_clips[Sprite::UP_LEFT_3] = {145,385,width,height};
		walk_clips[Sprite::UP_LEFT_4] = {209,385,width,height};
		
		walk_clips[Sprite::UP_RIGHT_1] = {12,450,width,height};
		walk_clips[Sprite::UP_RIGHT_2] = {76,450,width,height};
		walk_clips[Sprite::UP_RIGHT_3] = {140,450,width,height};
		walk_clips[Sprite::UP_RIGHT_4] = {204,450,width,height};
    }
    
    return success;
}

void freeGreedyZombieMedia(LTexture* cTexture)
{
    if(cTexture != nullptr)
    {
        delete cTexture;
        cTexture = nullptr;
    }
}

void GreedyZombie::setSpeed(float& speed){Enemy::setSpeed(speed);}

void GreedyZombie::setPosX(float& x){Enemy::setPosX(x);}

void GreedyZombie::setPosY(float& y){Enemy::setPosY(y);}

void GreedyZombie::setVelX(float& dx){Enemy::setVelX(dx);}

void GreedyZombie::setVelY(float& dy){Enemy::setVelY(dy);}

//function to load media for sprite
bool GreedyZombie::loadMedia(LTexture* thisTex, std::string path,SDL_Renderer* gRenderer)
{
    return Enemy::loadMedia(thisTex,path,gRenderer);
}

void GreedyZombie::setPointerToTexture(LTexture* thisTex){Enemy::setPointerToTexture(thisTex);}

void GreedyZombie::setPointersToMedia(LTexture* cTexture,std::vector <SDL_Rect> &clips)
{
    GreedyZombie::setPointerToTexture(cTexture);
    GreedyZombie::setSpriteClips(&clips);
}

LTexture* GreedyZombie::getPointerToTexture(){return Enemy::getPointerToTexture();}

void GreedyZombie::setSpriteClips(std::vector <SDL_Rect> *this_clips){Enemy::setSpriteClips(this_clips);}

std::vector <SDL_Rect> *GreedyZombie::getSpriteClips(){return Enemy::getSpriteClips();}


void GreedyZombie::setPlace(std::int16_t& screenWidth, std::int16_t& screenHeight)
{
    Enemy::setPlace(screenWidth,screenHeight);
}

void GreedyZombie::setCamera( SDL_Rect& camera  ) //set camera relative to dot and intialize screen and level dimensions
{
	Enemy::setCamera(camera);
}

void GreedyZombie::handleEvent(Event& thisEvent){Enemy::handleEvent(thisEvent);}

void GreedyZombie::handleEvent_EnemyAI(RNGType& rngSeed)
{
    //setup rng with set probablities    
    boost::random::discrete_distribution <int> distDirection(probabilitiesDirection);
    boost::random::variate_generator <RNGType&, boost::random::discrete_distribution <> > DirectionDie(rngSeed,distDirection);
    
    std::int8_t thisRandNumber = DirectionDie();
    GreedyZombie::setRandNumber(thisRandNumber);
}

void GreedyZombie::setRandNumber(std::int8_t& thisNum){Enemy::setRandNumber(thisNum);}
std::int8_t GreedyZombie::getRandNumber(){return Enemy::getRandNumber();}

void GreedyZombie::logic(float& timeStep, std::vector<DungeonTile*> &dungeonTiles)
{
    
    //if cockroach is not colliding with wall
    if(GreedyZombie::getEnemyState() != Enemy::EnemyState::COLLIDE_WITH_WALL)
    {
        //move cockroach
        GreedyZombie::moveOnTiles_TileType(timeStep,dungeonTiles);
    }
        
   

    switch(GreedyZombie::getEnemyState())
    {
        case Enemy::EnemyState::MOVING_NO_PLAYER:
        {
            GreedyZombie::runLogicState_MovingNoPlayer(timeStep); break;
        }
        case Enemy::EnemyState::MOVING_SEE_PLAYER:
        {
            GreedyZombie::runLogicState_MovingSeePlayer(timeStep); break;
        }
        case Enemy::EnemyState::HIT_BY_WEAPON:
        {
             GreedyZombie::runLogicState_HitByWeapon(timeStep); break;
        }
        case Enemy::EnemyState::HIT_PLAYER:
        {
            GreedyZombie::runLogicState_HitPlayer(timeStep); break;
        }
        case Enemy::EnemyState::PUSHED_BACK:
        {
            GreedyZombie::runLogicState_PushedBack(timeStep); break;
        }
        case Enemy::EnemyState::COLLIDE_WITH_WALL:
        {
            GreedyZombie::runLogicState_CollideWithWall(timeStep); break;
        }
    }
    
    //increment loop count 
    GreedyZombie::incrementLoopCount();
    //if 5th time interval has passed
    if(GreedyZombie::getLoopCount() >= timeIntervalSwitchDirection )
    {
        //reset loop count
        GreedyZombie::resetLoopCount();
        //Set state to determine new direction
        GreedyZombie::pushState(GreedyZombie::GreedyZombieState::DETERMINE_DIRECTION);
    }
}


void GreedyZombie::runLogicState_MovingNoPlayer(float& timeStep)
{
    //if cockroach is in state of determining direction
    if(GreedyZombie::getCurrentState() == GreedyZombie::GreedyZombieState::DETERMINE_DIRECTION)
    {
        switch(GreedyZombie::getRandNumber())
        {
            case 0:{GreedyZombie::pushState(GreedyZombie::GreedyZombieState::MOVE_UP); break;}
            case 1:{GreedyZombie::pushState(GreedyZombie::GreedyZombieState::MOVE_LEFT); break;}
            case 2:{GreedyZombie::pushState(GreedyZombie::GreedyZombieState::MOVE_RIGHT); break;}
            case 3:{GreedyZombie::pushState(GreedyZombie::GreedyZombieState::MOVE_DOWN); break;}
            case 4:{GreedyZombie::pushState(GreedyZombie::GreedyZombieState::PAUSE); break;}
        }
    }
    
    //go through cockroach movements on stack
    else
    {
        //pop current state if stack is not empty and loop count is reset
        if(!state_stack.empty() && GreedyZombie::getLoopCount() == 0){GreedyZombie::popState();}
    }
    
    //check if player can be seen
    GreedyZombie::checkViewForPlayer();
    
    //make cockroach react to collision
    GreedyZombie::reactToCollision();
}

//variable to use in runLogicState_SeePlayer
//keeps track of which interval player was seen
static std::int8_t movingSeePlayerLoopCountStart;
//bool to check if tempInterval set
static bool movingSeePlayerLoopStartSet = false;

void GreedyZombie::runLogicState_MovingSeePlayer(float& timeStep)
{
    //std::cout << "Player seen! \n";
    
    //get time interval player seen
    if(!movingSeePlayerLoopStartSet)
    {
        movingSeePlayerLoopStartSet = true;
        movingSeePlayerLoopCountStart = GreedyZombie::getLoopCount();
    }
    
    //move in direction player was seen
    switch(GreedyZombie::getFaceDirection())
    {
        case Sprite::FaceDirection::NORTH:
        {
            GreedyZombie::pushState(GreedyZombie::GreedyZombieState::MOVE_UP); 
            break;
        }
        case Sprite::FaceDirection::EAST:
        {
            GreedyZombie::pushState(GreedyZombie::GreedyZombieState::MOVE_RIGHT); 
            break;
        }
        case Sprite::FaceDirection::SOUTH:
        {
            GreedyZombie::pushState(GreedyZombie::GreedyZombieState::MOVE_DOWN); 
            break;
        }
        case Sprite::FaceDirection::WEST:
        {
            GreedyZombie::pushState(GreedyZombie::GreedyZombieState::MOVE_LEFT); 
            break;
        }
        default:{break;}
    }
    
    //if time interval is reset
    if(GreedyZombie::getLoopCount() == 0)
    {
        movingSeePlayerLoopStartSet = false;
        Enemy::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER);
    }
    
    //make cockroach react to collision
    GreedyZombie::reactToCollision();
}


void GreedyZombie::runLogicState_HitByWeapon(float& timeStep)
{
    
}

void GreedyZombie::runLogicState_HitPlayer(float& timeStep)
{
    
}

void GreedyZombie::runLogicState_PushedBack(float& timeStep)
{
    //if count of times enemy has been pushed back is less than number of times 
    //enemy has to be pushed back
    if( GreedyZombie::getCountPushBack() < GreedyZombie::getNumTimesEnemyPushBack() )
    {
        GreedyZombie::pushBackEnemy(timeStep,onePushBack,GreedyZombie::getPushBackDirection()); //get pushed back
        GreedyZombie::incrementCountPushBack(); //increment count
    }
    //else set enemy state back to normal and reset count
    else
    {
        GreedyZombie::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER);
        //reset pushback variables if colliding with wall
        GreedyZombie::resetPushBackVariables();
    }
}

void GreedyZombie::runLogicState_CollideWithWall(float& timeStep)
{ 
    std::int16_t pushBackDist = 2;
    
    GreedyZombie::pushBackEnemy(timeStep,pushBackDist,CollisionDirection::WALL);
    
    //reset pushback variables if colliding with wall
    GreedyZombie::resetPushBackVariables();
    
    //reset back to enemy state moving no player
    GreedyZombie::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER);
}

void GreedyZombie::reactToCollision()
{
    //check if cockroach was hit
   switch(GreedyZombie::getCollisionObjectPtr()->typeOfCollision)
   {
       case CollisionType::HIT_BY_SWORD:
       {
            //Lower enemy health
           GreedyZombie::decrementHealth(cockroach_HitBySwordDamage);
           //set number of times to push back enemy by 1 push back. 5 pixels
           std::int8_t numTimesPushBack = cockroach_PushBackBySword / onePushBack;
           GreedyZombie::setNumTimesEnemyPushBack(numTimesPushBack);
           //set direction of push back for enemy
           GreedyZombie::setPushBackDirection(GreedyZombie::getCollisionObjectPtr()->directionOfCollision); 
           //set state to enemy being pushed back
           GreedyZombie::setEnemyState(Enemy::EnemyState::PUSHED_BACK);
           
		   //reset count for times enemy has been pushed back
		   GreedyZombie::resetCountPushBack();
		   //reset collision type to none
			GreedyZombie::resetCollisionType();
           break;
        }
       case CollisionType::HIT_BY_BULLET:
       {
		    //Lower enemy health
           GreedyZombie::decrementHealth(cockroach_HitByBulletDamage);
           //set number of times to push back enemy by 1 push back. 5 pixels
           std::int8_t numTimesPushBack = cockroach_PushBackByBullet / onePushBack;
           GreedyZombie::setNumTimesEnemyPushBack(numTimesPushBack);
           //set direction of push back for enemy
           GreedyZombie::setPushBackDirection(GreedyZombie::getCollisionObjectPtr()->directionOfCollision); 
           //set state to enemy being pushed back
           GreedyZombie::setEnemyState(Enemy::EnemyState::PUSHED_BACK);
           
		   //reset count for times enemy has been pushed back
		   GreedyZombie::resetCountPushBack();
		   //reset collision type to none
			GreedyZombie::resetCollisionType();
           
		   break;
	   }
       default:{ break;}
   }
   
   
}

void GreedyZombie::move(float& timeStep)
{
    switch(GreedyZombie::getCurrentState())
    {
        case GreedyZombie::GreedyZombieState::MOVE_UP:
        {
            GreedyZombie::moveUp(timeStep); 
            break;
        }
        case GreedyZombie::GreedyZombieState::MOVE_LEFT:
        {
            GreedyZombie::moveLeft(timeStep); 
            break;
        }
        case GreedyZombie::GreedyZombieState::MOVE_RIGHT:
        {
            GreedyZombie::moveRight(timeStep); 
            break;
        }
        case GreedyZombie::GreedyZombieState::MOVE_DOWN:
        {
            GreedyZombie::moveDown(timeStep); 
            break;
        }
        case GreedyZombie::GreedyZombieState::PAUSE:
        {
            GreedyZombie::pause(timeStep); 
            break;
        }
    }
}


bool touchesDungeonWallVector( SDL_Rect& box, std::vector<DungeonTile*> &dungeonTiles );

bool GreedyZombie::moveOnTiles(float& timeStep, std::vector<DungeonTile*> &dungeonTiles)
{
    GreedyZombie::move(timeStep);
    
    //if dot touches a wall tile
    if(touchesDungeonWallVector( GreedyZombie::getCollisionBox(), dungeonTiles ) )
    {
        //set enemy state to collide with wall
        GreedyZombie::setEnemyState(Enemy::EnemyState::COLLIDE_WITH_WALL);

		return true;
    }
    else{GreedyZombie::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER);}
    
    GreedyZombie::setMoveClip();
    GreedyZombie::setFrame();

	return false;
}

DungeonTile::TileType GreedyZombie::moveOnTiles_TileType(float& timeStep, std::vector<DungeonTile*> &dungeonTiles)
{
    GreedyZombie::move(timeStep);
    
    DungeonTile::TileType tileType = touchesDungeonTile(GreedyZombie::getCollisionBox(),
                                                        dungeonTiles);
    //if dot touches a wall tile
    if( tileType == DungeonTile::TileType::TOP_LEFT || tileType == DungeonTile::TileType::LEFT 
        || tileType == DungeonTile::TileType::BOTTOM_LEFT || tileType == DungeonTile::TileType::TOP || 
        tileType == DungeonTile::TileType::CENTER || tileType == DungeonTile::TileType::BOTTOM ||
        tileType == DungeonTile::TileType::TOP_RIGHT || tileType == DungeonTile::TileType::RIGHT || 
        tileType == DungeonTile::TileType::BOTTOM_RIGHT ||
        
        //door
        tileType == DungeonTile::TileType::DOOR ||
        // center hole
        tileType == DungeonTile::TileType::CENTER)
    {
        //set enemy state to collide with wall
        GreedyZombie::setEnemyState(Enemy::EnemyState::COLLIDE_WITH_WALL);
    }
   
    GreedyZombie::setMoveClip();
    GreedyZombie::setFrame();

    return tileType;
}

void GreedyZombie::moveBack(float& timeStep){Enemy::moveBack(timeStep);}


//Frame animation 
void GreedyZombie::setDirection(){Enemy::setDirection();}
void GreedyZombie::setMoveClip(){Enemy::setMoveClip();}
//function to determine which frame to use
void GreedyZombie::setFrame()
{
	int fCount = GreedyZombie::getFrameCount();
    
    std::int8_t offsetForFrame = 0;
    
    //if frame count is more than 2, reset
    //divide frame count by 3 frames of animation to slow down animation
    // How integers work: 0/4 == 0 1/4 == 0 2/4 == 0 3/4 = 0 4/4 = 0
    //after 4th frame, reset frame count
    if(fCount/4 > 3){GreedyZombie::resetFrameCount();}
    
    if(GreedyZombie::getSpriteState() == Sprite::State::STAND){offsetForFrame = 2;}
    else if(GreedyZombie::getSpriteState() == Sprite::State::WALK)
    {
        //stand
        if(fCount/4 == 0){offsetForFrame = 0;}
        //step with left
        else if(fCount/4 == 1){offsetForFrame = 1;}
        //stand
        else if(fCount/4 == 2){offsetForFrame = 2;}
        //step with right
        else if(fCount/4 == 3){offsetForFrame = 3;}
    }
    
    GreedyZombie::setFrameOffset(offsetForFrame);
}

void GreedyZombie::incrementFrameCount(){Enemy::incrementFrameCount();}
std::int8_t GreedyZombie::getFrameCount(){return Enemy::getFrameCount();}
void GreedyZombie::resetFrameCount(){Enemy::resetFrameCount();}

void GreedyZombie::setFrameOffset(std::int8_t& thisOffset){Enemy::setFrameOffset(thisOffset);}
std::int8_t GreedyZombie::getFrameOffset(){return Enemy::getFrameOffset();}

void GreedyZombie::setNumberOfAnimationFrames(std::int8_t& numFrames){Enemy::setNumberOfAnimationFrames(numFrames);}
std::int8_t GreedyZombie::getNumberOfFramesOfAnimation(){return Enemy::getNumberOfFramesOfAnimation();}

void GreedyZombie::setClipToShow(SDL_Rect* clip){ Enemy::setClipToShow(clip);}
SDL_Rect* GreedyZombie::getClipToShow(){return Enemy::getClipToShow();}
	
void GreedyZombie::faceNorth(){Enemy::faceNorth();}

void GreedyZombie::faceSouth(){Enemy::faceSouth();}

void GreedyZombie::faceWest(){Enemy::faceWest();}

void GreedyZombie::faceEast(){Enemy::faceEast();}

void GreedyZombie::setFaceDirection(Sprite::FaceDirection dir){Enemy::setFaceDirection(dir);}
Sprite::FaceDirection GreedyZombie::getFaceDirection(){return Enemy::getFaceDirection();}

void GreedyZombie::setSpriteState(Sprite::State state){Enemy::setSpriteState(state);}
Sprite::State GreedyZombie::getSpriteState(){return Enemy::getSpriteState();}

void GreedyZombie::render(SDL_Rect& camera, SDL_Renderer* gRenderer, SDL_Rect* clip)
{
    //Enemy::render(camera,gRenderer,clip);
    
    if(GreedyZombie::getPointerToTexture() != nullptr)
    {
        std::int16_t x = GreedyZombie::getCollisionBox().x - camera.x;
        std::int16_t y = GreedyZombie::getCollisionBox().y - camera.y;
        
        SDL_Rect* clip = GreedyZombie::getClipToShow();
        if(clip == nullptr){clip = &(*GreedyZombie::getSpriteClips())[UP_1];}
        GreedyZombie::getPointerToTexture()->render( x, y, gRenderer,clip);
    }
   
	//render collision box of enemy
   //GreedyZombie::renderEnemyCollisionBox(camera,gRenderer);
   //Enemy::renderEnemyView(camera,gRenderer);
}

void GreedyZombie::renderEnemyCollisionBox(SDL_Rect& camera, SDL_Renderer* gRenderer)
{
	 SDL_SetRenderDrawColor(gRenderer,
                           200,
                           0,
                           0,
                           50);
    
    SDL_Rect pBox = {  GreedyZombie::getCollisionBox().x - camera.x ,
                         GreedyZombie::getCollisionBox().y - camera.y ,
                        GreedyZombie::getCollisionBox().w,
                        GreedyZombie::getCollisionBox().h };
    SDL_RenderDrawRect(gRenderer,&pBox);
}

float GreedyZombie::getPosX(){return Enemy::getPosX();}

float GreedyZombie::getPosY(){return Enemy::getPosY();}

int GreedyZombie::getHeight(){return Enemy::getHeight();}

int GreedyZombie::getWidth(){return Enemy::getWidth();}

float GreedyZombie::getVelX(){return Enemy::getVelX();}

float GreedyZombie::getVelY(){return Enemy::getVelY();}

float GreedyZombie::getSpeed(){return Enemy::getSpeed();}

void GreedyZombie::placeChar(int x, int y){Enemy::placeChar(x,y);}

void GreedyZombie::setCollisionBox(SDL_Rect& box){Enemy::setCollisionBox(box);}

SDL_Rect& GreedyZombie::getCollisionBox(){return Enemy::getCollisionBox();}

SDL_Rect& GreedyZombie::getSpaceBox(){return Enemy::getSpaceBox();}

void GreedyZombie::setOwnerTypeOfCollisionObject(CollisionBoxOwnerType& oType)
{
    Enemy::setOwnerTypeOfCollisionObject(oType);
}

CollisionType GreedyZombie::getCollisionType(){return Enemy::getCollisionType();}
void GreedyZombie::resetCollisionType(){Enemy::resetCollisionType();}
CollisionObject* GreedyZombie::getCollisionObjectPtr(){return Enemy::getCollisionObjectPtr();}

void GreedyZombie::pushBackEnemy(float& timeStep,std::int16_t& pushBackDist,CollisionDirection dir)
{
    Enemy::pushBackEnemy(timeStep,pushBackDist,dir);
}

void GreedyZombie::setNumTimesEnemyPushBack(std::int8_t& num){Enemy::setNumTimesEnemyPushBack(num);}
std::int8_t GreedyZombie::getNumTimesEnemyPushBack(){return Enemy::getNumTimesEnemyPushBack();}
std::int8_t GreedyZombie::getCountPushBack(){return Enemy::getCountPushBack();}
void GreedyZombie::incrementCountPushBack(){Enemy::incrementCountPushBack();}
void GreedyZombie::resetCountPushBack(){Enemy::resetCountPushBack();}
void GreedyZombie::setPushBackDirection(CollisionDirection dir){Enemy::setPushBackDirection(dir);}
CollisionDirection GreedyZombie::getPushBackDirection(){return Enemy::getPushBackDirection();}
void GreedyZombie::resetPushBackDirection(){Enemy::resetPushBackDirection();}
void GreedyZombie::resetPushBackVariables(){Enemy::resetPushBackVariables();}

//Health

void GreedyZombie::setHealth(std::int16_t& thisHP){Enemy::setHealth(thisHP);}
std::int16_t GreedyZombie::getHealth(){return Enemy::getHealth();}
std::int16_t& GreedyZombie::getHealthAddress(){return Enemy::getHealthAddress();}
void GreedyZombie::incrementHealth(std::int16_t& amount){Enemy::incrementHealth(amount);}
void GreedyZombie::decrementHealth(std::int16_t& amount){Enemy::decrementHealth(amount);}

//State
void GreedyZombie::setEnemyState(Enemy::EnemyState state){Enemy::setEnemyState(state);}
Enemy::EnemyState GreedyZombie::getEnemyState(){return Enemy::getEnemyState();}

void GreedyZombie::pushState(GreedyZombie::GreedyZombieState state)
{
    state_stack.push(state);
}

void GreedyZombie::popState()
{
    state_stack.pop();
}
GreedyZombie::GreedyZombieState GreedyZombie::getCurrentState()
{
    return state_stack.top();
}

//Movement

//functions for movement
void GreedyZombie::moveUp(float& timeStep){Enemy::moveUp(timeStep); GreedyZombie::faceNorth();}

void GreedyZombie::moveDown(float& timeStep){Enemy::moveDown(timeStep); GreedyZombie::faceSouth();}

void GreedyZombie::moveLeft(float& timeStep){Enemy::moveLeft(timeStep); GreedyZombie::faceWest();}

void GreedyZombie::moveRight(float& timeStep){Enemy::moveRight(timeStep); GreedyZombie::faceEast();}

void GreedyZombie::pause(float& timeStep){}

void GreedyZombie::incrementLoopCount(){Enemy::incrementLoopCount();}
std::int8_t GreedyZombie::getLoopCount(){return Enemy::getLoopCount();}
void GreedyZombie::resetLoopCount(){Enemy::resetLoopCount();}

void GreedyZombie::setEnemyView(Enemy::EnemyViewOption option){Enemy::setEnemyView(option);}

void GreedyZombie::setLineOfSightDimensions(std::int16_t& w, std::int16_t& h){Enemy::setLineOfSightDimensions(w,h);}
void GreedyZombie::setLineOfSightToEnemyBox(){Enemy::setLineOfSightToEnemyBox();}
void GreedyZombie::checkViewForPlayer(){Enemy::checkViewForPlayer();}

void GreedyZombie::sound(AudioRenderer* gAudioRenderer)
{
	
}
