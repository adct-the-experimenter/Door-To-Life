#include "my_enemy.h"

//constructor
MyEnemy::MyEnemy(int x,int y,int width,int height) : Enemy(x,y,width,height)
{
    //std::int16_t initialHealth = 50;
    MyEnemy::setHealth(cockroachHealth);
    MyEnemy::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER);
    MyEnemy::pushState(MyEnemy::MyEnemyState::DETERMINE_DIRECTION);
    
    //initialize speed
    float speed = 10;
    MyEnemy::setSpeed(speed);
    
    probabilitiesDirection = {0.2, 0.2,0.2,0.2,0.3};
    
    //setup collision object for cockroach
    MyEnemy::setupMyEnemyCollisionObject();
    
    //set view of cockroach
    MyEnemy::setEnemyView(Enemy::EnemyViewOption::LINE_OF_SIGHT);
    
    std::int16_t lineWidth = width; std::int16_t lineHeight = height * 2.5;
    MyEnemy::setLineOfSightDimensions(lineWidth,lineHeight);
    MyEnemy::setLineOfSightToEnemyBox();
    
    MyEnemy::resetPushBackVariables();
    
    //std::cout << "\n MyEnemy constructor called! \n";
}

MyEnemy::~MyEnemy()
{
    //std::cout << "\n MyEnemy destructor called! \n";
    probabilitiesDirection = {0.3, 0.4,0.2,0.4};
}

void MyEnemy::setupMyEnemyCollisionObject()
{
    CollisionBoxOwnerType type = CollisionBoxOwnerType::GREEDY_ZOMBIE;
    MyEnemy::setOwnerTypeOfCollisionObject(type);
}

