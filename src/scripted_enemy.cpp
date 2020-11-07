#include "scripted_enemy.h"

//constructor
ScriptedEnemy::ScriptedEnemy(int x,int y,int width,int height) : Enemy(x,y,width,height)
{
    //std::int16_t initialHealth = 50;
    ScriptedEnemy::setHealth(cockroachHealth);
    ScriptedEnemy::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER);
    ScriptedEnemy::pushState(ScriptedEnemy::ScriptedEnemyState::DETERMINE_DIRECTION);
    
    //initialize speed
    float speed = 10;
    ScriptedEnemy::setSpeed(speed);
    
    probabilitiesDirection = {0.2, 0.2,0.2,0.2,0.3};
    
    //setup collision object for cockroach
    ScriptedEnemy::setupScriptedEnemyCollisionObject();
    
    //set view of cockroach
    ScriptedEnemy::setEnemyView(Enemy::EnemyViewOption::LINE_OF_SIGHT);
    
    std::int16_t lineWidth = width; std::int16_t lineHeight = height * 2.5;
    ScriptedEnemy::setLineOfSightDimensions(lineWidth,lineHeight);
    ScriptedEnemy::setLineOfSightToEnemyBox();
    
    ScriptedEnemy::resetPushBackVariables();
    
    //std::cout << "\n ScriptedEnemy constructor called! \n";
}

ScriptedEnemy::~ScriptedEnemy()
{
    //std::cout << "\n ScriptedEnemy destructor called! \n";
    probabilitiesDirection = {0.3, 0.4,0.2,0.4};
}

void ScriptedEnemy::setupScriptedEnemyCollisionObject()
{
    CollisionBoxOwnerType type = CollisionBoxOwnerType::GREEDY_ZOMBIE;
    ScriptedEnemy::setOwnerTypeOfCollisionObject(type);
}

