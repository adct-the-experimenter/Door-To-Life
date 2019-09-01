#ifndef ENEMY_H
#define ENEMY_H

#include "sprite.h"

#include "globalvariables.h"

#include "lineofsight.h" //for line of sight member
#include "damage_values.h"

#include <stack>

typedef boost::mt19937_64 RNGType;

class Enemy : public Sprite
{
public:

    //constructor to set up resources
    Enemy( int x, int y,int width,int height);

    //destructor to free resources
    virtual ~Enemy();
                                    
    //functions to manipulate sprite state variable
    virtual void setSpriteState(Sprite::State state);
    virtual Sprite::State getSpriteState();
    
    //set speed
    virtual void setSpeed(float& speed);

    //set current position of dot
    virtual void setPosX(float& x);
    virtual void setPosY(float& y);

    //set x and y velocity of dot
    virtual void setVelX(float& dx);
    virtual void setVelY(float& dy);
    
    //function to load media for sprite
    virtual bool loadMedia(LTexture* thisTex, std::string path,SDL_Renderer* gRenderer);
    virtual void setPointerToTexture(LTexture* thisTex);
    virtual LTexture* getPointerToTexture();
    
    //functions to initialize and return sprite clips
    virtual void setSpriteClips(std::vector <SDL_Rect> *this_clips);
    virtual std::vector <SDL_Rect> *getSpriteClips();

    //Takes key presses and adjusts sprite's velocity
    virtual void handleEvent(Event& thisEvent);
    
    //Takes random seed and determines actions
    virtual void handleEvent_EnemyAI(RNGType& rngSeed) = 0;

    //initialize screen dimensions and level dimensions that sprite will move in
    virtual void setPlace(std::int16_t& screenWidth, std::int16_t& screenHeight);
    //Centers the camera over the sprite and intialize screen dimensions and level dimensions
    virtual void setCamera( SDL_Rect& camera);

    //logic module for enemy
    virtual void logic(float& timeStep, std::vector<DungeonTile*> &dungeonTiles) = 0;
    
    

 /** Move sprite**/
    virtual void move(float& timeStep);

    virtual bool moveOnTiles(float& timeStep, std::vector<DungeonTile*> &dungeonTiles);
    
    //moves dot based on time since last render and returns tile type of tile dot collides with
    virtual DungeonTile::TileType moveOnTiles_TileType(float& timeStep, std::vector<DungeonTile*> &dungeonTiles);

    
    virtual void moveBack(float& timeStep);
    
    virtual void moveUp(float& timeStep);
    virtual void moveLeft(float& timeStep);
    virtual void moveRight(float& timeStep);
    virtual void moveDown(float& timeStep);
    virtual void pause(float& timeStep);
    
     //Frame animation 
    virtual void setDirection();
    virtual void setMoveClip();
    //function to determine which frame to use
    virtual void setFrame();
    
    //Frame Animation
    
    //functions to determine frame count
    virtual void incrementFrameCount();
    virtual std::int8_t getFrameCount();
    virtual void resetFrameCount();
    
    //functions to determine frame offset
    virtual void setFrameOffset(std::int8_t& thisOffset);
    virtual std::int8_t getFrameOffset();
    
    //functions to set and get number of frames of animation
    virtual void setNumberOfAnimationFrames(std::int8_t& numFrames);
    virtual std::int8_t getNumberOfFramesOfAnimation();
    
    //functions to set and get clip
    virtual void setClipToShow(SDL_Rect* clip);
	virtual SDL_Rect* getClipToShow();

    //have sprite face certain directions
    virtual void faceSouth();
    virtual void faceNorth();
    virtual void faceWest();
    virtual void faceEast();
    
     //set which direction sprite is facing
    virtual void setFaceDirection(Sprite::FaceDirection dir);
    //return which direction sprite is facing
    virtual Sprite::FaceDirection getFaceDirection();

    //Shows the sprite on screen
    virtual void render(SDL_Rect& camera, SDL_Renderer* lRenderer, SDL_Rect* clip = NULL);

    //place sprite to a specific place. helpful between state changes
    virtual void placeChar(int x, int y);

    //Get sprite's's position and dimensions and velocity
    virtual float getPosX(); virtual float getPosY(); 
    virtual int getHeight(); virtual int getWidth();

    virtual float getVelX(); virtual float getVelY();
    virtual float getSpeed();
    
    virtual void setCollisionBox(SDL_Rect& box);

