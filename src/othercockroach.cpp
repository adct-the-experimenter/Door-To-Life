#include "othercockroach.h"

//connstructor
OtherCockroach::OtherCockroach(int x,int y,int width,int height) : Enemy(x,y,width,height)
{
    //std::int16_t initialHealth = 50;
    OtherCockroach::setHealth(cockroachHealth);
    OtherCockroach::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER);
    OtherCockroach::pushState(OtherCockroach::CockroachState::DETERMINE_DIRECTION);
    
    //initialize speed
    float speed = 10;
    OtherCockroach::setSpeed(speed);
    
    probabilitiesDirection = {0.2, 0.2,0.2,0.2,0.3};
    
    //setup collision object for cockroach
    OtherCockroach::setupCockroachCollisionObject();
    
    //set view of cockroach
    OtherCockroach::setEnemyView(Enemy::EnemyViewOption::LINE_OF_SIGHT);
    
    std::int16_t lineWidth = width; std::int16_t lineHeight = height * 2.5;
    OtherCockroach::setLineOfSightDimensions(lineWidth,lineHeight);
    OtherCockroach::setLineOfSightToEnemyBox();
    
    OtherCockroach::resetPushBackVariables();
    
    m_cockroachHeight = 10;
    
    //std::cout << "\n OtherCockroach constructor called! \n";
}

OtherCockroach::~OtherCockroach()
{
    //std::cout << "\n OtherCockroach destructor called! \n";
    probabilitiesDirection = {0.3, 0.4,0.2,0.4};
}

void OtherCockroach::setupCockroachCollisionObject()
{
    CollisionBoxOwnerType type = CollisionBoxOwnerType::COCKROACH;
    OtherCockroach::setOwnerTypeOfCollisionObject(type);
}

bool loadCockRoachVisualMedia(LTexture* cTexture,
                        std::vector <SDL_Rect> &walk_clips,
                        SDL_Renderer* gRenderer )
{
    bool success = true;
    
    std::string cTexFilePath = DATADIR_STR + std::string("/Graphics/cockroach.png");
    //initialize cockroach image
    if(!cTexture->loadFromFile(cTexFilePath.c_str(),gRenderer) )
    {
        success = false;
        std::cout << "other cockroach image loading failed! \n";
    }
    else
    {
        walk_clips.resize(32);
    
        std::int8_t width = 51;
        std::int8_t height = 65;
        
        walk_clips[Sprite::UP_1] = {6,192,51,65};
        walk_clips[Sprite::UP_2] = {70,192,51,65}; 
        walk_clips[Sprite::UP_3] = {136,192,51,65}; 
        walk_clips[Sprite::UP_4] = {199,192,51,65};
        
        walk_clips[Sprite::UP_LEFT_1] = {0,82,64,54};
        walk_clips[Sprite::UP_LEFT_2] = {63,82,64,54};
        walk_clips[Sprite::UP_LEFT_3] = {126,82,64,54};
        walk_clips[Sprite::UP_LEFT_4] = {190,82,64,54};
        
        walk_clips[Sprite::LEFT_1] = {0,82,64,54};
        walk_clips[Sprite::LEFT_2] = {63,82,64,54};
        walk_clips[Sprite::LEFT_3] = {126,82,64,54};
        walk_clips[Sprite::LEFT_4] = {190,82,64,54};
        
        walk_clips[Sprite::DOWN_LEFT_1] = {0,82,64,54};
        walk_clips[Sprite::DOWN_LEFT_2] = {63,82,64,54};
        walk_clips[Sprite::DOWN_LEFT_3] = {126,82,64,54};
        walk_clips[Sprite::DOWN_LEFT_4] = {190,82,64,54};
        
        walk_clips[Sprite::DOWN_1] = {5,3,51,65};
        walk_clips[Sprite::DOWN_2] = {68,3,51,65};
        walk_clips[Sprite::DOWN_3] = {134,3,51,65};
        walk_clips[Sprite::DOWN_4] = {198,3,51,65};
        
        walk_clips[Sprite::RIGHT_1] = {0,138,64,54};
        walk_clips[Sprite::RIGHT_2] = {65,138,64,54};
        walk_clips[Sprite::RIGHT_3] = {127,138,64,54};
        walk_clips[Sprite::RIGHT_4] = {191,138,64,54};
        
        walk_clips[Sprite::DOWN_RIGHT_1] = {0,138,64,54};
        walk_clips[Sprite::DOWN_RIGHT_2] = {65,138,64,54};
        walk_clips[Sprite::DOWN_RIGHT_3] = {127,138,64,54};
        walk_clips[Sprite::DOWN_RIGHT_4] = {191,138,64,54};
        
        walk_clips[Sprite::UP_RIGHT_1] = {0,138,64,54};
        walk_clips[Sprite::UP_RIGHT_2] = {65,138,64,54};
        walk_clips[Sprite::UP_RIGHT_3] = {127,138,64,54};
        walk_clips[Sprite::UP_RIGHT_4] = {191,138,64,54};
    }
    
    return success;
}