bool loadScriptedEnemyMedia(LTexture* cTexture,
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

void freeScriptedEnemyMedia(LTexture* cTexture)
{
    if(cTexture != nullptr)
    {
        //delete cTexture;
        cTexture = nullptr;
    }
}

void ScriptedEnemy::setSpeed(float& speed){Enemy::setSpeed(speed);}

void ScriptedEnemy::setPosX(float& x){Enemy::setPosX(x);}

void ScriptedEnemy::setPosY(float& y){Enemy::setPosY(y);}

void ScriptedEnemy::setVelX(float& dx){Enemy::setVelX(dx);}

void ScriptedEnemy::setVelY(float& dy){Enemy::setVelY(dy);}

//function to load media for sprite
bool ScriptedEnemy::loadMedia(LTexture* thisTex, std::string path,SDL_Renderer* gRenderer)
{
    return Enemy::loadMedia(thisTex,path,gRenderer);
}

void ScriptedEnemy::setPointerToTexture(LTexture* thisTex){Enemy::setPointerToTexture(thisTex);}

void ScriptedEnemy::setPointersToMedia(LTexture* cTexture,std::vector <SDL_Rect> &clips)
{
    ScriptedEnemy::setPointerToTexture(cTexture);
    ScriptedEnemy::setSpriteClips(&clips);
}

LTexture* ScriptedEnemy::getPointerToTexture(){return Enemy::getPointerToTexture();}

void ScriptedEnemy::setSpriteClips(std::vector <SDL_Rect> *this_clips){Enemy::setSpriteClips(this_clips);}

std::vector <SDL_Rect> *ScriptedEnemy::getSpriteClips(){return Enemy::getSpriteClips();}


void ScriptedEnemy::setPlace(std::int16_t& screenWidth, std::int16_t& screenHeight)
{
    Enemy::setPlace(screenWidth,screenHeight);
}

void ScriptedEnemy::setCamera( SDL_Rect& camera  ) //set camera relative to dot and intialize screen and level dimensions
{
	Enemy::setCamera(camera);
}

void ScriptedEnemy::handleEvent(Event& thisEvent){Enemy::handleEvent(thisEvent);}

void ScriptedEnemy::handleEvent_EnemyAI(RNGType& rngSeed)
{
    //setup rng with set probablities    
    boost::random::discrete_distribution <int> distDirection(probabilitiesDirection);
    boost::random::variate_generator <RNGType&, boost::random::discrete_distribution <> > DirectionDie(rngSeed,distDirection);
    
    std::int8_t thisRandNumber = DirectionDie();
    ScriptedEnemy::setRandNumber(thisRandNumber);
}

void ScriptedEnemy::setRandNumber(std::int8_t& thisNum){Enemy::setRandNumber(thisNum);}
std::int8_t ScriptedEnemy::getRandNumber(){return Enemy::getRandNumber();}

void ScriptedEnemy::logic(float& timeStep, std::vector<DungeonTile*> &dungeonTiles)
{
    
    //if cockroach is not colliding with wall
    if(ScriptedEnemy::getEnemyState() != Enemy::EnemyState::COLLIDE_WITH_WALL)
    {
        //move enemy
        ScriptedEnemy::moveOnTiles_TileType(timeStep,dungeonTiles);
    }
        
   

    switch(ScriptedEnemy::getEnemyState())
    {
        case Enemy::EnemyState::MOVING_NO_PLAYER:
        {
            ScriptedEnemy::runLogicState_MovingNoPlayer(timeStep); break;
        }
        case Enemy::EnemyState::MOVING_SEE_PLAYER:
        {
            ScriptedEnemy::runLogicState_MovingSeePlayer(timeStep); break;
        }
        case Enemy::EnemyState::HIT_BY_WEAPON:
        {
             ScriptedEnemy::runLogicState_HitByWeapon(timeStep); break;
        }
        case Enemy::EnemyState::HIT_PLAYER:
        {
            ScriptedEnemy::runLogicState_HitPlayer(timeStep); break;
        }
        case Enemy::EnemyState::PUSHED_BACK:
        {
            ScriptedEnemy::runLogicState_PushedBack(timeStep); break;
        }
        case Enemy::EnemyState::COLLIDE_WITH_WALL:
        {
            ScriptedEnemy::runLogicState_CollideWithWall(timeStep); break;
        }
    }
    
    //increment loop count 
    ScriptedEnemy::incrementLoopCount();
    //if 5th time interval has passed
    if(ScriptedEnemy::getLoopCount() >= timeIntervalSwitchDirection )
    {
        //reset loop count
        ScriptedEnemy::resetLoopCount();
        //Set state to determine new direction
        ScriptedEnemy::pushState(ScriptedEnemy::ScriptedEnemyState::DETERMINE_DIRECTION);
    }
}


void ScriptedEnemy::runLogicState_MovingNoPlayer(float& timeStep)
{
    //if cockroach is in state of determining direction
    if(ScriptedEnemy::getCurrentState() == ScriptedEnemy::ScriptedEnemyState::DETERMINE_DIRECTION)
    {
        switch(ScriptedEnemy::getRandNumber())
        {
            case 0:{ScriptedEnemy::pushState(ScriptedEnemy::ScriptedEnemyState::MOVE_UP); break;}
            case 1:{ScriptedEnemy::pushState(ScriptedEnemy::ScriptedEnemyState::MOVE_LEFT); break;}
            case 2:{ScriptedEnemy::pushState(ScriptedEnemy::ScriptedEnemyState::MOVE_RIGHT); break;}
            case 3:{ScriptedEnemy::pushState(ScriptedEnemy::ScriptedEnemyState::MOVE_DOWN); break;}
            case 4:{ScriptedEnemy::pushState(ScriptedEnemy::ScriptedEnemyState::PAUSE); break;}
        }
    }
    
    //go through cockroach movements on stack
    else
    {
        //pop current state if stack is not empty and loop count is reset
        if(!state_stack.empty() && ScriptedEnemy::getLoopCount() == 0){ScriptedEnemy::popState();}
    }
    
    //check if player can be seen
    ScriptedEnemy::checkViewForPlayer();
    
    //make cockroach react to collision
    ScriptedEnemy::reactToCollision();
}

//variable to use in runLogicState_SeePlayer
//keeps track of which interval player was seen
static std::int8_t movingSeePlayerLoopCountStart;
//bool to check if tempInterval set
static bool movingSeePlayerLoopStartSet = false;

void ScriptedEnemy::runLogicState_MovingSeePlayer(float& timeStep)
{
    //std::cout << "Player seen! \n";
    
    //get time interval player seen
    if(!movingSeePlayerLoopStartSet)
    {
        movingSeePlayerLoopStartSet = true;
        movingSeePlayerLoopCountStart = ScriptedEnemy::getLoopCount();
    }
    
    //move in direction player was seen
    switch(ScriptedEnemy::getFaceDirection())
    {
        case Sprite::FaceDirection::NORTH:
        {
            ScriptedEnemy::pushState(ScriptedEnemy::ScriptedEnemyState::MOVE_UP); 
            break;
        }
        case Sprite::FaceDirection::EAST:
        {
            ScriptedEnemy::pushState(ScriptedEnemy::ScriptedEnemyState::MOVE_RIGHT); 
            break;
        }
        case Sprite::FaceDirection::SOUTH:
        {
            ScriptedEnemy::pushState(ScriptedEnemy::ScriptedEnemyState::MOVE_DOWN); 
            break;
        }
        case Sprite::FaceDirection::WEST:
        {
            ScriptedEnemy::pushState(ScriptedEnemy::ScriptedEnemyState::MOVE_LEFT); 
            break;
        }
        default:{break;}
    }
    
    //if time interval is reset
    if(ScriptedEnemy::getLoopCount() == 0)
    {
        movingSeePlayerLoopStartSet = false;
        Enemy::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER);
    }
    
    //make cockroach react to collision
    ScriptedEnemy::reactToCollision();
}