bool loadMyEnemyMedia(LTexture* cTexture,
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

void freeMyEnemyMedia(LTexture* cTexture)
{
    if(cTexture != nullptr)
    {
        //delete cTexture;
        cTexture = nullptr;
    }
}

void MyEnemy::setSpeed(float& speed){Enemy::setSpeed(speed);}

void MyEnemy::setPosX(float& x){Enemy::setPosX(x);}

void MyEnemy::setPosY(float& y){Enemy::setPosY(y);}

void MyEnemy::setVelX(float& dx){Enemy::setVelX(dx);}

void MyEnemy::setVelY(float& dy){Enemy::setVelY(dy);}

//function to load media for sprite
bool MyEnemy::loadMedia(LTexture* thisTex, std::string path,SDL_Renderer* gRenderer)
{
    return Enemy::loadMedia(thisTex,path,gRenderer);
}

void MyEnemy::setPointerToTexture(LTexture* thisTex){Enemy::setPointerToTexture(thisTex);}

void MyEnemy::setPointersToMedia(LTexture* cTexture,std::vector <SDL_Rect> &clips)
{
    MyEnemy::setPointerToTexture(cTexture);
    MyEnemy::setSpriteClips(&clips);
}

LTexture* MyEnemy::getPointerToTexture(){return Enemy::getPointerToTexture();}

void MyEnemy::setSpriteClips(std::vector <SDL_Rect> *this_clips){Enemy::setSpriteClips(this_clips);}

std::vector <SDL_Rect> *MyEnemy::getSpriteClips(){return Enemy::getSpriteClips();}


void MyEnemy::setPlace(std::int16_t& screenWidth, std::int16_t& screenHeight)
{
    Enemy::setPlace(screenWidth,screenHeight);
}

void MyEnemy::setCamera( SDL_Rect& camera  ) //set camera relative to dot and intialize screen and level dimensions
{
	Enemy::setCamera(camera);
}

void MyEnemy::handleEvent(Event& thisEvent){Enemy::handleEvent(thisEvent);}

void MyEnemy::handleEvent_EnemyAI(RNGType& rngSeed)
{
    //setup rng with set probablities    
    boost::random::discrete_distribution <int> distDirection(probabilitiesDirection);
    boost::random::variate_generator <RNGType&, boost::random::discrete_distribution <> > DirectionDie(rngSeed,distDirection);
    
    std::int8_t thisRandNumber = DirectionDie();
    MyEnemy::setRandNumber(thisRandNumber);
}

void MyEnemy::setRandNumber(std::int8_t& thisNum){Enemy::setRandNumber(thisNum);}
std::int8_t MyEnemy::getRandNumber(){return Enemy::getRandNumber();}

void MyEnemy::logic(float& timeStep, std::vector<DungeonTile*> &dungeonTiles)
{
    
    //if cockroach is not colliding with wall
    if(MyEnemy::getEnemyState() != Enemy::EnemyState::COLLIDE_WITH_WALL)
    {
        //move cockroach
        MyEnemy::moveOnTiles_TileType(timeStep,dungeonTiles);
    }
        
   

    switch(MyEnemy::getEnemyState())
    {
        case Enemy::EnemyState::MOVING_NO_PLAYER:
        {
            MyEnemy::runLogicState_MovingNoPlayer(timeStep); break;
        }
        case Enemy::EnemyState::MOVING_SEE_PLAYER:
        {
            MyEnemy::runLogicState_MovingSeePlayer(timeStep); break;
        }
        case Enemy::EnemyState::HIT_BY_WEAPON:
        {
             MyEnemy::runLogicState_HitByWeapon(timeStep); break;
        }
        case Enemy::EnemyState::HIT_PLAYER:
        {
            MyEnemy::runLogicState_HitPlayer(timeStep); break;
        }
        case Enemy::EnemyState::PUSHED_BACK:
        {
            MyEnemy::runLogicState_PushedBack(timeStep); break;
        }
        case Enemy::EnemyState::COLLIDE_WITH_WALL:
        {
            MyEnemy::runLogicState_CollideWithWall(timeStep); break;
        }
    }
    
    //increment loop count 
    MyEnemy::incrementLoopCount();
    //if 5th time interval has passed
    if(MyEnemy::getLoopCount() >= timeIntervalSwitchDirection )
    {
        //reset loop count
        MyEnemy::resetLoopCount();
        //Set state to determine new direction
        MyEnemy::pushState(MyEnemy::MyEnemyState::DETERMINE_DIRECTION);
    }
}


void MyEnemy::runLogicState_MovingNoPlayer(float& timeStep)
{
    //if cockroach is in state of determining direction
    if(MyEnemy::getCurrentState() == MyEnemy::MyEnemyState::DETERMINE_DIRECTION)
    {
        switch(MyEnemy::getRandNumber())
        {
            case 0:{MyEnemy::pushState(MyEnemy::MyEnemyState::MOVE_UP); break;}
            case 1:{MyEnemy::pushState(MyEnemy::MyEnemyState::MOVE_LEFT); break;}
            case 2:{MyEnemy::pushState(MyEnemy::MyEnemyState::MOVE_RIGHT); break;}
            case 3:{MyEnemy::pushState(MyEnemy::MyEnemyState::MOVE_DOWN); break;}
            case 4:{MyEnemy::pushState(MyEnemy::MyEnemyState::PAUSE); break;}
        }
    }
    
    //go through cockroach movements on stack
    else
    {
        //pop current state if stack is not empty and loop count is reset
        if(!state_stack.empty() && MyEnemy::getLoopCount() == 0){MyEnemy::popState();}
    }
    
    //check if player can be seen
    MyEnemy::checkViewForPlayer();
    
    //make cockroach react to collision
    MyEnemy::reactToCollision();
}

//variable to use in runLogicState_SeePlayer
//keeps track of which interval player was seen
static std::int8_t movingSeePlayerLoopCountStart;
//bool to check if tempInterval set
static bool movingSeePlayerLoopStartSet = false;

void MyEnemy::runLogicState_MovingSeePlayer(float& timeStep)
{
    //std::cout << "Player seen! \n";
    
    //get time interval player seen
    if(!movingSeePlayerLoopStartSet)
    {
        movingSeePlayerLoopStartSet = true;
        movingSeePlayerLoopCountStart = MyEnemy::getLoopCount();
    }
    
    //move in direction player was seen
    switch(MyEnemy::getFaceDirection())
    {
        case Sprite::FaceDirection::NORTH:
        {
            MyEnemy::pushState(MyEnemy::MyEnemyState::MOVE_UP); 
            break;
        }
        case Sprite::FaceDirection::EAST:
        {
            MyEnemy::pushState(MyEnemy::MyEnemyState::MOVE_RIGHT); 
            break;
        }
        case Sprite::FaceDirection::SOUTH:
        {
            MyEnemy::pushState(MyEnemy::MyEnemyState::MOVE_DOWN); 
            break;
        }
        case Sprite::FaceDirection::WEST:
        {
            MyEnemy::pushState(MyEnemy::MyEnemyState::MOVE_LEFT); 
            break;
        }
        default:{break;}
    }
    
    //if time interval is reset
    if(MyEnemy::getLoopCount() == 0)
    {
        movingSeePlayerLoopStartSet = false;
        Enemy::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER);
    }
    
    //make cockroach react to collision
    MyEnemy::reactToCollision();
}