void freeCockRoachVisualMedia(LTexture* cTexture)
{
    if(cTexture != nullptr)
    {
        //delete cTexture;
        cTexture = nullptr;
    }
}

bool loadCockRoachAudioMedia(ALuint* cockroachScreamBuffer)
{
	std::string path = "/Sound/Cockroach_Scream.ogg";
	if(!LoadBuffer(cockroachScreamBuffer,path))
	{
		return false;
	}
	
	return true;
}

void freeCockRoachAudioMedia(ALuint* cockroachScreamBuffer)
{
	alDeleteBuffers(1, cockroachScreamBuffer); 
}



void OtherCockroach::setSpeed(float& speed){Enemy::setSpeed(speed);}

void OtherCockroach::setPosX(float& x){Enemy::setPosX(x);}

void OtherCockroach::setPosY(float& y){Enemy::setPosY(y);}

void OtherCockroach::setVelX(float& dx){Enemy::setVelX(dx);}

void OtherCockroach::setVelY(float& dy){Enemy::setVelY(dy);}

//function to load media for sprite
bool OtherCockroach::loadMedia(LTexture* thisTex, std::string path,SDL_Renderer* gRenderer)
{
    return Enemy::loadMedia(thisTex,path,gRenderer);
}

void OtherCockroach::setPointerToTexture(LTexture* thisTex){Enemy::setPointerToTexture(thisTex);}

void OtherCockroach::setPointersToMedia(LTexture* cTexture,std::vector <SDL_Rect> &clips)
{
    OtherCockroach::setPointerToTexture(cTexture);
    OtherCockroach::setSpriteClips(&clips);
}

LTexture* OtherCockroach::getPointerToTexture(){return Enemy::getPointerToTexture();}

void OtherCockroach::setSpriteClips(std::vector <SDL_Rect> *this_clips){Enemy::setSpriteClips(this_clips);}

std::vector <SDL_Rect> *OtherCockroach::getSpriteClips(){return Enemy::getSpriteClips();}


void OtherCockroach::setPlace(std::int16_t& screenWidth, std::int16_t& screenHeight)
{
    Enemy::setPlace(screenWidth,screenHeight);
}

void OtherCockroach::setCamera( SDL_Rect& camera  ) //set camera relative to dot and intialize screen and level dimensions
{
	Enemy::setCamera(camera);
}

void OtherCockroach::handleEvent(Event& thisEvent){Enemy::handleEvent(thisEvent);}

void OtherCockroach::handleEvent_EnemyAI(RNGType& rngSeed)
{
    //setup rng with set probablities    
    boost::random::discrete_distribution <int> distDirection(probabilitiesDirection);
    boost::random::variate_generator <RNGType&, boost::random::discrete_distribution <> > DirectionDie(rngSeed,distDirection);
    
    std::int8_t thisRandNumber = DirectionDie();
    OtherCockroach::setRandNumber(thisRandNumber);
}