void ScriptedEnemy::runLogicState_PushedBack(float& timeStep)
{
    //if count of times enemy has been pushed back is less than number of times 
    //enemy has to be pushed back
    if( ScriptedEnemy::getCountPushBack() < ScriptedEnemy::getNumTimesEnemyPushBack() )
    {
        ScriptedEnemy::pushBackEnemy(timeStep,onePushBack,ScriptedEnemy::getPushBackDirection()); //get pushed back
        ScriptedEnemy::incrementCountPushBack(); //increment count
    }
    //else set enemy state back to normal and reset count
    else
    {
        ScriptedEnemy::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER);
        //reset pushback variables if colliding with wall
        ScriptedEnemy::resetPushBackVariables();
    }
}

void ScriptedEnemy::runLogicState_CollideWithWall(float& timeStep)
{ 
    std::int16_t pushBackDist = 2;
    
    ScriptedEnemy::pushBackEnemy(timeStep,pushBackDist,CollisionDirection::WALL);
    
    //reset pushback variables if colliding with wall
    ScriptedEnemy::resetPushBackVariables();
    
    //reset back to enemy state moving no player
    ScriptedEnemy::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER);
}

void ScriptedEnemy::reactToCollision()
{
    //check if cockroach was hit
   switch(ScriptedEnemy::getCollisionObjectPtr()->typeOfCollision)
   {
       case CollisionType::HIT_BY_SWORD:
       {
            //Lower enemy health
           ScriptedEnemy::decrementHealth(cockroach_HitBySwordDamage);
           //set number of times to push back enemy by 1 push back. 5 pixels
           std::int8_t numTimesPushBack = cockroach_PushBackBySword / onePushBack;
           ScriptedEnemy::setNumTimesEnemyPushBack(numTimesPushBack);
           //set direction of push back for enemy
           ScriptedEnemy::setPushBackDirection(ScriptedEnemy::getCollisionObjectPtr()->directionOfCollision); 
           //set state to enemy being pushed back
           ScriptedEnemy::setEnemyState(Enemy::EnemyState::PUSHED_BACK);
           
		   //reset count for times enemy has been pushed back
		   ScriptedEnemy::resetCountPushBack();
		   //reset collision type to none
			ScriptedEnemy::resetCollisionType();
           break;
        }
       case CollisionType::HIT_BY_BULLET:
       {
		    //Lower enemy health
           ScriptedEnemy::decrementHealth(cockroach_HitByBulletDamage);
           //set number of times to push back enemy by 1 push back. 5 pixels
           std::int8_t numTimesPushBack = cockroach_PushBackByBullet / onePushBack;
           ScriptedEnemy::setNumTimesEnemyPushBack(numTimesPushBack);
           //set direction of push back for enemy
           ScriptedEnemy::setPushBackDirection(ScriptedEnemy::getCollisionObjectPtr()->directionOfCollision); 
           //set state to enemy being pushed back
           ScriptedEnemy::setEnemyState(Enemy::EnemyState::PUSHED_BACK);
           
		   //reset count for times enemy has been pushed back
		   ScriptedEnemy::resetCountPushBack();
		   //reset collision type to none
			ScriptedEnemy::resetCollisionType();
           
		   break;
	   }
       default:{ break;}
   }
   
   
}

void ScriptedEnemy::move(float& timeStep)
{
    switch(ScriptedEnemy::getCurrentState())
    {
        case ScriptedEnemy::ScriptedEnemyState::MOVE_UP:
        {
            ScriptedEnemy::moveUp(timeStep); 
            break;
        }
        case ScriptedEnemy::ScriptedEnemyState::MOVE_LEFT:
        {
            ScriptedEnemy::moveLeft(timeStep); 
            break;
        }
        case ScriptedEnemy::ScriptedEnemyState::MOVE_RIGHT:
        {
            ScriptedEnemy::moveRight(timeStep); 
            break;
        }
        case ScriptedEnemy::ScriptedEnemyState::MOVE_DOWN:
        {
            ScriptedEnemy::moveDown(timeStep); 
            break;
        }
        case ScriptedEnemy::ScriptedEnemyState::PAUSE:
        {
            ScriptedEnemy::pause(timeStep); 
            break;
        }
    }
}