void MyEnemy::runLogicState_HitByWeapon(float& timeStep)
{
    
}

void MyEnemy::runLogicState_HitPlayer(float& timeStep)
{
    
}

void MyEnemy::runLogicState_PushedBack(float& timeStep)
{
    //if count of times enemy has been pushed back is less than number of times 
    //enemy has to be pushed back
    if( MyEnemy::getCountPushBack() < MyEnemy::getNumTimesEnemyPushBack() )
    {
        MyEnemy::pushBackEnemy(timeStep,onePushBack,MyEnemy::getPushBackDirection()); //get pushed back
        MyEnemy::incrementCountPushBack(); //increment count
    }
    //else set enemy state back to normal and reset count
    else
    {
        MyEnemy::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER);
        //reset pushback variables if colliding with wall
        MyEnemy::resetPushBackVariables();
    }
}

void MyEnemy::runLogicState_CollideWithWall(float& timeStep)
{ 
    std::int16_t pushBackDist = 2;
    
    MyEnemy::pushBackEnemy(timeStep,pushBackDist,CollisionDirection::WALL);
    
    //reset pushback variables if colliding with wall
    MyEnemy::resetPushBackVariables();
    
    //reset back to enemy state moving no player
    MyEnemy::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER);
}

void MyEnemy::reactToCollision()
{
    //check if cockroach was hit
   switch(MyEnemy::getCollisionObjectPtr()->typeOfCollision)
   {
       case CollisionType::HIT_BY_SWORD:
       {
            //Lower enemy health
           MyEnemy::decrementHealth(cockroach_HitBySwordDamage);
           //set number of times to push back enemy by 1 push back. 5 pixels
           std::int8_t numTimesPushBack = cockroach_PushBackBySword / onePushBack;
           MyEnemy::setNumTimesEnemyPushBack(numTimesPushBack);
           //set direction of push back for enemy
           MyEnemy::setPushBackDirection(MyEnemy::getCollisionObjectPtr()->directionOfCollision); 
           //set state to enemy being pushed back
           MyEnemy::setEnemyState(Enemy::EnemyState::PUSHED_BACK);
           
		   //reset count for times enemy has been pushed back
		   MyEnemy::resetCountPushBack();
		   //reset collision type to none
			MyEnemy::resetCollisionType();
           break;
        }
       case CollisionType::HIT_BY_BULLET:
       {
		    //Lower enemy health
           MyEnemy::decrementHealth(cockroach_HitByBulletDamage);
           //set number of times to push back enemy by 1 push back. 5 pixels
           std::int8_t numTimesPushBack = cockroach_PushBackByBullet / onePushBack;
           MyEnemy::setNumTimesEnemyPushBack(numTimesPushBack);
           //set direction of push back for enemy
           MyEnemy::setPushBackDirection(MyEnemy::getCollisionObjectPtr()->directionOfCollision); 
           //set state to enemy being pushed back
           MyEnemy::setEnemyState(Enemy::EnemyState::PUSHED_BACK);
           
		   //reset count for times enemy has been pushed back
		   MyEnemy::resetCountPushBack();
		   //reset collision type to none
			MyEnemy::resetCollisionType();
           
		   break;
	   }
       default:{ break;}
   }
   
   
}