void OtherCockroach::setRandNumber(std::int8_t& thisNum){Enemy::setRandNumber(thisNum);}
std::int8_t OtherCockroach::getRandNumber(){return Enemy::getRandNumber();}

void OtherCockroach::logic(float& timeStep, std::vector<DungeonTile*> &dungeonTiles)
{
    
    //if cockroach is not colliding with wall
    if(OtherCockroach::getEnemyState() != Enemy::EnemyState::COLLIDE_WITH_WALL)
    {
        //move cockroach
        OtherCockroach::moveOnTiles_TileType(timeStep,dungeonTiles);
    }
        
   

    switch(OtherCockroach::getEnemyState())
    {
        case Enemy::EnemyState::MOVING_NO_PLAYER:
        {
            OtherCockroach::runLogicState_MovingNoPlayer(timeStep); break;
        }
        case Enemy::EnemyState::MOVING_SEE_PLAYER:
        {
            OtherCockroach::runLogicState_MovingSeePlayer(timeStep); break;
        }
        case Enemy::EnemyState::HIT_BY_WEAPON:
        {
             OtherCockroach::runLogicState_HitByWeapon(timeStep); break;
        }
        case Enemy::EnemyState::HIT_PLAYER:
        {
            OtherCockroach::runLogicState_HitPlayer(timeStep); break;
        }
        case Enemy::EnemyState::PUSHED_BACK:
        {
            OtherCockroach::runLogicState_PushedBack(timeStep); break;
        }
        case Enemy::EnemyState::COLLIDE_WITH_WALL:
        {
            OtherCockroach::runLogicState_CollideWithWall(timeStep); break;
        }
    }
    
    //increment loop count 
    OtherCockroach::incrementLoopCount();
    //if 5th time interval has passed
    if(OtherCockroach::getLoopCount() >= timeIntervalSwitchDirection )
    {
        //reset loop count
        OtherCockroach::resetLoopCount();
        //Set state to determine new direction
        OtherCockroach::pushState(OtherCockroach::CockroachState::DETERMINE_DIRECTION);
    }
}


void OtherCockroach::runLogicState_MovingNoPlayer(float& timeStep)
{
    //if cockroach is in state of determining direction
    if(OtherCockroach::getCurrentState() == OtherCockroach::CockroachState::DETERMINE_DIRECTION)
    {
        switch(OtherCockroach::getRandNumber())
        {
            case 0:{OtherCockroach::pushState(OtherCockroach::CockroachState::MOVE_UP); break;}
            case 1:{OtherCockroach::pushState(OtherCockroach::CockroachState::MOVE_LEFT); break;}
            case 2:{OtherCockroach::pushState(OtherCockroach::CockroachState::MOVE_RIGHT); break;}
            case 3:{OtherCockroach::pushState(OtherCockroach::CockroachState::MOVE_DOWN); break;}
            case 4:{OtherCockroach::pushState(OtherCockroach::CockroachState::PAUSE); break;}
        }
    }
    
    //go through cockroach movements on stack
    else
    {
        //pop current state if stack is not empty and loop count is reset
        if(!state_stack.empty() && OtherCockroach::getLoopCount() == 0){OtherCockroach::popState();}
    }
    
    //check if player can be seen
    OtherCockroach::checkViewForPlayer();
    
    //make cockroach react to collision
    OtherCockroach::reactToCollision();
}

//variable to use in runLogicState_SeePlayer
//keeps track of which interval player was seen
static std::int8_t movingSeePlayerLoopCountStart;
//bool to check if tempInterval set
static bool movingSeePlayerLoopStartSet = false;