bool touchesDungeonWallVector( SDL_Rect& box, std::vector<DungeonTile*> &dungeonTiles );

bool ScriptedEnemy::moveOnTiles(float& timeStep, std::vector<DungeonTile*> &dungeonTiles)
{
    ScriptedEnemy::move(timeStep);
    
    //if dot touches a wall tile
    if(touchesDungeonWallVector( ScriptedEnemy::getCollisionBox(), dungeonTiles ) )
    {
        //set enemy state to collide with wall
        ScriptedEnemy::setEnemyState(Enemy::EnemyState::COLLIDE_WITH_WALL);

		return true;
    }
    else{ScriptedEnemy::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER);}
    
    ScriptedEnemy::setMoveClip();
    ScriptedEnemy::setFrame();

	return false;
}

DungeonTile::TileType ScriptedEnemy::moveOnTiles_TileType(float& timeStep, std::vector<DungeonTile*> &dungeonTiles)
{
    ScriptedEnemy::move(timeStep);
    
    DungeonTile::TileType tileType = touchesDungeonTile(ScriptedEnemy::getCollisionBox(),
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
        ScriptedEnemy::setEnemyState(Enemy::EnemyState::COLLIDE_WITH_WALL);
    }
   
    ScriptedEnemy::setMoveClip();
    ScriptedEnemy::setFrame();

    return tileType;
}

void ScriptedEnemy::moveBack(float& timeStep){Enemy::moveBack(timeStep);}


//Frame animation 

//function to determine which frame to use
void ScriptedEnemy::setFrame()
{
	int fCount = ScriptedEnemy::getFrameCount();
    
    std::int8_t offsetForFrame = 0;
    
    //if frame count is more than 2, reset
    //divide frame count by 3 frames of animation to slow down animation
    // How integers work: 0/4 == 0 1/4 == 0 2/4 == 0 3/4 = 0 4/4 = 0
    //after 4th frame, reset frame count
    if(fCount/4 > 3){ScriptedEnemy::resetFrameCount();}
    
    if(ScriptedEnemy::getSpriteState() == Sprite::State::STAND){offsetForFrame = 2;}
    else if(ScriptedEnemy::getSpriteState() == Sprite::State::WALK)
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
    
    ScriptedEnemy::setFrameOffset(offsetForFrame);
}


void ScriptedEnemy::render(SDL_Rect& camera, SDL_Renderer* gRenderer, SDL_Rect* clip)
{
    //Enemy::render(camera,gRenderer,clip);
    
    if(ScriptedEnemy::getPointerToTexture() != nullptr)
    {
        std::int16_t x = ScriptedEnemy::getCollisionBox().x - camera.x;
        std::int16_t y = ScriptedEnemy::getCollisionBox().y - camera.y;
        
        SDL_Rect* clip = ScriptedEnemy::getClipToShow();
        if(clip == nullptr){clip = &(*ScriptedEnemy::getSpriteClips())[UP_1];}
        ScriptedEnemy::getPointerToTexture()->render( x, y, gRenderer,clip);
    }
   
	//render collision box of enemy
   //ScriptedEnemy::renderEnemyCollisionBox(camera,gRenderer);
   //Enemy::renderEnemyView(camera,gRenderer);
}

void ScriptedEnemy::renderEnemyCollisionBox(SDL_Rect& camera, SDL_Renderer* gRenderer)
{
	 SDL_SetRenderDrawColor(gRenderer,
                           200,
                           0,
                           0,
                           50);
    
    SDL_Rect pBox = {  ScriptedEnemy::getCollisionBox().x - camera.x ,
                         ScriptedEnemy::getCollisionBox().y - camera.y ,
                        ScriptedEnemy::getCollisionBox().w,
                        ScriptedEnemy::getCollisionBox().h };
    SDL_RenderDrawRect(gRenderer,&pBox);
}


void ScriptedEnemy::pushState(ScriptedEnemy::ScriptedEnemyState state)
{
    state_stack.push(state);
}

void ScriptedEnemy::popState()
{
    state_stack.pop();
}
ScriptedEnemy::ScriptedEnemyState ScriptedEnemy::getCurrentState()
{
    return state_stack.top();
}

//Movement

void ScriptedEnemy::pause(float& timeStep){}


void ScriptedEnemy::sound(AudioRenderer* gAudioRenderer)
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