void MyEnemy::move(float& timeStep)
{
    switch(MyEnemy::getCurrentState())
    {
        case MyEnemy::MyEnemyState::MOVE_UP:
        {
            MyEnemy::moveUp(timeStep); 
            break;
        }
        case MyEnemy::MyEnemyState::MOVE_LEFT:
        {
            MyEnemy::moveLeft(timeStep); 
            break;
        }
        case MyEnemy::MyEnemyState::MOVE_RIGHT:
        {
            MyEnemy::moveRight(timeStep); 
            break;
        }
        case MyEnemy::MyEnemyState::MOVE_DOWN:
        {
            MyEnemy::moveDown(timeStep); 
            break;
        }
        case MyEnemy::MyEnemyState::PAUSE:
        {
            MyEnemy::pause(timeStep); 
            break;
        }
    }
}


bool touchesDungeonWallVector( SDL_Rect& box, std::vector<DungeonTile*> &dungeonTiles );

bool MyEnemy::moveOnTiles(float& timeStep, std::vector<DungeonTile*> &dungeonTiles)
{
    MyEnemy::move(timeStep);
    
    //if dot touches a wall tile
    if(touchesDungeonWallVector( MyEnemy::getCollisionBox(), dungeonTiles ) )
    {
        //set enemy state to collide with wall
        MyEnemy::setEnemyState(Enemy::EnemyState::COLLIDE_WITH_WALL);

		return true;
    }
    else{MyEnemy::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER);}
    
    MyEnemy::setMoveClip();
    MyEnemy::setFrame();

	return false;
}

DungeonTile::TileType MyEnemy::moveOnTiles_TileType(float& timeStep, std::vector<DungeonTile*> &dungeonTiles)
{
    MyEnemy::move(timeStep);
    
    DungeonTile::TileType tileType = touchesDungeonTile(MyEnemy::getCollisionBox(),
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
        MyEnemy::setEnemyState(Enemy::EnemyState::COLLIDE_WITH_WALL);
    }
   
    MyEnemy::setMoveClip();
    MyEnemy::setFrame();

    return tileType;
}

void MyEnemy::moveBack(float& timeStep){Enemy::moveBack(timeStep);}


//Frame animation 
void MyEnemy::setDirection(){Enemy::setDirection();}
void MyEnemy::setMoveClip(){Enemy::setMoveClip();}
//function to determine which frame to use
void MyEnemy::setFrame()
{
	int fCount = MyEnemy::getFrameCount();
    
    std::int8_t offsetForFrame = 0;
    
    //if frame count is more than 2, reset
    //divide frame count by 3 frames of animation to slow down animation
    // How integers work: 0/4 == 0 1/4 == 0 2/4 == 0 3/4 = 0 4/4 = 0
    //after 4th frame, reset frame count
    if(fCount/4 > 3){MyEnemy::resetFrameCount();}
    
    if(MyEnemy::getSpriteState() == Sprite::State::STAND){offsetForFrame = 2;}
    else if(MyEnemy::getSpriteState() == Sprite::State::WALK)
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
    
    MyEnemy::setFrameOffset(offsetForFrame);
}

void MyEnemy::incrementFrameCount(){Enemy::incrementFrameCount();}
std::int8_t MyEnemy::getFrameCount(){return Enemy::getFrameCount();}
void MyEnemy::resetFrameCount(){Enemy::resetFrameCount();}

void MyEnemy::setFrameOffset(std::int8_t& thisOffset){Enemy::setFrameOffset(thisOffset);}
std::int8_t MyEnemy::getFrameOffset(){return Enemy::getFrameOffset();}