void OtherCockroach::runLogicState_MovingSeePlayer(float& timeStep)
{
    //std::cout << "Player seen! \n";
    
    //get time interval player seen
    if(!movingSeePlayerLoopStartSet)
    {
        movingSeePlayerLoopStartSet = true;
        movingSeePlayerLoopCountStart = OtherCockroach::getLoopCount();
    }
    
    //move in direction player was seen
    switch(OtherCockroach::getFaceDirection())
    {
        case Sprite::FaceDirection::NORTH:
        {
            OtherCockroach::pushState(OtherCockroach::CockroachState::MOVE_UP); 
            break;
        }
        case Sprite::FaceDirection::EAST:
        {
            OtherCockroach::pushState(OtherCockroach::CockroachState::MOVE_RIGHT); 
            break;
        }
        case Sprite::FaceDirection::SOUTH:
        {
            OtherCockroach::pushState(OtherCockroach::CockroachState::MOVE_DOWN); 
            break;
        }
        case Sprite::FaceDirection::WEST:
        {
            OtherCockroach::pushState(OtherCockroach::CockroachState::MOVE_LEFT); 
            break;
        }
        default:{break;}
    }
    
    //if time interval is reset
    if(OtherCockroach::getLoopCount() == 0)
    {
        movingSeePlayerLoopStartSet = false;
        Enemy::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER);
    }
    
    //make cockroach react to collision
    OtherCockroach::reactToCollision();
}


void OtherCockroach::runLogicState_HitByWeapon(float& timeStep)
{
    
}

void OtherCockroach::runLogicState_HitPlayer(float& timeStep)
{
    
}

void OtherCockroach::runLogicState_PushedBack(float& timeStep)
{
    //if count of times enemy has been pushed back is less than number of times 
    //enemy has to be pushed back
    if( OtherCockroach::getCountPushBack() < OtherCockroach::getNumTimesEnemyPushBack() )
    {
        OtherCockroach::pushBackEnemy(timeStep,onePushBack,OtherCockroach::getPushBackDirection()); //get pushed back
        OtherCockroach::incrementCountPushBack(); //increment count
    }
    //else set enemy state back to normal and reset count
    else
    {
        OtherCockroach::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER);
        //reset pushback variables if colliding with wall
        OtherCockroach::resetPushBackVariables();
    }
}

void OtherCockroach::runLogicState_CollideWithWall(float& timeStep)
{ 
    std::int16_t pushBackDist = 2;
    
    OtherCockroach::pushBackEnemy(timeStep,pushBackDist,CollisionDirection::WALL);
    
    //reset pushback variables if colliding with wall
    OtherCockroach::resetPushBackVariables();
    
    //reset back to enemy state moving no player
    OtherCockroach::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER);
}

void OtherCockroach::reactToCollision()
{
    //check if cockroach was hit
   switch(OtherCockroach::getCollisionObjectPtr()->typeOfCollision)
   {
       case CollisionType::HIT_BY_SWORD:
       {
            //Lower enemy health
           OtherCockroach::decrementHealth(cockroach_HitBySwordDamage);
           //set number of times to push back enemy by 1 push back. 5 pixels
           std::int8_t numTimesPushBack = cockroach_PushBackBySword / onePushBack;
           OtherCockroach::setNumTimesEnemyPushBack(numTimesPushBack);
           //set direction of push back for enemy
           OtherCockroach::setPushBackDirection(OtherCockroach::getCollisionObjectPtr()->directionOfCollision); 
           //set state to enemy being pushed back
           OtherCockroach::setEnemyState(Enemy::EnemyState::PUSHED_BACK);
           
		   //reset count for times enemy has been pushed back
		   OtherCockroach::resetCountPushBack();
		   //reset collision type to none
			OtherCockroach::resetCollisionType();
           break;
        }
       case CollisionType::HIT_BY_BULLET:
       {
		    //Lower enemy health
           OtherCockroach::decrementHealth(cockroach_HitByBulletDamage);
           //set number of times to push back enemy by 1 push back. 5 pixels
           std::int8_t numTimesPushBack = cockroach_PushBackByBullet / onePushBack;
           OtherCockroach::setNumTimesEnemyPushBack(numTimesPushBack);
           //set direction of push back for enemy
           OtherCockroach::setPushBackDirection(OtherCockroach::getCollisionObjectPtr()->directionOfCollision); 
           //set state to enemy being pushed back
           OtherCockroach::setEnemyState(Enemy::EnemyState::PUSHED_BACK);
           
		   //reset count for times enemy has been pushed back
		   OtherCockroach::resetCountPushBack();
		   //reset collision type to none
			OtherCockroach::resetCollisionType();
           
		   break;
	   }
       default:{ break;}
   }
   
   
}