    //return sprite's collision box
    virtual SDL_Rect& getCollisionBox();

    //return Sprite's spacing box
    virtual SDL_Rect& getSpaceBox();
    
//Collision object Functions
    
    // set owner type of collision object
    virtual void setOwnerTypeOfCollisionObject(CollisionBoxOwnerType& oType);
    //get type of collision that happened
    virtual CollisionType getCollisionType();
    //function to reset collision type to none to avoid getting stuck at a collision type
    virtual void resetCollisionType();
    //get pointer to collision object
    virtual CollisionObject* getCollisionObjectPtr();

// Push Back
    //function to push back enemy a certain distance
    virtual void pushBackEnemy(float& timeStep,std::int16_t& pushBackDist,CollisionDirection dir);

    //function to set number of times to push back enemy
    virtual void setNumTimesEnemyPushBack(std::int8_t& num);
    //function to return number of times to push back enemy
    virtual std::int8_t getNumTimesEnemyPushBack();
    //functions to determine count for times enemy pushed back
    virtual std::int8_t getCountPushBack();
    virtual void incrementCountPushBack();
    virtual void resetCountPushBack();
    virtual void resetPushBackVariables();
	
    
    virtual void setPushBackDirection(CollisionDirection dir);
    virtual CollisionDirection getPushBackDirection();
    virtual void resetPushBackDirection();
    
    //function to do logic for reacting to certain collision types
    virtual void reactToCollision() = 0;
    
//Health
    //function to set health
    virtual void setHealth(std::int16_t& thisHP);
    //function to increment health
    virtual void incrementHealth(std::int16_t& amount);
    //function to decrement health
    virtual void decrementHealth(std::int16_t& amount);
    //function to return health 
    virtual std::int16_t getHealth();
    virtual std::int16_t& getHealthAddress();
    
//State
    enum class EnemyState : std::int8_t{ MOVING_NO_PLAYER = 0, MOVING_SEE_PLAYER,
                                         HIT_BY_WEAPON, HIT_PLAYER,
                                         PUSHED_BACK,
                                         COLLIDE_WITH_WALL};

    virtual void setEnemyState(Enemy::EnemyState state);
    virtual Enemy::EnemyState getEnemyState();
    
    virtual void setRandNumber(std::int8_t& thisNum);
    virtual std::int8_t getRandNumber();
    
    //functions to run logic for states
    virtual void runLogicState_MovingNoPlayer(float& timeStep) = 0;
    virtual void runLogicState_MovingSeePlayer(float& timeStep) = 0;
    virtual void runLogicState_HitByWeapon(float& timeStep) = 0;
    virtual void runLogicState_HitPlayer(float& timeStep) = 0;
    virtual void runLogicState_PushedBack(float& timeStep) = 0;
    virtual void runLogicState_CollideWithWall(float& timeStep) = 0;
    
    virtual void incrementLoopCount();
    virtual std::int8_t getLoopCount();
    virtual void resetLoopCount();
    
//Enemy View Options

    //option for view enemy has to see player
    enum class EnemyViewOption : std::int8_t {NONE = 0, LINE_OF_SIGHT, FIELD_OF_VIEW};
    //function to set enemy view
    virtual void setEnemyView(Enemy::EnemyViewOption option);
    
    //function to set dimensions for line of sight
    virtual void setLineOfSightDimensions(std::int16_t& w, std::int16_t& h);
    
    //function to pas enemy collision box to line of sight
    virtual void setLineOfSightToEnemyBox();
    
    //function to check view for player
    //depending on what was set. Line of Sight or field of view or none
    //and set enemy state to see player if true
    virtual void checkViewForPlayer();
    
    virtual void renderEnemyView(SDL_Rect& camera, SDL_Renderer* gRenderer);
    
    virtual CollisionObject* GetLineOfSightCollisionObject();
    
private:

//members not inherited from sprite class
    std::int16_t health;
    Enemy::EnemyState enemy_state;
    
    std::int8_t randNumber;
    
    //number of times loop has been repeated
    std::int8_t loopCount;
    
    Enemy::EnemyViewOption enemy_view;
    
    //member to signal if player has been spotted
    LineOfSight enemy_lineofsight;
   //Push back
    // number of times to push back enemy by 10 pixels to match enemyPushBack
    std::int8_t numTimes_pushBackEnemy;
    //count for number of times enemy pushed back
    std::int8_t countPushBackEnemy;
    //direction of push back
    CollisionDirection pushBackDirection;
};

#endif