void MyEnemy::setNumberOfAnimationFrames(std::int8_t& numFrames){Enemy::setNumberOfAnimationFrames(numFrames);}
std::int8_t MyEnemy::getNumberOfFramesOfAnimation(){return Enemy::getNumberOfFramesOfAnimation();}

void MyEnemy::setClipToShow(SDL_Rect* clip){ Enemy::setClipToShow(clip);}
SDL_Rect* MyEnemy::getClipToShow(){return Enemy::getClipToShow();}
	
void MyEnemy::faceNorth(){Enemy::faceNorth();}

void MyEnemy::faceSouth(){Enemy::faceSouth();}

void MyEnemy::faceWest(){Enemy::faceWest();}

void MyEnemy::faceEast(){Enemy::faceEast();}

void MyEnemy::setFaceDirection(Sprite::FaceDirection dir){Enemy::setFaceDirection(dir);}
Sprite::FaceDirection MyEnemy::getFaceDirection(){return Enemy::getFaceDirection();}

void MyEnemy::setSpriteState(Sprite::State state){Enemy::setSpriteState(state);}
Sprite::State MyEnemy::getSpriteState(){return Enemy::getSpriteState();}

void MyEnemy::render(SDL_Rect& camera, SDL_Renderer* gRenderer, SDL_Rect* clip)
{
    //Enemy::render(camera,gRenderer,clip);
    
    if(MyEnemy::getPointerToTexture() != nullptr)
    {
        std::int16_t x = MyEnemy::getCollisionBox().x - camera.x;
        std::int16_t y = MyEnemy::getCollisionBox().y - camera.y;
        
        SDL_Rect* clip = MyEnemy::getClipToShow();
        if(clip == nullptr){clip = &(*MyEnemy::getSpriteClips())[UP_1];}
        MyEnemy::getPointerToTexture()->render( x, y, gRenderer,clip);
    }
   
	//render collision box of enemy
   //MyEnemy::renderEnemyCollisionBox(camera,gRenderer);
   //Enemy::renderEnemyView(camera,gRenderer);
}

void MyEnemy::renderEnemyCollisionBox(SDL_Rect& camera, SDL_Renderer* gRenderer)
{
	 SDL_SetRenderDrawColor(gRenderer,
                           200,
                           0,
                           0,
                           50);
    
    SDL_Rect pBox = {  MyEnemy::getCollisionBox().x - camera.x ,
                         MyEnemy::getCollisionBox().y - camera.y ,
                        MyEnemy::getCollisionBox().w,
                        MyEnemy::getCollisionBox().h };
    SDL_RenderDrawRect(gRenderer,&pBox);
}

float MyEnemy::getPosX(){return Enemy::getPosX();}

float MyEnemy::getPosY(){return Enemy::getPosY();}

int MyEnemy::getHeight(){return Enemy::getHeight();}

int MyEnemy::getWidth(){return Enemy::getWidth();}

float MyEnemy::getVelX(){return Enemy::getVelX();}

float MyEnemy::getVelY(){return Enemy::getVelY();}

float MyEnemy::getSpeed(){return Enemy::getSpeed();}

void MyEnemy::placeChar(int x, int y){Enemy::placeChar(x,y);}

void MyEnemy::setCollisionBox(SDL_Rect& box){Enemy::setCollisionBox(box);}

SDL_Rect& MyEnemy::getCollisionBox(){return Enemy::getCollisionBox();}

SDL_Rect& MyEnemy::getSpaceBox(){return Enemy::getSpaceBox();}

void MyEnemy::setOwnerTypeOfCollisionObject(CollisionBoxOwnerType& oType)
{
    Enemy::setOwnerTypeOfCollisionObject(oType);
}

CollisionType MyEnemy::getCollisionType(){return Enemy::getCollisionType();}
void MyEnemy::resetCollisionType(){Enemy::resetCollisionType();}
CollisionObject* MyEnemy::getCollisionObjectPtr(){return Enemy::getCollisionObjectPtr();}