void OtherCockroach::move(float& timeStep)
{
    switch(OtherCockroach::getCurrentState())
    {
        case OtherCockroach::CockroachState::MOVE_UP:
        {
            OtherCockroach::moveUp(timeStep); 
            break;
        }
        case OtherCockroach::CockroachState::MOVE_LEFT:
        {
            OtherCockroach::moveLeft(timeStep); 
            break;
        }
        case OtherCockroach::CockroachState::MOVE_RIGHT:
        {
            OtherCockroach::moveRight(timeStep); 
            break;
        }
        case OtherCockroach::CockroachState::MOVE_DOWN:
        {
            OtherCockroach::moveDown(timeStep); 
            break;
        }
        case OtherCockroach::CockroachState::PAUSE:
        {
            OtherCockroach::pause(timeStep); 
            break;
        }
    }
}


bool touchesDungeonWallVector( SDL_Rect& box, std::vector<DungeonTile*> &dungeonTiles );

bool OtherCockroach::moveOnTiles(float& timeStep, std::vector<DungeonTile*> &dungeonTiles)
{
    OtherCockroach::move(timeStep);
    
    //if dot touches a wall tile
    if(touchesDungeonWallVector( OtherCockroach::getCollisionBox(), dungeonTiles ) )
    {
        //set enemy state to collide with wall
        OtherCockroach::setEnemyState(Enemy::EnemyState::COLLIDE_WITH_WALL);

		return true;
    }
    else{OtherCockroach::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER);}
    
    OtherCockroach::setMoveClip();
    OtherCockroach::setFrame();

	return false;
}

DungeonTile::TileType OtherCockroach::moveOnTiles_TileType(float& timeStep, std::vector<DungeonTile*> &dungeonTiles)
{
    OtherCockroach::move(timeStep);
    
    DungeonTile::TileType tileType = touchesDungeonTile(OtherCockroach::getCollisionBox(),
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
        OtherCockroach::setEnemyState(Enemy::EnemyState::COLLIDE_WITH_WALL);
    }
   
    OtherCockroach::setMoveClip();
    OtherCockroach::setFrame();

    return tileType;
}

void OtherCockroach::moveBack(float& timeStep){Enemy::moveBack(timeStep);}


//Frame animation 
void OtherCockroach::setDirection(){Enemy::setDirection();}
void OtherCockroach::setMoveClip(){Enemy::setMoveClip();}
//function to determine which frame to use
void OtherCockroach::setFrame()
{
	int fCount = OtherCockroach::getFrameCount();
    
    std::int8_t offsetForFrame = 0;
    
    //if frame count is more than 2, reset
    //divide frame count by 3 frames of animation to slow down animation
    // How integers work: 0/4 == 0 1/4 == 0 2/4 == 0 3/4 = 0 4/4 = 0
    //after 4th frame, reset frame count
    if(fCount/4 > 3){OtherCockroach::resetFrameCount();}
    
    if(OtherCockroach::getSpriteState() == Sprite::State::STAND){offsetForFrame = 2;}
    else if(OtherCockroach::getSpriteState() == Sprite::State::WALK)
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
    
    OtherCockroach::setFrameOffset(offsetForFrame);
}

void OtherCockroach::incrementFrameCount(){Enemy::incrementFrameCount();}
std::int8_t OtherCockroach::getFrameCount(){return Enemy::getFrameCount();}
void OtherCockroach::resetFrameCount(){Enemy::resetFrameCount();}

void OtherCockroach::setFrameOffset(std::int8_t& thisOffset){Enemy::setFrameOffset(thisOffset);}
std::int8_t OtherCockroach::getFrameOffset(){return Enemy::getFrameOffset();}

void OtherCockroach::setNumberOfAnimationFrames(std::int8_t& numFrames){Enemy::setNumberOfAnimationFrames(numFrames);}
std::int8_t OtherCockroach::getNumberOfFramesOfAnimation(){return Enemy::getNumberOfFramesOfAnimation();}

void OtherCockroach::setClipToShow(SDL_Rect* clip){ Enemy::setClipToShow(clip);}
SDL_Rect* OtherCockroach::getClipToShow(){return Enemy::getClipToShow();}
	
void OtherCockroach::faceNorth(){Enemy::faceNorth();}

void OtherCockroach::faceSouth(){Enemy::faceSouth();}

void OtherCockroach::faceWest(){Enemy::faceWest();}

void OtherCockroach::faceEast(){Enemy::faceEast();}

void OtherCockroach::setFaceDirection(Sprite::FaceDirection dir){Enemy::setFaceDirection(dir);}
Sprite::FaceDirection OtherCockroach::getFaceDirection(){return Enemy::getFaceDirection();}

void OtherCockroach::setSpriteState(Sprite::State state){Enemy::setSpriteState(state);}
Sprite::State OtherCockroach::getSpriteState(){return Enemy::getSpriteState();}

void OtherCockroach::render(SDL_Rect& camera, SDL_Renderer* gRenderer, SDL_Rect* clip)
{
    //Enemy::render(camera,gRenderer,clip);
    
    if(OtherCockroach::getPointerToTexture() != nullptr)
    {
        std::int16_t x = OtherCockroach::getCollisionBox().x - camera.x;
        std::int16_t y = OtherCockroach::getCollisionBox().y - camera.y;
        
        SDL_Rect* clip = OtherCockroach::getClipToShow();
        if(clip == nullptr){clip = &(*OtherCockroach::getSpriteClips())[UP_1];}
        OtherCockroach::getPointerToTexture()->render( x, y, gRenderer,clip);
    }
   
	//render collision box of enemy
   //OtherCockroach::renderEnemyCollisionBox(camera,gRenderer);
   //Enemy::renderEnemyView(camera,gRenderer);
}

void OtherCockroach::renderEnemyCollisionBox(SDL_Rect& camera, SDL_Renderer* gRenderer)
{
	 SDL_SetRenderDrawColor(gRenderer,
                           200,
                           0,
                           0,
                           50);
    
    SDL_Rect pBox = {  OtherCockroach::getCollisionBox().x - camera.x ,
                         OtherCockroach::getCollisionBox().y - camera.y ,
                        OtherCockroach::getCollisionBox().w,
                        OtherCockroach::getCollisionBox().h };
    SDL_RenderDrawRect(gRenderer,&pBox);
}

float OtherCockroach::getPosX(){return Enemy::getPosX();}

float OtherCockroach::getPosY(){return Enemy::getPosY();}

int OtherCockroach::getHeight(){return Enemy::getHeight();}

int OtherCockroach::getWidth(){return Enemy::getWidth();}

float OtherCockroach::getVelX(){return Enemy::getVelX();}

float OtherCockroach::getVelY(){return Enemy::getVelY();}

float OtherCockroach::getSpeed(){return Enemy::getSpeed();}

void OtherCockroach::placeChar(int x, int y){Enemy::placeChar(x,y);}

void OtherCockroach::setCollisionBox(SDL_Rect& box){Enemy::setCollisionBox(box);}

SDL_Rect& OtherCockroach::getCollisionBox(){return Enemy::getCollisionBox();}

SDL_Rect& OtherCockroach::getSpaceBox(){return Enemy::getSpaceBox();}

void OtherCockroach::setOwnerTypeOfCollisionObject(CollisionBoxOwnerType& oType)
{
    Enemy::setOwnerTypeOfCollisionObject(oType);
}

CollisionType OtherCockroach::getCollisionType(){return Enemy::getCollisionType();}
void OtherCockroach::resetCollisionType(){Enemy::resetCollisionType();}
CollisionObject* OtherCockroach::getCollisionObjectPtr(){return Enemy::getCollisionObjectPtr();}

void OtherCockroach::pushBackEnemy(float& timeStep,std::int16_t& pushBackDist,CollisionDirection dir)
{
    Enemy::pushBackEnemy(timeStep,pushBackDist,dir);
}