void MyEnemy::pushBackEnemy(float& timeStep,std::int16_t& pushBackDist,CollisionDirection dir)
{
    Enemy::pushBackEnemy(timeStep,pushBackDist,dir);
}

void MyEnemy::setNumTimesEnemyPushBack(std::int8_t& num){Enemy::setNumTimesEnemyPushBack(num);}
std::int8_t MyEnemy::getNumTimesEnemyPushBack(){return Enemy::getNumTimesEnemyPushBack();}
std::int8_t MyEnemy::getCountPushBack(){return Enemy::getCountPushBack();}
void MyEnemy::incrementCountPushBack(){Enemy::incrementCountPushBack();}
void MyEnemy::resetCountPushBack(){Enemy::resetCountPushBack();}
void MyEnemy::setPushBackDirection(CollisionDirection dir){Enemy::setPushBackDirection(dir);}
CollisionDirection MyEnemy::getPushBackDirection(){return Enemy::getPushBackDirection();}
void MyEnemy::resetPushBackDirection(){Enemy::resetPushBackDirection();}
void MyEnemy::resetPushBackVariables(){Enemy::resetPushBackVariables();}

//Health

void MyEnemy::setHealth(std::int16_t& thisHP){Enemy::setHealth(thisHP);}
std::int16_t MyEnemy::getHealth(){return Enemy::getHealth();}
std::int16_t& MyEnemy::getHealthAddress(){return Enemy::getHealthAddress();}
void MyEnemy::incrementHealth(std::int16_t& amount){Enemy::incrementHealth(amount);}
void MyEnemy::decrementHealth(std::int16_t& amount){Enemy::decrementHealth(amount);}

//State
void MyEnemy::setEnemyState(Enemy::EnemyState state){Enemy::setEnemyState(state);}
Enemy::EnemyState MyEnemy::getEnemyState(){return Enemy::getEnemyState();}

void MyEnemy::pushState(MyEnemy::MyEnemyState state)
{
    state_stack.push(state);
}

void MyEnemy::popState()
{
    state_stack.pop();
}
MyEnemy::MyEnemyState MyEnemy::getCurrentState()
{
    return state_stack.top();
}

//Movement

//functions for movement
void MyEnemy::moveUp(float& timeStep){Enemy::moveUp(timeStep); MyEnemy::faceNorth();}

void MyEnemy::moveDown(float& timeStep){Enemy::moveDown(timeStep); MyEnemy::faceSouth();}

void MyEnemy::moveLeft(float& timeStep){Enemy::moveLeft(timeStep); MyEnemy::faceWest();}

void MyEnemy::moveRight(float& timeStep){Enemy::moveRight(timeStep); MyEnemy::faceEast();}

void MyEnemy::pause(float& timeStep){}

void MyEnemy::incrementLoopCount(){Enemy::incrementLoopCount();}
std::int8_t MyEnemy::getLoopCount(){return Enemy::getLoopCount();}
void MyEnemy::resetLoopCount(){Enemy::resetLoopCount();}

void MyEnemy::setEnemyView(Enemy::EnemyViewOption option){Enemy::setEnemyView(option);}

void MyEnemy::setLineOfSightDimensions(std::int16_t& w, std::int16_t& h){Enemy::setLineOfSightDimensions(w,h);}
void MyEnemy::setLineOfSightToEnemyBox(){Enemy::setLineOfSightToEnemyBox();}
void MyEnemy::checkViewForPlayer(){Enemy::checkViewForPlayer();}

void MyEnemy::sound(AudioRenderer* gAudioRenderer)
{
	extern ALuint scream_buffer;
		
	if(OtherCockroach::getEnemyState() == Enemy::EnemyState::PUSHED_BACK)
	{
		std::cout << "cockroach scream called! \n";
		float x = OtherCockroach::getPosX();
		float y = OtherCockroach::getPosY();
		if(scream_buffer != 0){gAudioRenderer->renderAudio(x,y,&scream_buffer);}
	}
}