void OtherCockroach::setNumTimesEnemyPushBack(std::int8_t& num){Enemy::setNumTimesEnemyPushBack(num);}
std::int8_t OtherCockroach::getNumTimesEnemyPushBack(){return Enemy::getNumTimesEnemyPushBack();}
std::int8_t OtherCockroach::getCountPushBack(){return Enemy::getCountPushBack();}
void OtherCockroach::incrementCountPushBack(){Enemy::incrementCountPushBack();}
void OtherCockroach::resetCountPushBack(){Enemy::resetCountPushBack();}
void OtherCockroach::setPushBackDirection(CollisionDirection dir){Enemy::setPushBackDirection(dir);}
CollisionDirection OtherCockroach::getPushBackDirection(){return Enemy::getPushBackDirection();}
void OtherCockroach::resetPushBackDirection(){Enemy::resetPushBackDirection();}
void OtherCockroach::resetPushBackVariables(){Enemy::resetPushBackVariables();}

//Health

void OtherCockroach::setHealth(std::int16_t& thisHP){Enemy::setHealth(thisHP);}
std::int16_t OtherCockroach::getHealth(){return Enemy::getHealth();}
std::int16_t& OtherCockroach::getHealthAddress(){return Enemy::getHealthAddress();}
void OtherCockroach::incrementHealth(std::int16_t& amount){Enemy::incrementHealth(amount);}
void OtherCockroach::decrementHealth(std::int16_t& amount){Enemy::decrementHealth(amount);}

//State
void OtherCockroach::setEnemyState(Enemy::EnemyState state){Enemy::setEnemyState(state);}
Enemy::EnemyState OtherCockroach::getEnemyState(){return Enemy::getEnemyState();}

void OtherCockroach::pushState(OtherCockroach::CockroachState state)
{
    state_stack.push(state);
}

void OtherCockroach::popState()
{
    state_stack.pop();
}
OtherCockroach::CockroachState OtherCockroach::getCurrentState()
{
    return state_stack.top();
}

//Movement

//functions for movement
void OtherCockroach::moveUp(float& timeStep){Enemy::moveUp(timeStep); OtherCockroach::faceNorth();}

void OtherCockroach::moveDown(float& timeStep){Enemy::moveDown(timeStep); OtherCockroach::faceSouth();}

void OtherCockroach::moveLeft(float& timeStep){Enemy::moveLeft(timeStep); OtherCockroach::faceWest();}

void OtherCockroach::moveRight(float& timeStep){Enemy::moveRight(timeStep); OtherCockroach::faceEast();}

void OtherCockroach::pause(float& timeStep){}

void OtherCockroach::incrementLoopCount(){Enemy::incrementLoopCount();}
std::int8_t OtherCockroach::getLoopCount(){return Enemy::getLoopCount();}
void OtherCockroach::resetLoopCount(){Enemy::resetLoopCount();}

void OtherCockroach::setEnemyView(Enemy::EnemyViewOption option){Enemy::setEnemyView(option);}

void OtherCockroach::setLineOfSightDimensions(std::int16_t& w, std::int16_t& h){Enemy::setLineOfSightDimensions(w,h);}
void OtherCockroach::setLineOfSightToEnemyBox(){Enemy::setLineOfSightToEnemyBox();}
void OtherCockroach::checkViewForPlayer(){Enemy::checkViewForPlayer();}



void OtherCockroach::sound(AudioRenderer* gAudioRenderer)
{
	extern ALuint cockroach_scream_buffer;
		
	if(OtherCockroach::getEnemyState() == Enemy::EnemyState::PUSHED_BACK)
	{
		//std::cout << "cockroach scream called! \n";
		float x = OtherCockroach::getPosX();
		float y = OtherCockroach::getPosY();
		if(cockroach_scream_buffer != 0){gAudioRenderer->renderAudioRelativeToPlayerHeight(x,y,m_cockroachHeight,&cockroach_scream_buffer);}
	}
}
